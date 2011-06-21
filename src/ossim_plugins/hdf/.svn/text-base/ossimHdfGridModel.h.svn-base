//*****************************************************************************
// FILE: ossimHdfGridModel.h
//
// Copyright (C) 2001 ImageLinks, Inc.
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// AUTHOR: Mingjie Su
//
// DESCRIPTION:
//   Contains declaration of class ossimHdfGridModel. This is an
//   implementation of an interpolation sensor model.
//
//*****************************************************************************
//  $Id: ossimHdfGridModel.h 2645 2011-05-26 15:21:34Z oscar.kramer $

#ifndef ossimHdfGridModel_HEADER
#define ossimHdfGridModel_HEADER

//HDF4 Includes
#include <hdf/hdf.h>
#include <hdf/mfhdf.h>

//HDF5 Includes
#include <hdf5.h>

#include <ossim/projection/ossimCoarseGridModel.h>
#include "../ossimPluginConstants.h"

/******************************************************************************
 *
 * CLASS:  ossimHdfGridModel
 *
 *****************************************************************************/
class OSSIM_PLUGINS_DLL ossimHdfGridModel : public ossimCoarseGridModel
{
public:
   
    //! CONSTRUCTOR (filename) Accepts name of hdf file and the index of SDS data
   ossimHdfGridModel(const ossimFilename& file, 
                    const ossimDrect& imageRect,
                    ossimString latGridIndexOrName, 
                    ossimString lonGridIndexOrName, 
                    const ossimIpt& gridSpacing);
   
   ~ossimHdfGridModel();

private:
   void setGridNodes(ossimDblGrid& grid, int32 sds_id, const ossimIpt& spacing);
   void debugDump();

   bool m_isHdf4;

   TYPE_DATA
};

#endif
