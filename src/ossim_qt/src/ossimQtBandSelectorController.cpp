//*******************************************************************
// Copyright (C) 2003 ImageLinks Inc. 
//
// License:  See top level LICENSE.txt.
//
// Author:  David Burken
// 
// Description:
// Main interface between the band selector dialog box and the band selector
// from the image chain.
//
//*************************************************************************
// $Id: ossimQtBandSelectorController.cpp 13140 2008-07-06 17:41:22Z dburken $

#include <cstdlib> /* for atoi */
#include <vector>
using namespace std;

#include <qcheckbox.h>
#include <qstringlist.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include "ossimQListBox.h"
#include "ossimQtBandSelectorController.h"
#include "ossimQtBandSelectorDialog.h"
#include <ossim/base/ossimConstants.h>
#include <ossim/imaging/ossimBandSelector.h>
#include <ossim/base/ossimPropertyEvent.h>
#include <ossim/base/ossimTrace.h>
#include <ossim/base/ossimNotifyContext.h>
#include "ossimQtDisplayUtility.h"

static ossimTrace traceDebug("ossimQtBandSelectorController:degug");

ossimQtBandSelectorController::ossimQtBandSelectorController(ossimQtBandSelectorDialog* dialog)
   :
      ossimConnectableObjectListener(),
      theDialog(dialog),
      theBandSelector(NULL),
      theTrueColorPosition(0),
      theCurrentMode(ossimQtBandSelectorController::UNKNOWN)
{
}

ossimQtBandSelectorController::~ossimQtBandSelectorController()
{
   if (theBandSelector)
   {
      theBandSelector->removeListener((ossimConnectableObjectListener*)this);
      theBandSelector = NULL;
   }
}

void ossimQtBandSelectorController::objectDestructingEvent(ossimObjectDestructingEvent& event)
{
   if (theBandSelector)
   {
      if(event.getObject() == PTR_CAST(ossimObject, theBandSelector))
      {      
         theDialog->close(true);
      }
   }
}

void ossimQtBandSelectorController::clearButtonClicked() const
{
   theDialog->theSelectedBandsListBox->clear();
}

void ossimQtBandSelectorController::allButtonClicked() const
{
   if (!theBandSelector) return;

   theDialog->theSelectedBandsListBox->clear();
   
   // Update the available list box.
   ossim_uint32 bands = theBandSelector->getNumberOfInputBands();
   for (ossim_uint32 band = 0; band < bands; ++band)
   {
      QString item = ossimString::toString(band+1).c_str();
      theDialog->theSelectedBandsListBox->insertItem(item);
   }
}

void ossimQtBandSelectorController::rightButtonClicked() const
{
   // Find the selected items and move them over.
   const int COUNT = theDialog->theAvailableBandsListBox->count();
   for (int i = 0; i < COUNT; ++i)
   {
      if (theDialog->theAvailableBandsListBox->isSelected(i))
      {
         QListBoxItem* item = theDialog->theAvailableBandsListBox->item(i);
         QString s = item->text();
         theDialog->theSelectedBandsListBox->insertItem(s);
      }
   }
}

void ossimQtBandSelectorController::leftButtonClicked() const
{
   // Find the selected items and remove them.
   const int COUNT = theDialog->theSelectedBandsListBox->count();
   for (int i = 0; i < COUNT; ++i)
   {
      if (theDialog->theSelectedBandsListBox->isSelected(i))
      {
         theDialog->theSelectedBandsListBox->removeItem(i);
      }
   }
}

void ossimQtBandSelectorController::upButtonClicked() const
{
   // Find the selected items and move them up.
   const int COUNT = theDialog->theSelectedBandsListBox->count();
   
   for (int i = 1; i < COUNT; ++i) // Skip the top cell...
   {
      if (theDialog->theSelectedBandsListBox->isSelected(i))
      {
         QListBoxItem* item = theDialog->theSelectedBandsListBox->item(i);
         QString s = item->text();
         theDialog->theSelectedBandsListBox->removeItem(i);
         theDialog->theSelectedBandsListBox->insertItem(s, (i-1));
      }
   }
}

void ossimQtBandSelectorController::downButtonClicked() const
{
   // Find the selected items and move them down.
   const int COUNT = theDialog->theSelectedBandsListBox->count();
   
   for (int i = (COUNT-2); i >= 0; --i) // Skip the bottom cell...
   {
      if (theDialog->theSelectedBandsListBox->isSelected(i))
      {
         QListBoxItem* item = theDialog->theSelectedBandsListBox->item(i);
         QString s = item->text();
         theDialog->theSelectedBandsListBox->removeItem(i);
         theDialog->theSelectedBandsListBox->insertItem(s, (i+1));
      }
   }
}
   
