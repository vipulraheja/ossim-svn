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
#include "ossimCImageFileWriter.h"
#include "imaging/formats/ossimImageFileWriter.h"
#include "imaging/factory/ossimImageWriterFactoryRegistry.h"
#include "base/data_types/ossimString.h"

void ossimSetFilename(ossimImageFileWriterH writer,
				 const ossimFilenameH file)
{
	ossimImageFileWriter* w = (ossimImageFileWriter*)writer;
	w->setFilename(*(ossimFilename*) file);
}

void ossimExecuteImageFileWriter(ossimImageFileWriterH writer)
{
   ((ossimImageFileWriter*)writer)->execute();
}

bool ossimAddListener(ossimImageFileWriterH writer, ossimListenerH listener)
{
    ossimImageFileWriter* w = (ossimImageFileWriter*)writer;
    ossimListener* l = (ossimListener*)listener;
    return w->addListener(l);
}
bool ossimRemoveListener(ossimImageFileWriterH writer, ossimListenerH listener)
{
    ossimImageFileWriter* w = (ossimImageFileWriter*)writer;
    ossimListener* l = (ossimListener*)listener;
    return w->removeListener(l);
}

void setOutputName(ossimImageFileWriterH writer, char* outputName)
{
	ossimImageFileWriter* w = (ossimImageFileWriter*)writer;
	w->setOutputName(ossimString(outputName));
}

void ossimFileWrighterAbort(ossimImageFileWriterH writer)
{
	ossimImageFileWriter* w = (ossimImageFileWriter*)writer;
	w->abort();
}
