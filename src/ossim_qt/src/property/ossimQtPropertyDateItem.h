//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// LICENSE: LGPL see top level LICENSE.txt
//
// Author: Garrett Potts (gpotts@imagelinks.com)
//
//*************************************************************************
// $Id: ossimQtPropertyDateItem.h 6785 2004-09-23 17:18:03Z gpotts $
#ifndef ossimQtPropertyDateItem_HEADER
#define ossimQtPropertyDateItem_HEADER
#include <qguardedptr.h>
#include <qhbox.h>
#include <qdatetimeedit.h>
#include "ossimQtPropertyItem.h"

class ossimQtPropertyDateItem : public ossimQtPropertyItem
{
   Q_OBJECT
public:
   ossimQtPropertyDateItem(ossimQtPropertyListView *propList,
                             ossimQtPropertyItem *after,
                             ossimQtPropertyItem *parent,
                             ossimRefPtr<ossimProperty> oProp);
   virtual ~ossimQtPropertyDateItem();
   virtual void showEditor();
   virtual void hideEditor();
   
protected:
   QDateTimeEdit* theDateTimeEditor;

   QDateTimeEdit* dateTimeEditor();

public slots:
   virtual void returnPressed();
   virtual void setValue();
   virtual void valueChanged(const QDateTime& value);
   virtual void resetProperty(bool notify = true);

};

#endif
