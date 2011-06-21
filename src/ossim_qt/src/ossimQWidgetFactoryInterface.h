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
// Base class interface declaration for QWidget factory.
// 
//*******************************************************************
//  $Id: ossimQWidgetFactoryInterface.h 5886 2004-01-13 18:29:33Z gpotts $
#ifndef ossimQWidgetFactoryInterface_HEADER
#define ossimQWidgetFactoryInterface_HEADER

class ossimObject;
class QWidget;

class ossimQWidgetFactoryInterface
{
public:
   ossimQWidgetFactoryInterface();
   
   virtual ~ossimQWidgetFactoryInterface();
   
   virtual QWidget* createEditor(ossimObject* obj,
                                 QWidget* parent,
                                 unsigned int f = 0) const = 0;
};

#endif /* #ifndef ossimQWidgetFactoryInterface_HEADER */
