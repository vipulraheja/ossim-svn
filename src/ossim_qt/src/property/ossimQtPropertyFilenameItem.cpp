//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// OSSIM is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License 
// as published by the Free Software Foundation.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//
// You should have received a copy of the GNU General Public License
// along with this software. If not, write to the Free Software 
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-
// 1307, USA.
//
// See the GPL in the COPYING.GPL file for more details.
//
// Author: Garrett Potts (gpotts@imagelinks.com)
//
//*************************************************************************
// $Id: ossimQtPropertyFilenameItem.cpp 9114 2006-06-14 17:42:07Z gpotts $
#include <qfiledialog.h>
#include "ossimQtPropertyFilenameItem.h"
#include <ossim/base/ossimFilenameProperty.h>
#include <ossim/base/ossimFilename.h>
#include "ossimQtPropertyListView.h"

ossimQtPropertyFilenameItem::ossimQtPropertyFilenameItem(ossimQtPropertyListView *propList,
                                                         ossimQtPropertyItem *after,
                                                         ossimQtPropertyItem *parent,
                                                         ossimRefPtr<ossimProperty> oProp)
   :ossimQtPropertyItem(propList, after, parent, oProp)
{
   theLineEditor = 0;
   theBox        = 0;
   thePushButton = 0;

   if(getOssimProperty().valid())
   {
      setText( 1, getOssimProperty()->valueToString().c_str());
   }
   else
   {
      setText( 1, "");
   }
}

ossimQtPropertyFilenameItem::~ossimQtPropertyFilenameItem()
{
   if(theBox)
   {
      delete theBox;
      theBox = 0;
   }
}

void ossimQtPropertyFilenameItem::showEditor()
{
   if(!getOssimProperty()) return;
    ossimQtPropertyItem::showEditor();
    if ( !theLineEditor || theLineEditor->text().length() == 0 )
    {
       lineEditor()->blockSignals( TRUE );
       lineEditor()->setText( getOssimProperty()->valueToString().c_str() );
       lineEditor()->blockSignals( FALSE );
    }
    
    placeEditor(theBox);
    theBox->show();
    theLineEditor->setFocus();
}

void ossimQtPropertyFilenameItem::hideEditor()
{
   ossimQtPropertyItem::hideEditor();

   if(theBox)
   {
      theBox->hide();
   }
}

QLineEdit *ossimQtPropertyFilenameItem::lineEditor()
{
   if ( theLineEditor )
   {
      return theLineEditor;
   }

   theBox = new QHBox( theListView->viewport() );
   theBox->setFrameStyle( QFrame::StyledPanel | QFrame::Sunken );
   theBox->setLineWidth( 2 );
   theBox->hide();
   
   theLineEditor = new QLineEdit( theBox );
   thePushButton = new QPushButton( "...", theBox );
   thePushButton->setFixedWidth( 20 );
   connect( thePushButton, SIGNAL( clicked() ),
            this, SLOT( getText() ) );
   theLineEditor->setFrame( FALSE );
   connect( theLineEditor, SIGNAL( returnPressed() ),
            this, SLOT( setValue() ) );
   
   theLineEditor->setReadOnly(getOssimProperty()->isReadOnly());
   if(getOssimProperty()->isReadOnly())
   {
      thePushButton->setEnabled(false);
   }
   
   return theLineEditor;
}

void ossimQtPropertyFilenameItem::setValue()
{
   if(getOssimProperty().valid())
   {
      if(theLineEditor->text() == getOssimProperty()->valueToString().c_str())
      {
         return;
      }
      getOssimProperty()->setValue(theLineEditor->text().ascii());

      setText( 1, theLineEditor->text().ascii());
      notifyValueChange();
   }
   
}

void ossimQtPropertyFilenameItem::getText()
{
   ossimFilenameProperty* filenameProp = PTR_CAST(ossimFilenameProperty,
                                                  getOssimProperty().get());

   if(filenameProp)
   {
      ossimString filterString;
      ossimFilename filename;
      
      filterString = filenameProp->getFilterListAsString(" ");
      if(filterString == "")
      {
         filterString = "*";
      }
      filename = theLineEditor->text().ascii();
      QString value;
      if(filenameProp->isIoTypeInput())
      {
         value = QFileDialog::getOpenFileName(theLineEditor->text(),
                                              ("(" +filterString+")").c_str(),
                                              theListView,
                                              "Open File Dialog",
                                              "Choose a file to open");
      }
      else if(filenameProp->isIoTypeOutput())
      {
         value = QFileDialog::getSaveFileName(theLineEditor->text(),
                                              ("(" +filterString+")").c_str(),
                                              theListView,
                                              "Save File Dialog",
                                              "Choose a file to save");
      }
      theLineEditor->setText(value);
      setValue();
   }
}

void ossimQtPropertyFilenameItem::resetProperty(bool notify)
{
   ossimQtPropertyItem::resetProperty(notify);
   setText( 1, getOssimProperty()->valueToString().c_str());
   if(theLineEditor)
   {
      theLineEditor->setText(getOssimProperty()->valueToString().c_str());
   }
}
