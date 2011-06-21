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
#ifndef ossimCImageFileWriter_HEADER
#define ossimCImageFileWriter_HEADER
#include "ossimCKeywordlist.h"
#include "ossimCFilename.h"
#include "ossimCString.h"

typedef void* ossimImageFileWriterH;
typedef void* ossimListenerH;

#ifdef __cplusplus
extern "C"
{
#endif

    bool ossimAddListener(ossimImageFileWriterH writer, ossimListenerH listener);
    bool ossimRemoveListener(ossimImageFileWriterH writer, ossimListenerH listener);
    void ossimSetFilename(ossimImageFileWriterH writer, const ossimFilenameH file);
//    ossimImageFileWriterH ossimCreateImageFileWriterFromKwl(ossimKeywordlistH kwl);
//    ossimImageFileWriterH ossimCreateImageFileWriterFromKwlPrefix(
//            ossimKeywordlistH kwl, const char* prefix);
   void ossimExecuteImageFileWriter(ossimImageFileWriterH writer);
   ossimImageFileWriterH ossimCreateWriter(ossimStringH typeName);
   void ossimGetImageTypeList(ossimStringVectorH imageTypeList);
   void setOutputName(ossimImageFileWriterH writer, char* outputName);
	void ossimFileWrighterAbort(ossimImageFileWriterH writer);
   
#ifdef __cplusplus
}
#endif
#endif
