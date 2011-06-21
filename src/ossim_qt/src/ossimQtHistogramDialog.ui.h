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
// $Id: ossimQtHistogramDialog.ui.h 5757 2003-12-12 19:50:32Z gpotts $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

void ossimQtHistogramDialog::init()
{
   theController = new ossimQtHistogramController(this);
}

void ossimQtHistogramDialog::destroy()
{
   if (theController)
   {
      delete theController;
      theController = NULL;
   }
}

void ossimQtHistogramDialog::closeButtonClicked()
{
   close(true);
}


void ossimQtHistogramDialog::applyButtonClicked()
{
   if (theController)
   {
      theController->applyButtonClicked();
   }
}

void ossimQtHistogramDialog::resetButtonClicked()
{
   if (theController)
   {
      theController->resetButtonClicked();
   }
}

void ossimQtHistogramDialog::enableCheckBoxClicked()
{
   if (theController)
   {
      theController->enableCheckBoxClicked();
   }
}

void ossimQtHistogramDialog::setHistogramRemapper(ossimHistogramRemapper* remapper)
{
   if (remapper)
   {
      // Build theStretchModeComboBox menu.
      theStretchModeComboBox->clear();
      const ossim_uint32 MODES = remapper->getNumberOfStretchModes();
      for (ossim_uint32 mode = 0; mode < MODES; ++mode)
      {
         QString item = remapper->getStretchModeString(mode).c_str();
         theStretchModeComboBox->insertItem(item);
      }
      
      // Build up theBandComboBox menu.
      QString item = "master";
      theBandComboBox->clear();
      theBandComboBox->insertItem(item);

      const ossim_uint32 BANDS = remapper->getNumberOfOutputBands();
      for (ossim_uint32 band = 0; band < BANDS; ++band)
      {
         item = ossimString::toString(band+1).c_str();
         theBandComboBox->insertItem(item);
      }
   }

   if (theController)
   {
      theController->setHistogramRemapper(remapper);
   }

   theHistogramWidget->setHistogramRemapper(remapper);

   // This will paint an average of all bands on the widget.
   theHistogramWidget->paintHistogram();
}

void ossimQtHistogramDialog::lowClipPercentReturnPressed()
{
   if (theController)
   {
      theController->lowClipPercentReturnPressed();
   }
}

void ossimQtHistogramDialog::highClipPercentReturnPressed()
{
   if (theController)
   {
      theController->highClipPercentReturnPressed();
   }
}

void ossimQtHistogramDialog::lowClipValueReturnPressed()
{
   if (theController)
   {
      theController->lowClipValueReturnPressed();
   }
}

void ossimQtHistogramDialog::highClipValueReturnPressed()
{
   if (theController)
   {
      theController->highClipValueReturnPressed();
   }
}

void ossimQtHistogramDialog::midPointReturnPressed()
{
   if (theController)
   {
      theController->midPointReturnPressed();
   }
}

void ossimQtHistogramDialog::outputMinValueReturnPressed()
{
   if (theController)
   {
      theController->outputMinValueReturnPressed();
   }
}

void ossimQtHistogramDialog::outputMaxValueReturnPressed()
{
   if (theController)
   {
      theController->outputMaxValueReturnPressed();
   }
}


void ossimQtHistogramDialog::stretchModeComboBoxActivated( int item )
{
   if (theController)
   {
      theController->stretchModeComboBoxActivated(item);
   }  
}


void ossimQtHistogramDialog::bandComboBoxActivated( int item )
{
   if (theController)
   {
      theController->bandComboBoxActivated(item);
   } 
}


void ossimQtHistogramDialog::histogramFileLineEditReturnPressed()
{
   if (theController)
   {
      ossimFilename f = theHistogramFileLineEdit->text().ascii();
      theController->setHistogramFile(f);
   }
}

void ossimQtHistogramDialog::histogramFilePushButtonClicked()
{
   QFileDialog* fd = new QFileDialog( this );
   fd->setMode(QFileDialog::AnyFile);
   fd->setDir(ossimQtHistogramController::getLatestOutputFilePath().c_str());
   
   QString file;
   if (fd->exec() == QDialog::Accepted )
   {
      file = fd->selectedFile();
      ossimFilename f = file.ascii();
      theController->setHistogramFile(f);
   }

   // Delete fd???
   delete fd;
   fd = NULL;
}
