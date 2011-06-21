//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Utility class for staging data into the omar database.
//
//----------------------------------------------------------------------------
// $Id$

#include <omarStagerUtil.h>
#include <omarRasterDataSetObject.h>
#include <omarRasterEntryObject.h>
#include <omarArrayOfFileObject.h>
#include <omarGeometryObject.h>
#include <omarGeospatialType.h>
#include <omarProductType.h>
#include <omarUnitType.h>
#include <omarSecurityClassificationType.h>
#include <omarSensorType.h>
#include <omarArrayOfGeospatialType.h>
#include <omarArrayOfRasterEntryObject.h>
#include <ossim/base/ossimDateProperty.h>
#include <ossim/base/ossimDate.h>
#include <ossim/base/ossimDirectory.h>
#include <ossim/base/ossimDrect.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimTrace.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimNotify.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/projection/ossimProjection.h>
#include <ossim/projection/ossimProjectionFactoryRegistry.h>

#include <ossim/base/ossimTrace.h>

static ossimTrace traceTypes("omarStagerUtil:types");
static ossimTrace traceDebug("omarStagerUtil:debug");

omarStagerUtil::omarStagerUtil()
   : //theImage(0)
   theGeospatialTypeList(0),
   theUnitTypeList(0),
   theSecurityClassificationTypeList(0),
   theSensorTypeList(0)
{
   initGeospatialTypeList();
   initUnitTypeList();
   initProductTypeList();
   initSecurityClassificationTypeList();
   initSensorTypeList();
}

omarStagerUtil::~omarStagerUtil()
{
   // Delete the geospatial type list.
   std::vector<omarGeospatialType* >::iterator geospatialTypIdx =
      theGeospatialTypeList.begin();
   while (geospatialTypIdx != theGeospatialTypeList.end())
   {
      if (*geospatialTypIdx)
      {
         delete (*geospatialTypIdx);
         (*geospatialTypIdx) = 0;
      }
      ++geospatialTypIdx;
   }
   theGeospatialTypeList.clear();

   // Delete the unit type list.
   std::vector<omarUnitType* >::iterator unitTypeIdx = 
      theUnitTypeList.begin();
   while (unitTypeIdx != theUnitTypeList.end())
   {
      if (*unitTypeIdx)
      {
         delete (*unitTypeIdx);
         (*unitTypeIdx) = 0;
      }
      ++unitTypeIdx;
   }
   theUnitTypeList.clear();
}

bool omarStagerUtil::stageDir(const ossimFilename& dir)
{
   if (dir.isDir())
   {
      ossimNotify(ossimNotifyLevel_NOTICE)
         << "processing dir: " << dir
         << std::endl;

      // List of directories in this directory...
      std::vector<ossimFilename> dirs;

      // List of files in this directory...
      std::vector<ossimFilename> files;
      
      ossimDirectory d;
      if (d.open(dir))
      {
         ossimFilename f;
         if (d.getFirst(f))
         {
            while (f!="")
            {
              if (f.isDir())
              {
                 if (isDotDir(f) == false) // Skip dot directories...
                 {
                    dirs.push_back(f);
                 }
              }
              else
              {
                 files.push_back(f);
              }
              d.getNext(f);
            }
         }
         
         // process files...
         bool isDirectoryBasedFlag = false;
         std::vector<ossimFilename>::const_iterator i = files.begin();
         while (i != files.end())
         {
            if ( stageFile((*i), isDirectoryBasedFlag) )
            {
               if ( isDirectoryBasedFlag )
               {
                  break;
               }
            }
            ++i;
         }

         if ( isDirectoryBasedFlag == false )
         {
            // process directories...
            i = dirs.begin();
            while (i != dirs.end())
            {
               stageDir( (*i) );
               ++i;
            }
         }
      }
   }
   else
   {
      bool isDirectoryBasedFlag = false;
      return stageFile(dir, isDirectoryBasedFlag);
   }
   return true;
}

bool omarStagerUtil::stageFile(const ossimFilename& file)
{
   if (!isStagable(file))
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "rejected file: " << file << std::endl;
      return false;
   }

   ossimRefPtr<ossimImageHandler> ih =
      ossimImageHandlerRegistry::instance()->open(file);

   if (ih.valid() == false)
   {
      return false;
   }

   return stageFile(ih);
}

