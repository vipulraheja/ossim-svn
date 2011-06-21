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
// $Id: ossimQtMatrixPropertyDialog.ui.h 5757 2003-12-12 19:50:32Z gpotts $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
void ossimQtMatrixPropertyDialog::init()
{
    theController = new ossimQtMatrixPropertyController(this);
}

void ossimQtMatrixPropertyDialog::destroy()
{
    if(theController)
    {
	delete theController;
	theController = 0;
    }
}

ossimQtMatrixPropertyController* ossimQtMatrixPropertyDialog::controller()
{
    return theController;
}

void ossimQtMatrixPropertyDialog::theNormalizeButton_clicked()
{
    theController->normalizeButton();
}


void ossimQtMatrixPropertyDialog::theZeroButton_clicked()
{
    theController->zeroButton();
}


void ossimQtMatrixPropertyDialog::theApplyButton_clicked()
{
    theController->applyButton();
}



void ossimQtMatrixPropertyDialog::theCloseButton_clicked()
{
    close(true);
}
