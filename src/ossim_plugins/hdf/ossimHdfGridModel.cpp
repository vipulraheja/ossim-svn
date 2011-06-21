//*****************************************************************************
// FILE: ossimHdfGridModel.cc
//
// License:  See LICENSE.txt file in the top level directory.
//
// AUTHOR: Mingjie Su
//
// DESCRIPTION:
//   Contains implementation of class ossimHdfGridModel. This is an
//   implementation of an interpolation sensor model. 
//
//   IMPORTANT: The lat/lon grid is for ground points on the ellipsoid.
//   The dLat/dHgt and dLon/dHgt partials therefore are used against
//   elevations relative to the ellipsoid.
//
//*****************************************************************************
//  $Id: ossimHdfGridModel.cpp 2645 2011-05-26 15:21:34Z oscar.kramer $

#include "ossimHdfGridModel.h"

RTTI_DEF1(ossimHdfGridModel, "ossimHdfGridModel", ossimCoarseGridModel);

//*****************************************************************************
//  CONSTRUCTOR: ossimHdfGridModel(filename)
//  
//  Constructs model from geometry file
//  
//*****************************************************************************
ossimHdfGridModel::ossimHdfGridModel(const ossimFilename& file,
                                     const ossimDrect& imageRect,
                                     ossimString latGridIndexOrName,
                                     ossimString lonGridIndexOrName,
                                     const ossimIpt& gridSpacing)
   :  ossimCoarseGridModel(),
   m_isHdf4(true)
{
   theLatGrid.setDomainType(ossimDblGrid::SAWTOOTH_90);
   theLonGrid.setDomainType(ossimDblGrid::WRAP_180);

   if (latGridIndexOrName.contains("/Latitude") == false && 
       lonGridIndexOrName.contains("/Longitude") == false)//hdf4
   {
      ossim_int32 latGridIndex = ossimString::toInt(latGridIndexOrName);
      ossim_int32 lonGridIndex = ossimString::toInt(lonGridIndexOrName);
      int32 sd_id = SDstart(file.c_str(), DFACC_READ);
      if (sd_id > 0)
      {
         int32 sds_id = SDselect(sd_id, latGridIndex);
         if (sds_id > 0)
         {
            setGridNodes(theLatGrid, sds_id, gridSpacing);
         }
         SDendaccess (sds_id); 

         sds_id = SDselect(sd_id, lonGridIndex);
         if (sds_id > 0)
         {
            setGridNodes(theLonGrid, sds_id, gridSpacing);
         }
         SDendaccess (sds_id); 
      }
      SDend(sd_id);
   }
   else //hdf5
   {
      m_isHdf4 = false;
      ossim_int32 file_id = H5Fopen(file.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
      ossim_int32 dataset_id = H5Dopen(file_id, latGridIndexOrName);
      if (dataset_id >= 0)
      {
         setGridNodes(theLatGrid, dataset_id, gridSpacing);
      }
      H5Dclose(dataset_id);

      dataset_id = H5Dopen(file_id, lonGridIndexOrName);
      if (dataset_id > 0)
      {
         setGridNodes(theLatGrid, dataset_id, gridSpacing);
      }
      H5Dclose(dataset_id);

      H5Fclose(file_id);
   }
   

   // Filter this HDF data as it is often very noisy:
   double filter_kernel[81];
   double weight = 1.0/81.0;
   for (int i=0; i<81; i++)
      filter_kernel[i] = weight;
   theLatGrid.filter(9,9, filter_kernel);
   theLonGrid.filter(9,9, filter_kernel);

   theLatGrid.enableExtrapolation();
   theLonGrid.enableExtrapolation();
   theHeightEnabledFlag = false;
   initializeModelParams(imageRect);
   
   //debugDump(); //###
}

ossimHdfGridModel::~ossimHdfGridModel()
{
}

void ossimHdfGridModel::setGridNodes(ossimDblGrid& grid, int32 sds_id, const ossimIpt& spacing)
{
   int x=0, y=0;
   ossim_uint32 index = 0;
   if (m_isHdf4)
   {
      int32 dim_sizes[MAX_VAR_DIMS];
      int32 rank, data_type, n_attrs;
      char  name[MAX_NC_NAME];

      int32 status = SDgetinfo(sds_id, name, &rank, dim_sizes, &data_type, &n_attrs);
      if (status == -1)
         return;

      int32 origin[2] = {0, 0}; 
      int32 num_rows = dim_sizes[0]; 
      int32 num_cols = dim_sizes[1]; 

      ossimDpt grid_origin(0,0); // The grid as used in base class, has UV-space always at 0,0 origin
      ossimIpt grid_size (num_cols, num_rows);
      ossimDpt dspacing (spacing);
      grid.initialize(grid_size, grid_origin, dspacing);

      float32* values = new float32 [num_rows * num_cols]; 
      intn statusN = SDreaddata(sds_id, origin, NULL, dim_sizes, (VOIDP)values);
      if (statusN > -1)
      {
         for (y = 0; y < num_rows; y++)
         {
            for (x = 0; x < num_cols; x++)
            {
               grid.setNode(x, y, values[index++]);
            }
         }
      }
      delete values;
   }
   else
   {
      hsize_t dims_out[2]; //dataset dimensions
      hid_t datatype = H5Dget_type(sds_id);
      hid_t dataspace = H5Dget_space(sds_id);    //dataspace handle
      int rank = H5Sget_simple_extent_ndims(dataspace);
      if (rank == 2)
      {
         herr_t status_n  = H5Sget_simple_extent_dims(dataspace, dims_out, NULL);

         ossim_int32 latGridRows = dims_out[0];
         ossim_int32 lonGridCols = dims_out[1];

         ossim_int32 cols = spacing.x;
         ossim_int32 rows = spacing.y;

         ossim_int32 spacingX = 0;
         ossim_int32 spacingY = 0;

         if (rows % latGridRows == 0 && cols % lonGridCols == 0)
         {
            spacingY = rows/latGridRows; //line increment step
            spacingX = cols/lonGridCols; //pixel increment step
         }
         
         ossimIpt gridSpacing(spacingX, spacingY);

         ossimDpt grid_origin(0,0); // The grid as used in base class, has UV-space always at 0,0 origin
         ossimIpt grid_size (cols, rows);
         ossimDpt dspacing (gridSpacing);
         grid.initialize(grid_size, grid_origin, dspacing);

         if( H5Tequal(H5T_NATIVE_FLOAT,  datatype))
         {
            ossim_float32* data_out = new ossim_float32[dims_out[0] * dims_out[1]];
            herr_t status = H5Dread(sds_id, datatype, dataspace, dataspace,
               H5P_DEFAULT, data_out);

            index = 0;
            for (y = 0; y < rows; y++)
            {
               for (x = 0; x < cols; x++)
               {
                  index = x + y * cols;
                  grid.setNode(x, y, data_out[index]);
               }
            }
            delete[] data_out;
         }
         else if( H5Tequal(H5T_NATIVE_DOUBLE,  datatype))
         {
            ossim_float64* data_out = new ossim_float64[dims_out[0] * dims_out[1]];
            herr_t status = H5Dread(sds_id, datatype, dataspace, dataspace,
               H5P_DEFAULT, data_out);

            index = 0;
            for (y = 0; y < rows; y++)
            {
               for (x = 0; x < cols; x++)
               {
                  index = x + y * cols;
                  grid.setNode(x, y, data_out[index]);
               }
            }
            delete[] data_out;
         }
      }
      H5Tclose(datatype);
      H5Sclose(dataspace);
   }
}

      
void ossimHdfGridModel::debugDump()
{
   ossimIpt size = theImageSize;
   ossimIpt step (theImageSize/200);
   int margin = 0;
   double lat, lon;
   ossimDpt pt (0,0);
   ofstream fslat ("lat_grid.dat");
   ofstream fslon ("lon_grid.dat");
   fslat<< setprecision(10) <<endl;
   fslon<< setprecision(10) <<endl;
   for (pt.v = -margin*step.v; pt.v < theImageSize.v+margin*step.v; pt.v += step.y)
   {
      for (pt.u = -margin*step.u; pt.u < theImageSize.u+margin*step.u ; pt.u += step.u)
      {
         lat = theLatGrid(pt.u, pt.v);
         lon = theLonGrid(pt.u, pt.v);
         fslat << pt.u << " " << pt.v << " " << lat << endl;
         fslon << pt.u << " " << pt.v << " " << lon << endl;
      }
   }
   fslat.close();
   fslon.close();
}