bool omarStagerUtil::stageFile(const ossimFilename& file,
                               bool& isDirectoryBasedFlag)
{
   if ( !isStagable(file) )
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
      << "rejected file: " << file << std::endl;
      return false;
   }

   ossimRefPtr<ossimImageHandler> ih
      = ossimImageHandlerRegistry::instance()->open(file);

   if (ih.valid() == false)
   {
      isDirectoryBasedFlag = false;
      return false;
   }

   // Set the directory walker flag.
   isDirectoryBasedFlag = isDirectoryBasedImage(ih.get());

   return stageFile(ih);
}
   

bool omarStagerUtil::stageFile(ossimRefPtr<ossimImageHandler> ih)
{
   bool result = false;

   if (ih.valid() == false)
   {
      return result;
   }
      
   // Main data set.
   omarRasterDataSetObject* rds = new omarRasterDataSetObject();
   
   // Data set has an array of entries.
   omar2__ArrayOfRasterEntryObject* entryArray =
      new omarArrayOfRasterEntryObject();
   rds->setRasterEntrySet(entryArray);
   
   // Set the geospatial type to RASTER.
   setGeospatialType(ih.get(), rds);
   
   // Set the product type. (raster, dted, cib...)
   setProductType(ih.get(), rds);
   
   // Set the security classification.
   setSecurityClassificationType(ih.get(), rds);
   
   // Set the sensor type like SPOT5, Landsat7...
   setSensorType(ih.get(), rds);
   
   setFileList(ih.get(), rds);
   
   setAcqDate(ih.get(), rds);
   
   //---
   // North up bounding rect of whole dataset.
   // This will be expanded by each entry.
   //---
   ossimDrect rasterDataSetBoundingRect;
   rasterDataSetBoundingRect.makeNan();
   
   ossim_uint32 entryIdx = 0;
   std::vector<ossim_uint32> entryList;
   ih->getEntryList(entryList);
   for(entryIdx = 0; entryIdx < ih->getNumberOfEntries(); ++entryIdx)
   {
      stageEntry(entryList[entryIdx],
                 ih.get(),
                 rds,
                 rasterDataSetBoundingRect);
   }
   
   //---
   // Set the bounds of the whole data set now that we have a good bounding
   // box.
   //---
   std::string wktPolyStr;
   getWktPolygon(rasterDataSetBoundingRect, wktPolyStr);
   omarGeometryObject* geomObj = new omarGeometryObject();
   geomObj->setSrsCode(int(4326));
   geomObj->setWktString(wktPolyStr);
   rds->setBounds(geomObj);      
   
   _omar1__saveRasterDataSetObject obj;
   _omar1__saveRasterDataSetObjectResponse objResp;
   
   obj.in0     = rds;
   objResp.out = 0;
   
   StagerWebServiceHttpBinding foo;
   if ( foo.__omar1__saveRasterDataSetObject(&obj, &objResp) == SOAP_OK )
   {
      result = true;
      ossimNotify(ossimNotifyLevel_NOTICE)<< "Staged file: " << ih->getFilename() << std::endl;
   }
   else
   {
      result = false;
      ossimNotify(ossimNotifyLevel_NOTICE)<< "Failed to staged file: " << ih->getFilename() << std::endl;
   }
   
   delete rds;
   rds = 0;

   return result;
}

bool omarStagerUtil::isStagable(const ossimFilename& file) const
{
   if (isDotFile(file))
   {
      return false;
   }
   
   std::string ext = file.ext().downcase().c_str();

   if (ext == "aux") return false;
   if (ext == "geom") return false;
   if (ext == "his") return false;
   if (ext == "jpw") return false;
   if (ext == "omd") return false;
   if (ext == "ovr") return false;
   if (ext == "pdf") return false;   
   if (ext == "sdw") return false;
   if (ext == "spec") return false;
   if (ext == "statistics") return false;
   if (ext == "txt") return false;

   return true;
}

void omarStagerUtil::setGeospatialType(ossimRefPtr<ossimImageHandler> ih,
                                       omarRasterDataSetObject* rds)
{
   if ( (ih.valid() == false) || !rds)
   {
      return;
   }

   // Find the instance with a code of "RASTER" and stuff it.
   std::vector<omarGeospatialType* >::iterator i =
      theGeospatialTypeList.begin();
   while (i != theGeospatialTypeList.end())
   {
      if ( (*i)->getCode() == "RASTER" )
      {
         omar2__GeospatialType* type =
            new omarGeospatialType(*(*i));
         rds->setGeospatialType( type );
      }
      ++i;
   }
}

