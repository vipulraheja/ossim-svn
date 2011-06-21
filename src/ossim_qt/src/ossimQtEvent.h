//*******************************************************************
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
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtEvent.h 15766 2009-10-20 12:37:09Z gpotts $
#ifndef ossimQtEvent_HEADER
#define ossimQtEvent_HEADER
#include <algorithm>
#include <qevent.h>
#include <map>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimRefPtr.h>
class ossimDataManager;
class ossimQtProject;

enum ossimQtEventIdType
{
   OSSIM_QT_EVENT_REFRESH_DISPLAY_ID = QEvent::User,
   OSSIM_QT_EVENT_FLUSH_DISPLAY_ID,
   OSSIM_QT_EVENT_DISPLAY_LIST_ID,
   OSSIM_QT_EVENT_DISPLAY_GEO_VIEW_ID,
   OSSIM_QT_EVENT_MOUSE_ID,
   OSSIM_QT_EVENT_TRACK_POSITION_ID,
   OSSIM_QT_EVENT_DISPLAY_CHAIN_ID,
   OSSIM_QT_EVENT_RESAMPLER_ID,
   OSSIM_QT_EVENT_GET_DATA_MANAGER,
   OSSIM_QT_EVENT_GET_PROJECT,
   OSSIM_QT_EVENT_STATE_EVENT,
   OSSIM_QT_EVENT_QUERY_OBJECT_ALLOCATED,
   OSSIM_QT_EVENT_ADD_IMAGE_FILE
};

class ossimQtCustomEvent : public QCustomEvent
{
public:
  enum ossimQtCustomEventMode
    {
      ossimQtCustomEvent_NOPROPAGATE = 0,
      ossimQtCustomEvent_PROPAGATE
    };
  ossimQtCustomEvent(ossimQtCustomEventMode mode,
		     ossimQtEventIdType type,
		     QObject* eventObject=NULL)
    :QCustomEvent((QEvent::Type)type),
     theMode(mode),
     theEventObject(eventObject)
  {
  }
  virtual bool isPropagating()const
  {
    return (theMode == ossimQtCustomEvent_PROPAGATE);
  }
  virtual void setPropagating()
  {
    theMode = ossimQtCustomEvent_PROPAGATE;
  }
  virtual void setNoPropagating()
  {
    theMode =  ossimQtCustomEvent_NOPROPAGATE;
  }
  virtual void setMode(ossimQtCustomEventMode mode)
  {
    theMode = mode;
  }
  ossimQtCustomEventMode getMode()const
  {
    return theMode;
  }
  const QObject* getEventObject()const
  {
    return theEventObject;
  }
  void setEventObject(QObject* obj)
  {
    theEventObject = obj;
  }
public:
  ossimQtCustomEventMode theMode;
  QObject*               theEventObject;
};

class ossimQtRefreshDisplayEvent : public ossimQtCustomEvent
{
public:
   ossimQtRefreshDisplayEvent(ossimQtCustomEventMode mode = ossimQtCustomEvent_NOPROPAGATE)
      :ossimQtCustomEvent(mode,
			  OSSIM_QT_EVENT_REFRESH_DISPLAY_ID)
      {}
};

class ossimQtFlushDisplayEvent : public ossimQtCustomEvent
{
public:
   ossimQtFlushDisplayEvent(ossimQtCustomEventMode mode=ossimQtCustomEvent_NOPROPAGATE)
      :ossimQtCustomEvent(mode,
			  OSSIM_QT_EVENT_FLUSH_DISPLAY_ID)
      {}
};

class ossimQtDisplayListEvent : public ossimQtCustomEvent
{
public:
   ossimQtDisplayListEvent(ossimQtCustomEventMode mode = ossimQtCustomEvent_NOPROPAGATE)
      :ossimQtCustomEvent(mode, OSSIM_QT_EVENT_DISPLAY_LIST_ID)
      {
         theDisplayListIterator = theDisplayList.end();
      }

   void eraseDisplay(QObject* display);
   void addDisplay(QObject* display);
   QObject* firstDisplay();
   QObject* nextDisplay();
   
protected:
   std::map<QObject*, QObject*> theDisplayList;
   std::map<QObject*, QObject*>::iterator theDisplayListIterator;
};

class ossimQtDisplayGeoViewEvent : public ossimQtCustomEvent
{
public:
   ossimQtDisplayGeoViewEvent(const ossimObject* view=NULL,
			      const ossimGpt& center = ossimGpt(),
			      ossimQtCustomEventMode mode = ossimQtCustomEvent_NOPROPAGATE)
      :ossimQtCustomEvent(mode,
			  OSSIM_QT_EVENT_DISPLAY_GEO_VIEW_ID)
      {
         if(view)
         {
            theView = view->dup();
         }
         theViewCenter = center;
      }
   virtual ~ossimQtDisplayGeoViewEvent()
      {
         if(theView.valid())
         {
            theView = 0;
         }
      }
   void setView(ossimObject* view)
      {
         if(view)
         {
            theView = view;
         }
      }
   void setCenter(const ossimGpt& center)
      {
         theViewCenter = center;
      }
   const ossimObject* getView()const
      {
         return theView.get();
      }
   const ossimGpt& getViewCenter()const
      {
         return theViewCenter;
      }
   
protected:
   ossimRefPtr<ossimObject> theView;
   ossimGpt                 theViewCenter;
};

