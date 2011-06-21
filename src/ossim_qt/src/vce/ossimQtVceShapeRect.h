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
// $Id: ossimQtVceShapeRect.h 5757 2003-12-12 19:50:32Z gpotts $
#ifndef ossimQtVceShapeRect_HEADER
#define ossimQtVceShapeRect_HEADER
#include "ossimQtVceShape.h"

class ossimQtVceShapeRect : public ossimQtVceShape
{
public:
   ossimQtVceShapeRect(QCanvas* canvas, QObject* vceParent=NULL);
   ossimQtVceShapeRect(int x,
                       int y,
                       int w,
                       int h,
                       QCanvas* canvas,
                       QObject* vceParent=NULL);
   ossimQtVceShapeRect(const QRect& rect,
                       QCanvas* canvas,
                       QObject* vceParent=NULL);
   virtual ~ossimQtVceShapeRect();
   virtual bool collidesWith( const QCanvasItem* ) const;
   virtual QRect boundingVceShapeRect()const;
   virtual void setSize(int w, int h);
   virtual int rtti()const;
protected:
   int theWidth;
   int theHeight;
   virtual void drawShape(QPainter& painter);
};

#endif