void omarStagerUtil::setSecurityClassificationType(ossimRefPtr<ossimImageHandler> ih,
                                       omarRasterDataSetObject* rds)
{
   if ( (ih.valid() == false) || !rds)
   {
      return;
   }

   // Find the instance with a code of "RASTER" and stuff it.
   std::vector<omarSecurityClassificationType* >::iterator i =
      theSecurityClassificationTypeList.begin();
   while (i != theSecurityClassificationTypeList.end())
   {
      if ( (*i)->getCode() == "UNCLASS" )
      {
         omar2__SecurityClassificationType* type =
            new omarSecurityClassificationType(*(*i));
         rds->setSecurityClassificationType( type );
      }
      ++i;
   }
}

void omarStagerUtil::setSensorType(ossimRefPtr<ossimImageHandler> ih,
                                   omarRasterDataSetObject* rds)
{
   if ( (ih.valid() == false) || !rds)
   {
      return;
   }

   // Find the instance with a code of "RASTER" and stuff it.
   std::vector<omarSensorType* >::iterator i =
      theSensorTypeList.begin();
   while (i != theSensorTypeList.end())
   {
      if ( (*i)->getCode() == "UNKNOWN" )
      {
         omar2__SensorType* type =
            new omarSensorType(*(*i));
         rds->setSensorType( type );
      }
      ++i;
   }
}

void omarStagerUtil::setProductType(ossimRefPtr<ossimImageHandler> ih,
                                    omarRasterDataSetObject* rds)
{
   if ( (ih.valid() == false) || !rds)
   {
      return;
   }

   // Find the instance with a code of "RASTER" and stuff it.
   ossimString code;
   ossimString imageHandlerName = ih->getClassName();
   omarProductType* productType = 0;

   if (imageHandlerName == "ossimAdrgTileSource")
   {
      code = "ADRG";
      productType = findProductType(code);
   }
   else
   {
      code = "RASTER";
      productType = findProductType(code);
   }

   if (productType)
   {
      //---
      // Note: The memory for omar2__ProductType* will be owned(managed)
      // by the omarRasterDataSetObject.
      //---
      omar2__ProductType* type = new omarProductType(*productType);
      rds->setProductType( type );
   }
}

omarProductType* omarStagerUtil::findProductType(const ossimString& code) const
{
   omarProductType* result = 0;
   
   std::vector<omarProductType* >::const_iterator i =
      theProductTypeList.begin();
   while (i != theProductTypeList.end())
   {
      if ( (*i)->getCode() == code )
      {
         result = (*i);
         break;
      }  
      ++i;
   }
   
   return result;
}

void omarStagerUtil::stageEntry(ossim_uint32 entryIndex,
                                ossimRefPtr<ossimImageHandler> ih,
                                omarRasterDataSetObject* rds,
                                ossimDrect& boundingRect)
{
   if ( (ih.valid() == false) || !rds)
   {
      return;
   }

   // Set the image handle to the entry.
   if (ih->setCurrentEntry(entryIndex) == false)
   {
      return;
   }
   
   // Make a new entry object.
   omarRasterEntryObject* entryObj = new omarRasterEntryObject();

   // Set the entry index.
   entryObj->setEntryId((int)entryIndex);
   
   // Set the gsd units.  For now we'll keep it in meters.
   setEntryGsdUnitType(ih, entryObj);

   // Get the geometry file.
   ossimKeywordlist kwl;
   ih->getImageGeometry(kwl);

   // Make a projection for the entry.
   ossimRefPtr<ossimProjection> imageProj =
      ossimProjectionFactoryRegistry::instance()->createProjection(
         kwl);

   if (imageProj.valid())
   {
      // Set the gsd.
      ossimDpt gsd = imageProj->getMetersPerPixel();
      entryObj->setGsdX(gsd.x);
      entryObj->setGsdY(gsd.y);

      // Set the histogram flag.
      if (ih->createHistogramFilename().exists())
      {
         entryObj->setHistogramAvailableFlag(true);
      }
      else
      {
        entryObj->setHistogramAvailableFlag(false); 
      }

      // Set the overview flag.
      if (ih->createOverviewFilename().exists())
      {
         entryObj->setOverviewAvailableFlag(true);
      }
      else
      {
        entryObj->setOverviewAvailableFlag(false); 
      }

      // Set the number of bands.
      int bands = static_cast<int>(ih->getNumberOfOutputBands());
      entryObj->setNumberOfBands(bands);

      // Set the height (lines).
      entryObj->setHeight(static_cast<int>(ih->getNumberOfLines(0)));

      // Set the width (samples).
      entryObj->setWidth(static_cast<int>(ih->getNumberOfSamples(0)));
      
      // Get the entries valid image vertices.
      std::vector<ossimGpt> groundPts;
      getEntryValidVerticies(ih, imageProj, groundPts);
      
      // This will keep expanding out the bounding rect.
      updateBoundingRect(groundPts, boundingRect);

      if (traceDebug())
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "omarStagerUtil:stageEntry DEBUG:"
            << "\nEntry[" << entryIndex << "] bounding rect:"
            << boundingRect
            << std::endl;
      }

      // Get the wktString for the points.
      std::string wktPolyStr;
      getWktPolygon(groundPts, wktPolyStr);
      //ossimNotify()<< "wktPolyStr: " << wktPolyStr << std::endl;
      omarGeometryObject* geomObj = new omarGeometryObject();
      geomObj->setSrsCode(int(4326));
      geomObj->setWktString(wktPolyStr);
      entryObj->setValidVertices(geomObj); 
      
   } // End of "if (imageProj.valid())"

   // Add the entry to the raster data set.
   rds->rasterEntrySet->RasterEntryObject.push_back(entryObj);
   
}

