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
// $Id: ossimQtDisplayUtility.cpp 9114 2006-06-14 17:42:07Z gpotts $
#include "ossimQtDisplayUtility.h"
#include <qapplication.h>
#include "ossimQtEvent.h"
#include <ossim/base/ossimDisplayListEvent.h>
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimPropertyEvent.h>

void ossimQtDisplayUtility::flushAllOutputs(ossimConnectableObject* obj, bool doDisplaysFlag)
{
  if(!obj) return;
   ossimPropertyEvent evt(obj);
   obj->fireEvent(evt);
   obj->propagateEventToOutputs(evt);

   if(doDisplaysFlag)
     {
       findAndFlushAllConnectedDisplays(obj);
     }
}

void ossimQtDisplayUtility::refreshAllOutputs(ossimConnectableObject* obj, bool doDisplaysFlag)
{
  if(!obj) return;
   ossimPropertyEvent evt(obj);
   obj->fireEvent(evt);
   obj->propagateEventToOutputs(evt);

   if(doDisplaysFlag)
     {
       findAndRefreshAllConnectedDisplays(obj);
     }
}


void ossimQtDisplayUtility::findAndRefreshAllConnectedDisplays(ossimConnectableObject* obj)
{
  if(!obj) return;
  std::map<QObject*, QObject*> displayList;

  findAllDisplays(displayList, obj);
  refreshAllDisplays(displayList);
}

void ossimQtDisplayUtility::findAndFlushAllConnectedDisplays(ossimConnectableObject* obj)
{
  if(!obj) return;
  std::map<QObject*, QObject*> displayList;

  findAllDisplays(displayList, obj);
  flushAllDisplays(displayList);
}

void ossimQtDisplayUtility::findAllDisplays(std::map<QObject*, QObject*>& displayList,
					    ossimConnectableObject* obj)
{
  if(!obj) return;
  ossimDisplayListEvent displayListEvent(obj);

  ossimConnectableObject* root = getRoot(obj);
  root->propagateEventToOutputs(displayListEvent);

  QObject* display = NULL;
  display = (QObject*)displayListEvent.firstDisplay();
  if(display)
  {
     do
     {
        if(displayList.find(display) == displayList.end())
        {
           displayList.insert(std::make_pair((QObject*)display,
                                             (QObject*)display));
        }
     }while((display = (QObject*)displayListEvent.nextDisplay())!=NULL);
  }
}

void ossimQtDisplayUtility::refreshAllDisplays(std::map<QObject*,QObject*>& displayList)
{
  std::map<QObject*, QObject*>::iterator iter = displayList.begin();
  while(iter != displayList.end())
    {
      ossimQtRefreshDisplayEvent* evt = new ossimQtRefreshDisplayEvent;
      QApplication::postEvent((*iter).first, evt);
      ++iter;
    }
}

void ossimQtDisplayUtility::flushAllDisplays(std::map<QObject*,QObject*>& displayList)
{
  std::map<QObject*, QObject*>::iterator iter = displayList.begin();
  while(iter != displayList.end())
  {
      ossimQtFlushDisplayEvent* evt = new ossimQtFlushDisplayEvent;
      QApplication::postEvent((*iter).first, evt);
      ++iter;
  }
}

ossimConnectableObject* ossimQtDisplayUtility::getRoot(ossimConnectableObject* obj)
{
   ossimConnectableObject* root = obj;
   if(!root) return root;
   while(PTR_CAST(ossimConnectableObject, root->getOwner()))
   {
      root=PTR_CAST(ossimConnectableObject, root->getOwner());
   }

   return root;
}
