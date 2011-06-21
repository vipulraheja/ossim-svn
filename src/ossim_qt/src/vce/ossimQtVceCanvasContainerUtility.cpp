//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  See top level LICENSE.txt file.
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtVceCanvasContainerUtility.cpp 9114 2006-06-14 17:42:07Z gpotts $
#include <algorithm>
#include "ossimQtVceCanvasContainerUtility.h"
#include "ossimQtVceCanvasWidget.h"
#include <ossim/base/ossimKeywordNames.h>
#include "ossimQtVceImageSourceObject.h"
#include "ossimQtVceImageDisplayObject.h"
#include "ossimQtVceShapeRect.h"
#include "ossimQtVceConnectionObject.h"
#include "ossimQtVceImageHandlerObject.h"

ossimQtVceCanvasContainerUtility::ossimQtVceCanvasContainerUtility(ossimQtVceCanvasWidget* canvasWidget)
   :theCanvas(canvasWidget)
{
}

ossimQtVceCanvasContainerUtility::~ossimQtVceCanvasContainerUtility()
{
   theCanvas = NULL;
}

void ossimQtVceCanvasContainerUtility::copyFromKeywordlist(const ossimKeywordlist& kwl,
                                                           const char* prefix)
{  
   theCanvas->unselectItems();
   theIdMap.clear();
   std::map<int, std::vector<int> > idMapping;   
   addAllObjects(idMapping,
                 kwl,
                 prefix);
   
   connectAllObjects(idMapping);
   
   resetIds();
   initialize();
   theIdMap.clear();
}

ossimQtVceShape* ossimQtVceCanvasContainerUtility::findObject(int id)
{
   ossimQtVceShape* vceShape = NULL;

   if(id >= 0)
   {
      std::map<int, ossimQtVceShape*>::iterator iter = theIdMap.find(id);

      if(iter != theIdMap.end())
      {
         vceShape = (*iter).second;
      }
   }
   
   return vceShape;
}

const ossimQtVceShape* ossimQtVceCanvasContainerUtility::findObject(int id)const
{
   const ossimQtVceShape* vceShape = NULL;

   if(id >= 0)
   {
      std::map<int, ossimQtVceShape*>::const_iterator iter = theIdMap.find(id);

      if(iter != theIdMap.end())
      {
         vceShape = (*iter).second;
      }
   }
   
   return vceShape;
}

void ossimQtVceCanvasContainerUtility::addAllObjects(std::map<int, std::vector<int> >& idMapping,
                                                     const ossimKeywordlist& kwl,
                                                     const char* prefix)
{
   
   const char* type = kwl.find(prefix, ossimKeywordNames::TYPE_KW);
   if(ossimString(type) == "ossimQtVceCanvasWidget")
   {
      ossimString copyPrefix = prefix;
      ossimString regExpression =  ossimString("^(") + copyPrefix + "object[0-9]+.)";
      std::vector<ossimString> keys =
         kwl.getSubstringKeyList( regExpression );
      long numberOfObjects = keys.size();
      
      if(numberOfObjects > 0)
      {
	 int offset = (copyPrefix+"object").size();
	 int idx = 0;
	 std::vector<int> theNumberList(numberOfObjects);
	 for(idx = 0; idx < (int)theNumberList.size();++idx)
         {
            ossimString numberStr(keys[idx].begin() + offset,
                                  keys[idx].end());
            theNumberList[idx] = numberStr.toInt();
         }
	 std::sort(theNumberList.begin(), theNumberList.end());
	 for(idx=0;idx < (int)theNumberList.size();++idx)
         {
            ossimString newPrefix = copyPrefix;
            newPrefix += ossimString("object");
            newPrefix += ossimString::toString(theNumberList[idx]);
            newPrefix += ossimString(".");
            
            
            const char* vceShapeType = kwl.find(newPrefix.c_str(),
                                                ossimKeywordNames::TYPE_KW);
            
            if(vceShapeType)
            {
               ossimQtVceShape* vceShape = createShape(vceShapeType);
               
               if(vceShape)
               {
                  if(vceShape->loadState(kwl,
                                         newPrefix.c_str()))
                  {
                     std::vector<int> connectionIds;
                     vceShape->setX(vceShape->x() + 10);
                     vceShape->setY(vceShape->y() + 10);
                     vceShape->setSelected(true);
                     vceShape->show();
                     theCanvas->theSelectedItems.push_back(vceShape);
                     theIdMap.insert(std::make_pair(vceShape->getId(),
                                                    vceShape));
                     findInputConnectionIds(connectionIds,
                                            kwl,
                                            newPrefix);
                     if(connectionIds.size() > 0)
                     {
                        idMapping.insert(std::make_pair(vceShape->getId(),
                                                        connectionIds));
                     }
                  }
                  else
                  {
                     delete vceShape;
                     vceShape = NULL;
                  }
               }
            }
         }
      }
   }
}