void omarStagerUtil::setEntryGsdUnitType(ossimRefPtr<ossimImageHandler> ih,
                                         omarRasterEntryObject* entry)
{
   if ( (ih.valid() == false) || !entry)
   {
      return;
   }
   
   // Find the instance with a code of "METERS" and stuff it.
   std::vector<omarUnitType* >::iterator i =
      theUnitTypeList.begin();
   while (i != theUnitTypeList.end())
   {
      if ( (*i)->getCode() == "METERS" )
      {
         omar2__UnitType* type = new omarUnitType(*(*i));
         entry->setGsdUnitType( type );
      }
      ++i;
   }  
}

void omarStagerUtil::getEntryValidVerticies(
   ossimRefPtr<ossimImageHandler> ih,
   ossimRefPtr<ossimProjection> imageProj,
   std::vector<ossimGpt>& groundPoints)
{
   if ( (ih.valid() == false) || (imageProj.valid() == false) )
   {
      return;
   }  

   std::vector<ossimIpt> validVertices;
   ih->getValidImageVertices(validVertices,
                             OSSIM_CLOCKWISE_ORDER,
                             0);

   std::vector<ossimIpt>::const_iterator i = validVertices.begin();
   while (i != validVertices.end())
   {
      ossimGpt gpt;
      imageProj->lineSampleToWorld((*i), gpt);

      // Store all point in wgs84.
      gpt.changeDatum(ossimDatumFactory::instance()->wgs84());

      // Add to array.
      groundPoints.push_back(gpt);
      ++i;
   }
}

void omarStagerUtil::updateBoundingRect(
   const std::vector<ossimGpt>& groundPoints, ossimDrect& boundingRect)
{
   // NOTE: hemisphere wrap probably should be concidered...
   
   if (groundPoints.size() == 0)
   {
      return;
   }
   ossimDpt ul;
   ossimDpt lr;
   if (boundingRect.hasNans() == false)
   {
      ul = boundingRect.ul();
      lr = boundingRect.lr();
   }
   else
   {
      ul = groundPoints[0];
      lr = groundPoints[0];
   }
   std::vector<ossimGpt>::const_iterator i = groundPoints.begin();
   while (i < groundPoints.end())
   {
      if ( (*i).latd() > ul.y )
      {
         ul.y = (*i).latd();
      }
      else if ( (*i).latd() < lr.y )
      {
         lr.y = (*i).latd();
      }
      if ( (*i).lond() < ul.x )
      {
         ul.x = (*i).lond();
      }
      else if ( (*i).lond() > lr.x )
      {
         lr.x = (*i).lond();
      }
      ++i;
   }
   boundingRect.set_ul(ul);
   boundingRect.set_lr(lr);
}

