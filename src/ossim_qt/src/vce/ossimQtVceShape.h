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
// $Id: ossimQtVceShape.h 9114 2006-06-14 17:42:07Z gpotts $
#ifndef ossimQtVceShape_HEADER
#define ossimQtVceShape_HEADER
#include <qcanvas.h>
#include <qpen.h>
#include <qbrush.h>
#include "ossimQtVceShapeRtti.h"
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimKeywordNames.h>
class ossimQtVceConnectionObject;
class ossimQtVceConnectableObject;
class ossimQtVceShape : public QCanvasPolygonalItem
{
public:
   ossimQtVceShape(QCanvas* canvas,
		   QObject* vceParent);
   virtual void setVceParent(QObject* obj);
  QObject* getVceParent();
   virtual QRect boundingRect()const;
   virtual QRect boundingRectAdvanced() const;
   virtual QRect boundingVceShapeRect()const=0;
   virtual bool collidesWith( const QCanvasItem* ) const;
   virtual ossimQtVceConnectableObject* castToConnectable();
   virtual ossimQtVceConnectionObject* castToConnection();
   virtual const ossimQtVceConnectableObject* castToConnectable()const;
   virtual const ossimQtVceConnectionObject* castToConnection()const;
   virtual void draw ( QPainter & p );
   static ossimQtVceShape* castToVceShape(QCanvasItem* item);
   static const ossimQtVceShape* castToVceShape(const QCanvasItem* item);

   void setNewId();
   ossim_int32 getId()const;

   virtual void initialize();
   
   virtual bool saveState(ossimKeywordlist& kwl,
                          const char* prefix=0)const;
   virtual bool loadState(const ossimKeywordlist& kwl,
                          const char* prefix=0);
protected:
   QSize  theSelectionBoxSize;
   QObject* theVceParent;
   ossim_int32 theId;

   static ossim_int32 theVceShapeIdCounter;
   virtual bool collidesWith( const QCanvasSprite*,
                              const QCanvasPolygonalItem*,
                              const QCanvasRectangle*,
                              const QCanvasEllipse*,
                              const QCanvasText* ) const;
   virtual QPointArray areaPoints () const;
  //  virtual void drawShape(QPainter& painter)=0;
   virtual void drawSelection(QPainter&);
};

#endif
