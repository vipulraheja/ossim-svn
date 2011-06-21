//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  See top level LICENSE.txt file.
//
// See the GPL in the COPYING.GPL file for more details.
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtVceConnectableObject.cpp 15766 2009-10-20 12:37:09Z gpotts $
#include <sstream>
#include <qpainter.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimIpt.h>
#include "ossimQtVceConnectableObject.h"
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimObjectDestructingEvent.h>
#include <ossim/base/ossimConnectionEvent.h>
#include <ossim/base/ossimPropertyEvent.h>
#include <ossim/base/ossimRefreshEvent.h>
#include <ossim/base/ossimObjectFactoryRegistry.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimNotifyContext.h>
#include "ossimQtVceConnectionObject.h"
#include "ossimQtDisplayUtility.h"

class ossimQtVceConnectableObjectPrivateListener : public ossimConnectableObjectListener
   {
   public:
      ossimQtVceConnectableObjectPrivateListener(ossimQtVceConnectableObject* obj)
      :theVceConnectableObject(obj)
      {}
      virtual void disconnectInputEvent(ossimConnectionEvent& event );
      virtual void connectInputEvent(ossimConnectionEvent& event );
      virtual void connectOutputEvent(ossimConnectionEvent& /* event */);
      virtual void disconnectOutputEvent(ossimConnectionEvent& /* event */);
      virtual void objectDestructingEvent(ossimObjectDestructingEvent& /*event*/);
      virtual void propertyEvent(ossimPropertyEvent& /* event */);
      virtual void refreshEvent(ossimRefreshEvent& /* event */);
      
      ossimQtVceConnectableObject* theVceConnectableObject;
   };

void ossimQtVceConnectableObjectPrivateListener::disconnectInputEvent(ossimConnectionEvent& /*event*/ )
{
   if(theVceConnectableObject)
   {
      theVceConnectableObject->internalInputConnectionChanged();
   }
}

void ossimQtVceConnectableObjectPrivateListener::connectInputEvent(ossimConnectionEvent& /*event*/ )
{
   if(theVceConnectableObject)
   {
      theVceConnectableObject->internalInputConnectionChanged();
   }
}

void ossimQtVceConnectableObjectPrivateListener::connectOutputEvent(ossimConnectionEvent& /* event */)
{
   if(theVceConnectableObject)
   {
      theVceConnectableObject->internalOutputConnectionChanged();
   }
}

void ossimQtVceConnectableObjectPrivateListener::disconnectOutputEvent(ossimConnectionEvent& /* event */)
{
   if(theVceConnectableObject)
   {
      theVceConnectableObject->internalOutputConnectionChanged();
   }
}

void ossimQtVceConnectableObjectPrivateListener::objectDestructingEvent(ossimObjectDestructingEvent& /*event*/)
{
   
}

void ossimQtVceConnectableObjectPrivateListener::propertyEvent(ossimPropertyEvent& /* event */)
{
   if(theVceConnectableObject)
   {
      theVceConnectableObject->internalProperty();
   }
}

void ossimQtVceConnectableObjectPrivateListener::refreshEvent(ossimRefreshEvent& /* event */)
{
   if(theVceConnectableObject)
   {
      theVceConnectableObject->internalRefresh();
   }
}

ossimQtVceConnectableObject::ossimQtVceConnectableObject(QCanvas* canvas,
                                                         QObject* vceParent)
:ossimQtVceShape(canvas, vceParent),
theConnectableObject(NULL)
{
   setX(64);
   setY(64);
   theWidth  = 64;
   theHeight = 64;
   theConnectorSize.setWidth(8);
   theConnectorSize.setHeight(8);
   
   thePrivateListener = new ossimQtVceConnectableObjectPrivateListener(this);
}

ossimQtVceConnectableObject::~ossimQtVceConnectableObject()
{
   thePrivateListener->disableListener();
   disconnectObject();
   theConnectableObject = 0;
}

ossimQtVceConnectableObject* ossimQtVceConnectableObject::castToConnectable()
{
   return this;
}

const ossimQtVceConnectableObject* ossimQtVceConnectableObject::castToConnectable()const
{
   return this;
}

void ossimQtVceConnectableObject::moveBy(double dx, double dy)
{
   ossimQtVceShape::moveBy(dx, dy);
   redrawConnections();
}

void ossimQtVceConnectableObject::draw(QPainter& painter)
{
   ossimQtVceShape::draw(painter);
   drawConnectors(painter);
}

