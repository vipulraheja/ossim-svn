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
// $Id: ossimQtApplicationUtility.h 5756 2003-12-12 19:20:12Z gpotts $
#ifndef ossimQtApplicationUtility_HEADER
#define ossimQtApplicationUtility_HEADER

class QObject;
class QEvent;
class ossimQtApplicationUtility
{
public:
  static QObject* getRoot(QObject* obj);
  static void postEventToRoot(QObject* obj, 
                              QEvent* event);
   static void sendEventToRoot(QObject* obj, 
                               QEvent* event);
};

#endif
