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
// Author:  David Burken
//
// Description:
//
// Contains class definition for ossimQWidgetFactorRegistry.
//
//*******************************************************************
// $Id: ossimQWidgetFactoryRegistry.cpp 9114 2006-06-14 17:42:07Z gpotts $

#include <iostream>
using namespace std;

#include <qwidget.h>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimNotifyContext.h>
#include "ossimQWidgetFactoryRegistry.h"
#include "ossimQWidgetEditorFactory.h"
#include "ossimQWidgetFactoryInterface.h"

ossimQWidgetFactoryRegistry* ossimQWidgetFactoryRegistry::theInstance = NULL;

ossimQWidgetFactoryRegistry::ossimQWidgetFactoryRegistry()
   :
      theFactoryList()
{
}

ossimQWidgetFactoryRegistry* ossimQWidgetFactoryRegistry::instance()
{
   if (theInstance == NULL)
   {
      theInstance = new ossimQWidgetFactoryRegistry();
      theInstance->registerFactory(ossimQWidgetEditorFactory::instance());
   }
   return theInstance;
}

ossimQWidgetFactoryRegistry::~ossimQWidgetFactoryRegistry()
{
   clear();
   if (theInstance)
   {
      delete theInstance;
      theInstance = NULL;
   }
}

void ossimQWidgetFactoryRegistry::addFactory(ossimQWidgetFactoryInterface* factory)
{
   registerFactory(factory);
}

void ossimQWidgetFactoryRegistry::registerFactory(ossimQWidgetFactoryInterface* factory)
{
   if(factory)
   {
      theFactoryList.push_back(factory);
   }
}

QWidget* ossimQWidgetFactoryRegistry::createEditor(ossimObject* obj,
                                                   QWidget* parent,
                                                   unsigned int f) const
{
   QWidget* result = NULL;
   
   if (!obj)
   {
      ossimNotify(ossimNotifyLevel_FATAL) << "FATAL ossimQWidgetEditorFactory::createEditor: NULL obj passed in!" << std::endl;
      return result;
   }
   if (!parent)
   {
      ossimNotify(ossimNotifyLevel_FATAL) << "FATAL ossimQWidgetEditorFactory::createEditor: NULL parent passed in!" << std::endl;
      return result;
   }

   vector<ossimQWidgetFactoryInterface*>::const_iterator factory;
   factory = theFactoryList.begin();
   while((factory != theFactoryList.end()) && !result)
   {
     result = (*factory)->createEditor(obj, parent, f);
     ++factory;
   }
   
   return result;
}

void ossimQWidgetFactoryRegistry::clear()
{
   theFactoryList.clear();
}

ossimQWidgetFactoryRegistry::ossimQWidgetFactoryRegistry(const ossimQWidgetFactoryRegistry&)
{}

const ossimQWidgetFactoryRegistry&
ossimQWidgetFactoryRegistry::operator=(const ossimQWidgetFactoryRegistry& rhs)
{ return rhs; }
