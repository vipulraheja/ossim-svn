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
// $Id: ossimQtPropertyListView.h 9114 2006-06-14 17:42:07Z gpotts $
#ifndef ossimQtPropertyListView_HEADER
#define ossimQtPropertyListView_HEADER
#include <qlistview.h>
#include <ossim/base/ossimRefPtr.h>
class ossimObject;
class ossimQtPropertyItem;
class ossimProperty;

class ossimQtPropertyListView : public QListView
{
   Q_OBJECT
public:
   ossimQtPropertyListView(QWidget* parent = 0,
                           const char* name = 0,
                           WFlags flags = 0);

   /*!
    * Will set the object and then call transfer to
    * window.
    */
   virtual void setObject(ossimObject* obj);

   /*!
    * Will clear the list and transfer the objects properties to the window.
    * works like a refresh.
    */
   virtual void transferToWindow();

   /*!
    * Transferred the changed properties only and
    * to the internally stored object.
    */
   virtual void transferFromWindow();

   virtual void setAutoApplyFlag(bool flag);
   virtual bool getAutoApplyFlag()const;

   const QColor& getBackgroundColor1()const;
   const QColor& getBackgroundColor2()const;
   const QColor& getSelectedBackgroundColor()const;
   virtual void setCurrentItem(QListViewItem *i);
   virtual void valueChanged( ossimQtPropertyItem *i );
   
protected:
   ossimObject* theObject;
   bool         theAutoApplyFlag;
   QColor       theBackgroundColor1;
   QColor       theBackgroundColor2;
   QColor       theSelectedBackgroundColor;
   
   virtual void resizeEvent(QResizeEvent *e);
   virtual void setProperty(ossimRefPtr<ossimProperty> prop);

   /**
    * Loops through all ossimQtPropertyItems held in list and
    * refreshes the GUI properties from the filter(s) or object(s) that
    * originally populated the properties.  Called at the end of setProperty
    * to ensure that other properties are up to date after setting a given
    * property.
    */
   virtual void refreshGUI();
   
public slots:
   void updateEditorSize();
   void resetProperty();
   void resetAllProperties();
   void applyProperty();
   void applyAllProperties();
   void toggleOpen( QListViewItem *i );
   void itemPressed( QListViewItem *i, const QPoint &p, int c );

   
};

#endif