class ossimQtMouseEvent:public ossimQtCustomEvent
{
public:
    ossimQtMouseEvent(const ossimIpt& shiftToZeroZero,
		      QMouseEvent* evt,
		      ossimQtCustomEventMode mode = ossimQtCustomEvent_NOPROPAGATE)
		      :ossimQtCustomEvent(mode,
					  OSSIM_QT_EVENT_MOUSE_ID),
                       theEvent(evt), 
		       theShiftToZeroZero(shiftToZeroZero),
		       thePoint(evt->x(), evt->y()),
		       theButton(evt->button()),
		       theState(evt->state()),
		       theStateAfter(evt->stateAfter()),
		       theQtEventType(evt->type())
			 
  {
  }

  QMouseEvent* getEvent() const
  {
     return theEvent;
  }
  void setButton(ButtonState button)
  {
    theButton = button;
  }
  ossimIpt getShiftToZeroZero()const
  {
    return theShiftToZeroZero;
  }
  ossimIpt getPoint()const
  {
    return thePoint;
  }
  ossimIpt getShiftPoint()const
  {
    return thePoint - theShiftToZeroZero;
  }
  ButtonState getButton()const
  {
    return theButton;
  }
  ButtonState getState()const
  {
    return theState;
  }
  ButtonState getStateAfter()const
  {
    return theStateAfter;
  }
  QEvent::Type getQtEventType()const
  {
    return theQtEventType;
  }
  void setState(ButtonState state)
  {
    theState = state;
  }
  void setStateAfter(ButtonState stateAfter)
  {
    theStateAfter = stateAfter;
  }
  void setQtEventType(QEvent::Type type)
  {
    theQtEventType = type;
  }
  
protected:
  QMouseEvent* theEvent;
  ossimIpt     theShiftToZeroZero;
  ossimIpt     thePoint;
  ButtonState  theButton;
  ButtonState  theState;
  ButtonState  theStateAfter;
  QEvent::Type theQtEventType;
};

class ossimQtDisplayTrackPositionEvent : public ossimQtCustomEvent
{
public:
  ossimQtDisplayTrackPositionEvent(const ossimGpt& gpt,
				   ossimQtCustomEventMode mode = ossimQtCustomEvent_NOPROPAGATE)
    :ossimQtCustomEvent(mode,
			OSSIM_QT_EVENT_TRACK_POSITION_ID),
     theGround(gpt)
  {
  }
  ossimQtDisplayTrackPositionEvent()
    :ossimQtCustomEvent(ossimQtCustomEvent_NOPROPAGATE, OSSIM_QT_EVENT_TRACK_POSITION_ID)
  {
    theGround.makeNan();
  }
  
  void setGround(const ossimGpt& gpt)
  {
    theGround = gpt;
  }
  
  const ossimGpt& getGround()const
  {
    return theGround;
  }
  void setButton(ButtonState button)
  {
    theButton = button;
  }
  ButtonState getButton()const
  {
    return theButton;
  }
  ButtonState getState()const
  {
    return theState;
  }
  ButtonState getStateAfter()const
  {
    return theStateAfter;
  }
  QEvent::Type getQtEventType()const
  {
    return theQtEventType;
  }
  void setState(ButtonState state)
  {
    theState = state;
  }
  void setStateAfter(ButtonState stateAfter)
  {
    theStateAfter = stateAfter;
  }
  void setQtEventType(QEvent::Type type)
  {
    theQtEventType = type;
  }
protected:
  ossimGpt     theGround;
  ButtonState  theButton;
  ButtonState  theState;
  ButtonState  theStateAfter;
  QEvent::Type theQtEventType;
};

class ossimQtDisplayChainEvent : public ossimQtCustomEvent
{
public:
  ossimQtDisplayChainEvent(ossim_int32 id,
			   ossimQtCustomEventMode mode = ossimQtCustomEvent_NOPROPAGATE)
    :ossimQtCustomEvent(mode, OSSIM_QT_EVENT_DISPLAY_CHAIN_ID),
     theId(id)
  {}

  ossim_int32 getId()const
  {
    return theId;
  }
  void setId(ossim_int32 id)
  {
    theId = id;
  }

protected:
  ossim_int32 theId;
};

