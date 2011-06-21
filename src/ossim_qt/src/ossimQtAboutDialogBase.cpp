//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: OSSIM QT about dialog base class.
//
// $Id: ossimQtAboutDialogBase.cpp 11812 2007-10-05 20:02:18Z dburken $
//----------------------------------------------------------------------------

#include <qvbox.h>
#include <qhbox.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qsizepolicy.h>
#include <qcombobox.h>
#include <qhgroupbox.h>
#include <ossimQtAboutDialogBase.h>
#include <ossim/init/ossimInit.h>
#include <ossim/base/ossimString.h>

ossimQtAboutDialogBase::ossimQtAboutDialogBase(QWidget* parent,
                                               const char* name,
                                               bool modal,
                                               WFlags f)
   : QDialog( parent, name, modal, (f|WDestructiveClose) ),
     theParent(parent),
     theMainVBox(NULL),
     theHBox1(NULL),
     theHBox2(NULL),
     theHBox3(NULL),
     theCloseButton(NULL)
{
   setCaption("About OSSIM");

   // Main vertical box.
   theMainVBox = new QVBoxLayout(this);

   // First row, holds the pixmap.
   theHBox1 = new QHBoxLayout(theMainVBox);
   
   // Second row, holds the text.
   theHBox2 = new QHBoxLayout(theMainVBox);

   // Third row, holds the close button.
   theHBox3 = new QHBoxLayout(theMainVBox);

   QSpacerItem* leftSpacer = new QSpacerItem( 10,
                                              10,
                                              QSizePolicy::Expanding,
                                              QSizePolicy::Minimum );

   theHBox3->addItem(leftSpacer);
   
   theCloseButton = new QPushButton( this, "theCloseButton" );
   theCloseButton->setText( "Close" );
   theCloseButton->setDefault(false);
   theCloseButton->setAutoDefault(false);   
   theHBox3->addWidget(theCloseButton);

   QSpacerItem* rightSpacer = new QSpacerItem( 10,
                                               10,
                                               QSizePolicy::Expanding,
                                               QSizePolicy::Minimum );
   
   theHBox3->addItem(rightSpacer);
   
   //---
   // Connect all the signals to slots...
   //
   // NOTE:
   // If a push button is set to "default" or "auto default" it will always
   // call that slot when return is pressed in the dialog.
   // Since this isn't what I want, all defaults are set to off!
   //---
   connect( theCloseButton, SIGNAL ( clicked() ),
            this, SLOT ( closeClicked() ) );
}

ossimQtAboutDialogBase::~ossimQtAboutDialogBase()
{
}

QString ossimQtAboutDialogBase::getVersionString() const
{
   return QString(ossimInit::instance()->version().c_str());
}

void ossimQtAboutDialogBase::closeClicked()
{
   close(true);
}

ossimQtAboutDialogBase::ossimQtAboutDialogBase(const ossimQtAboutDialogBase& /* obj */ )
   : QDialog()
{
}

const ossimQtAboutDialogBase& ossimQtAboutDialogBase::operator=(const ossimQtAboutDialogBase& /* rhs */ )
{
   return *this;
}
