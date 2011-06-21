//*****************************************************************************
// Copyright (C) 2003 James E. Hopper & ImageLinks Inc. 
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// You should have received a copy of the GNU General Public License
// along with this software. If not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-
// 1307, USA.
//
// See the GPL in the COPYING.GPL file for more details.
//
// AUTHOR: James E. Hopper (hopperj@macconnect.com)
//         Garrett Potts (gpotts@imagelinks)
//
//*****************************************************************************
#ifndef ossimCImageWriterFactoryRegistry_HEADER
#define ossimCImageWriterFactoryRegistry_HEADER

    typedef void* ossimImageWriterFactoryRegistryH;
    typedef void* ossimImageFileWriterH;
    typedef void* ossimKeywordlistH;
    typedef void* ossimStringH;
    typedef void* ossimStringVectorH;
    
#ifdef __cplusplus
extern "C"
{
#endif

//    ossimImageWriterFactoryRegistryH instance();
    
    ossimImageFileWriterH createWriterKeyword(
            const ossimKeywordlistH kwl,
            const char *prefix); //default = 0
            
   ossimImageFileWriterH createWriter(const ossimStringH& typeName);

    /*!
    * getImageTypeList.  This is the actual image type name.  So for
    * example, ossimTiffWriter has several image types.  Some of these
    * include TIFF_TILED, TIFF_TILED_BAND_SEPARATE ... etc.  The ossimGdalWriter
    * may include GDAL_IMAGINE_HFA, GDAL_RGB_NITF, GDAL_JPEG20000, ... etc
    * A writer should be able to be instantiated by this name as well as a class name
    */
    void getImageTypeList(ossimStringVectorH imageTypeList);

#ifdef __cplusplus
}
#endif

#endif
