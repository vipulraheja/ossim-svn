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
// $Id: ossimQtVceConnectionObject.h 5757 2003-12-12 19:50:32Z gpotts $
#ifndef ossimQtVceConnectionObject_HEADER
#define ossimQtVceConnectionObject_HEADER
#include <qcanvas.h>
#include <qpen.h>
#include <qbrush.h>
#include <qpoint.h>
#include "ossimQtVceShape.h"
class ossimQtVceConnectableObject;
class ossimQtVceConnectionObject : public ossimQtVceShape
{
public:
   ossimQtVceConnectionObject(QCanvas* canvas,
			      QObject* vceParent);
   
   virtual ~ossimQtVceConnectionObject();
   virtual ossimQtVceConnectionObject* castToConnection();
   virtual const ossimQtVceConnectionObject* castToConnection()const;
   virtual bool collidesWith(const QCanvasItem * other)const;
   
   virtual void updateEndPoints();
   virtual void setEndPoints(const QPoint& startPt,
                             const QPoint& endPt);
   /*!
    * You can specify optional slot indices.  The value < 0
    * indicates that a default connection will be made.  Else
    * it will try to connect to the specified slot.  Usually
    * the indices specifed for fixed slot connections.
    */
   bool makeConnection(ossimQtVceConnectableObject* start,
                       ossimQtVceConnectableObject* end,
                       int startIdx = -1,
                       int endIdx = -1);

   /*!
    * basically this is used when someone removes a start connection
    * and then re-connects it back to another objects.
    */
   void connectStart(ossimQtVceShape* start,
                     int idx=-1);
   
   /*!
    * basically this is used when someone removes an end connection
    * and then re-connects it back to another objects.
    */
   void connectEnd(ossimQtVceShape* end,
                   int idx=-1);

   /*!
    * Will remove both connections;
    */
   void removeConnection();

   
   void disconnectStart();
   void disconnectEnd();

   virtual int rtti()const;
   virtual QRect boundingVceShapeRect()const;
   ossimQtVceConnectableObject* getStart();
   ossimQtVceConnectableObject* getEnd();
   const ossimQtVceConnectableObject* getStart()const;
   const ossimQtVceConnectableObject* getEnd()const;

   void getStartPoint(QPoint& pt)const;
   void getEndPoint(QPoint& pt)const;
   
   bool intersects(const QRect& rect)const;
protected:
   ossimQtVceConnectableObject* theStart;
   ossimQtVceConnectableObject* theEnd;
   QPoint                       theStartPt;
   QPoint                       theEndPt;

   virtual bool getInternalStartPoint(QPoint& pt)const;
   virtual bool getInternalEndPoint(QPoint& pt)const;
   virtual void drawShape(QPainter&);
   virtual void drawDirectionArrow(QPainter&);
   virtual QPointArray areaPoints () const;
   virtual void drawSelection(QPainter& painter);
};

#endif
