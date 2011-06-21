//*****************************************************************************
// FILE: ossimFilenameW.h
//
// Copyright (C) 2003 James E. Hopper.
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
//
//*****************************************************************************
#ifndef ossimCFilename_HEADER
#define ossimCFilename_HEADER

#include "ossimCObject.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef void* ossimFilenameH;

	//ossimObjectH castFilenameToObject(ossimFilenameH filename);
	ossimFilenameH ossimCFilename(char* src);
	void ossimFreeFilename(ossimFilenameH Filename);

   void convertBackToForwardSlashesC(ossimFilenameH Filename);
   void convertForwardToBackSlashesC(ossimFilenameH Filename);

   // Methods to test ossimFilename for various states.
   bool        existsC(ossimFilenameH Filename);
   bool        isFileC(ossimFilenameH Filename);
   bool        isDirC(ossimFilenameH Filename);
   bool        isReadableC(ossimFilenameH Filename);
   bool        isWritableC(ossimFilenameH Filename);
   bool        isExecutableC(ossimFilenameH Filename);
   ossim_int64 fileSizeC(ossimFilenameH Filename);

   // Methods to access parts of the ossimFilename.
   ossimStringH   ext(ossimFilenameH Filename);
   ossimFilenameH file(ossimFilenameH Filename);
   ossimFilenameH path(ossimFilenameH Filename);
   ossimFilenameH drive(ossimFilenameH Filename);
   ossimFilenameH fileNoExtension(ossimFilenameH Filename);

   ossimFilenameH setExtension(ossimFilenameH Filename, ossimStringH e);
   ossimFilenameH setPath(ossimFilenameH Filename, ossimStringH p);
   ossimFilenameH setFile(ossimFilenameH Filename, ossimStringH f);

   void split(ossimFilenameH Filename,
              ossimStringH drivePart,
              ossimStringH pathPart,
              ossimStringH filePart,
              ossimStringH extPart);
   
   void merge(ossimFilenameH Filename,
              const ossimStringH drivePart,
              const ossimStringH pathPart,
              const ossimStringH filePart,
              const ossimStringH extPart);

   /*!
    * Returns file appended onto this string. Path seperator is always placed
    * between this and file.  Returns file if this string is empty.
    * Given: this = /foo  and file  = bar output  = /foo/bar
    * Given: this = /foo/ and file  = bar output  = /foo/bar
    */
   ossimFilenameH dirCat(ossimFilenameH Pathname, ossimFilenameH file);

   /*!
    */
   bool createDirectory(ossimFilenameH Filename,
                        bool recurseFlag,// true
                        int perm); //0777

   /*!
    * Removes pathname from filesystem if supported by platform.
    * Return true on success, false on error.
    * If supported will set errno and output equivalent string if one occurs.
    */
	bool removePathnameC(ossimFilenameH Filename,
					  const char* pathname);
   
   /*!
    * since windows uses \ for path separation
    * and unix / we need to be consistent.
    */
   static const char thePathSeparator = '/';

#ifdef __cplusplus
}
#endif

#endif