void omarStagerUtil::setFileList(ossimRefPtr<ossimImageHandler> ih,
                                 omarRasterDataSetObject* rds)
{
   if ( (ih.valid() == false) || !rds)
   {
      return;
   }

   omarArrayOfFileObject* afo = new omarArrayOfFileObject();
   std::vector<ossimFilename> list;

   // Add the main file.
   list.push_back(ih->getFilename());

   if (isDirectoryBasedImage(ih))
   {
      //---
      // We will add the directory with dot at the end to indicate that this
      // directory belongs to this image.
      //---
      ossimFilename path = ih->getFilename().path();
      path += "/.";
      
      list.push_back(path);
   }
   else
   {
      ossimFilename f;
      
      std::vector<ossimString> searchExtList;
      getSearchFileExtensions(searchExtList);
      
      std::vector<ossimString>::const_iterator i = searchExtList.begin();
      while ( i != searchExtList.end() )
      {
         f = ih->getFilenameWithThisExtension((*i), false);
         if (f.exists())
         {
            if (isInList(f, list) == false)
            {
               list.push_back(f);
            }
         }
         ++i;
      }

      // Look for a readme file.
      f = ih->getFilename().noExtension();
      f += "_readme.txt";
      if (f.exists())
      {
         if (isInList(f, list) == false)
         {
            list.push_back(f);
         }
      }      
   }
   
//    ossim_uint32 entryIdx = 0;
//    std::vector<ossim_uint32> entryList;
//    ih->getEntryList(entryList);
//    std::vector<ossim_uint32>const_iterator i = entryList.begin();
//    while (i != entryList.end())
//    {
//       ih->setEntry
//    for(entryIdx = 0; entryIdx < ih->getNumberOfEntries(); ++entryIdx)
//    {
//       stageEntry(entryList[entryIdx],
//                  ih.get(),
//                  rds,
//                  rasterDataSetBoundingRect);
//    }

   // Give the list to the omarArrayOfFileObject.
   afo->setFileList(list);

   //---
   // Give the omarArrayOfFileObject to the omarRasterDataSetObject.
   //
   // Note the omarArrayOfFileObject memory is managed by the
   // omarRasterDataSetObject.
   //---
   rds->setAssociatedFileSet(afo);

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "omarStagerUtil::setFileList DEBUG:"
         << std::endl;
      for (ossim_uint32 i = 0; i < list.size(); ++i)
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "list[" << i << "]: " << list[i] << std::endl;
      }
   }
}

void omarStagerUtil::getSearchFileExtensions(
   std::vector<ossimString>& searchExtList) const
{
   searchExtList.push_back(ossimString("aux"));
   searchExtList.push_back(ossimString("geom"));
   searchExtList.push_back(ossimString("his"));
   searchExtList.push_back(ossimString("log"));
   searchExtList.push_back(ossimString("omd"));
   searchExtList.push_back(ossimString("ovr"));
   searchExtList.push_back(ossimString("spec"));
   searchExtList.push_back(ossimString("txt"));
}

void omarStagerUtil::setAcqDate(ossimRefPtr<ossimImageHandler> ih,
                                omarRasterDataSetObject* rds)
{
   if ( (ih.valid() == false) || !rds)
   {
      return;
   }

   //---
   // NOTE:  This is a very loosely coupled way to get acq date.
   //---
   ossimString key = "acquisition_date";
   ossimRefPtr<ossimProperty> prop = ih->getProperty(key);
   if (prop.valid())
   {
      ossimDateProperty* datePtr = PTR_CAST(ossimDateProperty, prop.get());
      if (datePtr)
      {
         time_t* t = new time_t;
         *t = datePtr->getDate();

         //---
         // Note: the omarRasterDataSetObject will manage the time_t memory.
         //---
         rds->setAcquisitionDate(t);
      }
   }
}

void omarStagerUtil::setIngestDate(ossimRefPtr<ossimImageHandler> ih,
                                   omarRasterDataSetObject* rds)
{
   if ( (ih.valid() == false) || !rds)
   {
      return;
   }

   // Get time from image handler meta data.
   time_t* t = new time_t;
   time(t);

   rds->setIngestDate(t);
}

void omarStagerUtil::setBounds(ossimRefPtr<ossimImageHandler> ih,
                               omarRasterDataSetObject* rds)
{
   if ( (ih.valid() == false) || !rds)
   {
      return;
   }

   omarGeometryObject* obj = new omarGeometryObject();
   obj->setSrsCode(int(4326));

   std::string wktStr = "1234";
   obj->setWktString(wktStr);

   rds->setBounds(obj);
}

void omarStagerUtil::getWktPolygon(const std::vector<ossimGpt>& vertices,
                                   std::string& wktPolyStr) const
{
   if (vertices.size() == 0)
   {
      ossimNotify(ossimNotifyLevel_NOTICE)<< "omarStagerUtil::getWktPolygon empty..." << std::endl;
      return;
   }
   
   wktPolyStr = "POLYGON((";
   
   std::vector<ossimGpt>::const_iterator i = vertices.begin();
   while (i != vertices.end())
   {
      wktPolyStr += ossimString::toString((*i).lond(), 15, true);
      wktPolyStr += " ";
      wktPolyStr += ossimString::toString((*i).latd(), 15, true);
      wktPolyStr += ", ";
      ++i;
   }

   // Close the polygon.
   i = vertices.begin();
   wktPolyStr += ossimString::toString((*i).lond(), 15, true);
   wktPolyStr += " ";
   wktPolyStr += ossimString::toString((*i).latd(), 15, true);
   wktPolyStr += "))";
}

