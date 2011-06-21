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
//
//*****************************************************************************
#include "ossimCGeomFileWriter.h"
#include "imaging/metadata/ossimGeomFileWriter.h"

	void deleteOssimGeomFileWriter(ossimGeomFileWriterH geom)
	{
		if(geom)
			delete (ossimGeomFileWriter*)geom;
	}
   
	ossimGeomFileWriterH createOssimGeomFileWriter()
	{
		ossimGeomFileWriter *g = new ossimGeomFileWriter();
		return (ossimGeomFileWriterH)g;
	}
   
	ossimGeomFileWriterH createConnectedOssimGeomFileWriter(
		ossimConnectableObjectH inputSource, const ossimFilenameH filename)
	{
		ossimGeomFileWriter *g = new ossimGeomFileWriter(
			(ossimImageSource*)inputSource, *(ossimFilename*)filename);
		return (ossimGeomFileWriterH)g;
	}
	
	ossimGeomFileWriterH createConnectedOssimGeomFileWriterS(
		ossimConnectableObjectH inputSource, char* filename)
	{
		ossimFilename fn(filename);
		ossimGeomFileWriter *g = new ossimGeomFileWriter(
			(ossimImageSource*)inputSource, fn);
		return (ossimGeomFileWriterH)g;
	}

	void ossimExecuteGeomFileWriter(ossimGeomFileWriterH geom)
	{
	((ossimGeomFileWriter*)geom)->execute();
	}