void ossimQtVceConnectableObject::drawConnectors(QPainter& painter)
{
   QBrush oldBrush = painter.brush();
   
   QBrush redBrush(QColor(255,0,0), SolidPattern );
   QBrush greenBrush(QColor(0,255,0), SolidPattern );
   int numberOfInputs  = getNumberOfInputs();
   int numberOfOutputs = getNumberOfOutputs();
   int idx = 0;
   QRect rect;
   QPointArray ptArray(3);
   for(idx = 0; idx < numberOfInputs; ++ idx)
   {
      if(getInputConnectionSlotBoundingRect(rect,
                                            idx))
      {
         int x,y;
         x = rect.x();
         y = rect.y();
         
         ptArray[0] = QPoint(x, y);
         ptArray[1] = QPoint(x+rect.width(), y+rect.height()/2);
         ptArray[2] = QPoint(x, y+rect.height());
         
         if(theInputConnectionArray[idx])
         {
            painter.setBrush(greenBrush);
         }
         else
         {
            painter.setBrush(redBrush);
         }
         painter.drawConvexPolygon(ptArray);
      }
   }
   for(idx = 0; idx < numberOfOutputs; ++ idx)
   {
      if(getOutputConnectionSlotBoundingRect(rect,
                                             idx))
      {
         int x,y;
         x = rect.x();
         y = rect.y();
         
         ptArray[0] = QPoint(x, y);
         ptArray[1] = QPoint(x+rect.width(), y+rect.height()/2);
         ptArray[2] = QPoint(x, y+rect.height());
         
         if(theOutputConnectionArray[idx])
         {
            painter.setBrush(greenBrush);
         }
         else
         {
            painter.setBrush(redBrush);
         }
         
         painter.drawConvexPolygon(ptArray);
      }
   }
   
   painter.setBrush(oldBrush);
}

void ossimQtVceConnectableObject::redrawConnections()
{
   int idx = 0;
   
   for(idx = 0; idx < (int)theInputConnectionArray.size();++idx)
   {
      if(theInputConnectionArray[idx])
      {
         theInputConnectionArray[idx]->updateEndPoints();
      }
   }
   for(idx = 0; idx < (int)theOutputConnectionArray.size();++idx)
   {
      if(theOutputConnectionArray[idx])
      {
         theOutputConnectionArray[idx]->updateEndPoints();
      }
   }
}


ossimConnectableObject* ossimQtVceConnectableObject::getConnectableObject()
{
   return theConnectableObject.get();
}



void ossimQtVceConnectableObject::setConnectableObject(ossimConnectableObject* connectable)
{
   if(theConnectableObject.valid())
   {
      ossimNotify(ossimNotifyLevel_WARN) << "WARNING ossimQtVceConnectableObject::setConnectableObject: Currently don't support changing\n"
      << "a connectable object to another one" << std::endl;
      theConnectableObject->removeListener(thePrivateListener);
   }
   // need to add support for connection linking so if we change the
   // connectable object to some other object
   //
   theConnectableObject =  connectable;
   
   if(isInternalObjectsInputListFixed())
   {
      resizeInputList(getInternalObjectsNumberOfInputs());
   }
   else
   {
      resizeInputList(1);
   }
   if(isInternalObjectsOutputListFixed())
   {
      resizeOutputList(getInternalObjectsNumberOfOutputs());
   }
   else
   {
      resizeOutputList(1);
   }
   
   if(theConnectableObject.valid())
   {
      theConnectableObject->addListener(thePrivateListener);
   }
}

void ossimQtVceConnectableObject::removeConnection(ossimQtVceConnectionObject* connectionObject)
{
   int idx = getInputConnectionIndex(connectionObject);
   if(idx >= 0)
   {
      if(isInternalObjectsInputListFixed())
      {
         theInputConnectionArray[idx] = NULL;
      }
      else
      {
         theInputConnectionArray.erase(theInputConnectionArray.begin() + idx);
      }
      setInputsToInternalObject();
   }
   else
   {
      idx = getOutputConnectionIndex(connectionObject);
      if(idx >= 0)
      {
         if(isInternalObjectsOutputListFixed())
         {
            theOutputConnectionArray[idx] = NULL;
         }
         else
         {
            theOutputConnectionArray.erase(theOutputConnectionArray.begin() + idx);
         }
         setOutputsToInternalObject();
      }
   }
   
   hide();
   redrawConnections();
   show();
}

