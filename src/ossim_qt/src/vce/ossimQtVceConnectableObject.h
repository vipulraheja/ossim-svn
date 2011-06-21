//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtVceConnectableObject.h 15766 2009-10-20 12:37:09Z gpotts $
#ifndef ossimQtVceConnectableObject_HEADER
#define ossimQtVceConnectableObject_HEADER
#include <ossim/base/ossimConnectableObject.h>
#include "ossimQtVceShape.h"
class ossimQtVceConnectionObject;
class ossimQtVceConnectableObjectPrivateListener;

class ossimQtVceConnectableObject : public ossimQtVceShape
{
   friend class ossimQtVceConnectableObjectPrivateListener;
public:
   ossimQtVceConnectableObject(QCanvas* canvas,
			       QObject* vceParent);
  virtual ~ossimQtVceConnectableObject();
  virtual ossimQtVceConnectableObject* castToConnectable();
  virtual const ossimQtVceConnectableObject* castToConnectable()const;
  virtual void moveBy(double dx, double dy);
  virtual void draw(QPainter& painter);
  void redrawConnections();
  virtual ossimConnectableObject* getConnectableObject();

  virtual void setConnectableObject(ossimConnectableObject* connectable);
  virtual void removeConnection(ossimQtVceConnectionObject* connectionObject);

  virtual bool getConnectionSlotBoundingRect(QRect& rect,
					     const QPoint& pt)const;
   
  /*!
   * This is reserved for returning the location of the slot
   * this will be used by the conection object to determine where its
   * start and end points will go.
   */
  virtual bool getConnectionSlotBoundingRect(QRect& rect,
					     const ossimQtVceConnectionObject* connectionObject)const;
  virtual bool getInputConnectionSlotBoundingRect(QRect& rect,
						  int idx)const;
  virtual bool getOutputConnectionSlotBoundingRect(QRect& rect,
						   int idx)const;
  virtual int getNumberOfInputs()const;
  virtual int getNumberOfOutputs()const;

  /*!
   * 
   */
  virtual bool setInputConnection(ossimQtVceConnectionObject* connectionObject,
				  int idx=-1);

  /*!
   *
   */
  virtual bool setOutputConnection(ossimQtVceConnectionObject* connectionObject,
				   int idx=-1);

  /*!
   * This will be a non destructive resize
   */
  virtual void resizeInputList(int newSize);


  /*!
   * This will be a non destructive resize
   */
   virtual void resizeOutputList(int newSize);
   
   virtual int getInputConnectionIndex(const ossimQtVceConnectionObject* connectionObj)const;
   virtual int getOutputConnectionIndex(const ossimQtVceConnectionObject* connectionObj)const;

   /*!
    * Will test if the given point hits the input connection.  The result is
    * the connection index hit. It will return -1 if no hit is found.
    *
    */
   virtual int hitInputConnection(const QPoint& pt)const;

   /*!
    * Will test if the given point hits the output connection.  The result is
    * the connection index hit. It will return -1 if no hit is found.
    *
    */
   virtual int hitOutputConnection(const QPoint& pt)const;
   
   virtual ossimQtVceConnectionObject* getInputConnection(int idx);
   virtual ossimQtVceConnectionObject* getOutputConnection(int idx);
   
   virtual int getNumberOfInputConnections()const;
   virtual int getNumberOfOutputConnections()const;
   
   virtual int findAvailableInput()const;
   virtual int findAvailableOutput()const;
   virtual void disconnectObject();
   void getValidDrawingArea(QRect& rect)const;
   virtual void setSize(const QSize& size);
   void initialize();

   virtual bool saveState(ossimKeywordlist& kwl,
                          const char* prefix=0)const;
   virtual bool loadState(const ossimKeywordlist& kwl,
                          const char* prefix=0);

protected:
   ossimRefPtr<ossimConnectableObject> theConnectableObject;
   ossimQtVceConnectableObjectPrivateListener* thePrivateListener;   
   /*!
    * these are slot connection objects and are not owned by this object. These
    * are visual components.  They can be deleted safely though.
    */
   std::vector<ossimQtVceConnectionObject*> theInputConnectionArray;
   std::vector<ossimQtVceConnectionObject*> theOutputConnectionArray;
   int theWidth;
   int theHeight;
   
   QSize theConnectorSize;
   
   virtual void checkSize(QSize& size);
   void drawConnectors(QPainter& painter);
   
   bool setInputsToInternalObject();
   bool setOutputsToInternalObject();
   
   virtual bool canConnectInternalObjectsInputTo(int idx,
                                                 ossimQtVceConnectionObject* connectionObject);
   virtual bool canConnectInternalObjectsOutputTo(int idx,
                                                  ossimQtVceConnectionObject* connectionObject);
   virtual bool connectInternalObjectsInputTo(ossimConnectableObject::ConnectableObjectList& inputList);
   virtual bool connectInternalObjectsOutputTo(ossimConnectableObject::ConnectableObjectList& inputList);
   
   virtual bool isInternalObjectsInputListFixed()const;
   virtual bool isInternalObjectsOutputListFixed()const;
   virtual int   getInternalObjectsNumberOfInputs()const;
   virtual int   getInternalObjectsNumberOfOutputs()const;
   
   
   virtual void internalInputConnectionChanged();
   virtual void internalOutputConnectionChanged();
   virtual void internalRefresh();
   virtual void internalProperty();
};

#endif
