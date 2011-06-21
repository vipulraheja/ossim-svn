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
//
// Contains class declaration for the class ossimQWidgetFactoryRegistry.
//
//*******************************************************************
// $Id: ossimQWidgetFactoryRegistry.h 5886 2004-01-13 18:29:33Z gpotts $
#ifndef ossimQWidgetFactoryRegistry_HEADER
#define ossimQWidgetFactoryRegistry_HEADER

#include <vector>

class ossimQWidgetFactoryInterface;
class ossimObject;
class QWidget;

class ossimQWidgetFactoryRegistry
{
public:
   
   virtual ~ossimQWidgetFactoryRegistry();

   static ossimQWidgetFactoryRegistry* instance();
   
   void addFactory(ossimQWidgetFactoryInterface* factory);

   void registerFactory(ossimQWidgetFactoryInterface* factory);

   virtual QWidget* createEditor(ossimObject* obj,
                                 QWidget* parent,
                                 unsigned int f = 0) const;

protected:
   ossimQWidgetFactoryRegistry();
   
private:
   ossimQWidgetFactoryRegistry(const ossimQWidgetFactoryRegistry& rhs);
   const ossimQWidgetFactoryRegistry& operator=(const ossimQWidgetFactoryRegistry& rhs);
   
   void clear();
   
   std::vector<ossimQWidgetFactoryInterface*> theFactoryList;
   static ossimQWidgetFactoryRegistry* theInstance;
};

#endif /* #ifndef ossimQWidgetFactoryRegistry_HEADER */
