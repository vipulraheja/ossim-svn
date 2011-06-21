//----------------------------------------------------------------------------
// Copyright (C) 2004 David Burken, all rights reserved.
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// Description: OSSIM QT about dialog base class.
//
// $Id: ossimQtAboutDialogBase.h 7150 2004-12-28 21:50:45Z dburken $
//----------------------------------------------------------------------------
#ifndef ossimQtAboutDialogBase_HEADER
#define ossimQtAboutDialogBase_HEADER

#include <qdialog.h>
#include <qstring.h>

// Forward class declarations.
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QWidget;
class QComboBox;
class QCheckBox;
class QGroupBox;

class ossimQtAboutDialogBase : public QDialog
{
   Q_OBJECT

public:

   /** public constructor */
   ossimQtAboutDialogBase(QWidget* parent = 0,
                          const char* name = "ossimQtAboutDialogBase",
                          bool modal = false,
                          WFlags f = 0 );

   /** virtual destructor */
   virtual ~ossimQtAboutDialogBase();

   /**
    * @return The current version number as a QString in the format of
    * "Version 1.5 Release 6" where 1=major, 5=minor and 6=release.
    */
   virtual QString getVersionString() const;

public slots:

   /**
    * Slot connected to theCloseButton clicked signal.
    */
   virtual void closeClicked();

protected:

   QWidget*              theParent;
   QVBoxLayout*          theMainVBox;
   QHBoxLayout*          theHBox1;
   QHBoxLayout*          theHBox2;
   QHBoxLayout*          theHBox3;
   QPushButton*          theCloseButton;

private:
   /** Hide from use copy constructor. */
   ossimQtAboutDialogBase(const ossimQtAboutDialogBase& obj);

   /** Hide from use assignment operator. */
   const ossimQtAboutDialogBase& operator=(const ossimQtAboutDialogBase& rhs);
};

#endif /* End of "#ifndef ossimQtAboutDialogBase_HEADER" */