void omarStagerUtil::getWktPolygon(const ossimDrect& rect,
                                   std::string& wktPolyStr) const
{
   wktPolyStr = "POLYGON((";

   // Set the upper left.
   wktPolyStr += ossimString::toString(rect.ul().x, 15, true);
   wktPolyStr += " ";
   wktPolyStr += ossimString::toString(rect.ul().y, 15, true);
   wktPolyStr += ", ";

   // Set the upper right.
   wktPolyStr += ossimString::toString(rect.ur().x, 15, true);
   wktPolyStr += " ";
   wktPolyStr += ossimString::toString(rect.ur().y, 15, true);
   wktPolyStr += ", ";

   // Set the lower right.
   wktPolyStr += ossimString::toString(rect.lr().x, 15, true);
   wktPolyStr += " ";
   wktPolyStr += ossimString::toString(rect.lr().y, 15, true);
   wktPolyStr += ", ";

   // Set the lower left.
   wktPolyStr += ossimString::toString(rect.ll().x, 15, true);
   wktPolyStr += " ";
   wktPolyStr += ossimString::toString(rect.ll().y, 15, true);
   wktPolyStr += ", ";

   // Close the polygon.
   wktPolyStr += ossimString::toString(rect.ul().x, 15, true);
   wktPolyStr += " ";
   wktPolyStr += ossimString::toString(rect.ul().y, 15, true);
   wktPolyStr += "))"; 
}

void omarStagerUtil::initGeospatialTypeList()
{
   StagerWebServiceHttpBinding wsdl;
   _omar1__getGeospatialTypes* geospatialTypes =
      new _omar1__getGeospatialTypes;
   _omar1__getGeospatialTypesResponse* geospatialTypesResponse =
      new _omar1__getGeospatialTypesResponse;
   if (wsdl.__omar1__getGeospatialTypes(geospatialTypes,
                                        geospatialTypesResponse)
       == SOAP_OK)
   {
      unsigned int count = geospatialTypesResponse->out->GeospatialType.size();
      for (unsigned int i = 0; i < count; ++i)
      {
         omar2__GeospatialType* g = geospatialTypesResponse->out->GeospatialType[i];
         omarGeospatialType* g1 =
            new omarGeospatialType(*(omarGeospatialType*)g);
         theGeospatialTypeList.push_back(g1);
      }
   }
   else
   {
     ossimNotify(ossimNotifyLevel_WARN)
        << "omarStagerUtil::initGeospatialTypeList error!" << std::endl;
   }

   delete geospatialTypesResponse;
   geospatialTypesResponse = 0;
   delete geospatialTypes;
   geospatialTypes = 0;

   if (traceTypes())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "omarStagerUtil::initGeospatialTypeList DEBUG:"
         << std::endl;
      if (theGeospatialTypeList.size())
      {
         std::vector<omarGeospatialType* >::const_iterator i =
            theGeospatialTypeList.begin();
         ossim_uint32 idx = 0;
         while (i != theGeospatialTypeList.end())
         {
            if (*i)
            {
               omarGeospatialType* g = (*i);
               {
                  ossimNotify(ossimNotifyLevel_DEBUG)
                     << "GeospatialType[" << idx << "]: "
                     << "\ncode:        " << *(g->code)
                     << "\ndescription: " << *(g->description)
                     << "\nid:          " << *(g->id)
                     << std::endl;
               }
            }
            ++idx;
            ++i;
         }
      }
      else
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "no geospatial types found!" << std::endl;
      }
      
   } // end of: "if (traceTypes())"
}

void omarStagerUtil::initUnitTypeList()
{
   StagerWebServiceHttpBinding wsdl;
   _omar1__getUnitTypes* unitTypes =
      new _omar1__getUnitTypes();
   _omar1__getUnitTypesResponse* unitTypesResponse =
      new _omar1__getUnitTypesResponse();
   if (wsdl.__omar1__getUnitTypes(unitTypes,
                                  unitTypesResponse)
       == SOAP_OK)
   {
      unsigned int count = unitTypesResponse->out->UnitType.size();
      for (unsigned int i = 0; i < count; ++i)
      {
         omar2__UnitType* g = unitTypesResponse->out->UnitType[i];
         omarUnitType* g1 = new omarUnitType(*(omarUnitType*)g);
         theUnitTypeList.push_back(g1);
      }
   }
   else
   {
      ossimNotify(ossimNotifyLevel_DEBUG) << "bad..." << std::endl;
   }

   delete unitTypesResponse;
   unitTypesResponse = 0;
   delete unitTypes;
   unitTypes = 0;

   if (traceTypes())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "omarStagerUtil::initUnitTypeList DEBUG:"
         << std::endl;
      if (theUnitTypeList.size())
      {
         std::vector<omarUnitType* >::const_iterator i =
            theUnitTypeList.begin();
         ossim_uint32 idx = 0;
         while (i != theUnitTypeList.end())
         {
            if (*i)
            {
               omarUnitType* g = (*i);
               {
                  ossimNotify(ossimNotifyLevel_DEBUG)
                     << "UnitType[" << idx << "]: "
                     << "\ncode:        " << *(g->code)
                     << "\ndescription: " << *(g->description)
                     << "\nid:          " << *(g->id)
                     << std::endl;
               }
            }
            ++idx;
            ++i;
         }
      }
      else
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "no geospatial types found!" << std::endl;
      }
      
   } // end of:  "if (traceTypes())"
}

