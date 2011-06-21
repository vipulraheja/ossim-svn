//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtElevationManagerDialog.ui.h 7667 2005-06-16 13:33:28Z gpotts $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/


void ossimQtElevationManagerDialog::elevationEnabledCheckBoxClicked()
{
   if (theElevationEnabledCheckBox && theController)
   {
      theController->onEnable(theElevationEnabledCheckBox->isChecked());
   }
}


void ossimQtElevationManagerDialog::closeButtonClicked()
{
   close(true);  // true to destroy on close...
}


void ossimQtElevationManagerDialog::addDirectoryClicked()
{
   if (!theController) return;

   QFileDialog* fd = new QFileDialog( this );
   fd->setMode(QFileDialog::DirectoryOnly);
   fd->setDir(ossimQtElevationManagerController::getLatestOpenCellPath().c_str());
   
   QString directory;
   if (fd->exec() == QDialog::Accepted )
   {
      directory = fd->selectedFile();
      theController->onAddDirectory(directory);
   }

   // Delete fd???
   delete fd;
   fd = NULL;
}


void ossimQtElevationManagerDialog::removeButtonClicked()
{
   if (!theController || !theElevationListBox) return;

   QStringList cells;
   theElevationListBox->getSelectedList(cells);
   theController->onRemove(cells);
}

void ossimQtElevationManagerDialog::moveUpButtonClicked()
{
   if (!theController || !theElevationListBox) return;

   QStringList cells;
   theElevationListBox->getSelectedList(cells);
   theController->onUp(cells);
}


void ossimQtElevationManagerDialog::removeAllButtonClicked()
{
   if (!theController) return;

   theController->onRemoveAll();
}


void ossimQtElevationManagerDialog::moveDownButtonClicked()
{
   if (!theController || !theElevationListBox) return;

   QStringList cells;
   theElevationListBox->getSelectedList(cells);
   theController->onDown(cells);
}


void ossimQtElevationManagerDialog::moveToTopButtonClicked()
{
   if (!theController || !theElevationListBox) return;

   QStringList cells;
   theElevationListBox->getSelectedList(cells);
   theController->onTop(cells); 
}


void ossimQtElevationManagerDialog::moveToBottomButtonClicked()
{
   if (!theController || !theElevationListBox) return;

   QStringList cells;
   theElevationListBox->getSelectedList(cells);
   theController->onBottom(cells);
}


void ossimQtElevationManagerDialog::mosaicButtonClicked()
{
   if (!theController || !theElevationListBox) return;

   QStringList cells;
   theElevationListBox->getSelectedList(cells);
   theController->onMosaic(cells); 
}


void ossimQtElevationManagerDialog::autoLoadCheckBoxClicked()
{
   if (theAutoLoadCheckBox && theController)
   {
      theController->onAutoLoadEnable(theAutoLoadCheckBox->isChecked());
   }
}


void ossimQtElevationManagerDialog::autoSortingCheckBoxClicked()
{
   if (theAutoSortCheckBox && theController)
   {
      theController->onAutoSortEnable(theAutoSortCheckBox->isChecked());
   }
}

void ossimQtElevationManagerDialog::addButtonClicked()
{
   if (!theController) return;
   
   QStringList cells = QFileDialog::getOpenFileNames("Cells (*.dt0 *.dt1 *.dt2 *.hgt);;All Files(*)",
                                                     ossimQtElevationManagerController::getLatestOpenCellPath().c_str(),
                                                     this,
                                                     "open cell dialog"
                                                     "Select one or more cells" );

   theController->onAdd(cells);
}


void ossimQtElevationManagerDialog::init()
{
   theController = new ossimQtElevationManagerController(this);
}


void ossimQtElevationManagerDialog::destroy()
{
    if (theController)
    {
	delete theController;
	theController = NULL;
    }
}
