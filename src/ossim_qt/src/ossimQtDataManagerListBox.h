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
// $Id: ossimQtDataManagerListBox.h 15766 2009-10-20 12:37:09Z gpotts $
#ifndef ossimQtDataManagerListBox_HEADER
#define ossimQtDataManagerListBox_HEADER
#include <qlistbox.h>
#include <vector>
#include <map>
#include <ossim/base/ossimId.h>
#include <ossim/base/ossimConnectableObject.h>
class ossimDataManager;
class ossimConnectableObject;

class ossimQtDataManagerListBox : public QListBox
{
    Q_OBJECT
public:
    ossimQtDataManagerListBox(QWidget* parent=0, 
			      const char* name=0, 
			      WFlags f=0);

   ossimQtDataManagerListBox(ossimConnectableObject::ConnectableObjectList& layers,
                             QWidget* parent=0, 
                             const char* name=0, 
                             WFlags f=0);
   
   void setDataManager(ossimDataManager* dataManager);

   void getSelectedObjects(ossimConnectableObject::ConnectableObjectList& objList);
   void getSelectedObjectsAsIds(std::vector<ossimId>& idList);
   void setObjects(ossimConnectableObject::ConnectableObjectList& objList);
   ossimConnectableObject::ConnectableObjectList getSelectedObjects();
   std::vector<ossimId> getSelectedObjectsAsIds();

public slots:
  void deleteSelectedObjects();
  void duplicateSelectedObjects();
  void mosaicSelectedObjects();
  void blendSelectedObjects();
  void featherSelectedObjects();

protected:
   ossimDataManager* theDataManager;
   mutable bool      theDragStartFlag;
   virtual void contentsMousePressEvent(QMouseEvent* e);
   virtual void contentsMouseMoveEvent(QMouseEvent* e);
   void addObjects(ossimConnectableObject::ConnectableObjectList& objList);
   void addObject(ossimConnectableObject* objList);
   virtual void startDrag();
};

#endif
