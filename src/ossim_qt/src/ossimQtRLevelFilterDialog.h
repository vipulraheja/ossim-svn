//----------------------------------------------------------------------------
// Copyright (C) 2004 David Burken, all rights reserved.
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// Description: Property editor dialog for ossimRLevelFilter.
//
// $Id: ossimQtRLevelFilterDialog.h 9114 2006-06-14 17:42:07Z gpotts $
//----------------------------------------------------------------------------
#ifndef ossimQtRLevelFilterDialog_HEADER
#define ossimQtRLevelFilterDialog_HEADER

#include <qdialog.h>
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimObjectDestructingEvent.h>

// Forward class declarations.
class ossimRLevelFilter;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QWidget;
class QComboBox;
class QCheckBox;
class QGroupBox;

class ossimQtRLevelFilterDialog :
   public QDialog,
   public ossimConnectableObjectListener
{
   Q_OBJECT

public:

   /** public constructor */
   ossimQtRLevelFilterDialog(QWidget* parent = 0,
                             const char* name = "ossimQtRLevelFilterDialog",
                             bool modal = false,
                             WFlags f = 0 );

   /** virtual destructor */
   virtual ~ossimQtRLevelFilterDialog();

   /**
    * Method to catch destruction event sent by the ossimRLevelFilter.
    */
   virtual void objectDestructingEvent(ossimObjectDestructingEvent& event);

   void setRLevelFilter(ossimRLevelFilter* filter);

public slots:

   /**
    * Slot connected to theOutputImageField selection changed signal.
    */
   virtual void rlevelChanged(int level);

   /**
    * Slot connected to theOutputImageButton clicked signal.
    */
   virtual void enableClicked();

   /**
    * Slot connected to theCloseButton clicked signal.
    */
   virtual void closeClicked();

protected:

   QWidget*              theParent;
   ossimRLevelFilter*    theFilter;

   QVBoxLayout*          theMainVBox;

   QHBoxLayout*          theHBox1;
   QGroupBox*            theRLevelGroupBox;
   QComboBox*            theRLevelMenu;

   QHBoxLayout*          theHBox2;
   QGroupBox*            theEnableGroupBox;
   QCheckBox*            theEnableCheckBox;

   QHBoxLayout*          theHBox3;
   QPushButton*          theCloseButton;

private:
   /** Hide from use copy constructor. */
   ossimQtRLevelFilterDialog(const ossimQtRLevelFilterDialog& obj);

   /** Hide from use assignment operator. */
   const ossimQtRLevelFilterDialog& operator=(const ossimQtRLevelFilterDialog& rhs);

   void buildRLevelMenu()  const;
   void updateEnableMenu() const;
   void updateRLevelMenu() const;
};

#endif /* End of "#ifndef ossimQtRLevelFilterDialog_HEADER" */
