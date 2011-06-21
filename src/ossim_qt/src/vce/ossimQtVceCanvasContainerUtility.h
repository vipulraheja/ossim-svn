//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  See top level LICENSE.txt file.
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtVceCanvasContainerUtility.h 9114 2006-06-14 17:42:07Z gpotts $
#ifndef ossimQtVceCanvasContainerUtility_HEADER
#define ossimQtVceCanvasContainerUtility_HEADER
#include <map>
#include <ossim/base/ossimKeywordlist.h>

class QCanvasItem;
class ossimQtVceShape;
class ossimQtVceCanvasWidget;
class ossimQtVceCanvasContainerUtility
{
public:
   ossimQtVceCanvasContainerUtility(ossimQtVceCanvasWidget* canvasWidget);
   virtual ~ossimQtVceCanvasContainerUtility();
   virtual void copyFromKeywordlist(const ossimKeywordlist& kwl,
                                    const char* prefix=0);
   ossimQtVceShape* createShape(const ossimString& type);

   bool copySelectedToKeywordlist(ossimKeywordlist& kwl,
                                     const char* prefix=0)const;
   bool copyCanvasStateToKeywordList(ossimKeywordlist& kwl,
                                     const char* prefix=0)const;
protected:
   ossimQtVceCanvasWidget* theCanvas;
   /*!
    * This is used when trying to copy objects from the
    * keywordlist. it takes and id and the object.  This
    * is used for faster searching.
    */
   mutable std::map<int, ossimQtVceShape*> theIdMap;
   
   ossimQtVceShape* findObject(int id);
   const ossimQtVceShape* findObject(int id)const;
   void addAllObjects(std::map<int, std::vector<int> >& idMapping,
                      const ossimKeywordlist& kwl,
                      const char* prefix=0);
   void findInputConnectionIds(std::vector<int>& idArray,
                               const ossimKeywordlist& kwl,
                               const char* prefix = 0)const;
   /*!
    * This is an id mapping so we can do connections.  So for
    * each object there is an array of input id's.
    */
   void connectAllObjects(std::map<int, std::vector<int> >& idMapping);

   void resetIds();
   void initialize();

   bool copyToKeywordlist(const std::vector<QCanvasItem*>& canvasItems,
                          ossimKeywordlist& kwl,
                          const char* prefix=0)const;
};

#endif
