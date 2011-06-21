//*******************************************************************
// Copyright (C) 2003 ImageLinks Inc. 
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
// 
// Description:
// Main interface between the elevation manager and the elevation manager
// dialog box.
//
//*************************************************************************
// $Id: ossimQtElevationManagerController.cpp 16112 2009-12-17 18:19:54Z gpotts $

#include <vector>
using namespace std;

#include <qcheckbox.h>
#include <qstringlist.h>
#include <qmessagebox.h>
#include <ossimQListBox.h>
#include <ossimQtElevationManagerController.h>
#include <ossimQtElevationManagerDialog.h>
#include <ossimQtEvent.h>
#include <ossimQtApplicationUtility.h>
#include <ossimDataManager.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/elevation/ossimElevManager.h>

ossimFilename ossimQtElevationManagerController::theLatestOpenCellPath;

#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/imaging/ossimImageChain.h>
#include <ossim/imaging/ossimOrthoImageMosaic.h>
#include <ossim/base/ossimTrace.h>

static ossimTrace traceDebug("ossimQtElevationManagerController:degug");

ossimQtElevationManagerController::ossimQtElevationManagerController(ossimQtElevationManagerDialog* dialog)
   :
      theDialog(dialog),
      theMgr(NULL)
{
   // Get the pointer to the elevation manager.
   theMgr = ossimElevManager::instance();
   theMgr->addListener( this );
   
#if 0
   if (theLatestOpenCellPath == ossimFilename::NIL)
   {
      // See if there is a default path...
      theLatestOpenCellPath = theMgr->getDefaultElevationPath();
   }
#endif
   update(); // Initialize the dialog box.
   
}

ossimQtElevationManagerController::~ossimQtElevationManagerController()
{
   if ( theMgr )
   {
      theMgr->removeListener( this );
      theMgr = NULL;
   }
}

void ossimQtElevationManagerController::onAdd(const QStringList& cells) const
{
   static const char MODULE[] = "ossimQtElevationManagerController::onAdd";
   QMessageBox::information ( theDialog,
                             "ERROR",
                             "ossimQtElevationManagerController::onAdd: NEED TO REFACTOR FOR NEW ELEVATION MANAGER",
                             QMessageBox::Ok);
#if 0
   QStringList list = cells;
   QStringList::Iterator it = list.begin();
   while( it != list.end() )
   {
      ossimFilename cell((*it).ascii());

      if (traceDebug())
      {
         CLOG << "\ncell:  " << cell
              << std::endl;
      }

      
      if (theMgr->isCellOpen(cell))
      {
         QString caption("Notice:");
         QString text = cell.c_str();
         text += " is already loaded by the elevation manager.";

         // Give the user an already open
         QMessageBox::information ( theDialog,
                                    caption,
                                    text,
                                    QMessageBox::Ok);
         
      }
      else if (theMgr->openCell(cell) == false)
      {
         QString caption("Warning:");
         QString text = cell.c_str();
         text += " could not be opened!";

         // Give the user an already open
         QMessageBox::warning( theDialog,
                               caption,
                               text,
                               QMessageBox::Ok,
                               QMessageBox::NoButton);
         
      }
      ++it;
   }

   updateListBox();
#endif
} 

void ossimQtElevationManagerController::onAddDirectory(const QString& directory) const
{
   QMessageBox::information ( theDialog,
                             "ERROR",
                             "ossimQtElevationManagerController::onAddDirectory: NEED TO REFACTOR FOR NEW ELEVATION MANAGER",
                             QMessageBox::Ok);
#if 0
   ossimFilename dir = (const char*)directory;
   if (theMgr->openDirectory(dir) == false)
   {
      QString caption("Warning:");
      QString text = dir.c_str();
      text += " could not be opened!";
   }
#endif
   updateListBox();
}

void
ossimQtElevationManagerController::onRemove(const QStringList& cells) const
{
   QMessageBox::information ( theDialog,
                             "ERROR",
                             "ossimQtElevationManagerController::onRemove: NEED TO REFACTOR FOR NEW ELEVATION MANAGER",
                             QMessageBox::Ok);
   
#if 0
   QStringList list = cells;
   QStringList::Iterator it = list.begin();
   while( it != list.end() )
   {
      ossimFilename cell = (const char*)(*it);
      if (!theMgr->closeCell(cell))
      {
         QString caption("Warning:");
         QString text = cell.c_str();
         text += " could not be closed!";
      }

      ++it;
   }
#endif
   updateListBox();
} 