void ossimQtBandSelectorController::moveToTopButtonClicked() const
{
   // Find the selected items and move them to the top.
   const int COUNT = theDialog->theSelectedBandsListBox->count();

   int top_index = 0;
   for (int i = 1; i < COUNT; ++i) // Skip the top cell...
   {
      if (theDialog->theSelectedBandsListBox->isSelected(i))
      {
         QListBoxItem* item = theDialog->theSelectedBandsListBox->item(i);
         QString s = item->text();
         theDialog->theSelectedBandsListBox->removeItem(i);
         theDialog->theSelectedBandsListBox->insertItem(s, top_index);
         ++top_index;
      }
   }
}

void ossimQtBandSelectorController::moveToBottomButtonClicked() const
{
   // Find the selected items and move them to the bottom.
   const int COUNT = theDialog->theSelectedBandsListBox->count();

   int bottom_index = COUNT-1;
   for (int i = (COUNT-2); i >= 0; --i) // Skip the bottom cell...
   {
      if (theDialog->theSelectedBandsListBox->isSelected(i))
      {
         QListBoxItem* item = theDialog->theSelectedBandsListBox->item(i);
         QString s = item->text();
         theDialog->theSelectedBandsListBox->removeItem(i);
         theDialog->theSelectedBandsListBox->insertItem(s, bottom_index);
         --bottom_index;
      }
   } 
}

void ossimQtBandSelectorController::applyButtonClicked() const
{
   if (!theBandSelector) return;

   const ossim_uint32 BANDS = theBandSelector->getNumberOfInputBands();
   vector<ossim_uint32> bandList;
   ossim_uint32 count = theDialog->theSelectedBandsListBox->count();
   
   for (ossim_uint32 i = 0; i < count; ++i)
   {
      ossim_uint32 band = 0;
      ossimString s = (const char*)theDialog->theSelectedBandsListBox->
         item(i)->text();
      if (!s.empty())
      {
         band = (ossim_uint32)atoi(s.c_str());
         if (band > 0 && band <= BANDS)
         {
            bandList.push_back(band - 1);
         }
         else
         {
            ossimNotify(ossimNotifyLevel_FATAL)
               << "FATAL ossimQtBandSelectorController::applyButtonClicked "
               << "band index is not within range of 0 to " << BANDS << "!"
               << std::endl;
            return;
         }
      }
      else
      {
         ossimNotify(ossimNotifyLevel_FATAL)
            << "FATAL ossimQtBandSelectorController::applyButtonClicked: "
            << "No bands available, the band list is empty!" << std::endl;
         return;
      }
   }

   theBandSelector->enableSource();
   theBandSelector->setOutputBandList(bandList);

   // since no bounding rects change just iuue a repaint by flushing the
   // display cache else we would issue a flushAllOutputs.
   //
   ossimQtDisplayUtility::flushAllOutputs(theBandSelector);
}

void ossimQtBandSelectorController::greyButtonClicked()
{
   setModeId(ossimQtBandSelectorController::GREY);
}

void ossimQtBandSelectorController::trueButtonClicked()
{
   setModeId(ossimQtBandSelectorController::TRUE_COLOR);
}

void ossimQtBandSelectorController::nBandButtonClicked()
{
   setModeId(ossimQtBandSelectorController::NBAND);
}

void ossimQtBandSelectorController::availableBandClicked(QListBoxItem* item)
{
   QString s = item->text();
      
   switch(getModeId())
   {
      case ossimQtBandSelectorController::GREY:
         theDialog->theSelectedBandsListBox->clear();
         theDialog->theSelectedBandsListBox->insertItem(s);
         break;

      case ossimQtBandSelectorController::TRUE_COLOR:
         theDialog->theSelectedBandsListBox->changeItem(s,
                                                        theTrueColorPosition);
         ++theTrueColorPosition;
         if (theTrueColorPosition > 2)
         {
            theTrueColorPosition = 0;
         }

         // Highlight the next band in the selected list.
         theDialog->theSelectedBandsListBox->setSelected(theTrueColorPosition,
                                                         true);
         break;

      
      default:
         break;
   }
}

