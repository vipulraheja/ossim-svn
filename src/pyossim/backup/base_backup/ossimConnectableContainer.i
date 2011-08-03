/*-----------------------------------------------------------------------------
 * Filename        : ossim2dTo2dTransform.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossim2dTo2dTransform
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <map>

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimConnectableContainerInterface.h>
#include <ossim/base/ossimConnectableContainer.h>

%}

/* Wrapping class ossimConnectableContainer */
class ossimConnectableContainer : public ossimConnectableObject,
        public ossimConnectableContainerInterface,
        public ossimConnectableObjectListener
{
        public:
                typedef std::map<ossim_int64,
                        ossimRefPtr<ossimConnectableObject> > connectablObjectMapType;

                ossimConnectableContainer(ossimConnectableObject* owner=0);

                virtual ossimObject* getObject();
                virtual const ossimObject* getObject()const;

                virtual ossimConnectableObject* getConnectableObject(ossim_uint32 index);

                /* Ignored due to Macros
                OSSIM_DEPRECATE_METHOD(virtual ossimConnectableObject::ConnectableObjectList findAllObjectsOfType(const RTTItypeid& typeInfo,
                                        bool recurse=true));
                OSSIM_DEPRECATE_METHOD(virtual ossimConnectableObject::ConnectableObjectList findAllObjectsOfType(const ossimString& className,
                                        bool recurse=true));
                OSSIM_DEPRECATE_METHOD(virtual ossimConnectableObject* findFirstObjectOfType(const RTTItypeid& typeInfo,
                                        bool recurse=true));
                OSSIM_DEPRECATE_METHOD(virtual ossimConnectableObject* findFirstObjectOfType(const ossimString& className,
                                        bool recurse=true));
                OSSIM_DEPRECATE_METHOD(ossimConnectableObject* findObject(const ossimId& id,
                                        bool recurse=true));
                OSSIM_DEPRECATE_METHOD(ossimConnectableObject* findObject(const ossimConnectableObject* obj,
                                        bool recurse=true));
                */
                                        
                void makeUniqueIds();

                ossim_uint32 getNumberOfObjects(bool recurse=true)const;

                virtual bool addChild(ossimConnectableObject* attachableObject);
                virtual bool removeChild(ossimConnectableObject* object);

                virtual bool canConnectMyInputTo(ossim_int32 index,
                                const ossimConnectableObject* obj) const;
                virtual bool canConnectMyOutputTo(ossim_int32 index,
                                const ossimConnectableObject* obj) const;

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;

                /*___________________PLACE ALL EVENT HANDLING STUFF HERE_____________
                //   virtual void objectDestructingEvent(ossimObjectDestructingEvent& event);
                //   virtual void propertyEvent(ossimPropertyEvent& event);

                //   virtual void disconnectInputEvent(ossimConnectionEvent& event);
                //   virtual void connectInputEvent(ossimConnectionEvent& event);

                //   virtual void disconnectOutputEvent(ossimConnectionEvent& event);
                //   virtual void connectOutputEvent(ossimConnectionEvent& event); */


                virtual void getChildren(std::vector<ossimConnectableObject*>& children,
                                bool immediateChildrenOnlyFlag);
                void deleteAllChildren();

                virtual void accept(ossimVisitor& visitor);

                /*    void propagateEventToOutputs(ossimEvent& event,
                //                                 ossimConnectableObject* start);
                //    void propagateEventToInputs(ossimEvent& event,
                //                                ossimConnectableObject* start); */

        protected:
                virtual ~ossimConnectableContainer();
                ossimConnectableContainer(const ossimConnectableContainer& rhs);

                void removeAllListeners();
                bool addAllObjects(std::map<ossimId, std::vector<ossimId> >& idMapping,
                                const ossimKeywordlist& kwl,
                                const char* prefix);

                bool connectAllObjects(const std::map<ossimId, std::vector<ossimId> >& idMapping);

                void findInputConnectionIds(std::vector<ossimId>& result,
                                const ossimKeywordlist& kwl,
                                const char* prefix);

                connectablObjectMapType theObjectMap;

                ossimConnectableContainerChildListener* theChildListener;

                /* Ignoring Macros
                TYPE_DATA */
};
