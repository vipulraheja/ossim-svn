//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// OSSIM is free software; you can redistribute it and/or
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
// Author: Garrett Potts (gpotts@imagelinks.com)
//
//*************************************************************************
// $Id: ossimQtVceShapeRtti.h 5757 2003-12-12 19:50:32Z gpotts $
#ifndef ossimQtVceShapeRtti_HEADER
#define ossimQtVceShapeRtti_HEADER

enum ossimQtVceShapeRttiType
{
   ossimQtVceShapeRttiType_FIRST_ID     = 25000,
   ossimQtVceShapeRttiType_IMAGE_LOADER = 25000, // make sure this has the first id
   ossimQtVceShapeRttiType_IMAGE_SOURCE,
   ossimQtVceShapeRttiType_IMAGE_HANDLER,
   ossimQtVceShapeRttiType_IMAGE_WRITER,
   ossimQtVceShapeRttiType_IMAGE_COMBINER,
   ossimQtVceShapeRttiType_IMAGE_FILTER,
   ossimQtVceShapeRttiType_CONNECTION,
   ossimQtVceShapeRttiType_IMAGE_DISPLAY,
   ossimQtVceShapeRttiType_RECT,
   
   ossimQtVceShapeRttiType_LAST_ID  // with this we can do range checking
};

#endif
