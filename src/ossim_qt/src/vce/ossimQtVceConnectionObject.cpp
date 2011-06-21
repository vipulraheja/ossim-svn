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
// $Id: ossimQtVceConnectionObject.cpp 13139 2008-07-06 17:40:31Z dburken $

#include <cstdlib>
#include <qpainter.h>
#include <qrect.h>
#include <qpointarray.h>
#include "ossimQtVceConnectionObject.h"
#include "ossimQtVceConnectableObject.h"
#include <ossim/base/ossimLine.h>
#include <ossim/base/ossimDrect.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimPolygon.h>

ossimQtVceConnectionObject::ossimQtVceConnectionObject(QCanvas* canvas,
						       QObject* vceParent)
   :ossimQtVceShape(canvas, vceParent),
    theStart(NULL),
    theEnd(NULL)
{
  theStartPt.setX(0);
  theStartPt.setY(0);
  theEndPt.setX(0);
  theEndPt.setY(0);

  hide();
}

ossimQtVceConnectionObject::~ossimQtVceConnectionObject()
{
  hide();
  removeConnection();
  
  theStart = NULL;
  theEnd   = NULL;
}


ossimQtVceConnectionObject* ossimQtVceConnectionObject::castToConnection()
{
  return this;
}

const ossimQtVceConnectionObject* ossimQtVceConnectionObject::castToConnection()const
{
  return this;
}

void ossimQtVceConnectionObject::updateEndPoints()
{
  hide();

  QPoint pt;
  if(getInternalStartPoint(pt))
    {
      theStartPt = pt;
    }
  if(getInternalEndPoint(pt))
    {
      theEndPt   = pt;
    }

  show();
}

void ossimQtVceConnectionObject::setEndPoints(const QPoint& startPt,
                                              const QPoint& endPt)
{
   hide();
   theStartPt = startPt;
   theEndPt   = endPt;
   show();
}

bool ossimQtVceConnectionObject::collidesWith(const QCanvasItem * other)const
{
  if(!other) return false;
  QPoint startPt = theStartPt;
  QPoint endPt   = theEndPt;
  bool result = false;

  
  ossimLine line1(ossimDpt(startPt.x(),
                           startPt.y()),
                  ossimDpt(endPt.x(),
                           endPt.y()));
  if(other->rtti() == rtti())
  {
     ossimQtVceConnectionObject* tempOther = (ossimQtVceConnectionObject*)other;
     
     QPoint tempStartPt;
     QPoint tempEndPt;
     tempOther->getStartPoint(tempStartPt);
     tempOther->getEndPoint(tempEndPt);
     ossimLine line2(ossimDpt(tempStartPt.x(),
                              tempStartPt.y()),
                     ossimDpt(tempEndPt.x(),
                              tempEndPt.y()));
     
     ossimDpt dpt = line1.intersectSegment(line2);
     result = (!dpt.hasNans());
  }
  else
  {
     result = intersects(other->boundingRect());
  }
  
  return result;
}

int ossimQtVceConnectionObject::rtti()const
{
   return ossimQtVceShapeRttiType_CONNECTION;
}

bool ossimQtVceConnectionObject::makeConnection(ossimQtVceConnectableObject* start,
                                                ossimQtVceConnectableObject* end,
                                                int startIdx,
                                                int endIdx)
{
  bool validConnection = false;
  theStart = start;
  theEnd   = end;
  
  if(start&&end)
    {
      validConnection = theEnd->setInputConnection(this,
						   endIdx);
      
      if(validConnection)
	{
	  validConnection = theStart->setOutputConnection(this,
							  startIdx);
	  updateEndPoints();
	}
      
      if(!validConnection)
	{
	  theEnd->removeConnection(this);
	  theStart->removeConnection(this);
	  theEnd   = NULL;
	  theStart = NULL;
	  
	  QRect bounds = boundingRect();
	  setX(bounds.x() + bounds.width()/2);
	  setY(bounds.y() + bounds.height()/2);
	}
    }
  return validConnection;
}

void ossimQtVceConnectionObject::removeConnection()
{
  if(theStart)
    {
      theStart->removeConnection(this);
    }
  if(theEnd)
    {
      theEnd->removeConnection(this);
    }
}

ossimQtVceConnectableObject* ossimQtVceConnectionObject::getStart()
{
  return theStart;
}

ossimQtVceConnectableObject* ossimQtVceConnectionObject::getEnd()
{
  return theEnd;
}

const ossimQtVceConnectableObject* ossimQtVceConnectionObject::getStart()const
{
  return theStart;
}

const ossimQtVceConnectableObject* ossimQtVceConnectionObject::getEnd()const
{
  return theEnd;
}

void ossimQtVceConnectionObject::getStartPoint(QPoint& pt)const
{
   pt = theStartPt;
}

bool ossimQtVceConnectionObject::getInternalStartPoint(QPoint& pt)const
{
  QRect start;

  if(!theStart) return false;

  if(theStart->getConnectionSlotBoundingRect(start, this))
    {
      pt.setX(start.x() + start.width()/2);
      pt.setY(start.y() + start.height()/2);
      
      return true;
    }
  
  return false;
}

void ossimQtVceConnectionObject::getEndPoint(QPoint& pt)const
{
   pt = theEndPt;
}

bool ossimQtVceConnectionObject::getInternalEndPoint(QPoint& pt)const
{
  QRect end;

  if(!theEnd) return false;

  if(theEnd->getConnectionSlotBoundingRect(end, this))
    {
      pt.setX(end.x() + end.width()/2);
      pt.setY(end.y() + end.height()/2);
      
      return true;
    }
  
  return false;
}

