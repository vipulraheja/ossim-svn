//*****************************************************************************
// FILE: ossimFilenameW.cc
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
#include "base/data_types/ossimFilename.h"
#include "imaging/formats/ossimImageHandler.h"
#include "base/common/ossimObject.h"
#include "ossimCFilename.h"
#include "ossimCString.h"

	ossimFilenameH ossimCFilename(char* src)
	{
	return (ossimFilenameH) new ossimFilename(src); 
	}
	
	void ossimFreeFilename(ossimFilenameH Filename)
	{
		if(Filename)
			delete (ossimFilename*)Filename;
	}
	
	void convertBackToForwardSlashesC(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
		name->convertBackToForwardSlashes();
	}
	
	void convertForwardToBackSlashesC(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
		name->convertForwardToBackSlashes();
	}

	bool existsC(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
		return name->exists();
	}
	
	bool isFileC(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
		return name->isFile();
	}
	
	bool isDirC(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
		return name->isDir();
	}
	
	bool isReadableC(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
		return name->isReadable();
	}
	
	bool isWritableC(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
		return name->isWritable();
	}
	
	bool isExecutableC(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
		return name->isExecutable();
	}
	
	ossim_int64 fileSizeC(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
		return name->fileSize();
	}

   ossimStringH   ext(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
                ossimString* temp = new ossimString(name->ext());
		return (ossimStringH)temp;
	}

   ossimFilenameH file(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
                ossimFilename* temp = new ossimFilename(name->file());
		return (ossimFilenameH)temp;
	}

   ossimFilenameH path(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
                ossimFilename* temp = new ossimFilename(name->path());
		return (ossimFilenameH)temp;
	}

   ossimFilenameH drive(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
                ossimFilename* temp = new ossimFilename(name->drive());
		return (ossimFilenameH)temp;
	}

   ossimFilenameH fileNoExtension(ossimFilenameH Filename)
	{
		ossimFilename* name = (ossimFilename*)Filename;
                ossimFilename* temp = new ossimFilename(name->fileNoExtension());
		return (ossimFilenameH)temp;
	}

   ossimFilenameH setExtension(ossimFilenameH Filename, ossimStringH e)
   {
		ossimFilename* name = (ossimFilename*)Filename;
                ossimFilename* temp = new ossimFilename(name->setExtension(*(ossimString*)e));
		return (ossimFilenameH)temp;
   }
   
   ossimFilenameH setPath(ossimFilenameH Filename, ossimStringH p)
   {
		ossimFilename* name = (ossimFilename*)Filename;
                ossimFilename* temp = new ossimFilename(name->setPath(*(ossimString*)p));
		return (ossimFilenameH)temp;
   }
   
   ossimFilenameH setFile(ossimFilenameH Filename, ossimStringH f)
   {
		ossimFilename* name = (ossimFilename*)Filename;
                ossimFilename* temp = new ossimFilename(name->setFile(*(ossimString*)f));
		return (ossimFilenameH)temp;
   }

    void split(ossimFilenameH Filename,
            ossimStringH drivePart,
            ossimStringH pathPart,
            ossimStringH filePart,
            ossimStringH extPart)
    {
            ossimFilename* name = (ossimFilename*)Filename;
            name->split(*(ossimString*)drivePart, *(ossimString*)pathPart, 
            *(ossimString*)filePart, *(ossimString*)extPart);
    }

    void merge(ossimFilenameH Filename,
            const ossimStringH drivePart,
            const ossimStringH pathPart,
            const ossimStringH filePart,
            const ossimStringH extPart)
    {
            ossimFilename* name = (ossimFilename*)Filename;
            name->merge(*(ossimString*)drivePart, *(ossimString*)pathPart, 
                *(ossimString*)filePart, *(ossimString*)extPart);
    }

	ossimFilenameH dirCat(ossimFilenameH Pathname, ossimFilenameH file)
	{
		ossimFilename* path = (ossimFilename*)Pathname;
		ossimFilename* filename = (ossimFilename*)file;
		ossimFilename* pathname = new ossimFilename(path->dirCat(*filename));
		return pathname;   
	}

	bool createDirectory(ossimFilenameH Filename,
                            bool recurseFlag,
                            int perm)
	{
		ossimFilename* file = (ossimFilename*)Filename;
		return file->createDirectory(recurseFlag, perm);
	}

	bool removePathnameC(ossimFilenameH Filename,
					  const char* pathname)
	{
		ossimFilename* file = (ossimFilename*)Filename;
		return file->remove(pathname);
	}