bool ossimQtVceConnectableObject::getConnectionSlotBoundingRect(QRect& rect,
                                                                const QPoint& pt)const
{
   bool result = false;
   int inputIdx = hitInputConnection(pt);
   
   if(inputIdx > -1)
   {
      result   = getInputConnectionSlotBoundingRect(rect, inputIdx);
   }
   else
   {
      int outputIdx = hitOutputConnection(pt);
      
      if(outputIdx>-1)
      {
         result = getOutputConnectionSlotBoundingRect(rect, outputIdx);
      }
   }
   
   return result;
}


bool ossimQtVceConnectableObject::getConnectionSlotBoundingRect(QRect& rect,
                                                                const ossimQtVceConnectionObject* connectionObject)const
{
   bool result = false;
   if(getInputConnectionSlotBoundingRect(rect, getInputConnectionIndex(connectionObject)))
   {
      result = true;
   }
   else if(getOutputConnectionSlotBoundingRect(rect, getOutputConnectionIndex(connectionObject)))
   {
      result = true;
   }
   
   return result;
}

bool ossimQtVceConnectableObject::getInputConnectionSlotBoundingRect(QRect& rect,
                                                                     int idx)const
{
   if(idx < 0) return false;
   bool result = false;
   if(idx < (int)theInputConnectionArray.size())
   {
      int idxY    = theHeight/(int)theInputConnectionArray.size();
      int centerY = ((idxY/2) - (theConnectorSize.height()/2)) + idxY*idx;
      rect = QRect((int)x(),
                   (int)y() + centerY,
                   theConnectorSize.width(),
                   theConnectorSize.height());
      
      result = true;
   }
   
   return result;
}

bool ossimQtVceConnectableObject::getOutputConnectionSlotBoundingRect(QRect& rect,
                                                                      int idx)const
{
   bool result = false;
   if(idx < 0) return false;
   if(idx < (int)theOutputConnectionArray.size())
   {
      int idxY    = theHeight/(int)theOutputConnectionArray.size();
      int centerY = ((idxY/2) - (theConnectorSize.height()/2)) + idxY*idx;
      rect = QRect((int)x()+(theWidth-theConnectorSize.width()),
                   (int)y() + centerY,
                   theConnectorSize.width(),
                   theConnectorSize.height());
      
      result = true;
   }
   
   return result;
}

int ossimQtVceConnectableObject::getNumberOfInputs()const
{
   return theInputConnectionArray.size();
}

int ossimQtVceConnectableObject::getNumberOfOutputs()const
{
   return theOutputConnectionArray.size();
}


bool ossimQtVceConnectableObject::setInputConnection(ossimQtVceConnectionObject* connectionObject,
                                                     int idx)
{
   bool result = false;
   int tempIdx = idx;
   if(tempIdx < 0) tempIdx = findAvailableInput();
   
   if((tempIdx >= 0) && (tempIdx <= (int)theInputConnectionArray.size()))
   {
      if(canConnectInternalObjectsInputTo(tempIdx,
                                          connectionObject))
      {
         if(tempIdx != (int)theInputConnectionArray.size())
         {
            if(theInputConnectionArray[tempIdx])
            {
               ossimNotify(ossimNotifyLevel_NOTICE)
               << "NOTICE ossimQtVceConnectableObject::setInputConnection: Need to Implement update since we are removing a connection!!" << std::endl;
            }
            
            theInputConnectionArray[tempIdx] = connectionObject;
            if(!isInternalObjectsInputListFixed()&&
               tempIdx == ((int)theInputConnectionArray.size() - 1))
            {
               theInputConnectionArray.push_back((ossimQtVceConnectionObject*)NULL);
            }
            update();
         }
         else
         {
            theInputConnectionArray.push_back(connectionObject);
            theInputConnectionArray.push_back((ossimQtVceConnectionObject*)NULL);
         }
         result = true;
         setInputsToInternalObject();
      }
   }
   QSize tempSize(theWidth, theHeight);
   checkSize(tempSize);
   if(tempSize == QSize(theWidth, theHeight))
   {
      hide();
      redrawConnections();
      show();
   }
   else
   {
      setSize(tempSize);
   }
   return result;
}

