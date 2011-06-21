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
// Class declaration for ossimQListBox.
// Derived from QListBox.
// A QT QListBox with added stuff...
//
//*************************************************************************
// $Id: ossimQListBox.h 6310 2004-05-24 20:11:21Z dburken $
#ifndef ossimQListBox_HEADER
#define ossimQListBox_HEADER

#include <qlistbox.h>
#include <qwidgetplugin.h>
             
class ossimQListBox : public QListBox
{
   Q_OBJECT
      
public:
   ossimQListBox(QWidget* parent = 0,
                 const char* name = 0,
                 WFlags f = 0);

   /*
    * Returns the list of selected string items.
    * Note:  This method clears the QStringList passed to it prior to stuffing
    *        with selected entries.
    */
   void getSelectedList(QStringList& selectedList) const;

private:

   // Hide from use...
   ossimQListBox(const ossimQListBox& rhs);
   ossimQListBox& operator=(const ossimQListBox& rhs);
};

#endif /* #ifndef ossimQListBox_HEADER */
