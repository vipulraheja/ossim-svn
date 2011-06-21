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
// $Id: ossimQtStringListPropertyDialog.ui.h 5757 2003-12-12 19:50:32Z gpotts $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

void ossimQtStringListPropertyDialog::init()
{
    theController = new ossimQtStringListPropertyController(this);
}

void ossimQtStringListPropertyDialog::destroy()
{
    if(theController)
    {
	delete theController;
	theController = NULL;
    }
}

ossimQtStringListPropertyController* ossimQtStringListPropertyDialog::controller()
{
    return theController;
}


void ossimQtStringListPropertyDialog::theCloseButton_clicked()
{
    close(true);
}

void ossimQtStringListPropertyDialog::theApplyButton_clicked()
{
    theController->applyButton();
}