void ossimQtBandSelectorController::initListBoxes() const
{
   if (!theBandSelector) return;

   
   theDialog->theAvailableBandsListBox->clear();

   const ossim_uint32 BANDS = theBandSelector->getNumberOfInputBands();
   ossim_uint32 band;

   for (band = 0; band < BANDS; ++band)
   {
      QString item = ossimString::toString(band+1).c_str();
      theDialog->theAvailableBandsListBox->insertItem(item);
   }

   // Update the selected list box.
   theDialog->theSelectedBandsListBox->clear();
   vector<ossim_uint32> bandList;
   theBandSelector->getOutputBandList(bandList);

   if (getModeId() == ossimQtBandSelectorController::GREY)
   {
      theDialog->theSelectedBandsListBox->
         setSelectionMode(QListBox::NoSelection);

      QString band1 = "1";

      if (bandList.size() == 1)
      {
         band1 = ossimString::toString(bandList[0]+1).c_str();
      }

      theDialog->theSelectedBandsListBox->insertItem(band1);
   }
   else if (getModeId() == ossimQtBandSelectorController::TRUE_COLOR)
   {
      theDialog->theSelectedBandsListBox->
         setSelectionMode(QListBox::Single);

      QString band1;
      QString band2;
      QString band3;

      if (bandList.size() > 2)
      {
         band1 = ossimString::toString(bandList[0]+1).c_str();
         band2 = ossimString::toString(bandList[1]+1).c_str();
         band3 = ossimString::toString(bandList[2]+1).c_str();
      }
      else if (theBandSelector->getNumberOfInputBands() > 2)
      {
         band1 = "1";
         band2 = "2";
         band3 = "3";
      }
      else
      {
         band1 = "1";
         band2 = "1";
         band3 = "1";
      }

      theDialog->theSelectedBandsListBox->insertItem(band1);
      theDialog->theSelectedBandsListBox->insertItem(band2);
      theDialog->theSelectedBandsListBox->insertItem(band3);

      theDialog->theSelectedBandsListBox->setSelected(theTrueColorPosition,
                                                      true);
   }
   else // NBand
   {
      theDialog->theSelectedBandsListBox->setSelectionMode(QListBox::Single);

      for (band = 0; band < bandList.size(); ++band)
      {
         QString item = ossimString::toString(bandList[band]+1).c_str();
         theDialog->theSelectedBandsListBox->insertItem(item);
      }
   }
}

void ossimQtBandSelectorController::hideButtons() const
{
   if (!theDialog) return;
   
   theDialog->theClearButton->hide();
   theDialog->theAllButton->hide();
   theDialog->theRightButton->hide();
   theDialog->theLeftButton->hide();
   theDialog->theUpButton->hide();
   theDialog->theDownButton->hide();
   theDialog->theMoveToTopButton->hide();
   theDialog->theMoveToBottomButton->hide();
}

void ossimQtBandSelectorController::showButtons() const
{
   theDialog->theClearButton->show();
   theDialog->theAllButton->show();
   theDialog->theRightButton->show();
   theDialog->theLeftButton->show();
   theDialog->theUpButton->show();
   theDialog->theDownButton->show();
   theDialog->theMoveToTopButton->show();
   theDialog->theMoveToBottomButton->show();
}

void ossimQtBandSelectorController::setBandSelector(ossimBandSelector* bandSelector)
{
   if(theBandSelector)
   {
      theBandSelector->removeListener((ossimConnectableObjectListener*)this);
   }
   
   theBandSelector = bandSelector;
   
   if(theBandSelector)
   {
      theBandSelector->addListener((ossimConnectableObjectListener*)this);
   }

   // This will set up the list boxes.
   setModeId();
}

void ossimQtBandSelectorController::setModeId()
{
   if (!theBandSelector) return;

   vector<ossim_uint32> bandList;
   theBandSelector->getOutputBandList(bandList);
   const ossim_uint32 BANDS = bandList.size();
   
   int mode = ossimQtBandSelectorController::GREY;
   if (BANDS == 3)
   {
      mode = ossimQtBandSelectorController::TRUE_COLOR;
   }
   else if (BANDS == 2 || BANDS > 3)
   {
      mode = ossimQtBandSelectorController::NBAND;
   }
   setModeId(mode);
}

void ossimQtBandSelectorController::setModeId(int id)
{
   if (!theDialog) return;

   if (theCurrentMode != id)
   {
      // If grey or true hide the control buttons.
      if ( id == ossimQtBandSelectorController::GREY ||
           id == ossimQtBandSelectorController::TRUE_COLOR )
      {
         hideButtons();
      }
      else
      {
         showButtons();
      }
      
      if (getModeId() != id)
      {
         theDialog->theImageTypeButtonGroup->setButton(id);
      }
      
      initListBoxes();

      theCurrentMode = id;
   }
}

int ossimQtBandSelectorController::getModeId() const
{
   if (!theDialog) return 0;
   
   QButton* selected_button = theDialog->theImageTypeButtonGroup->selected();
   return theDialog->theImageTypeButtonGroup->id(selected_button);
}

// Private to disallow copy constructor, assignment operator use...
ossimQtBandSelectorController::ossimQtBandSelectorController(const ossimQtBandSelectorController&)
   :
      ossimConnectableObjectListener(),
      theDialog(NULL),
      theBandSelector(NULL),
      theTrueColorPosition(0),
      theCurrentMode(ossimQtBandSelectorController::UNKNOWN)
{
}

ossimQtBandSelectorController& ossimQtBandSelectorController::operator=(const ossimQtBandSelectorController&)
{
   return *this;
}
