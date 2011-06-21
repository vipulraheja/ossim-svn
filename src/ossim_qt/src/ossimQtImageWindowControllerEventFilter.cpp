//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtImageWindowControllerEventFilter.cpp 15766 2009-10-20 12:37:09Z gpotts $
#include <qapplication.h>
#include <qevent.h>
#include <ossimQtImageWindowControllerEventFilter.h>
#include <ossimQtImageWindowController.h>
#include <ossimQtApplicationUtility.h>
#include <ossimQtSwipeScrollingImageWidget.h>
#include <ossimQtImageWindow.h>

void ossimQtImageControllerPanEventFilter::scrollingImageWidgetMouseEvent(
   ossimQtMouseEvent* event)
{
   if (!theController) return;
   
   if(event->getQtEventType() == QEvent::MouseButtonRelease)
   {
      ossimIpt pt = event->getShiftPoint();
      theController->panTo(pt);
   }
   
   return;
}

void ossimQtImageControllerZoomEventFilter::scrollingImageWidgetMouseEvent(
   ossimQtMouseEvent* event)
{
   if (!theController) return;
   
   switch(event->getQtEventType())
   {
      case QEvent::MouseButtonRelease:
      {
         if(!thePanToOverrideFlag)
         {
            ossimIrect regionOfInterest = theAnnotator.getShiftedRoiRect();

            theController->zoomTo(regionOfInterest.ul(),
                                  regionOfInterest.lr());
         }
         else
         {
	    theController->panTo(event->getShiftPoint());
         }

         // Get rid of the box that was drawn.
         theAnnotator.clear();
         
         break;
      }
      default:
      {
         break;
      }
   }
}

bool ossimQtImageControllerZoomEventFilter::eventFilter(QObject* /*obj*/,
                                                        QEvent* event)
{
   if(!theController) return false;
   
   if(!theController->getImageWidget()) return false;
   
   switch(event->type())
   {
      case QEvent::KeyPress:
      {
         QKeyEvent* keyEvent = (QKeyEvent*)event;
         if(keyEvent->stateAfter() & Qt::ShiftButton)
         {
	    theController->setZoomModeOut();
         }
         if(keyEvent->stateAfter() & Qt::ControlButton)
         {
            thePanToOverrideFlag = true;
         }
         break;
      }
      case QEvent::KeyRelease:
      {
         QKeyEvent* keyEvent = (QKeyEvent*)event;
         if(keyEvent->state() & Qt::ShiftButton)
         {
            theController->setZoomModeIn();
         }
         if(keyEvent->state() & Qt::ControlButton)
         {
            thePanToOverrideFlag = false;
         }
         break;
      }
      default:
      {
         break;
      }
   }
   
   return false;
}

ossimQtImageControllerOssimEventCapture::~ossimQtImageControllerOssimEventCapture()
{
//   for(int idx = 0; idx < getNumberOfInputs(); ++idx)
//     {
//       if(getInput(idx))
// 	{
// 	  getInput(idx)->removeListener((ossimConnectableObjectListener*)this);
// 	}
//     }
   removeListener((ossimConnectableObjectListener*)this);
   removeListener((ossimDisplayEventListener*)this);
   theController = NULL;
   ossimConnectableObject::disconnect();
   ossimReferenced::unref_nodelete();
}


void ossimQtImageControllerOssimEventCapture::connectInputEvent(ossimConnectionEvent& /*event*/)
{
//   if(event.getNewObject())
//     {
//       event.getNewObject()->removeListener((ossimConnectableObjectListener*)this);
//       event.getNewObject()->addListener((ossimConnectableObjectListener*)this);
//     }
}

void ossimQtImageControllerOssimEventCapture::disconnectInputEvent(ossimConnectionEvent& /*event*/)
{
  
//   if(event.getOldObject())
//     {
//       event.getOldObject()->removeListener((ossimConnectableObjectListener*)this);
//     }

  if(!theController||!theController->getImageWindow())
    {
      return;
    }
  if(!isConnected())
    {
      removeListener((ossimConnectableObjectListener*)this);
      removeListener((ossimDisplayEventListener*)this);
      
      if(theController->getAutoDeleteIfNoInputFlag())
	{
	  QCloseEvent* closeEvent = new QCloseEvent;
	  QApplication::postEvent(theController->getImageWindow(), closeEvent);
	  theController = NULL;
	}
    }
  else
    {
      ossimConnectableObjectListener::disableListener();
      theController->initializePointers();
      theController->initializeMenus();
      QApplication::postEvent(theController->getImageWindow(),
			    new ossimQtRefreshDisplayEvent);
      ossimConnectableObjectListener::enableListener();
    }
}

void ossimQtImageControllerOssimEventCapture::objectDestructingEvent(
   ossimObjectDestructingEvent& event)
{
   if(event.getObject())
   {
      ossimConnectableObject* obj = PTR_CAST(ossimConnectableObject, event.getObject());
      if(obj)
      {
         obj->removeListener((ossimConnectableObjectListener*)this);
      }
   }
   if(!theController||!theController->getImageWindow())
   {
      return;
   }
   if(getInput(1))
   {
      if(event.getObject() == getInput(1))
      {
         ossimConnectableObjectListener::disableListener();
         theController->removeInput(PTR_CAST(ossimConnectableObject,event.getObject()));
         ossimConnectableObjectListener::enableListener();
      }
   }
}

void ossimQtImageControllerOssimEventCapture::displayListEvent(
   ossimDisplayListEvent& event)
{
   if(theController)
   {
      event.addDisplay(theController->getImageWindow());
   }
}

ossimString ossimQtImageControllerOssimEventCapture::getClassName() const
{
   return "ossimQtImageControllerOssimEventCapture";
}

ossimQtImageControllerZoomEventFilter::ossimQtImageControllerZoomEventFilter(
   ossimQtImageWindowController* controller)
   : theController(controller),
     thePanToOverrideFlag(false),
     theAnnotator()
{
   if (theController)
   {
      theAnnotator.setImageWidget(theController->getImageWidget());
   }
}

ossimQtImageControllerPanEventFilter::ossimQtImageControllerPanEventFilter(
   ossimQtImageWindowController* controller)
   : theController(controller)
{
}

ossimQtImageControllerOssimEventCapture::ossimQtImageControllerOssimEventCapture(
   ossimQtImageWindowController* imageWindow)
   :ossimConnectableObject(NULL, 1, 0, false, false),
    theController(imageWindow)
{
   ossimReferenced::ref();
   addListener((ossimConnectableObjectListener*)this);
   addListener((ossimDisplayEventListener*)this);
}

bool ossimQtImageControllerOssimEventCapture::canConnectMyInputTo(
   ossim_int32 /*myInputIndex*/, const ossimConnectableObject* /* object */)const
{
   return true;
}
void ossimQtImageControllerOssimEventCapture::propertyEvent(
   ossimPropertyEvent& /* event */)
{
}

void ossimQtImageControllerZoomEventFilter::enableAnnotator()
{
   theAnnotator.enablePaint();
}

void ossimQtImageControllerZoomEventFilter::disableAnnotator()
{
   theAnnotator.disablePaint();
}
