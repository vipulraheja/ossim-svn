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
// $Id: ossimQtVceComponentView.cpp 9114 2006-06-14 17:42:07Z gpotts $
#include "ossimQtVceComponentView.h"
#include <ossim/base/ossimObjectFactoryRegistry.h>


ossimQtVceComponentView::ossimQtVceComponentView(QWidget *parent,
                                       const char *name,
                                       WFlags f)
   :QIconView(parent, name, f)
{
   setSorting(true);
   setSelectionMode(Extended);
}

void ossimQtVceComponentView::setFilterString(const ossimString& filterString)
{
   theFilterString = filterString;
   reload();
}

void ossimQtVceComponentView::reload()
{
   loadComponentView();
}
 
void ossimQtVceComponentView::loadComponentView()
{
#if 0
   if(theFilterString != "")
   {
      clear();
      std::vector<ossimString> typeList;
      
      if(theFilterString == "Display")
      {
         
            loadDisplay(typeList,
                        "display");
      }
      else
      {
      }

      else if(theFilterString == "ossimImageHandler")
      {
         ossimQtVceComponentIcon* item = new ossimQtVceComponentIcon(this);
         
         item->setPixmap(QPixmap::fromMimeSource("dataextract"));
         item->setText("ImageHandler");
         item->setHiddenText("ossimImageHandler");
         insertItem(item);
      }
      else
      {
         ossimObjectFactoryRegistry::instance()->getTypeNameList(typeList,
                                                                 theFilterString);
         
         if(typeList.size())
         {
            ossimString pixmapName = "";
            if(theFilterString == "ossimImageFileWriter")
            {
               pixmapName = "datastore";
            }
            else if(theFilterString == "ossimImageCombiner")
            {
               pixmapName = "tilecascade";
            }
            else if(theFilterString == "ossimImageSourceFilter")
            {
               pixmapName = ""; // we don't have one yet for this type
            }
            loadIconsFromMime(typeList,
                              pixmapName);
         }
      }
   }
#endif
}

void ossimQtVceComponentView::loadDisplay(std::vector<ossimString>& /*typeNameList*/,
                                          const ossimString& name)
{
   // later I need to add a display factory for the Qt.  For now
   // we will just hard code it.  This will be easy to change this
   // to a factory implementation later.
   //
   ossimQtVceComponentIcon* item = new ossimQtVceComponentIcon(this);
   item->setPixmap(QPixmap::fromMimeSource(name.c_str()));
   item->setText("ImageWindow");
   item->setHiddenText("ossimQtImageWindow");
   insertItem(item);
}


void ossimQtVceComponentView::loadIconsFromMime(std::vector<ossimString>& typeNameList,
                                           const ossimString& name)
{
   for(int idx = 0; idx < (int)typeNameList.size();++idx)
   {
      ossimQtVceComponentIcon* item = new ossimQtVceComponentIcon(this);
      item->setPixmap(QPixmap::fromMimeSource(name.c_str()));
      item->setHiddenText(typeNameList[idx].c_str());
      ossimString tempString = typeNameList[idx];
      tempString = tempString.substitute("ossim",
                                         "");
      tempString = tempString.substitute("imglnk",
                                         "");
      item->setText(tempString.c_str());
      insertItem(item);
   }
}



void ossimQtVceComponentView::getSelected(std::vector<QIconViewItem*>& items)
{
   QIconViewItem* i = firstItem();

   while(i)
   {
      if(i->isSelected())
      {
         items.push_back(i);
      }
      i = i->nextItem();
   }
}

void ossimQtVceComponentView::startDrag()
{
   QDragObject *drag = dragObject();
   
    if ( !drag )
       return;
    
    if ( drag->drag() )
	if ( drag->target() != viewport() )
	    emit moved();
}

QDragObject *ossimQtVceComponentView::dragObject()
{
   std::vector<QIconViewItem*> selectionList;
   getSelected(selectionList);
   
   if(selectionList.size() < 1)
   {
      return NULL;
   }
   
   QTextDrag* textDrag = new QTextDrag(viewport());
   
   QString kwlString = "type:ossimQtVceComponentView\n";

   for(int idx = 0; idx < (int)selectionList.size();++idx)
   {
      kwlString = kwlString + "object" + QString::number(idx) + ".type: " + ((ossimQtVceComponentIcon*)selectionList[idx])->hiddenText();
      kwlString = kwlString + "\n";
   }
   textDrag->setText(kwlString);
   
   return textDrag;
}