bool ossimQtVceConnectableObject::setOutputConnection(ossimQtVceConnectionObject* connectionObject,
                                                      int idx)
{
   bool result = false;
   int tempIdx = idx;
   if(tempIdx < 0) tempIdx = findAvailableOutput();
   
   if((tempIdx >= 0) && (tempIdx <= (int)theOutputConnectionArray.size()))
   {
      if(canConnectInternalObjectsOutputTo(tempIdx,
                                           connectionObject))
      {
         if(tempIdx != (int)theOutputConnectionArray.size())
         {
            if(theOutputConnectionArray[tempIdx])
            {
               ossimNotify(ossimNotifyLevel_NOTICE)
               << "NOTICE ossimQtVceConnectableObject::setOutputConnection: Need to Implement update since we are removing a connection!!" << std::endl;
            }
            
            theOutputConnectionArray[tempIdx] = connectionObject;
            
            if(!isInternalObjectsOutputListFixed()&&
               tempIdx == ((int)theOutputConnectionArray.size() - 1))
            {
               theOutputConnectionArray.push_back((ossimQtVceConnectionObject*)NULL);
            }
         }
         else
         {
            theOutputConnectionArray.push_back(connectionObject);
            theOutputConnectionArray.push_back((ossimQtVceConnectionObject*)NULL);
         }
         result = true;
         setOutputsToInternalObject();
      }
   }
   QSize tempSize(theWidth, theHeight);
   checkSize(tempSize);
   if(tempSize == QSize(theWidth, theHeight))
   {
      update();
   }
   else
   {
      setSize(tempSize);
   }
   return result;
}


void ossimQtVceConnectableObject::resizeInputList(int newSize)
{
   int tempNewSize = newSize;
   
   if(tempNewSize < 0) tempNewSize = 0;
   
   std::vector<ossimQtVceConnectionObject*> tempInput = theInputConnectionArray;
   
   
   if(tempNewSize == 0)
   {
      theInputConnectionArray.clear();
   }
   else
   {
      theInputConnectionArray.resize(tempNewSize);
   }
   
   int idx = 0;
   int upper = tempNewSize <(int)tempInput.size()?tempNewSize:(int)tempInput.size();
   
   for(idx = 0; idx < upper; ++idx)
   {
      theInputConnectionArray[idx] = tempInput[idx];
   }
   for(;idx < tempNewSize;++idx)
   {
      theInputConnectionArray[idx] = NULL;
   }
   
   if(theInputConnectionArray.size() < 1)
   {
      if(!isInternalObjectsInputListFixed())
      {
         theInputConnectionArray.push_back((ossimQtVceConnectionObject*)NULL);
      }
   }
   else
   {
      if(!isInternalObjectsInputListFixed())
      {
         if(theInputConnectionArray[theInputConnectionArray.size()-1])
         {
            theInputConnectionArray.push_back((ossimQtVceConnectionObject*)NULL);
         }
      }
   }
   
}

void ossimQtVceConnectableObject::resizeOutputList(int newSize)
{
   int tempNewSize = newSize;
   
   if(tempNewSize < 0) tempNewSize = 0;
   
   std::vector<ossimQtVceConnectionObject*> tempOutput = theOutputConnectionArray;
   
   
   if(tempNewSize == 0)
   {
      theOutputConnectionArray.clear();
   }
   else
   {
      theOutputConnectionArray.resize(tempNewSize);
   }
   
   int idx = 0;
   int upper = tempNewSize <(int)tempOutput.size()?tempNewSize:(int)tempOutput.size();
   
   for(idx = 0; idx < (int)upper; ++idx)
   {
      theOutputConnectionArray[idx] = tempOutput[idx];
   }
   for(;idx < tempNewSize;++idx)
   {
      theOutputConnectionArray[idx] = NULL;
   }
   
   
   if(theOutputConnectionArray.size() < 1)
   {
      
      if(!isInternalObjectsOutputListFixed())
      {
         theOutputConnectionArray.push_back((ossimQtVceConnectionObject*)NULL);
      }
   }
   else
   {
      if(!isInternalObjectsOutputListFixed())
      {
         if(theOutputConnectionArray[theOutputConnectionArray.size()-1])
         {
            theOutputConnectionArray.push_back((ossimQtVceConnectionObject*)NULL);
         }
      }
   }
}

