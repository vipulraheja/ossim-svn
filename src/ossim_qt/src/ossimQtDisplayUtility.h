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
// $Id: ossimQtDisplayUtility.h 5756 2003-12-12 19:20:12Z gpotts $
#ifndef ossimQtDisplayUtility_HEADER
#define ossimQtDisplayUtility_HEADER
#include <map>
class ossimConnectableObject;
class QObject;
class ossimQtDisplayUtility
{
public:

   /*!
    * will force a property event on the passed in object and pass to all
    * outputs.  It will then find and flush all display cache.
    */
  static void flushAllOutputs(ossimConnectableObject* obj, bool doDisplaysFlag=true);

   /*!
    * will force a property event on the passed in object and pass to all
    * outputs.  It will then find and do a complete refresh on all output
    * displays
    */
  static void refreshAllOutputs(ossimConnectableObject* obj, bool doDisplaysFlag=true);
   
  static void findAndRefreshAllConnectedDisplays(ossimConnectableObject* obj);
  static void findAndFlushAllConnectedDisplays(ossimConnectableObject* obj);
  static void refreshAllDisplays(std::map<QObject*,QObject*>& displayList);
  static void flushAllDisplays(std::map<QObject*,QObject*>& displayList);
  static void findAllDisplays(std::map<QObject*,QObject*>& displayList,
			      ossimConnectableObject* obj);
   static ossimConnectableObject* getRoot(ossimConnectableObject* obj);
};

#endif
