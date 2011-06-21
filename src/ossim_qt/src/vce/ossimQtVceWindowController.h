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
// $Id: ossimQtVceWindowController.h 9114 2006-06-14 17:42:07Z gpotts $
#ifndef ossimQtVceWindowController_HEADER
#define ossimQtVceWindowController_HEADER
#include <qobject.h>
#include <qcanvas.h>
#include <ossim/base/ossimKeywordlist.h>

class ossimQtVceWindow;
class QMouseEvent;
class ossimQtVceCanvasWidget;
class QDragEnterEvent;
class QDropEvent;
class ossimQtVceConnectableObject;

class ossimQtVceWindowController : public QObject
{
   Q_OBJECT
public:
   ossimQtVceWindowController(ossimQtVceWindow* window);
   virtual ~ossimQtVceWindowController();

   virtual bool saveState(ossimKeywordlist& kwl,
                          const char* prefix=0)const;
   virtual bool loadState(const ossimKeywordlist& kwl,
                          const char* prefix=0);
   virtual void closeEvent(QCloseEvent* evt);
   
protected:
   ossimQtVceWindow*            theVceWindow;
   QCanvas*                     theCanvas;
   virtual void customEvent(QCustomEvent* event);

public slots:
   virtual void cutSelectedObjects();
   virtual void copySelectedObjects();
   virtual void selectAll();
   virtual void paste();
   virtual void alignLeft();
   virtual void alignRight();
   virtual void alignTop();
   virtual void alignBottom();

   // canvas mouse events
//    virtual void canvasWidgetMousePressEvent(QMouseEvent* evt);
//    virtual void canvasWidgetMouseReleaseEvent(QMouseEvent* evt);
//    virtual void canvasWidgetMouseDoubleClickEvent(QMouseEvent* evt);
//    virtual void canvasWidgetMouseMoveEvent(QMouseEvent* evt);
   
};
#endif
