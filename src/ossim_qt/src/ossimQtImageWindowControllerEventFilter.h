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
// $Id: ossimQtImageWindowControllerEventFilter.h 9114 2006-06-14 17:42:07Z gpotts $
#ifndef ossimQtImageWindowControllerEventFilter_HEADER
#define ossimQtImageWindowControllerEventFilter_HEADER
#include <qobject.h>
#include <ossimQtEvent.h>
#include <ossimQtRoiRectAnnotator.h>
#include <ossim/base/ossimPropertyEvent.h>
#include <ossim/base/ossimDisplayListEvent.h>
#include <ossim/base/ossimDisplayEventListener.h>
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimViewInterface.h>
#include <ossim/base/ossimConnectableObject.h>

class ossimQtImageWindowController;

class ossimQtImageControllerZoomEventFilter : public QObject
{
   Q_OBJECT   
public:
   ossimQtImageControllerZoomEventFilter(
      ossimQtImageWindowController* controller);

   virtual bool eventFilter(QObject* obj, QEvent* event);

   /** Enables box drawing. */
   void enableAnnotator();

   /** Disables box drawing. */
   void disableAnnotator();

public slots:
   void scrollingImageWidgetMouseEvent(ossimQtMouseEvent* event);
   
protected:
   ossimQtImageWindowController* theController;
   bool                          thePanToOverrideFlag;
   ossimQtRoiRectAnnotator       theAnnotator;
};

class ossimQtImageControllerPanEventFilter : public QObject
{
   Q_OBJECT   
public:
   ossimQtImageControllerPanEventFilter(ossimQtImageWindowController* controller);

public slots:
    void scrollingImageWidgetMouseEvent(ossimQtMouseEvent* event);
   
protected:
    ossimQtImageWindowController* theController;
};

class ossimQtImageControllerOssimEventCapture:public ossimConnectableObject,
                                              public ossimConnectableObjectListener,
					      public ossimDisplayEventListener
{
public:
   ossimQtImageControllerOssimEventCapture(ossimQtImageWindowController* imageWindow);
   
   virtual ~ossimQtImageControllerOssimEventCapture();
   
   virtual bool canConnectMyInputTo(ossim_int32 /*myInputIndex*/,
                                    const ossimConnectableObject* object)const;
   
   virtual void objectDestructingEvent(ossimObjectDestructingEvent& event);
   
   virtual void disconnectInputEvent(ossimConnectionEvent& event);
   
   virtual void connectInputEvent(ossimConnectionEvent& event);
   virtual void displayListEvent(ossimDisplayListEvent& event);
   virtual void propertyEvent(ossimPropertyEvent& event);
   virtual ossimString getClassName() const;
   
protected:
   ossimQtImageWindowController* theController;
};

#endif

