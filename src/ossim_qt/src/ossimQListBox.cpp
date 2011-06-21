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
// Class definition for ossimQListBox.
// Derived from QListBox.
// A QT QListBox with added stuff...
//
//*************************************************************************
// $Id: ossimQListBox.cpp 4731 2003-07-18 15:17:56Z dburken $

#include <qstringlist.h>
#include "ossimQListBox.h"


ossimQListBox::ossimQListBox(QWidget* parent,
                             const char* name,
                             WFlags f)
   :
      QListBox(parent, name, f) // base class.
{
   setSelectionMode(QListBox::Extended);
}

void ossimQListBox::getSelectedList(QStringList& selectedList) const
{
   // Start with a clean list.
   selectedList.clear();

   //---
   // Go through all items os the list box and stuff the selected ones in
   // the list.
   //---
   for ( unsigned int i = 0; i < count(); ++i )
   {
      if (item(i)->isSelected())
      {
         if ( !item(i)->text().isEmpty() )
         {
            // Add it to the list.
            selectedList.push_back(item(i)->text());
         }
      }
   }   
}

// private copy constructor.
ossimQListBox::ossimQListBox(const ossimQListBox& /* rhs */)
   :
      QListBox(NULL, NULL, 0)
{}

// private operator=
ossimQListBox& ossimQListBox::operator=(const ossimQListBox& /* rhs */)
{
   return *this;
}
