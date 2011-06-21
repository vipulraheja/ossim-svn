//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  See top level LICENSE.txt file.
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtIgenDialog.ui.h 8546 2005-12-19 21:56:57Z dburken $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

void ossimQtIgenDialog::init()
{   
   theController = new ossimQtIgenController(this);
}	

void ossimQtIgenDialog::destroy()
{
   if (theController)
   {
      delete theController;
      theController = NULL;
   }
   if (theImageWidget)
   {
      theImageWidget->refreshGraphics();
      theImageWidget = NULL;
   }
}

void ossimQtIgenDialog::closeButtonClicked()
{
   close(true);
}

void ossimQtIgenDialog::setImageWidget( ossimQtScrollingImageWidget * widget )
{
   theImageWidget = widget;

   if (theController)
   {
      theController->setImageWidget(widget);
      
      connect( theImageWidget,
               SIGNAL(destroyed()),
               this,
               SLOT(imageWidgetDestroyed()) );
   }
}

void ossimQtIgenDialog::setView(const ossimObject* view)
{
   if (theController)
   {
      theController->setView(view);
   }
}

void ossimQtIgenDialog::outputFilePushButtonClicked()
{
   if (theController)
   {
      QFileDialog* fd = new QFileDialog( this );
      fd->setMode(QFileDialog::AnyFile);
      fd->setDir(ossimQtIgenController::getLatestOutputFilePath().c_str());
      
      QString file;
      if (fd->exec() == QDialog::Accepted )
      {
         file = fd->selectedFile();
         theController->setOutputFile(file);
      }
      
      // Delete fd???
      delete fd;
      fd = NULL;
   }
}

void ossimQtIgenDialog::saveSpecFilePushButtonClicked()
{
   if (theController)
   {
      QFileDialog* fd = new QFileDialog( this );
      fd->setMode(QFileDialog::AnyFile);
      fd->setDir(ossimQtIgenController::getLatestOutputFilePath().c_str());
      
      QString file;
      if (fd->exec() == QDialog::Accepted )
      {
         file = fd->selectedFile();
         theController->saveSpecFile(file);
      }
      
      // Delete fd???
      delete fd;
      fd = NULL;
   }
}

void ossimQtIgenDialog::runIgenPushButtonClicked()
{
   if (theController)
   {
      theController->runIgen();
   }
}

void ossimQtIgenDialog::gsdLineEditReturnPressed()
{
   if (theController)
   {
      theController->gsdLineEditReturnPressed();
   }
}

void ossimQtIgenDialog::linesLineEditReturnPressed()
{
   if (theController)
   {
      theController->linesLineEditReturnPressed();
   }
}

void ossimQtIgenDialog::samplesLineEditReturnPressed()
{
   if (theController)
   {
      theController->samplesLineEditReturnPressed();
   }
}

void ossimQtIgenDialog::outputFileLineEditReturnPressed()
{
   if (theController)
   {
      theController->outputFileLineEditReturnPressed();
   }
}

void ossimQtIgenDialog::sceneRectPushButtonClicked()
{
   if (theController)
   {
      theController->setSceneBoundingRect();
   }
}

ossimQtIgenController* ossimQtIgenDialog::controller()
{
    return theController;
}

void ossimQtIgenDialog::imageWidgetDestroyed()
{
   theImageWidget = NULL;
}


void ossimQtIgenDialog::editWriterPushButtonClicked()
{
   if (theController)
   {
      theController->editWriter();
   }
}

void ossimQtIgenDialog::outputTypeComboBoxActivated( const QString & type)
{
    if (theController)
    {
	theController->setOutputType(type);
    }
}
