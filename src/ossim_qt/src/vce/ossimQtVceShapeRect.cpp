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
// $Id: ossimQtVceShapeRect.cpp 9114 2006-06-14 17:42:07Z gpotts $
#include <qpainter.h>
#include "ossimQtVceShapeRect.h"
#include "ossimQtVceConnectionObject.h"
#include <ossim/base/ossimLine.h>
#include <ossim/base/ossimDrect.h>
#include <ossim/base/ossimPolygon.h>

ossimQtVceShapeRect::ossimQtVceShapeRect(QCanvas* canvas,
                                         QObject* vceParent)
   :ossimQtVceShape(canvas, vceParent),
    theWidth(1),
    theHeight(1)
{
   setX(0);
   setY(0);
}

ossimQtVceShapeRect::ossimQtVceShapeRect(int x,
                                         int y,
                                         int w,
                                         int h,
                                         QCanvas* canvas,
                                         QObject* vceParent)
   :ossimQtVceShape(canvas, vceParent),
    theWidth(w),
    theHeight(h)
{
   setX(x);
   setY(y);
}

ossimQtVceShapeRect::ossimQtVceShapeRect(const QRect& rect,
                                         QCanvas* canvas,
                                         QObject* vceParent)
   :ossimQtVceShape(canvas, vceParent),
    theWidth(rect.width()),
    theHeight(rect.height())
{
   setX(rect.x());
   setY(rect.y());
}

ossimQtVceShapeRect::~ossimQtVceShapeRect()
{
   hide();
}

int ossimQtVceShapeRect::rtti()const
{
   return ossimQtVceShapeRttiType_RECT;
}


bool ossimQtVceShapeRect::collidesWith( const QCanvasItem* item) const
{
   if(!item) return false;
   const ossimQtVceShape* vceShape = castToVceShape(item);
   if(!vceShape) return ossimQtVceShape::collidesWith(item);
   
   const ossimQtVceConnectionObject* connection = vceShape->castToConnection();
   
   if(!connection)
   {
      return ossimQtVceShape::collidesWith(item);
   }
   
   QPoint startPt;
   QPoint endPt;
   connection->getStartPoint(startPt);
   connection->getEndPoint(endPt);
   
   return connection->intersects(boundingRect());
}

QRect ossimQtVceShapeRect::boundingVceShapeRect()const
{
   int pw = pen().width();
   return QRect((int)x()-pw/2,
                (int)y()-pw/2,
                theWidth+pw,
                theHeight+pw);
}

void ossimQtVceShapeRect::setSize(int w, int h)
{
   bool visibleFlag = isVisible();
   if(visibleFlag)
   {
      hide();
   }
   theWidth  = w;
   theHeight = h;
   
   if(visibleFlag)
   {
      show();
   }
}

void ossimQtVceShapeRect::drawShape(QPainter& painter)
{
   painter.drawRect(QRect((int)x(),
                          (int)y(),
                          theWidth,
                          theHeight));
}