void omarStagerUtil::initProductTypeList()
{
   StagerWebServiceHttpBinding wsdl;
   _omar1__getProductTypes* productTypes = new _omar1__getProductTypes();
   _omar1__getProductTypesResponse* productTypesResponse =
      new _omar1__getProductTypesResponse();
   if (wsdl.__omar1__getProductTypes(productTypes,
                                     productTypesResponse)
       == SOAP_OK)
   {
      unsigned int count = productTypesResponse->out->ProductType.size();
      for (unsigned int i = 0; i < count; ++i)
      {
         omar2__ProductType* g = productTypesResponse->out->ProductType[i];
         omarProductType* g1 = new omarProductType(*(omarProductType*)g);
         theProductTypeList.push_back(g1);
      }
   }
   else
   {
      ossimNotify(ossimNotifyLevel_DEBUG) << "bad..." << std::endl;
   }
   
   delete productTypesResponse;
   productTypesResponse = 0;
   delete productTypes;
   productTypes = 0;

   if (traceTypes())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "omarStagerUtil::initProductTypeList DEBUG:"
         << std::endl;
      if (theProductTypeList.size())
      {
         std::vector<omarProductType* >::const_iterator i =
            theProductTypeList.begin();
         ossim_uint32 idx = 0;
         while (i != theProductTypeList.end())
         {
            if (*i)
            {
               omarProductType* g = (*i);
               {
                  ossimNotify(ossimNotifyLevel_DEBUG)
                     << "ProductType[" << idx << "]: "
                     << "\ncode:        " << *(g->code)
                     << "\ndescription: " << *(g->description)
                     << "\nid:          " << *(g->id)
                     << std::endl;
               }
            }
            ++idx;
            ++i;
         }
      }
      else
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "no product types found!" << std::endl;
      }
      
   } // end of:  "if (traceTypes())"
}

void omarStagerUtil::initSecurityClassificationTypeList()
{
   StagerWebServiceHttpBinding wsdl;
   _omar1__getSecurityClassificationTypes* securityTypes = new _omar1__getSecurityClassificationTypes();
   _omar1__getSecurityClassificationTypesResponse* securityTypesResponse =
      new _omar1__getSecurityClassificationTypesResponse();
   if (wsdl.__omar1__getSecurityClassificationTypes(securityTypes,
                                     securityTypesResponse)
       == SOAP_OK)
   {
      unsigned int count = securityTypesResponse->out->SecurityClassificationType.size();
      for (unsigned int i = 0; i < count; ++i)
      {
         omar2__SecurityClassificationType* g = securityTypesResponse->out->SecurityClassificationType[i];
         omarSecurityClassificationType* g1 = new omarSecurityClassificationType(*(omarSecurityClassificationType*)g);
         theSecurityClassificationTypeList.push_back(g1);
      }
   }
   else
   {
      ossimNotify(ossimNotifyLevel_DEBUG) << "bad..." << std::endl;
   }
   
   delete securityTypesResponse;
   securityTypesResponse = 0;
   delete securityTypes;
   securityTypes = 0;

   if (traceTypes())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "omarStagerUtil::initSecurityClassificationTypeList DEBUG:"
         << std::endl;
      if (theSecurityClassificationTypeList.size())
      {
         std::vector<omarSecurityClassificationType* >::const_iterator i =
            theSecurityClassificationTypeList.begin();
         ossim_uint32 idx = 0;
         while (i != theSecurityClassificationTypeList.end())
         {
            if (*i)
            {
               omarSecurityClassificationType* g = (*i);
               {
                  ossimNotify(ossimNotifyLevel_DEBUG)
                     << "SecurityClassificationType[" << idx << "]: "
                     << "\ncode:        " << *(g->code)
                     << "\ndescription: " << *(g->description)
                     << "\nid:          " << *(g->id)
                     << std::endl;
               }
            }
            ++idx;
            ++i;
         }
      }
      else
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "no security types found!" << std::endl;
      }
      
   } // end of:  "if (traceTypes())"
}

