//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  See top level LICENSE.txt file.
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtEvent.cpp 9049 2006-05-08 20:16:29Z dburken $
#include "ossimQtEvent.h"

void ossimQtDisplayListEvent::addDisplay(QObject* display)
{
   if(display)
   {
      if(theDisplayList.find(display) == theDisplayList.end())
      {
         theDisplayList.insert(std::make_pair(display, display));
      }
   }
}

void ossimQtDisplayListEvent::eraseDisplay(QObject* display)
{
   std::map<QObject*, QObject*>::iterator iter = theDisplayList.find(display);

   if(iter != theDisplayList.end())
   {
      theDisplayList.erase(iter);
   }
}

QObject* ossimQtDisplayListEvent::firstDisplay()
{
   theDisplayListIterator = theDisplayList.begin();

   if(theDisplayList.size() > 0)
   {
      return (*theDisplayListIterator).first;
   }
   return NULL;
}

QObject* ossimQtDisplayListEvent::nextDisplay()
{
   ++theDisplayListIterator;
   if(theDisplayListIterator != theDisplayList.end())
   {
      return (*theDisplayListIterator).first;
   }
   
   return NULL;
}

