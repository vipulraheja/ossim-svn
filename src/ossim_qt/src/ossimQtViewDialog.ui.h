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
// $Id: ossimQtViewDialog.ui.h 13197 2008-07-22 19:09:35Z dburken $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
void ossimQtViewDialog::init()
{
    theController = new ossimQtViewDialogController(this);
}

void ossimQtViewDialog::destroy()
{
   if(theController)
   {
      delete theController;
      theController = 0;
   }
}

void ossimQtViewDialog::setDefaultView()
{
    theController->setDefaultView();
}

void ossimQtViewDialog::theCloseButton_clicked()
{
    close(true);
}


void ossimQtViewDialog::theApplyButton_clicked()
{
    theController->apply();
}

ossimQtViewDialogController* ossimQtViewDialog::controller()
{
    return theController;
}

void ossimQtViewDialog::theStatePlaneRadioButton_clicked()
{
    theController->transformationTypeChanged();
}

void ossimQtViewDialog::theMapRadioButton_clicked()
{
    theController->transformationTypeChanged();
}

void ossimQtViewDialog::theIdentityButton_clicked()
{
    theController->transformationTypeChanged();
}

void ossimQtViewDialog::theProjectionComboBox_textChanged( const QString & value)
{
    theController->currentProjectionChanged(value);
}

void ossimQtViewDialog::theProjectionComboBox_activated( const QString & value )
{
    theController->currentProjectionChanged(value);
}


void ossimQtViewDialog::thePropagateButton_clicked()
{
   theController->propagate();
}
