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
// $Id: ossimQtVceImageDisplayObject.cpp 15766 2009-10-20 12:37:09Z gpotts $
#include <qpainter.h>
#include <qevent.h>
#include <qapplication.h>
#include "ossimQtVceImageDisplayObject.h"
#include "ossimQtImageWindow.h"
#include <ossim/imaging/ossimImageSource.h>
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimDisplayEventListener.h>
#include <ossim/base/ossimDisplayListEvent.h>
#include "ossimQtEvent.h"
#include "ossimQtApplicationUtility.h"
#include "ossimQtProject.h"
#include "ossimQtImageWindow.h"
#include "ossimQtImageWindowController.h"
#include "ossimQtVceConnectionObject.h"
#include "ossimQtMainWindowWorkspace.h"

class ossimQtVceImageDisplayObjectPrivateEventFilter : public QObject
{
public: 
   ossimQtVceImageDisplayObjectPrivateEventFilter(ossimQtVceImageDisplayObject* obj)
      :theDisplayComponent(obj)
      {
      }
   
protected:
   bool eventFilter( QObject *o, QEvent *e )
      {
         if(o == theDisplayComponent->theDisplay)
         {
            if(e->type() == QEvent::Close)
            {
               theDisplayComponent->displayClosed();
            }
         }
         
         return false;
      }
   
   ossimQtVceImageDisplayObject* theDisplayComponent; 
};

class ossimQtVceImageDisplayObjectPrivateConnectable : public ossimConnectableObject,
                                                       public ossimConnectableObjectListener,
                                                       public ossimDisplayEventListener
{
public:
  ossimQtVceImageDisplayObjectPrivateConnectable(ossimQtVceImageDisplayObject* obj)
    :ossimConnectableObject(NULL,
			    2,
			    0,
			    true,
			    true),
     theDisplayComponent(obj)
  {
     addListener((ossimConnectableObjectListener*)this);
     addListener((ossimDisplayEventListener*)this);
  }
   virtual ~ossimQtVceImageDisplayObjectPrivateConnectable()
      {
         removeListener((ossimConnectableObjectListener*)this);
         removeListener((ossimDisplayEventListener*)this);
      }
   virtual bool canConnectMyInputTo(ossim_int32 myInputIndex,
                                    const ossimConnectableObject* object)const
  {
     return ((PTR_CAST(ossimImageSource,
                       object)||!object)&&(myInputIndex < 2));
  }
   virtual void disconnectInputEvent(ossimConnectionEvent& /*event*/ )
      {
         if(!theDisplayComponent) return;
         if(theDisplayComponent->theDisplay)
         {
            theDisplayComponent->theDisplay->controller()->disconnectAllInputs();
            if(getInput(0))
            {
               theDisplayComponent->theDisplay->controller()->addInput(getInput(0));
            }
            if(getInput(1))
            {
               theDisplayComponent->theDisplay->controller()->addInput(getInput(1));
            }
         }
      }
   virtual void connectInputEvent(ossimConnectionEvent& /*event*/ )
      {
         if(!theDisplayComponent) return;
         
         
         if(!theDisplayComponent->theDisplay)
         {
            ossimQtGetProjectEvent evt;
            ossimQtApplicationUtility::sendEventToRoot(theDisplayComponent->theVceParent, &evt);
            
            if(evt.getProject())
            {
               if(evt.getProject()->getWorkspace())
               {
                  theDisplayComponent->theDisplay = new ossimQtImageWindow(evt.getProject()->getWorkspace(), 0, 
                                                                           Qt::WDestructiveClose);
                  theDisplayComponent->theDisplay->installEventFilter(theDisplayComponent->theQtEventFilter);
                  theDisplayComponent->theDisplay->controller()->setAutoDeleteIfNoInputFlag(false);
               }
            }
         }
         else
         {
            theDisplayComponent->theDisplay->controller()->disconnectAllInputs();
         }
         
         if(theDisplayComponent->theDisplay)
         {
            for(int idx = 0; idx < (int)getNumberOfInputs();++idx)
            {
               if(getInput(idx))
               {
                  theDisplayComponent->theDisplay->controller()->addInput(getInput(idx));
               }
            }
            theDisplayComponent->theDisplay->show();
         }
      }
   virtual void displayListEvent(ossimDisplayListEvent& event)
      {
         if(!theDisplayComponent) return;
         if(theDisplayComponent->theDisplay)
         {
            event.addDisplay(theDisplayComponent->theDisplay);
         }
      }
  
   ossimQtVceImageDisplayObject* theDisplayComponent;
};

ossimQtVceImageDisplayObject::ossimQtVceImageDisplayObject(QCanvas* canvas,
							   QObject* vceParent)
   :ossimQtVceImageSourceObject(canvas,
				vceParent)
{
   setConnectableObject(new ossimQtVceImageDisplayObjectPrivateConnectable(this));
   
   theDisplay = NULL;
   thePixmap = QPixmap::fromMimeSource("display");
   theQtEventFilter = new ossimQtVceImageDisplayObjectPrivateEventFilter(this);

   theWidth  = thePixmap.width() + 2*theConnectorSize.width();
   theHeight = thePixmap.height() + 2*theConnectorSize.height();
}

