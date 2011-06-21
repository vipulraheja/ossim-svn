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
// $Id: ossimQtPropertyBooleanItem.h 7415 2005-04-26 14:34:03Z dburken $
#ifndef ossimQtPropertyBooleanItem_HEADER
#define ossimQtPropertyBooleanItem_HEADER
#include <qguardedptr.h>
#include <qcheckbox.h>
#include "ossimQtPropertyItem.h"

class ossimQtPropertyBooleanItem : public ossimQtPropertyItem
{
   Q_OBJECT
public:
   ossimQtPropertyBooleanItem(ossimQtPropertyListView *propList,
                          ossimQtPropertyItem *after,
                          ossimQtPropertyItem *parent,
                          ossimRefPtr<ossimProperty> oProp);
   virtual ~ossimQtPropertyBooleanItem();
   
   virtual void showEditor();
   virtual void hideEditor();
   virtual void toggle();
   virtual void setValue( const QVariant &v );
   virtual void updateGUI();
   

protected slots:
   void setValue();
   virtual void resetProperty(bool notify=true);

protected:
   QCheckBox* checkBox();
   QGuardedPtr<QCheckBox> theCheckBox;
};

#endif