int ossimQtVceConnectableObject::getInputConnectionIndex(const ossimQtVceConnectionObject* connectionObj)const
{
   int result = -1;
   if(connectionObj)
   {
      int idx = 0;
      for(idx = 0; ((idx < (int)theInputConnectionArray.size())&&(result <0));++idx)
      {
         if(theInputConnectionArray[idx] == connectionObj)
         {
            result = idx;
         }
      }
   }
   
   return result;
}

int ossimQtVceConnectableObject::getOutputConnectionIndex(const ossimQtVceConnectionObject* connectionObj)const
{
   int result = -1;
   if(connectionObj)
   {
      int idx = 0;
      for(idx = 0; ((idx < (int)theOutputConnectionArray.size())&&(result <0));++idx)
      {
         if(theOutputConnectionArray[idx] == connectionObj)
         {
            result = idx;
         }
      }
   }
   
   return result;
}


int ossimQtVceConnectableObject::hitInputConnection(const QPoint& pt)const
{
   int idx = 0;
   ossimIpt tempPt(pt.x(), pt.y());
   for(idx = 0; idx < (int)theInputConnectionArray.size(); ++idx)
   {
      QRect rect;
      getInputConnectionSlotBoundingRect(rect,
                                         idx);
      if(ossimIrect(rect.x(), rect.y(),
                    rect.x() + rect.width()-1,
                    rect.y() + rect.height()-1).pointWithin(tempPt))
      {
         return idx;
      }
   }
   
   return -1;
}

int ossimQtVceConnectableObject::hitOutputConnection(const QPoint& pt)const
{
   int idx = 0;
   ossimIpt tempPt(pt.x(), pt.y());
   for(idx = 0; idx < (int)theOutputConnectionArray.size(); ++idx)
   {
      QRect rect;
      getOutputConnectionSlotBoundingRect(rect,
                                          idx);
      if(ossimIrect(rect.x(), rect.y(),
                    rect.x() + rect.width()-1,
                    rect.y() + rect.height()-1).pointWithin(tempPt))
      {
         return idx;
      }
   }
   
   return -1;
}


ossimQtVceConnectionObject* ossimQtVceConnectableObject::getInputConnection(int idx)
{
   ossimQtVceConnectionObject* result = NULL;
   
   if((idx >= 0) || (idx < (int)theInputConnectionArray.size()))
   {
      result = theInputConnectionArray[idx];
   }
   
   return result;
}

ossimQtVceConnectionObject* ossimQtVceConnectableObject::getOutputConnection(int idx)
{
   ossimQtVceConnectionObject* result = NULL;
   
   if((idx >= 0) || (idx < (int)theOutputConnectionArray.size()))
   {
      result = theOutputConnectionArray[idx];
   }
   
   return result;
}

int ossimQtVceConnectableObject::getNumberOfInputConnections()const
{
   return theInputConnectionArray.size();
}

int ossimQtVceConnectableObject::getNumberOfOutputConnections()const
{
   return theOutputConnectionArray.size();
}

int ossimQtVceConnectableObject::findAvailableInput()const
{
   int idx = 0;
   
   for(idx = 0; idx < (int)theInputConnectionArray.size();++idx)
   {
      if(theInputConnectionArray[idx] == NULL)
      {
         return idx;
      }
   }
   
   if(!isInternalObjectsInputListFixed())
   {
      return (int)theInputConnectionArray.size();
   }
   
   return -1;
}

int ossimQtVceConnectableObject::findAvailableOutput()const
{
   int idx = 0;
   
   for(idx = 0; idx < (int)theOutputConnectionArray.size();++idx)
   {
      if(theOutputConnectionArray[idx] == NULL)
      {
         return idx;
      }
   }
   
   if(!isInternalObjectsOutputListFixed())
   {
      return (int)theOutputConnectionArray.size();
   }
   
   return -1;
}

void ossimQtVceConnectableObject::disconnectObject()
{
   std::vector<ossimQtVceConnectionObject*> temp = theInputConnectionArray;
   int idx = 0;
   for(idx = 0; idx < (int)temp.size(); ++idx)
   {
      if(temp[idx])
      {
         delete temp[idx];
         temp[idx];
      }
   }
   
   temp = theOutputConnectionArray;
   for(idx = 0; idx < (int)temp.size(); ++idx)
   {
      if(temp[idx])
      {
         delete temp[idx];
         temp[idx];
      }
   }
}

