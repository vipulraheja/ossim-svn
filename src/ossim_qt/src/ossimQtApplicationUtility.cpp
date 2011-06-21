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
// $Id: ossimQtApplicationUtility.cpp 5756 2003-12-12 19:20:12Z gpotts $
#include <qobject.h>
#include <qevent.h>
#include <qapplication.h>
#include "ossimQtApplicationUtility.h"

QObject* ossimQtApplicationUtility::getRoot(QObject* obj)
{
   if(!obj) return NULL;
   QObject* current = obj;
   while(current->parent())
   {
      current = current->parent();
   }
   
   return current;
}

void ossimQtApplicationUtility::postEventToRoot(QObject* obj, 
                                                QEvent* event)
{
   QObject* tempRoot = getRoot(obj);
   QApplication::postEvent(tempRoot, event);
}

void ossimQtApplicationUtility::sendEventToRoot(QObject* obj, 
                                                QEvent* event)
{
   QObject* tempRoot = getRoot(obj);
   QApplication::sendEvent(tempRoot, event);
}
