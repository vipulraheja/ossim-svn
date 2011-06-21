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
// $Id: ossimQtVceComponentDialogController.cpp 9114 2006-06-14 17:42:07Z gpotts $
#include "ossimQtVceComponentDialogController.h"
#include "ossimQtVceComponentDialog.h"
#include "ossimQtVceComponentView.h"
#include <ossim/base/ossimObjectFactoryRegistry.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimObject.h>


ossimQtVceComponentDialogController::ossimQtVceComponentDialogController(ossimQtVceComponentDialog* window)
{
   theWindow = window;
   loadViews();
//    theWindow->theLoaderComponentView->setFilterString("ossimImageHandler");
//    theWindow->theCombinerComponentView->setFilterString("ossimImageCombiner");
//    theWindow->theFilterComponentView->setFilterString("ossimImageSourceFilter");
//    theWindow->theExporterComponentView->setFilterString("ossimImageFileWriter");
//    theWindow->theDisplayComponentView->setFilterString("Display");
}

ossimQtVceComponentDialogController::~ossimQtVceComponentDialogController()
{
   theWindow = NULL;
}

void ossimQtVceComponentDialogController::loadViews()
{
   std::vector<ossimString> typeList;
   ossimObjectFactoryRegistry::instance()->getTypeNameList(typeList);
   ossim_uint32 idx = 0;

   loadDisplay();
   loadImageHandler();
   QIconView* currentView=0;
   
   ossimString pixmapName;
   for(idx = 0; idx < typeList.size(); ++idx)
   {
      ossimRefPtr<ossimObject> obj = ossimObjectFactoryRegistry::instance()->createObject(typeList[idx]);

      if(obj.valid())
      {
         currentView = 0;
         if(obj->canCastTo("ossimImageHandler"))
         {
            // left blank on purpose
         }
         else if(obj->canCastTo("ossimFusionCombiner"))
         {
            pixmapName = "tilecascade";
            currentView = theWindow->theFusionComponentView;
         }
         else if(obj->canCastTo("ossimImageCombiner"))
         {
            pixmapName = "tilecascade";
            currentView = theWindow->theCombinerComponentView;
         }
         else if(obj->canCastTo("ossimImageFileWriter"))
         {
            currentView = theWindow->theExporterComponentView;
            pixmapName = "datastore";
         }
         else if(obj->canCastTo("ossimMetadataFileWriter"))
         {
            currentView = theWindow->theMetaDataExporterComponentView;
            pixmapName = "datastore";
         }
         else if(obj->canCastTo("ossimImageSourceFilter"))
         {
            pixmapName = ""; // we don't have one yet for this type
            currentView = theWindow->theFilterComponentView;
         }
         else if(obj->canCastTo("ossimProcessInterface"))
         {
            currentView = theWindow->theProcessComponentView;
            pixmapName = "";// we don't have one yet for this type
         }

         if(currentView)
         {
            ossimQtVceComponentView::ossimQtVceComponentIcon* item = new ossimQtVceComponentView::ossimQtVceComponentIcon(currentView);
            item->setPixmap(QPixmap::fromMimeSource(pixmapName.c_str()));
            item->setHiddenText(typeList[idx].c_str());
            ossimString tempString = typeList[idx];
            tempString = tempString.substitute("ossim",
                                               "");
            tempString = tempString.substitute("imglnk",
                                               "");
            item->setText(tempString.c_str());
            currentView->insertItem(item);
         }
      }
   }
}

void ossimQtVceComponentDialogController::loadDisplay()
{
   ossimQtVceComponentView::ossimQtVceComponentIcon* item = new ossimQtVceComponentView::ossimQtVceComponentIcon(theWindow->theDisplayComponentView);
   item->setPixmap(QPixmap::fromMimeSource("display"));
   item->setText("ImageWindow");
   item->setHiddenText("ossimQtImageWindow");
   theWindow->theDisplayComponentView->insertItem(item);
}

void ossimQtVceComponentDialogController::loadImageHandler()
{
   ossimQtVceComponentView::ossimQtVceComponentIcon* item = new ossimQtVceComponentView::ossimQtVceComponentIcon(theWindow->theLoaderComponentView);
   
   item->setPixmap(QPixmap::fromMimeSource("dataextract"));
   item->setText("ImageHandler");
   item->setHiddenText("ossimImageHandler");
   theWindow->theLoaderComponentView->insertItem(item);
}
