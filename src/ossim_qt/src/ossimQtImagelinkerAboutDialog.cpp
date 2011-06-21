//----------------------------------------------------------------------------
// Copyright (C) 2004 Intelligence Data Systems, Inc. All rights reserved.
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// Description: ImageLinker about dialog.
//
// $Id: ossimQtImagelinkerAboutDialog.cpp 7150 2004-12-28 21:50:45Z dburken $
//----------------------------------------------------------------------------

#include <qpixmap.h>
#include <qhbox.h>
#include <qlayout.h>
#include <qlabel.h>

#include <ossimQtImagelinkerAboutDialog.h>

ossimQtImagelinkerAboutDialog::ossimQtImagelinkerAboutDialog(QWidget* parent,
                                                             const char* name,
                                                             bool modal,
                                                             WFlags f)
   : ossimQtAboutDialogBase(parent, name, modal, f)
{
   setCaption("About ImageLinker");
   QLabel* pixLabel = new QLabel( this );
   pixLabel->setPixmap(QPixmap::fromMimeSource("ImageLinkerSplash"));
   theHBox1->addWidget(pixLabel);

   QSpacerItem* leftSpacer = new QSpacerItem( 10,
                                              10,
                                              QSizePolicy::Expanding,
                                              QSizePolicy::Minimum );
   theHBox2->addItem(leftSpacer);
   
   QLabel* textLabel = new QLabel( this );
   QString text = "\n     ImageLinker     \n";
   text +=        getVersionString();
   text +=        "\nhttp://www.ossim.org\n\n";
   textLabel->setText(text);
   theHBox2->addWidget(textLabel);
   
   QSpacerItem* rightSpacer = new QSpacerItem( 10,
                                               10,
                                               QSizePolicy::Expanding,
                                               QSizePolicy::Minimum );
   
   theHBox2->addItem(rightSpacer);
}

ossimQtImagelinkerAboutDialog::~ossimQtImagelinkerAboutDialog()
{
}

ossimQtImagelinkerAboutDialog::ossimQtImagelinkerAboutDialog(const ossimQtImagelinkerAboutDialog& /* obj */ )
   : ossimQtAboutDialogBase()
{
}

const ossimQtImagelinkerAboutDialog& ossimQtImagelinkerAboutDialog::operator=(const ossimQtImagelinkerAboutDialog& /* rhs */ )
{
   return *this;
}