void ossimQtElevationManagerController::onRemoveAll() const
{
#if 0
   theMgr->closeAllCells();
   updateListBox();
#endif
}

void ossimQtElevationManagerController::onUp(const QStringList& cells) const
{
   QMessageBox::information ( theDialog,
                             "ERROR",
                             "ossimQtElevationManagerController::onUp: NEED TO REFACTOR FOR NEW ELEVATION MANAGER",
                             QMessageBox::Ok);
#if 0
   QStringList list = cells;
   QStringList::Iterator it = list.begin();
   while( it != list.end() )
   {
      ossimFilename cell = (const char*)(*it);
      if (!theMgr->moveCellUpOne(cell))
      {
         QString caption("Warning:");
         QString text = cell.c_str();
         text += " could not be moved up!";

         // Give the user an already open
         QMessageBox::warning( theDialog,
                               caption,
                               text,
                               QMessageBox::Ok,
                               QMessageBox::NoButton);
      }

      ++it;
   }
#endif
   updateListBox();
}


void ossimQtElevationManagerController::onDown(const QStringList& cells) const
{
   QMessageBox::information ( theDialog,
                             "ERROR",
                             "ossimQtElevationManagerController::onDown: NEED TO REFACTOR FOR NEW ELEVATION MANAGER",
                             QMessageBox::Ok);
#if 0
   QStringList list = cells;
   QStringList::Iterator it = list.end();
   unsigned int count = list.count();
   --it;

   for (unsigned int i = 0; i < count; ++i)
   {
      ossimFilename cell = (const char*)(*it);
      if (!theMgr->moveCellDownOne(cell))
      {
         // Send a warning
         QString caption("Warning:");
         QString text = cell.c_str();
         text += " could not be moved down!";
         QMessageBox::warning( theDialog,
                               caption,
                               text,
                               QMessageBox::Ok,
                               QMessageBox::NoButton);
      }
      --it;
   }
#endif
   updateListBox();
}

void ossimQtElevationManagerController::onTop(const QStringList& cells) const
{
   QMessageBox::information ( theDialog,
                             "ERROR",
                             "ossimQtElevationManagerController::onTop: NEED TO REFACTOR FOR NEW ELEVATION MANAGER",
                             QMessageBox::Ok);
#if 0
   QStringList list = cells;
   QStringList::Iterator it = list.end();
   unsigned int count = list.count();
   --it;
   
   for (unsigned int i = 0; i < count; ++i)
   {
      ossimFilename cell = (const char*)(*it);
      if (!theMgr->moveCellToTop(cell))
      {
         // Send a warning
         QString caption("Warning:");
         QString text = cell.c_str();
         text += " could not be moved to top!";
         QMessageBox::warning( theDialog,
                               caption,
                               text,
                               QMessageBox::Ok,
                               QMessageBox::NoButton);
      }
      --it;
   }
#endif
   
   updateListBox();
}

void ossimQtElevationManagerController::onBottom(const QStringList& cells) const
{
   QMessageBox::information ( theDialog,
                             "ERROR",
                             "ossimQtElevationManagerController::onBottom: NEED TO REFACTOR FOR NEW ELEVATION MANAGER",
                             QMessageBox::Ok);
#if 0
   QStringList list = cells;
   QStringList::Iterator it = list.begin();
   while( it != list.end() )
   {
      ossimFilename cell = (const char*)(*it);
      if (!theMgr->moveCellToBottom(cell))
      {
         QString caption("Warning:");
         QString text = cell.c_str();
         text += " could not be moved to bottom!";

         // Give the user an already open
         QMessageBox::warning( theDialog,
                               caption,
                               text,
                               QMessageBox::Ok,
                               QMessageBox::NoButton);
      }

      ++it;
   }
#endif
   updateListBox();
}

void ossimQtElevationManagerController::onClose(const QStringList& cells) const
{
   QMessageBox::information ( theDialog,
                             "ERROR",
                             "ossimQtElevationManagerController::onClose: NEED TO REFACTOR FOR NEW ELEVATION MANAGER",
                             QMessageBox::Ok);
#if 0   
   QStringList list = cells;
   QStringList::Iterator it = list.begin();
   while( it != list.end() )
   {
      ossimFilename cell = (const char*)(*it);
      if (!theMgr->closeCell(cell))
      {
         QString caption("Warning:");
         QString text = cell.c_str();
         text += " could not be closed!";

         // Give the user an already open
         QMessageBox::warning( theDialog,
                               caption,
                               text,
                               QMessageBox::Ok,
                               QMessageBox::NoButton);
      }

      ++it;
   }
#endif
   updateListBox();
}

