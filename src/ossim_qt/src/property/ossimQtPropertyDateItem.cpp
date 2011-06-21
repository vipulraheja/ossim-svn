//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// LICENSE: LGPL
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtPropertyDateItem.cpp 9114 2006-06-14 17:42:07Z gpotts $
#include "ossimQtPropertyDateItem.h"
#include "ossimQtPropertyListView.h"
#include <ossim/base/ossimDateProperty.h>
#include <qstringlist.h>

ossimQtPropertyDateItem::ossimQtPropertyDateItem(ossimQtPropertyListView *propList,
                                                 ossimQtPropertyItem *after,
                                                 ossimQtPropertyItem *parent,
                                                 ossimRefPtr<ossimProperty> oProp)
      :ossimQtPropertyItem(propList, after, parent, oProp),
       theDateTimeEditor(0)
{
   if(getOssimProperty().valid())
   {
      setText( 1, getOssimProperty()->valueToString().c_str());
   }
   else
   {
      setText( 1, "");
   }
}

ossimQtPropertyDateItem::~ossimQtPropertyDateItem()
{
   if(theDateTimeEditor)
   {
      delete theDateTimeEditor;
      theDateTimeEditor = 0;
   }
}

void ossimQtPropertyDateItem::showEditor()
{
   if(!getOssimProperty()) return;
   
   ossimQtPropertyItem::showEditor();
   ossimDateProperty* dateProperty = PTR_CAST(ossimDateProperty,
                                          getOssimProperty().get());
   if(dateProperty)
   {
      
      QTime time(dateProperty->getDate().getHour(),
                 dateProperty->getDate().getMin(),
                 dateProperty->getDate().getSec());
      QDate date(dateProperty->getDate().getYear(),
                 dateProperty->getDate().getMonth(),
                 dateProperty->getDate().getDay());
      
      QDateTime dateTime(date, time);
      
      dateTimeEditor()->blockSignals(TRUE);
      dateTimeEditor()->setDateTime(dateTime);
      dateTimeEditor()->blockSignals(FALSE);
      
      placeEditor(dateTimeEditor());
      
      dateTimeEditor()->show();
      dateTimeEditor()->setFocus();
   }
}

void ossimQtPropertyDateItem::hideEditor()
{
   ossimQtPropertyItem::hideEditor();
   if(theDateTimeEditor)
   {
      theDateTimeEditor->hide();
   }
}
   
QDateTimeEdit* ossimQtPropertyDateItem::dateTimeEditor()
{
   if(theDateTimeEditor)
   {
      return theDateTimeEditor;
   }
   if(getOssimProperty().valid())
   {
      ossimDateProperty* dateProperty = PTR_CAST(ossimDateProperty,
                                                 getOssimProperty().get());
      if(dateProperty)
      {
         
         theDateTimeEditor = new QDateTimeEdit(theListView);
         QTime time(dateProperty->getDate().getHour(),
                    dateProperty->getDate().getMin(),
                    dateProperty->getDate().getSec());
         QDate date(dateProperty->getDate().getYear(),
                    dateProperty->getDate().getMonth(),
                    dateProperty->getDate().getDay());
         
         QDateTime dateTime(date, time);
         dateTimeEditor()->setDateTime(dateTime);
         connect(theDateTimeEditor,
                 SIGNAL(valueChanged(const QDateTime& )),
                 this,
                 SLOT(valueChanged(const QDateTime&)));
      }
   }

   return theDateTimeEditor;
}

void ossimQtPropertyDateItem::returnPressed()
{
   setValue();
}

void ossimQtPropertyDateItem::setValue()
{
   QString value = dateTimeEditor()->dateTime().toString("yyyyMMddhhmmss");
   
   if(getOssimProperty().valid())
   {
      getOssimProperty()->setValue(value.ascii());
      
      setText(1, value);
      notifyValueChange();
   }
}

void ossimQtPropertyDateItem::resetProperty(bool notify)
{
   ossimQtPropertyItem::resetProperty(notify);
   ossimString value = getOssimProperty()->valueToString();
   
   setText(1, value.c_str());

   ossimDateProperty* dateProperty = PTR_CAST(ossimDateProperty,
                                              getOssimProperty().get());
   if(dateProperty)
   {
      QTime time(dateProperty->getDate().getHour(),
                 dateProperty->getDate().getMin(),
                 dateProperty->getDate().getSec());
      QDate date(dateProperty->getDate().getYear(),
                 dateProperty->getDate().getMonth(),
                 dateProperty->getDate().getDay());
                 
      QDateTime dateTime(date, time);
      
      
      dateTimeEditor()->blockSignals(TRUE);
      dateTimeEditor()->setDateTime(dateTime);
      dateTimeEditor()->blockSignals(FALSE);
   }
   
}

void ossimQtPropertyDateItem::valueChanged(const QDateTime& /* value */ )
{
   setValue();
}