bool ossimQtVceConnectableObject::setInputsToInternalObject()
{
   ossimConnectableObject::ConnectableObjectList inputList;
   int idx = 0;
   
   for(idx = 0; idx < (int)theInputConnectionArray.size();++idx)
   {
      if(isInternalObjectsInputListFixed())
      {
         inputList.push_back((ossimConnectableObject*)NULL);
         if(theInputConnectionArray[idx])
         {
            if(theInputConnectionArray[idx]->getStart())
            {
               inputList[idx] = theInputConnectionArray[idx]->getStart()->getConnectableObject();
            }
         }
      }
      else
      {
         if(theInputConnectionArray[idx])
         {
            if(theInputConnectionArray[idx]->getStart())
            {
               inputList.push_back(theInputConnectionArray[idx]->getStart()->getConnectableObject());
            }
         }
      }
   }
   
   bool result = connectInternalObjectsInputTo(inputList);
   ossimQtDisplayUtility::flushAllOutputs(theConnectableObject.get());
   
   return result;
}

bool ossimQtVceConnectableObject::setOutputsToInternalObject()
{
   ossimConnectableObject::ConnectableObjectList outputList;
   int idx = 0;
   
   for(idx = 0; idx < (int)theOutputConnectionArray.size();++idx)
   {
      if(isInternalObjectsOutputListFixed())
      {
         outputList.push_back((ossimConnectableObject*)NULL);
         if(theOutputConnectionArray[idx])
         {
            if(theOutputConnectionArray[idx]->getStart())
            {
               outputList[idx] = theOutputConnectionArray[idx]->getEnd()->getConnectableObject();
            }
         }
      }
      else
      {
         if(theOutputConnectionArray[idx])
         {
            if(theOutputConnectionArray[idx]->getStart())
            {
               outputList.push_back(theOutputConnectionArray[idx]->getEnd()->getConnectableObject());
            }
         }
      }
   }
   
   return connectInternalObjectsOutputTo(outputList);
}


bool ossimQtVceConnectableObject::canConnectInternalObjectsInputTo(int idx,
                                                                   ossimQtVceConnectionObject* connectionObject)
{
   if(theConnectableObject.get()&&connectionObject)
   {
      if(connectionObject->getStart())
      {
         return theConnectableObject->canConnectMyInputTo(idx,
                                                          connectionObject->getStart()->getConnectableObject());
      }
   }
   
   return false;
}

bool ossimQtVceConnectableObject::canConnectInternalObjectsOutputTo(int idx,
                                                                    ossimQtVceConnectionObject* connectionObject)
{
   if(theConnectableObject.valid()&&connectionObject)
   {
      if(connectionObject->getEnd())
      {
         return theConnectableObject->canConnectMyOutputTo(idx,
                                                           connectionObject->getEnd()->getConnectableObject());
      }
   }
   
   return true;
}

bool ossimQtVceConnectableObject::connectInternalObjectsInputTo(ossimConnectableObject::ConnectableObjectList& inputList)
{
   bool result = false;
   
   if(theConnectableObject.get())
   {
      result = theConnectableObject->connectMyInputTo(inputList, true, true);
   }
   
   return result;
}

bool ossimQtVceConnectableObject::connectInternalObjectsOutputTo(ossimConnectableObject::ConnectableObjectList& outputList)
{
   bool result = false;
   
   if(theConnectableObject.valid())
   {
      result = theConnectableObject->connectMyOutputTo(outputList, true, true);
   }
   
   return result;
}


bool ossimQtVceConnectableObject::isInternalObjectsInputListFixed()const
{
   if(theConnectableObject.valid())
   {
      return theConnectableObject->getInputListIsFixedFlag();
   }
   
   return true;
}

bool ossimQtVceConnectableObject::isInternalObjectsOutputListFixed()const
{
   if(theConnectableObject.valid())
   {
      return theConnectableObject->getOutputListIsFixedFlag();
   }
   return false;
}

int ossimQtVceConnectableObject::getInternalObjectsNumberOfInputs()const
{
   if(theConnectableObject.valid())
   {
      return theConnectableObject->getNumberOfInputs();
   }
   
   return 1;
}

int ossimQtVceConnectableObject::getInternalObjectsNumberOfOutputs()const
{
   if(theConnectableObject.valid())
   {
      return theConnectableObject->getNumberOfOutputs();
   }
   
   return 0;
   
}

void ossimQtVceConnectableObject::getValidDrawingArea(QRect& rect)const
{
   rect = QRect((int)x() + theConnectorSize.width(),
                (int)y() + theConnectorSize.height(),
                theWidth  - 2*theConnectorSize.width(),
                theHeight - 2*theConnectorSize.height());
}

