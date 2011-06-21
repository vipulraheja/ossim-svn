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
// $Id: ossimQtHsiRemapperDialog.ui.h 5757 2003-12-12 19:50:32Z gpotts $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/


void ossimQtHsiRemapperDialog::redButtonClicked()
{
   if (theController)
   {
      theController->redButtonClicked();
   }
}


void ossimQtHsiRemapperDialog::yellowButtonClicked()
{
   if (theController)
   {
      theController->yellowButtonClicked();
   }
}


void ossimQtHsiRemapperDialog::greenButtonClicked()
{
   if (theController)
   {
      theController->greenButtonClicked();
   }
}


void ossimQtHsiRemapperDialog::cyanButtonClicked()
{
   if (theController)
   {
      theController->cyanButtonClicked();
   }
}


void ossimQtHsiRemapperDialog::blueButtonClicked()
{
   if (theController)
   {
      theController->blueButtonClicked();
   }
}


void ossimQtHsiRemapperDialog::magentaButtonClicked()
{
   if (theController)
   {
      theController->magentaButtonClicked();
   }
}

void ossimQtHsiRemapperDialog::allButtonClicked()
{
   if (theController)
   {
      theController->allButtonClicked();
   }
}

void ossimQtHsiRemapperDialog::hueOffsetValueChanged(int value)
{
   if (theController)
   {
      theController->hueOffsetValueChanged(value);
   }
}

void ossimQtHsiRemapperDialog::hueLowRangeValueChanged(int value)
{
   if (theController)
   {
      theController->hueLowRangeValueChanged(value);
   }
}

void ossimQtHsiRemapperDialog::hueHighRangeValueChanged(int value )
{
   if (theController)
   {
      theController->hueHighRangeValueChanged(value);
   }

}

void ossimQtHsiRemapperDialog::saturationOffsetValueChanged(int value)
{
   if (theController)
   {
      theController->saturationOffsetValueChanged(value);
   }
}

void ossimQtHsiRemapperDialog::intensityOffsetValueChanged(int value)
{
   if (theController)
   {
      theController->intensityOffsetValueChanged(value);
   }
}

void ossimQtHsiRemapperDialog::lowIntensityClipValueChanged(int value)
{
   if (theController)
   {
      theController->lowIntensityClipValueChanged(value);
   }
}

void ossimQtHsiRemapperDialog::highIntensityClipValueChanged(int value)
{
   if (theController)
   {
      theController->highIntensityClipValueChanged(value);
   }
}

void ossimQtHsiRemapperDialog::enableButtonClicked()
{
   if (theController)
   {
      theController->enableButtonClicked();
   }
}

void ossimQtHsiRemapperDialog::resetGroupButtonClicked()
{
   if (theController)
   {
      theController->resetGroupButtonClicked();
   }
}


void ossimQtHsiRemapperDialog::resetAllButtonClicked()
{
   if (theController)
   {
      theController->resetAllButtonClicked();
   }
}

void ossimQtHsiRemapperDialog::closeButtonClicked()
{
   close(true);
}

void ossimQtHsiRemapperDialog::init()
{
   theColorRangeButtonGroup->setButton(6); // all button
   theController = new ossimQtHsiRemapperController(this);
}

void ossimQtHsiRemapperDialog::destroy()
{
   if (theController)
   {
      delete theController;
      theController = NULL;
   }
}

void ossimQtHsiRemapperDialog::setHsiRemapper(ossimHsiRemapper* remapper)
{
   if (theController)
   {
      theController->setHsiRemapper(remapper);
   }
}



void ossimQtHsiRemapperDialog::hueBlendRangeValueChanged( int value )
{
   if (theController)
   {
      theController->hueBlendRangeValueChanged( value );
   }
}


void ossimQtHsiRemapperDialog::whiteObjectClipValueChanged( int value )
{
   if (theController)
   {
      theController->whiteObjectClipValueChanged( value );
   }
}

