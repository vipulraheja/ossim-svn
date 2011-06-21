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
// $Id: ossimQtVceImageHandlerObject.cpp 9114 2006-06-14 17:42:07Z gpotts $
#include <qpainter.h>
#include "ossimQtVceImageHandlerObject.h"
#include <ossim/imaging/ossimImageRenderer.h>
#include <ossim/imaging/ossimScalarRemapper.h>
#include <ossim/projection/ossimImageViewAffineTransform.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/imaging/ossimImageHandler.h>

ossimQtVceImageHandlerObject::ossimQtVceImageHandlerObject(QCanvas* canvas,
                                                           QObject* vceParent)
   :ossimQtVceImageSourceObject(canvas, vceParent)
{
   theImage.create(theWidth,
                   theHeight,
                   32);
}

ossimQtVceImageHandlerObject::ossimQtVceImageHandlerObject(const QRect& bounds,
                                                           QCanvas* canvas,
                                                           QObject* vceParent)
   :ossimQtVceImageSourceObject(bounds,
                                canvas,
                                vceParent)
{
   theImage.create(theWidth,
                   theHeight,
                   32);
}

ossimQtVceImageHandlerObject::~ossimQtVceImageHandlerObject()
{
}

int ossimQtVceImageHandlerObject::rtti()const
{
   return ossimQtVceShapeRttiType_IMAGE_HANDLER;
}

void ossimQtVceImageHandlerObject::drawShape(QPainter& painter)
{
   painter.drawImage((int)x(), (int)y(), theImage);
}