class ossimQtResamplerEvent : public ossimQtCustomEvent
{
public:
   ossimQtResamplerEvent(const ossimString& minify,
			 const ossimString& magnify,
			 ossimQtCustomEventMode mode = ossimQtCustomEvent_NOPROPAGATE)
     :ossimQtCustomEvent(mode,
			 OSSIM_QT_EVENT_RESAMPLER_ID),
     theMinifyType(minify),
     theMagnifyType(magnify)
      {
      }

   const ossimString& getMinify()const
      {
         return theMinifyType;
      }
   void setMinify(const ossimString& type)
      {
         theMinifyType = type;
      }
   
   const ossimString& getMagnify()const
      {
         return theMagnifyType;
      }

   void setMagnify(const ossimString& type)
      {
         theMagnifyType = type;
      }
   
protected:
   ossimString theMinifyType;
   ossimString theMagnifyType;
};

class ossimQtGetDataManagerEvent : public ossimQtCustomEvent
{
public:
   ossimQtGetDataManagerEvent(ossimQtCustomEventMode mode = ossimQtCustomEvent_NOPROPAGATE)
      :ossimQtCustomEvent(mode,
                          OSSIM_QT_EVENT_GET_DATA_MANAGER),
       theDataManager(NULL)
      {
      }
   void setDataManager(ossimDataManager* manager)
      {
         theDataManager = manager;
      }
   ossimDataManager* getDataManager()
      {
         return theDataManager;
      }

protected:
   ossimDataManager* theDataManager;
};

class ossimQtGetProjectEvent : public ossimQtCustomEvent
{
public:
   ossimQtGetProjectEvent(ossimQtCustomEventMode mode = ossimQtCustomEvent_NOPROPAGATE)
      :ossimQtCustomEvent(mode,
                          OSSIM_QT_EVENT_GET_PROJECT),
       theProject(NULL)
      {
      }
   void setProject(ossimQtProject* project)
      {
         theProject = project;
      }
   ossimQtProject* getProject()
      {
         return theProject;
      }

protected:
   ossimQtProject* theProject;
};

class ossimQtStateEvent : public ossimQtCustomEvent
{
public:
   enum ossimQtStateEventType
   {
      ossimQtStateEventType_LOAD = 0,
      ossimQtStateEventType_SAVE
   };
   ossimQtStateEvent(ossimQtStateEventType type=ossimQtStateEventType_SAVE,
                     ossimQtCustomEventMode mode = ossimQtCustomEvent_PROPAGATE)
      :ossimQtCustomEvent(mode,
                          OSSIM_QT_EVENT_STATE_EVENT),
       theStateType(type)
      {
      }
   ossimString getPrefix()const
      {
         return thePrefix;
      }
   void setPrefix(const ossimString& prefix)
      {
         thePrefix = prefix;
      }
   ossimKeywordlist& getKeywordlist()
      {
         return theKwl;
      }

   void setStateType(ossimQtStateEventType type)
      {
         theStateType = type;
      }
   ossimQtStateEventType getStateType()const
      {
         return theStateType;
      }
   void setKeywordlist(const ossimKeywordlist& kwl)
      {
         theKwl = kwl;
      }
protected:
   ossimKeywordlist      theKwl;
   ossimString           thePrefix;
   ossimQtStateEventType theStateType;
};

class ossimQtQueryObjectAllocationEvent : public ossimQtCustomEvent
{
public:
   ossimQtQueryObjectAllocationEvent(ossimQtCustomEventMode mode = ossimQtCustomEvent_NOPROPAGATE)
      :ossimQtCustomEvent(mode,
                          OSSIM_QT_EVENT_QUERY_OBJECT_ALLOCATED),
       theObjectsAllocatedFlag(false)
      {}
   
   void setObjectsAllocatedFlag(bool flag = true)
      {
         theObjectsAllocatedFlag = flag;
      }
   bool getObjectsAllocated()const
      {
         return theObjectsAllocatedFlag;
      }
   void setQueryList(std::vector<ossimString>& queryList)
      {
         theClassNameList = queryList;
         std::sort(theClassNameList.begin(),
                   theClassNameList.end());
      }

   void getQueryList(std::vector<ossimString>& queryList)
      {
         queryList = theClassNameList;
      }
   bool find(const ossimString& className)const
      {
         return std::binary_search(theClassNameList.begin(),
                                   theClassNameList.end(),
                                   className);
      }
protected:
   bool theObjectsAllocatedFlag;
   
   std::vector<ossimString> theClassNameList;
};

class ossimQtAddImageFileEvent : public ossimQtCustomEvent
{
public:
  ossimQtAddImageFileEvent(const ossimFilename& filename,
			   ossimQtCustomEventMode mode = ossimQtCustomEvent_NOPROPAGATE)
    :ossimQtCustomEvent(mode, OSSIM_QT_EVENT_ADD_IMAGE_FILE),
    theFilename(filename)
  {}

  const ossimFilename& getFilename()const
  {
    return theFilename;
  }
  void setFilename(const ossimFilename& filename)
  {
    theFilename = filename;
  }

protected:
  ossimFilename theFilename;
};

#endif