void ossimQtVceConnectableObject::setSize(const QSize& size)
{
   hide();
   
   QSize newSize = size;
   checkSize(newSize);
   
   theWidth  = newSize.width();
   theHeight = newSize.height();
   
   redrawConnections();
   show();
}

void ossimQtVceConnectableObject::checkSize(QSize& size)
{
   int minPixelsForInputConnector  = theConnectorSize.height()*theInputConnectionArray.size();
   int minPixelsForOutputConnector = theConnectorSize.height()*theOutputConnectionArray.size();
   
   int maxPixelHeight = minPixelsForInputConnector > minPixelsForOutputConnector?minPixelsForInputConnector:minPixelsForOutputConnector;
   if(maxPixelHeight > ((int)size.height() - 2*theConnectorSize.height()))
   {
      size.setHeight(maxPixelHeight + theConnectorSize.height()*2);
   }
}

void ossimQtVceConnectableObject::internalInputConnectionChanged()
{
}

void ossimQtVceConnectableObject::internalOutputConnectionChanged()
{
}

void ossimQtVceConnectableObject::internalRefresh()
{
}

void ossimQtVceConnectableObject::internalProperty()
{
}

void ossimQtVceConnectableObject::initialize()
{
   if(theConnectableObject.valid())
   {
      ossimRefreshEvent evt(theConnectableObject.get());
      theConnectableObject->fireEvent(evt);
   }
}

bool ossimQtVceConnectableObject::saveState(ossimKeywordlist& kwl,
                                            const char* prefix)const
{
   bool result = ossimQtVceShape::saveState(kwl, prefix);
   int idx = 0;
   
   kwl.add(prefix,
           ossimKeywordNames::TYPE_KW,
           "ossimQtVceConnectableObject",
           true);
   
   if(result)
   {
      kwl.add(prefix,
              "size",
              ossimString::toString(theWidth)+" "+ossimString::toString(theHeight),
              true);
      
      if(theConnectableObject.valid())
      {
         ossimString newPrefix = ossimString(prefix) + "object1.";
         theConnectableObject->saveState(kwl,
                                         newPrefix.c_str());
      }
      for(idx = 0; idx < (int)theInputConnectionArray.size(); ++idx)
      {
         ossimString connectionString = "input_connection" + ossimString::toString(idx);
         if(theInputConnectionArray[idx])
         {
            if(theInputConnectionArray[idx]->getStart())
            {
               kwl.add(prefix,
                       connectionString,
                       theInputConnectionArray[idx]->getStart()->getId(),
                       true);
            }
            else
            {
               kwl.add(prefix,
                       connectionString,
                       -1,
                       true);
            }
         }
         else
         {
            kwl.add(prefix,
                    connectionString,
                    -1,
                    true);
         }
      }
      for(idx = 0; idx < (int)theOutputConnectionArray.size(); ++idx)
      {
         ossimString connectionString = "output_connection" + ossimString::toString(idx);
         if(theOutputConnectionArray[idx])
         {
            if(theOutputConnectionArray[idx]->getEnd())
            {
               kwl.add(prefix,
                       connectionString,
                       theOutputConnectionArray[idx]->getEnd()->getId(),
                       true);
            }
            else
            {
               kwl.add(prefix,
                       connectionString,
                       -1,
                       true);
            }
         }
         else
         {
            kwl.add(prefix,
                    connectionString,
                    -1,
                    true);
         }
      }
   }
   
   return true;
}

bool ossimQtVceConnectableObject::loadState(const ossimKeywordlist& kwl,
                                            const char* prefix)
{
   ossimQtVceShape::loadState(kwl, prefix);
   const char* size = kwl.find(prefix, "size");
   
   if(size)
   {
      std::stringstream s(size);
      s >> theWidth >> theHeight;
   }
   ossimRefPtr<ossimObject> obj = ossimObjectFactoryRegistry::instance()->createObject(kwl,
                                                                                       ossimString(prefix)+"object1.");
   if(obj.valid())
   {
      ossimConnectableObject* connectableObj = PTR_CAST(ossimConnectableObject,
                                                        obj.get());
      if(connectableObj)
      {
         setConnectableObject(connectableObj);
      }
      else
      {
         obj = 0;
      }
   }
   
   return true;
}
