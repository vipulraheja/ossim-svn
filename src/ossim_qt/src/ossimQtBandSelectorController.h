//*******************************************************************
// Copyright (C) 2003 ImageLinks Inc. 
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
// Author:  David Burken <dburken@imagelinks.com>
// 
// Description:
// Main interface between the band selector dialog box and the band selector
// from the image chain.
//
//*************************************************************************
// $Id: ossimQtBandSelectorController.h 9114 2006-06-14 17:42:07Z gpotts $
#ifndef ossimQtBandSelectorController_HEADER
#define ossimQtBandSelectorController_HEADER

#include <qstringlist.h>
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimObjectDestructingEvent.h>


class ossimQtBandSelectorDialog;
class ossimBandSelector;

class ossimQtBandSelectorController : public ossimConnectableObjectListener
{
public:

   enum ModeId
   {
      UNKNOWN = -1,
      GREY        =  0,
      TRUE_COLOR    =  1,
      NBAND   =  2
   };

   ossimQtBandSelectorController(ossimQtBandSelectorDialog* dialog);
   virtual ~ossimQtBandSelectorController();

   virtual void objectDestructingEvent(ossimObjectDestructingEvent& event);

   void clearButtonClicked()        const;
   void allButtonClicked()          const;
   void rightButtonClicked()        const;
   void leftButtonClicked()         const;
   void upButtonClicked()           const;
   void downButtonClicked()         const;
   void moveToTopButtonClicked()    const;
   void moveToBottomButtonClicked() const;
   void applyButtonClicked()        const;
   void greyButtonClicked();
   void trueButtonClicked();
   void nBandButtonClicked();
   void availableBandClicked(QListBoxItem* item);

   void setBandSelector(ossimBandSelector* bandSelector);
   
private:
   void updateListBoxes() const;
   void setModeId();
   void setModeId(int mode);
   int  getModeId() const;
   void initListBoxes() const;
   void hideButtons() const;
   void showButtons() const;

   // Disallow copy  constructor, assignment operator.
   ossimQtBandSelectorController( const ossimQtBandSelectorController&);
   ossimQtBandSelectorController& operator=( const ossimQtBandSelectorController&);
   
   ossimQtBandSelectorDialog* theDialog;
   ossimBandSelector*         theBandSelector;
   int                        theTrueColorPosition;
   int                        theCurrentMode;
};

#endif