void omarStagerUtil::initSensorTypeList()
{
   StagerWebServiceHttpBinding wsdl;
   _omar1__getSensorTypes* sensorTypes = new _omar1__getSensorTypes();
   _omar1__getSensorTypesResponse* sensorTypesResponse =
      new _omar1__getSensorTypesResponse();
   if (wsdl.__omar1__getSensorTypes(sensorTypes,
                                     sensorTypesResponse)
       == SOAP_OK)
   {
      unsigned int count = sensorTypesResponse->out->SensorType.size();
      for (unsigned int i = 0; i < count; ++i)
      {
         omar2__SensorType* g = sensorTypesResponse->out->SensorType[i];
         omarSensorType* g1 = new omarSensorType(*(omarSensorType*)g);
         theSensorTypeList.push_back(g1);
      }
   }
   else
   {
      ossimNotify(ossimNotifyLevel_DEBUG) << "bad..." << std::endl;
   }
   
   delete sensorTypesResponse;
   sensorTypesResponse = 0;
   delete sensorTypes;
   sensorTypes = 0;

   if (traceTypes())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "omarStagerUtil::initSensorTypeList DEBUG:"
         << std::endl;
      if (theSensorTypeList.size())
      {
         std::vector<omarSensorType* >::const_iterator i =
            theSensorTypeList.begin();
         ossim_uint32 idx = 0;
         while (i != theSensorTypeList.end())
         {
            if (*i)
            {
               omarSensorType* g = (*i);
               {
                  ossimNotify(ossimNotifyLevel_DEBUG)
                     << "SensorType[" << idx << "]: "
                     << "\ncode:        " << *(g->code)
                     << "\ndescription: " << *(g->description)
                     << "\nid:          " << *(g->id)
                     << std::endl;
               }
            }
            ++idx;
            ++i;
         }
      }
      else
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "no sensor types found!" << std::endl;
      }
      
   } // end of:  "if (traceTypes())"
}

bool omarStagerUtil::isInList(const ossimFilename& file,
                              const std::vector<ossimFilename>& list) const
{
   std::vector<ossimFilename>::const_iterator i = list.begin();
   while (i != list.end())
   {
      if (file == (*i))
      {
         return true;
      }
      ++i;
   }
   return false;
}

bool omarStagerUtil::isDirectoryBasedImage(ossimRefPtr<ossimImageHandler> ih)
{
   if ( (ih.valid() == false))
   {
      return false;
   }
   
   // Get the image handler name.
   ossimString imageHandlerName = ih->getClassName();
   
   if (imageHandlerName == "ossimAdrgTileSource")
   {
      return true;
   }
   else if (imageHandlerName == "ossimCibCadrgTileSource")
   {
      return true;
   }
   
   return false;
}

bool omarStagerUtil::isDotFile(const ossimFilename& file) const
{
   if ( file.isFile() )
   {
      ossimFilename f = file.file();
      std::string::size_type firstDotPos = f.find('.');
      if ( firstDotPos == 0)
      {
         return true;
      }
   }
   return false;
}

bool omarStagerUtil::isDotDir(const ossimFilename& dir) const
{
   // Get the size in bytes.
   std::string::size_type stringSize = dir.size();
   
   // Check for emptry string...
   if (stringSize == 0)
   {
      return false;
   }

   if ( dir.isDir() )
   {
      // Get the position of first dot from the end.
      std::string::size_type lastDotPos = dir.find_last_of('.');
      
      //---
      // Check for not found.
      // std::string::find(...) returns std::string::npos if not found.
      //---
      if (lastDotPos == std::string::npos)
      {
         return false; // no dot found
      }

      // Make copy.
      ossimFilename f = dir;
      
      // Convert an '\'s to '/'s. 
      f.convertBackToForwardSlashes();
      
      // Find the first slash from end.
      std::string::size_type lastSlashPos = f.find_last_of('/');

      if (lastSlashPos == std::string::npos) // no slashes...
      {
         if (lastDotPos == 0)
         {
            return true;
         }
         return false;
      }
      else // found a slash
      {
         if ( (lastSlashPos+1) == lastDotPos )
         {
            // dot in front of slash like /home/foo/.xemacs
            return true;
         }
      }
   }

   return false;
}
