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
// $Id: ossimQtLayerEditorController.h 5757 2003-12-12 19:50:32Z gpotts $
#ifndef ossimQtLayerEditorController_HEADER
#define ossimQtLayerEditorController_HEADER
#include <qobject.h>
#include <qstringlist.h>

class ossimQtLayerEditor;
class QListBoxItem;

class ossimQtLayerEditorController : public QObject
{
   Q_OBJECT
public:
   ossimQtLayerEditorController(ossimQtLayerEditor* layerEditor);

   static const char* EMPTY_SLOT_STRING;
   const char* getEmptySlotString()const;
   void setMaxNumberOfInputs(int maxNumber);
public slots:
   virtual void upButtonClicked();
   virtual void downButtonClicked();
   virtual void addLayerButtonClicked();
   virtual void removeLayerButtonClicked();

protected:
   ossimQtLayerEditor* theEditor;
   int                 theMaxNumberOfInputs;
   void swapInputListBoxItems(QListBoxItem* item1, 
                              QListBoxItem* item2);
   int numberOfEmptySlots()const;
   int insertIntoEmptySlot(int idx,
                           const QString& value);

signals:
   void movingSelectedLayersUp(bool& canMoveUpFlag);
   void movingSelectedLayersDown(bool& canMoveDownFlag);
   void removingSelectedLayersFromInput(bool& canRemoveSelected);
   void addingSelectedLayersToInput(bool& canAddSelected);
   void inputLayersChanged();
   void getInputLayers(QStringList& stringList);
};

#endif
