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
// $Id: ossimQtBandSelectorDialog.ui.h 5756 2003-12-12 19:20:12Z gpotts $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/


void ossimQtBandSelectorDialog::greyButtonClicked()
{
   if (theController)
   {
      theController->greyButtonClicked();
   }
}

void ossimQtBandSelectorDialog::trueButtonClicked()
{
   if (theController)
   {
      theController->trueButtonClicked();
   }
}

void ossimQtBandSelectorDialog::nBandButtonClicked()
{
   if (theController)
   {
      theController->nBandButtonClicked();
   }
}

void ossimQtBandSelectorDialog::clearButtonClicked()
{
   if (theController)
   {
      theController->clearButtonClicked();
   }

}

void ossimQtBandSelectorDialog::downButtonClicked()
{
   if (theController)
   {
      theController->downButtonClicked();
   }
}

void ossimQtBandSelectorDialog::moveToTopButtonClicked()
{
   if (theController)
   {
      theController->moveToTopButtonClicked();
   }
}

void ossimQtBandSelectorDialog::moveToBottomButtonClicked()
{
   if (theController)
   {
      theController->moveToBottomButtonClicked();
   }
}

void ossimQtBandSelectorDialog::applyButtonClicked()
{
   if (theController)
   {
      theController->applyButtonClicked();
   }
}

void ossimQtBandSelectorDialog::closeButtonClicked()
{
   close(true);
}

void ossimQtBandSelectorDialog::init()
{
   theController = new ossimQtBandSelectorController(this);
   theAvailableBandsListBox->setSelectionMode(QListBox::Single);
   theAvailableBandsListBox->setName("available_bands");
   theSelectedBandsListBox->setName("selected_bands");
}

void ossimQtBandSelectorDialog::destroy()
{
   if (theController)
   {
      delete theController;
      theController = NULL;
   }
}


void ossimQtBandSelectorDialog::setBandSelector( ossimBandSelector * bandSelector )
{
   if (theController)
   {
      theController->setBandSelector(bandSelector);
   }
}


void ossimQtBandSelectorDialog::updateDisplay()
{

}



void ossimQtBandSelectorDialog::allButtonClicked()
{
   if (theController)
   {
      theController->allButtonClicked();
   }
}


void ossimQtBandSelectorDialog::rightButtonClicked()
{
   if (theController)
   {
      theController->rightButtonClicked();
   }
}


void ossimQtBandSelectorDialog::leftButtonClicked()
{
   if (theController)
   {
      theController->leftButtonClicked();
   }
}


void ossimQtBandSelectorDialog::upButtonClicked()
{
   if (theController)
   {
      theController->upButtonClicked();
   }
}

void ossimQtBandSelectorDialog::availableBandClicked(QListBoxItem* item)
{
   if (theController)
   {
      theController->availableBandClicked(item);
   }

}