ossimQtVceImageDisplayObject::~ossimQtVceImageDisplayObject()
{
   hide();

   // need double cast to align he base pointer offsets correctly
   // First cast to the PrivateConnectable and then cast to the listener
   //
   theConnectableObject->removeListener((ossimConnectableObjectListener*)(ossimQtVceImageDisplayObjectPrivateConnectable*)theConnectableObject.get());
   theConnectableObject->removeListener((ossimDisplayEventListener*)(ossimQtVceImageDisplayObjectPrivateConnectable*)theConnectableObject.get());
   ((ossimQtVceImageDisplayObjectPrivateConnectable*)theConnectableObject.get())->theDisplayComponent = NULL;
   
   if(theDisplay)
   {
      if(theQtEventFilter)
      {
         theDisplay->removeEventFilter(theQtEventFilter);
      }
      theDisplay->controller()->disconnectAllInputs();
//       QCloseEvent* closeEvent = new QCloseEvent();
//       QApplication::postEvent(theDisplay, closeEvent);
      theDisplay->close(true);
      theDisplay = NULL;
   }
   
   if(theQtEventFilter)
   {
      delete theQtEventFilter;
      theQtEventFilter = NULL;
   }

   // we will let the base class delete the connectable object
   // allocated in the constructor.
   //
}

int ossimQtVceImageDisplayObject::rtti()const
{
   return ossimQtVceShapeRttiType_IMAGE_DISPLAY;
}


void ossimQtVceImageDisplayObject::drawShape(QPainter& painter)
{
   QRect bounds = boundingVceShapeRect();
   QPoint tempPt(bounds.x() + bounds.width()/2,
		 bounds.y() + bounds.height()/2);
   
   painter.drawPixmap(tempPt.x() - thePixmap.width()/2, 
		      tempPt.y() - thePixmap.height()/2, 
                      thePixmap);
}

void ossimQtVceImageDisplayObject::displayClosed()
{
   theDisplay = NULL;
}


bool ossimQtVceImageDisplayObject::connectInternalObjectsInputTo(std::vector<ossimConnectableObject*>& inputList)
{
   // need double cast to align he base pointer offsets correctly
   // First cast to the PrivateConnectable and then cast to the listener
   //
   theConnectableObject->removeListener((ossimConnectableObjectListener*)(ossimQtVceImageDisplayObjectPrivateConnectable*)theConnectableObject.get());
   theConnectableObject->removeListener((ossimDisplayEventListener*)(ossimQtVceImageDisplayObjectPrivateConnectable*)theConnectableObject.get());
   if(inputList.size() == 0)
   {
      if(theDisplay)
      {
         theDisplay->close(true);
      }
   }
   else
   {
      bool needDisplay = false;
      if(inputList.size() > 0)
      {
         if(inputList[0])
         {
            needDisplay = true;
         }
                          
      }
      if(inputList.size() > 1)
      {
         if(inputList[1])
         {
            needDisplay = true;
         }
      }

      if(needDisplay)
      {
         if(!theDisplay)
         {
            ossimQtGetProjectEvent evt;
            ossimQtApplicationUtility::sendEventToRoot(theVceParent, &evt);
            
            if(evt.getProject())
            {
               if(evt.getProject()->getWorkspace())
               {
                  theDisplay = new ossimQtImageWindow(evt.getProject()->getWorkspace(), 0, 
                                                      Qt::WDestructiveClose);
                  theDisplay->installEventFilter(theQtEventFilter);
                  theDisplay->controller()->setAutoDeleteIfNoInputFlag(false);
               }
            }
         }
         else
         {
            theDisplay->controller()->disconnectAllInputs();
         }

         if(theDisplay)
         {
            theConnectableObject->disconnectAllInputs();
            for(int idx = 0; idx < (int)inputList.size(); ++idx)
            {
               if(inputList[idx])
               {
                  theConnectableObject->connectMyInputTo(inputList[idx]);
                  theDisplay->controller()->addInput(inputList[idx]);
               }
            }
            theDisplay->show();
         }
      }
      else
      {
         if(theDisplay)
         {
            theDisplay->close(true);
         }
      }
   }
   
   // need double cast to align he base pointer offsets correctly
   // First cast to the PrivateConnectable and then cast to the listener
   //
   theConnectableObject->addListener((ossimConnectableObjectListener*)(ossimQtVceImageDisplayObjectPrivateConnectable*)theConnectableObject.get());
   theConnectableObject->addListener((ossimDisplayEventListener*)(ossimQtVceImageDisplayObjectPrivateConnectable*)theConnectableObject.get());

   return true;
}

bool ossimQtVceImageDisplayObject::saveState(ossimKeywordlist& kwl,
                                             const char* prefix)const
{
   ossimQtVceImageSourceObject::saveState(kwl, prefix);

   kwl.add(prefix,
           ossimKeywordNames::TYPE_KW,
           "ossimQtVceImageDisplayObject",
           true);
   
   return true;
}

bool ossimQtVceImageDisplayObject::loadState(const ossimKeywordlist& kwl,
                                             const char* prefix)
{
   return ossimQtVceImageSourceObject::loadState(kwl, prefix);
}
