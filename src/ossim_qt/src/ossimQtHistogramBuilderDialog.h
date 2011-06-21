//----------------------------------------------------------------------------
// Copyright (C) 2005 David Burken, all rights reserved.
//
// License:   See LICENSE.txt file in the top level directory.
//
// Author:  David Burken
//
// Description:  Dialog for building image histograms.
//
// $Id: ossimQtHistogramBuilderDialog.h 15766 2009-10-20 12:37:09Z gpotts $
//----------------------------------------------------------------------------
#ifndef ossimQtHistogramBuilderDialog_HEADER
#define ossimQtHistogramBuilderDialog_HEADER

#include <qdialog.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimHistogramWriter.h>
// Forward class declarations.
class ossimQtWindow;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QGroupBox;
class QHGroupBox;
class QPushButton;
class QSpacerItem;

class ossimQtHistogramBuilderDialog : public QDialog
{
   Q_OBJECT

public:

   /**
    * public constructor
    *
    * @note This does not contruct with destructive close flag so that
    * "exec()" can be called.  Same with all close calls do not use
    * destructive close(true).
    *
    * Callers should delete after using if a new was performed.
    */
   ossimQtHistogramBuilderDialog(QWidget* parent,
                                 ossimImageHandler* imageHandler);
   
   /** virtual destructor */
   virtual ~ossimQtHistogramBuilderDialog();
   
public slots:

   /**
    * Slot connected to theBuildButton clicked signal.
    */
   virtual void buildClicked();

   /**
    * Slot connected to the progress dialogs cancel clicked signal.
    */
   virtual void abortClicked();

   /**
    * Slot connected to theCloseButton clicked signal.
    */
   virtual void closeClicked();
   
protected:
   
   ossimRefPtr<ossimImageHandler>    theImageHandler;
   ossimRefPtr<ossimHistogramWriter> theWriter;

   QVBoxLayout*     theMainVBox;

   QHBoxLayout*     theHBox1;
   QGroupBox*       theSourceImageGroupBox;         
   QLabel*          theSourceImageLabel;

   QHBoxLayout*     theHBox2;
   QSpacerItem*     theSpacer1;
   QPushButton*     theBuildButton;
   QPushButton*     theCloseButton;

private:
   /** Hide from use copy constructor. */
   ossimQtHistogramBuilderDialog(const ossimQtHistogramBuilderDialog& obj);

   /** Hide from use assignment operator. */
   const ossimQtHistogramBuilderDialog& operator=(const ossimQtHistogramBuilderDialog& rhs);
};

#endif /* End of "#ifndef ossimQtHistogramBuilderDialog_HEADER" */
