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
// $Id: ossimQtAdjustableParameterDialog.ui.h 8864 2006-03-09 18:59:46Z gpotts $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

void ossimQtAdjustableParameterDialog::init()
{
    theController = new ossimQtAdjustableParameterDialogController(this);
}

void ossimQtAdjustableParameterDialog::destroy()
{
    if(theController)
    {
	delete theController;
	theController = NULL;
    }
}

void ossimQtAdjustableParameterDialog::theCloseButton_clicked()
{
    close(true);
}

ossimQtAdjustableParameterDialogController* ossimQtAdjustableParameterDialog::controller()
{
    return theController;
}


void ossimQtAdjustableParameterDialog::theKeepAdjustmentButton_clicked()
{
    if(theController)
    {
	theController->keepAdjustment();
    }
}


void ossimQtAdjustableParameterDialog::theAdjustmentSelectionBox_activated( const QString & )
{
    if(theController)
    {
	theController->selectionListChanged();
    }

}


void ossimQtAdjustableParameterDialog::theDeleteAdjustmentButto_clicked()
{
    if(theController)
    {
	theController->deleteAdjustment();
    }
}


void ossimQtAdjustableParameterDialog::theCopyAdjustmentButton_clicked()
{
   if(theController)
    {
	theController->copyAdjustment();
    }
}

void ossimQtAdjustableParameterDialog::theAdjustmentDescriptionInput_textChanged( const QString & )
{
    if(theController)
    {
	theController->adjustmentDescriptionChanged();
    }
}


void ossimQtAdjustableParameterDialog::theSaveButton_clicked()
{
   if(theController)
    {
	theController->saveAdjustment();
    }
}