void ossimQtElevationManagerController::updateListBox() const
{
#if 0   
   if (theDialog && theMgr)
   {
      if (theDialog->theElevationListBox)
      {
         theDialog->theElevationListBox->clear();

         // Get the new list and add it to the list box.
         vector<ossimFilename> cellList;
         theMgr->getOpenCellList(cellList);
         ossim_uint32 number_of_open_cells = cellList.size();
         for (ossim_uint32 i=0; i<number_of_open_cells; ++i)
         {
            QString item = cellList[i].c_str();
            theDialog->theElevationListBox->insertItem(item);
         }
      }
   }
#endif
}

void ossimQtElevationManagerController::updateEnableBox() const
{
#if 0
   if (theDialog && theMgr)
   {
      if (theDialog->theElevationEnabledCheckBox)
      {
         theDialog->theElevationEnabledCheckBox->
            setChecked(theMgr->isSourceEnabled());
      }
   }
#endif
}

void ossimQtElevationManagerController::updateAutoLoadEnableBox() const
{
#if 0
   if (theDialog && theMgr)
   {
      if (theDialog->theAutoLoadCheckBox)
      {
         theDialog->theAutoLoadCheckBox->
            setChecked(theMgr->isAutoLoadEnabled());
      }
   }
#endif
}

void ossimQtElevationManagerController::updateAutoSortEnableBox() const
{
#if 0
   if (theDialog && theMgr)
   {
      if (theDialog->theAutoSortCheckBox)
      {
         theDialog->theAutoSortCheckBox->
            setChecked(theMgr->isAutoSortEnabled());
      }
   }
#endif
}

void ossimQtElevationManagerController::onEnable(bool flag) const
{
#if 0
   if (theMgr)
   {
      if (flag)
      {
         theMgr->enableSource();
      }
      else
      {
         theMgr->disableSource();
      }
   }
#endif
}

void ossimQtElevationManagerController::onAutoLoadEnable(bool flag) const
{
#if 0
   if (theMgr)
   {
      if (flag)
      {
         theMgr->enableAutoLoad();
      }
      else
      {
         theMgr->disableAutoLoad(); 
      }
   }
#endif
}

void ossimQtElevationManagerController::onAutoSortEnable(bool flag) const
{
#if 0
   if (theMgr)
   {
      if (flag)
      {
         theMgr->enableAutoSort();
      }
      else
      {
         theMgr->disableAutoSort(); 
      }
   }
#endif
}   

void ossimQtElevationManagerController::onMosaic(const QStringList& cellList) const
{
   std::vector<ossimFilename> fileList;
   ossimQtGetDataManagerEvent tempEvt;
   ossimQtApplicationUtility::sendEventToRoot(theDialog, &tempEvt);

   for(ossim_uint32 idx = 0; idx < cellList.size(); ++idx)
   {
      fileList.push_back(cellList[idx].ascii());
   }
   ossimConnectableObject* result = NULL;
   if(tempEvt.getDataManager())
   {
      result = tempEvt.getDataManager()->createStandardElevMosaic(fileList);
   }

   if(result)
   {
      ossimQtDisplayChainEvent *evt = new ossimQtDisplayChainEvent(result->getId().getId());
      ossimQtApplicationUtility::postEventToRoot(theDialog, evt);
   }
}

void ossimQtElevationManagerController::processEvent(ossimElevationManagerEvent&) const
{
   update();
}

void ossimQtElevationManagerController::update() const
{
   updateListBox();
   updateEnableBox();
   updateAutoLoadEnableBox();
   updateAutoSortEnableBox();
}

// static method...
ossimFilename ossimQtElevationManagerController::getLatestOpenCellPath()
{
   return theLatestOpenCellPath;
}

// Private to disallow copy constructor, assignment operator use...
ossimQtElevationManagerController::ossimQtElevationManagerController(const ossimQtElevationManagerController&)
   :
      ossimElevationManagerEventListener()
{
}

ossimQtElevationManagerController& ossimQtElevationManagerController::operator=(const ossimQtElevationManagerController&)
{
   return *this;
}