void ossimQtVceConnectionObject::drawShape(QPainter& painter)
{
  if(theStart && theEnd)
    {
       // later we will allow for elbo joints and bezier
       // style drawing.  FOr now we will keep it to a simple
       // straight line.
       //
       painter.drawLine(theStartPt.x(), 
                        theStartPt.y(), 
                        theEndPt.x(), 
                        theEndPt.y());
       
//          drawDirectionArrow(painter);
          
    }
}

void ossimQtVceConnectionObject::drawDirectionArrow(QPainter& painter)
{
   ossimDpt startPt(theStartPt.x(),
                    theStartPt.y());
   ossimDpt endPt(theEndPt.x(),
                  theEndPt.y());

   ossimDpt delta = endPt-startPt;
   double len = delta.length();
   if(len > 5)
   {
      // reflect the delta
      ossimDpt normDelta = delta*(-1.0/len);
      ossimDpt perpDelta(-normDelta.y, normDelta.x);

      ossimDpt p1 = endPt + (normDelta*5 + perpDelta*5);
      ossimDpt p2 = endPt + (normDelta*5 - perpDelta*5);
      
      painter.drawLine(ossim::round<ossim_float64>(p1.x), 
                       ossim::round<ossim_float64>(p1.y), 
                       theEndPt.x(), 
                       theEndPt.y());
      
      painter.drawLine(ossim::round<ossim_float64>(p2.x), 
                       ossim::round<ossim_float64>(p2.y), 
                       theEndPt.x(), 
                       theEndPt.y());
   }
}


void ossimQtVceConnectionObject::drawSelection(QPainter& painter)
{
   QBrush brush = QBrush(QColor(0,0,0));
   QRect startRect(theStartPt.x()-theSelectionBoxSize.width()/2,
                   theStartPt.y()-theSelectionBoxSize.height()/2,
                   theSelectionBoxSize.width(),
                   theSelectionBoxSize.height());
   QRect endRect(theEndPt.x()-theSelectionBoxSize.width()/2,
                 theEndPt.y()-theSelectionBoxSize.height()/2,
                 theSelectionBoxSize.width(),
                 theSelectionBoxSize.height());
   
   painter.fillRect(startRect,
                    brush);
   painter.fillRect(endRect,
                    brush);
                   
}

QRect ossimQtVceConnectionObject::boundingVceShapeRect()const
{
  QPoint startPt = theStartPt;
  QPoint endPt = theEndPt;
  int minX, minY, maxX, maxY;
  
  minX = startPt.x()<endPt.x()?startPt.x():endPt.x();
  minY = startPt.y()<endPt.y()?startPt.y():endPt.y();
  maxX = startPt.x()>endPt.x()?startPt.x():endPt.x();
  maxY = startPt.y()>endPt.y()?startPt.y():endPt.y();
  
  QRect result(minX,
	       minY,
	       (maxX-minX) + 1,
	       (maxY-minY) + 1);
  
  return result;
}

QPointArray ossimQtVceConnectionObject::areaPoints () const
{
   QPointArray p(4);
   int x1 = theStartPt.x();
   int y1 = theStartPt.y();
   int x2 = theEndPt.x();
   int y2 = theEndPt.y();
   int xi = 0;
   int yi = 0;
   int pw = pen().width();
   int dx = abs(x1-x2);
   int dy = abs(y1-y2);
//   pw = pw*4/3+2 + 5; // approx pw*sqrt(2) plus the arrow distance
   pw = pw*4/3+2; // approx pw*sqrt(2)
   int px = x1<x2 ? -pw : pw ;
   int py = y1<y2 ? -pw : pw ;
   if ( dx && dy && (dx > dy ? (dx*2/dy <= 2) : (dy*2/dx <= 2)) )
   {
      // steep
      if ( px == py )
      {
         p[0] = QPoint(x1+xi   ,y1+yi+py);
         p[1] = QPoint(x2+xi-px,y2+yi   );
         p[2] = QPoint(x2+xi   ,y2+yi-py);
         p[3] = QPoint(x1+xi+px,y1+yi   );
      }
      else
      {
         p[0] = QPoint(x1+xi+px,y1+yi   );
         p[1] = QPoint(x2+xi   ,y2+yi-py);
         p[2] = QPoint(x2+xi-px,y2+yi   );
         p[3] = QPoint(x1+xi   ,y1+yi+py);
      }
   }
   else if ( dx > dy )
   {
      // horizontal
      p[0] = QPoint(x1+xi+px,y1+yi+py);
      p[1] = QPoint(x2+xi-px,y2+yi+py);
      p[2] = QPoint(x2+xi-px,y2+yi-py);
      p[3] = QPoint(x1+xi+px,y1+yi-py);
   }
   else
   {
      // vertical
      p[0] = QPoint(x1+xi+px,y1+yi+py);
      p[1] = QPoint(x2+xi+px,y2+yi-py);
      p[2] = QPoint(x2+xi-px,y2+yi-py);
      p[3] = QPoint(x1+xi-px,y1+yi+py);
   }

   return p;
}

bool ossimQtVceConnectionObject::intersects(const QRect& rect)const
{
   ossimDpt startPt(theStartPt.x(), theStartPt.y());
   ossimDpt endPt(theEndPt.x(), theEndPt.y());

   int rw = rect.width();
   int rh = rect.height();

   if(rw <2) rw = 2;
   if(rh <2) rh = 2;

   return ossimDrect(rect.x(),
                     rect.y(),
                     rect.x() + rw - 1,
                     rect.y() + rh - 1).clip(startPt, endPt);
}