void ossimQtVceCanvasContainerUtility::findInputConnectionIds(std::vector<int>& idArray,
                                                              const ossimKeywordlist& kwl,
                                                              const char* prefix)const
{
   ossimString newPrefix = prefix;
   long counter = 0;

   ossimString regExpression =  ossimString("^") + newPrefix + "input_connection[0-9]+";
   std::vector<ossimString> keys =
      kwl.getSubstringKeyList( regExpression );
   long numberOfKeys = keys.size();
   if(numberOfKeys > 0)
   {
      int offset = (newPrefix+"input_connection").size();
      int idx = 0;
      std::vector<int> numberList(numberOfKeys);
      for(idx = 0; idx < (int)numberList.size();++idx)
      {
         ossimString numberStr(keys[idx].begin() + offset,
                               keys[idx].end());
         numberList[idx] = numberStr.toInt();
      }
      std::sort(numberList.begin(), numberList.end());
      
      for(idx = 0; idx < (int)numberList.size(); ++ idx)
      {
         const char* lookup = kwl.find(ossimString(prefix)+
                                       ossimString("input_connection")+
                                       ossimString::toString(numberList[idx]));
         if(lookup)
         {
            int id = ossimString(lookup).toInt();
            idArray.push_back(id);
         }
         ++counter;
      }
   }
}

ossimQtVceShape* ossimQtVceCanvasContainerUtility::createShape(const ossimString& type)
{
  ossimQtVceShape* shapeResult = (ossimQtVceShape*)NULL;

  if(type == "ossimQtVceImageSourceObject")
  {
     shapeResult = new ossimQtVceImageSourceObject(theCanvas->canvas(), theCanvas);
  }
  
  return shapeResult;
}

bool ossimQtVceCanvasContainerUtility::copySelectedToKeywordlist(ossimKeywordlist& kwl,
                                                                 const char* prefix)const
{
   std::vector<QCanvasItem*> canvasItems;
   
   theCanvas->getSelectedItems(canvasItems);
   
   return copyToKeywordlist(canvasItems,
                            kwl,
                            prefix);
}

bool ossimQtVceCanvasContainerUtility::copyCanvasStateToKeywordList(ossimKeywordlist& kwl,
                                                                    const char* prefix)const
{
   std::vector<QCanvasItem*> canvasItems;

   QCanvasItemList allItems = theCanvas->canvas()->allItems();

   for(int idx = 0; idx < (int)allItems.size();++idx)
   {
      canvasItems.push_back(allItems[idx]);
   }
   
   return copyToKeywordlist(canvasItems,
                            kwl,
                            prefix);
}

void ossimQtVceCanvasContainerUtility::connectAllObjects(std::map<int, std::vector<int> >& idMapping)
{
   std::map<int, std::vector<int> >::iterator mapIter = idMapping.begin();
   int idx = 0;
   
   while(mapIter != idMapping.end())
   {
      ossimQtVceShape* endObj = findObject((*mapIter).first);

      if(endObj)
      {
         ossimQtVceConnectableObject* endConnectableObj = endObj->castToConnectable();
         if(endConnectableObj)
         {
            for(idx = 0; idx < (int)((*mapIter).second.size());++idx)
            {
               ossimQtVceShape* startObj = findObject(((*mapIter).second)[idx]);
               if(startObj)
               {
                  if(startObj->castToConnectable())
                  {
                     theCanvas->makeConnection(startObj->castToConnectable(),
                                               endConnectableObj);
                  }
               }
            }
         }
      }
      
      ++mapIter;
   }
   
}

void ossimQtVceCanvasContainerUtility::resetIds()
{
   std::map<int, ossimQtVceShape* >::iterator mapIter = theIdMap.begin();

   while(mapIter != theIdMap.end())
   {
      if((*mapIter).second)
      {
         (*mapIter).second->setNewId();
      }
      
      ++mapIter;
   }
}

void ossimQtVceCanvasContainerUtility::initialize()
{
   std::map<int, ossimQtVceShape* >::iterator mapIter = theIdMap.begin();

   while(mapIter != theIdMap.end())
   {
      if((*mapIter).second)
      {
         (*mapIter).second->initialize();
      }
      
      ++mapIter;
   }
}

bool ossimQtVceCanvasContainerUtility::copyToKeywordlist(const std::vector<QCanvasItem*>& canvasItems,
                                                         ossimKeywordlist& kwl,
                                                         const char* prefix)const
{
   int objCount = 0;
   for(int idx = 0; idx < (int)canvasItems.size(); ++idx)
   {
      ossimQtVceShape* vceShape = ossimQtVceShape::castToVceShape(canvasItems[idx]);
      
      if(vceShape)
      {
         // currently I don't want to save off connections since these are already
         // understood by the connectable shapes.  I may have to save it later though.
         //
         //
         if(!vceShape->castToConnection())
         {
            ossimString newPrefix = ossimString(prefix) + "object" + ossimString::toString(objCount) + ".";
            vceShape->saveState(kwl,
                                   newPrefix.c_str());
            ++objCount;
         }
      }
   }

   return (objCount > 0);
}
