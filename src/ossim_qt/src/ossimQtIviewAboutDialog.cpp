//----------------------------------------------------------------------------
// Copyright (C) 2004 David Burken, All rights reserved.
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// Description: ImageLinker about dialog.
//
// $Id: ossimQtIviewAboutDialog.cpp 7150 2004-12-28 21:50:45Z dburken $
//----------------------------------------------------------------------------

#include <qpixmap.h>
#include <qhbox.h>
#include <qlayout.h>
#include <qlabel.h>

#include <ossimQtIviewAboutDialog.h>

ossimQtIviewAboutDialog::ossimQtIviewAboutDialog(QWidget* parent,
                                                 const char* name,
                                                 bool modal,
                                                 WFlags f)
   : ossimQtAboutDialogBase(parent, name, modal, f)
{
   setCaption("About iview");
   QLabel* pixLabel = new QLabel( this );
   pixLabel->setPixmap(QPixmap::fromMimeSource("iviewsplash"));
   theHBox1->addWidget(pixLabel);

   QSpacerItem* leftSpacer = new QSpacerItem( 10,
                                              10,
                                              QSizePolicy::Expanding,
                                              QSizePolicy::Minimum );
   theHBox2->addItem(leftSpacer);
   
   QLabel* textLabel = new QLabel( this );
   QString text = "\n             iview      \n";
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

ossimQtIviewAboutDialog::~ossimQtIviewAboutDialog()
{
}

ossimQtIviewAboutDialog::ossimQtIviewAboutDialog(const ossimQtIviewAboutDialog& /* obj */ )
   : ossimQtAboutDialogBase()
{
}

const ossimQtIviewAboutDialog& ossimQtIviewAboutDialog::operator=(const ossimQtIviewAboutDialog& /* rhs */ )
{
   return *this;
}
