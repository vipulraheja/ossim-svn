//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  See top level LICENSE.txt file.
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtVceShape.cpp 9114 2006-06-14 17:42:07Z gpotts $
#include <sstream>
#include <qpainter.h>
#include <qcanvas.h>
#include <qbrush.h>
#include "ossimQtVceShape.h"
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimString.h>

ossim_int32 ossimQtVceShape::theVceShapeIdCounter = 0;

ossimQtVceShape::ossimQtVceShape(QCanvas* canvas,
				 QObject* obj)
  :QCanvasPolygonalItem(canvas),
   theVceParent(obj)
{
   setNewId();
   theSelectionBoxSize = QSize(5,5);
}
void ossimQtVceShape::setVceParent(QObject* obj)
{
  theVceParent = obj;
}

QObject* ossimQtVceShape::getVceParent()
{
  return theVceParent;
}

void ossimQtVceShape::draw(QPainter& painter)
{
  painter.setPen(pen());
  painter.setBrush(brush());
  drawShape(painter);
  if(isSelected())
  {
     drawSelection(painter);
  }
}

void ossimQtVceShape::drawSelection(QPainter& painter)
{
   QBrush oldBrush = painter.brush();
   QBrush brush = QBrush(QColor(0,0,0));
   QRect bounds = boundingVceShapeRect();

   QRect ulRect = bounds;
   QRect urRect = bounds;
   QRect lrRect = bounds;
   QRect llRect = bounds;

   int bw = bounds.width();
   int bh = bounds.height();
   int w = theSelectionBoxSize.width();
   int h = theSelectionBoxSize.height();
   
   ulRect.moveBy(-w, -h);
   ulRect.setSize(theSelectionBoxSize);

   llRect.moveBy(-w, bh);
   llRect.setSize(theSelectionBoxSize);

   lrRect.moveBy(bw, bh);
   lrRect.setSize(theSelectionBoxSize);

   urRect.moveBy(bw, -h);
   urRect.setSize(theSelectionBoxSize);

   painter.fillRect(ulRect,
                    brush);
   painter.fillRect(urRect,
                    brush);
   painter.fillRect(lrRect,
                    brush);
   painter.fillRect(llRect,
                    brush);
   painter.setBrush(oldBrush);
}

QRect ossimQtVceShape::boundingRect()const
{
   QRect bounds = boundingVceShapeRect();

   return QRect(bounds.x() - theSelectionBoxSize.width(),
		bounds.y() - theSelectionBoxSize.height(),
		bounds.width() + 2*theSelectionBoxSize.width()+1,
		bounds.height() + 2*theSelectionBoxSize.height()+1);
}

QRect ossimQtVceShape::boundingRectAdvanced() const
{
   int dx = int(x()+xVelocity())-int(x());
   int dy = int(y()+yVelocity())-int(y());
   QRect r = boundingVceShapeRect();
   r.moveBy(dx,dy);
   return r;
}

bool ossimQtVceShape::collidesWith (const QCanvasItem* other ) const
{
   if(!other) return false;
   QRect qrect1;

   const ossimQtVceShape* vceShape = castToVceShape(other);
   if(vceShape)
   {
      qrect1 = vceShape->boundingVceShapeRect();
   }
   else
   {
      qrect1 = other->boundingRect();
   }
   
   QRect qrect2 = boundingVceShapeRect();

   
   ossimIrect rect1(qrect1.x(),
                    qrect1.y(),
                    qrect1.x() + qrect1.width()-1,
                    qrect1.y() + qrect1.height()-1);
   ossimIrect rect2(qrect2.x(),
                    qrect2.y(),
                    qrect2.x() + qrect2.width()-1,
                    qrect2.y() + qrect2.height()-1);

   return rect1.intersects(rect2);
}

bool ossimQtVceShape::collidesWith(  const QCanvasSprite*,
                                     const QCanvasPolygonalItem*,
                                     const QCanvasRectangle*,
                                     const QCanvasEllipse*,
                                     const QCanvasText* ) const
{
   return false;
}

ossimQtVceShape* ossimQtVceShape::castToVceShape(QCanvasItem* item)
{
   if((item->rtti() >= ossimQtVceShapeRttiType_FIRST_ID )&&
      (item->rtti() <= ossimQtVceShapeRttiType_LAST_ID))
   {
      return (ossimQtVceShape*)item;
   }
   return (ossimQtVceShape*)NULL;
}

const ossimQtVceShape* ossimQtVceShape::castToVceShape(const QCanvasItem* item)
{
   if((item->rtti() >= ossimQtVceShapeRttiType_FIRST_ID )&&
      (item->rtti() <= ossimQtVceShapeRttiType_LAST_ID))
   {
      return (const ossimQtVceShape*)item;
   }
   return (const ossimQtVceShape*)NULL;
}

ossimQtVceConnectableObject* ossimQtVceShape::castToConnectable()
{
  return (ossimQtVceConnectableObject*)NULL;
}

ossimQtVceConnectionObject* ossimQtVceShape::castToConnection()
{
  return (ossimQtVceConnectionObject*)NULL;
}
const ossimQtVceConnectableObject* ossimQtVceShape::castToConnectable()const
{
  return (const ossimQtVceConnectableObject*)NULL;
}

const ossimQtVceConnectionObject* ossimQtVceShape::castToConnection()const
{
  return (const ossimQtVceConnectionObject*)NULL;
}

QPointArray ossimQtVceShape::areaPoints () const
{
  return QPointArray(boundingRect());
}

void ossimQtVceShape::initialize()
{
   
}

ossim_int32 ossimQtVceShape::getId()const
{
   return theId;
}

void ossimQtVceShape::setNewId()
{
   theId = theVceShapeIdCounter;
   ++theVceShapeIdCounter;
}

bool ossimQtVceShape::saveState(ossimKeywordlist& kwl,
                                const char* prefix)const
{
   kwl.add(prefix,
           ossimKeywordNames::TYPE_KW,
           "ossimQtVceShape",
           true);
   kwl.add(prefix,
           ossimKeywordNames::ID_KW,
           theId,
           true);
   kwl.add(prefix,
           "selection_box_size",
           ossimString::toString(theSelectionBoxSize.width())+" "+
           ossimString::toString(theSelectionBoxSize.height()),
           true);
   kwl.add(prefix,
           "position",
           ossimString::toString((int)x())+" "+
           ossimString::toString((int)y()),
           true);

   QRect b = boundingVceShapeRect();

   return true;
}

bool ossimQtVceShape::loadState(const ossimKeywordlist& kwl,
                                const char* prefix)
{
   const char* id = kwl.find(prefix, ossimKeywordNames::ID_KW);
   const char* selectionSize = kwl.find(prefix, "selection_box_size");
   const char* position = kwl.find(prefix, "position");

   if(id)
   {
      theId = ossimString(id).toInt();
   }
   if(selectionSize)
   {
      std::stringstream s(selectionSize);
      int w, h;
      s >> w >> h;
      theSelectionBoxSize = QSize(w, h);
   }
   
   if(position)
   {
      std::stringstream s(position);
      int x, y;
      s >> x >> y;

      setX(x);
      setY(y);
   }
   
   return true;
}
