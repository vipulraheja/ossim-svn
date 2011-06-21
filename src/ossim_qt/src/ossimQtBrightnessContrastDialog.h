//----------------------------------------------------------------------------
// Copyright (C) 2005 David Burken, all rights reserved.
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// Description: Custom dialog for ossimBrightnessContrastSource.
//
//----------------------------------------------------------------------------
// $Id: ossimQtBrightnessContrastDialog.h 9114 2006-06-14 17:42:07Z gpotts $
#ifndef ossimQtBrightnessContrastDialog_HEADER
#define ossimQtBrightnessContrastDialog_HEADER

#include <qdialog.h>
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimObjectDestructingEvent.h>

// Forward class declarations.
class ossimBrightnessContrastSource;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QWidget;
class QComboBox;
class QCheckBox;
class QGroupBox;
class QLabel;
class QSlider;

class ossimQtBrightnessContrastDialog :
   public QDialog,
   public ossimConnectableObjectListener
{
   Q_OBJECT

public:
   
   /** public constructor */
   ossimQtBrightnessContrastDialog(
      QWidget* parent = 0,
      const char* name = "ossimQtBrightnessContrastDialog",
      bool modal = false,
      WFlags f = 0 );

   /** virtual destructor */
   virtual ~ossimQtBrightnessContrastDialog();
   
   /**
    * Method to catch destruction event sent by the ossimRLevelFilter.
    */
   virtual void objectDestructingEvent(ossimObjectDestructingEvent& event);

   /**
    * @param filter ossimBrightnessContrastSource filter to control.
    */
   void setFilter(ossimBrightnessContrastSource* filter);

public slots:

   /**
    * Slot connected to brightness slider.
    */
   virtual void brightnessSliderChanged(int value);

   /**
    * Slot connected to contrast slider.
    */
   virtual void contrastSliderChanged(int value);

   /**
    * Slot connected to theOutputImageButton clicked signal.
    */
   virtual void enableClicked();

   /**
    * Slot connected to theResetButton clicked signal.
    */
   virtual void resetClicked();
   

   /**
    * Slot connected to theCloseButton clicked signal.
    */
   virtual void closeClicked();

protected:

   QWidget*                       theParent;
   ossimBrightnessContrastSource* theFilter;

   QVBoxLayout*                   theMainVBox;

   QHBoxLayout*                   theHBox1;
   QLabel*                        theBrightnessLabel;
   QSlider*                       theBrightnessSlider;
   QLabel*                        theBrightnessValueLabel;
   
   QHBoxLayout*                   theHBox2;
   QLabel*                        theContrastLabel;
   QSlider*                       theContrastSlider;
   QLabel*                        theContrastValueLabel;

   QHBoxLayout*                   theHBox3;
   QCheckBox*                     theEnableCheckBox;
   QPushButton*                   theResetButton;
   QPushButton*                   theCloseButton;

private:

   void updateDialog()          const;
   void updateEnableMenu()       const;
   void updateBrightnessSlider() const;
   void updateContrastSlider()   const;
   
   /** Hide from use copy constructor. */
   ossimQtBrightnessContrastDialog(const ossimQtBrightnessContrastDialog& obj);

   /** Hide from use assignment operator. */
   const ossimQtBrightnessContrastDialog& operator=(const ossimQtBrightnessContrastDialog& rhs);


   
};

#endif /* End of "#ifndef ossimQtBrightnessContrastDialog_HEADER" */
