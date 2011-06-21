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
// $Id: ossimQtVceWindowController.cpp 9049 2006-05-08 20:16:29Z dburken $
#include <qcanvas.h>
#include <qtoolbutton.h>
#include <qdragobject.h>
#include <qiconview.h>
#include <sstream>
#include "ossimQtVceWindowController.h"
#include "ossimQtVceWindow.h"
#include "ossimQtVceCanvasWidget.h"
#include "ossimQtVceImageSourceObject.h"
#include "ossimQtVceConnectionObject.h"
#include "ossimQtEvent.h"
#include "ossimQtVceComponentDialog.h"

ossimQtVceWindowController::ossimQtVceWindowController(ossimQtVceWindow* window)
{
   theVceWindow = window;
   theCanvas = NULL;
   if(theVceWindow)
   {
      theCanvas = new QCanvas();
      theVceWindow->theCanvasView->setCanvas(theCanvas);
      theVceWindow->theCanvasView->canvas()->setUpdatePeriod(30);

      theVceWindow->theCanvasView->resizeContents(4000, 4000);
      theVceWindow->theCanvasView->canvas()->retune(64);
   }
}

ossimQtVceWindowController::~ossimQtVceWindowController()
{
   if(theCanvas)
   {
      delete theCanvas;
      theCanvas = NULL;
   }
}

void ossimQtVceWindowController::customEvent(QCustomEvent* event)
{
   switch(event->type())
   {
   case OSSIM_QT_EVENT_STATE_EVENT:
   {
      ossimQtStateEvent* stateEvent = (ossimQtStateEvent*)event;
      
      if(stateEvent)
      {
         ossimKeywordlist& kwl = stateEvent->getKeywordlist();
          if(stateEvent->getStateType() == ossimQtStateEvent::ossimQtStateEventType_SAVE)
          {
             saveState(kwl, stateEvent->getPrefix());
          }
          else
          {
             loadState(kwl, stateEvent->getPrefix());
          }
      }
      break;
   }
   default:
     {
       break;
     }
   }
}

void ossimQtVceWindowController::cutSelectedObjects()
{
   if(theVceWindow)
   {
      theVceWindow->theCanvasView->cutSelected();
   }
}

void ossimQtVceWindowController::copySelectedObjects()
{
   if(theVceWindow)
   {
      theVceWindow->theCanvasView->copySelected();
   }
}

void ossimQtVceWindowController::selectAll()
{
   if(theVceWindow)
   {
      theVceWindow->theCanvasView->selectAll();
   }
}

void ossimQtVceWindowController::paste()
{
   if(theVceWindow)
   {
      theVceWindow->theCanvasView->paste();
   }
}

void ossimQtVceWindowController::alignLeft()
{
   if(theVceWindow)
   {
      theVceWindow->theCanvasView->alignSelectedToLeft();
   }
}

void ossimQtVceWindowController::alignRight()
{
   if(theVceWindow)
   {
      theVceWindow->theCanvasView->alignSelectedToRight();
   }
}

void ossimQtVceWindowController::alignTop()
{
   if(theVceWindow)
   {
      theVceWindow->theCanvasView->alignSelectedToTop();
   }
}

void ossimQtVceWindowController::alignBottom()
{
   if(theVceWindow)
   {
      theVceWindow->theCanvasView->alignSelectedToBottom();
   }
}

void ossimQtVceWindowController::closeEvent(QCloseEvent* evt)
{
   evt->accept();
   theVceWindow->close(true);
}

bool ossimQtVceWindowController::saveState(ossimKeywordlist& kwl,
                                           const char* prefix)const
{
   if(theVceWindow)
   {
      kwl.add(prefix,
              ossimKeywordNames::TYPE_KW,
              "ossimQtVceWindow",
              true);
      QWidget* widget = theVceWindow->parentWidget(true);
      QPoint pt(widget->pos());
      
      kwl.add(prefix,
              "position",
              ossimString::toString((int)pt.x()) + " " + ossimString::toString((int)pt.y()),
              true);
      
      kwl.add(prefix,
              "size",
              ossimString::toString((int)theVceWindow->width()) + " " + ossimString::toString((int)theVceWindow->height()),
              true);
      
      ossimString showState = "shown";
      if(theVceWindow->isMinimized())
      {
         showState = "minimized";
      }
      else if(theVceWindow->isMaximized())
      {
         showState = "maximized";
      }
      else if(theVceWindow->isHidden())
      {
         showState = "hidden";
      }
   
   kwl.add(prefix,
           "show_state",
           showState,
           true);
      return theVceWindow->theCanvasView->saveState(kwl, (ossimString(prefix)+"canvas_view0.").c_str());
   }
   
   return false;
}

bool ossimQtVceWindowController::loadState(const ossimKeywordlist& kwl,
                                           const char* prefix)
{
   if(theVceWindow)
   {
      theVceWindow->theCanvasView->loadState(kwl,
                                             (ossimString(prefix)+"canvas_view0.").c_str());
      ossimString position = kwl.find(prefix,
                                      "position");
      if(position == "")
      {
         position = "0 0";
      }
      ossimString size = kwl.find(prefix,
                                  "size");
      if(size == "")
      {
         size = "512 512";
      }
      ossimString dimensions = position + " " + size;
      int x, y, w, h;
      
      std::istringstream iDimensions(dimensions.c_str());
      iDimensions >> x >> y >> w >> h;
      
      theVceWindow->setGeometry(x,y,w,h);
      
      ossimString showState = kwl.find(prefix, "show_state");
      if(showState == "minimized")
      {
         theVceWindow->showMinimized();
      }
      else if(showState == "maximized")
      {
         theVceWindow->showMaximized();
      }
      else if(showState == "hidden")
      {
         theVceWindow->hide();
      }
      else
      {
         theVceWindow->show();
      }
      
      return true;
   }
   
   return false;
}
