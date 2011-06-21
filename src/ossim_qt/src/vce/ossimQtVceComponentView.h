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
// $Id: ossimQtVceComponentView.h 9114 2006-06-14 17:42:07Z gpotts $
#ifndef ossimQtVceComponentView_HEADER
#define ossimQtVceComponentView_HEADER
#include <vector>
#include <qiconview.h>
#include <qwidgetplugin.h>
#include <qstring.h>
#include <ossim/base/ossimString.h>

class ossimQtVceComponentView : public QIconView
{
   Q_OBJECT
public: 
   class ossimQtVceComponentIcon : public QIconViewItem
   {
   public:
      ossimQtVceComponentIcon(QIconView * parent)
         :QIconViewItem(parent)
      {
      }
         void setHiddenText(const QString& txt)
         {
            theHiddenText = txt;
         }
         const QString& hiddenText()const
         {
            return theHiddenText;
         }
         
         QString theHiddenText;
   };
   
   ossimQtVceComponentView(QWidget *parent,
                      const char *name="Vce Icon View",
                      WFlags f=0);
   void setFilterString(const ossimString& filterString);
   ossimString getFilterString()const;
   void reload();

public slots:
 
   void getSelected(std::vector<QIconViewItem*>& items);
   
protected:
   ossimString theFilterString;

   void loadComponentView();

   void loadIconsFromMime(std::vector<ossimString>& typeNameList,
                          const ossimString& name);

   void loadDisplay(std::vector<ossimString>& typeNameList,
                    const ossimString& name);
   
   virtual QDragObject *dragObject();
   virtual void startDrag();
   

};

#endif
