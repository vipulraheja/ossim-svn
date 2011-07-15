/*-----------------------------------------------------------------------------
 * Filename        : ossimConnectableContainerInterface.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimConnectableContainerInterface
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimRtti.h>
#include <ossim/base/ossimId.h>
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimConnectableContainerInterface.h>
#include <vector>

%}

/* Wrapping class ossimConnectableContainerInterface */
class ossimConnectableContainerInterface
{
        public:
                ossimConnectableContainerInterface(ossimObject* obj):theBaseObject(obj){}
                virtual ~ossimConnectableContainerInterface(){theBaseObject=NULL;}

//              Commented out due to SWIG Syntax Error                
//                virtual ossimConnectableObject::ConnectableObjectList findAllObjectsOfType(const RTTItypeid& typeInfo,
//                                virtual ossimConnectableObject::ConnectableObjectList findAllObjectsOfType(const ossimString& className, 
//                                        bool recurse=true)=0;

                                virtual ossimConnectableObject* findFirstObjectOfType(const RTTItypeid& typeInfo,
                                        bool recurse=true)=0;
                                virtual ossimConnectableObject* findFirstObjectOfType(const ossimString& className,
                                        bool recurse=true)=0;

                                virtual ossimConnectableObject* findObject(const ossimId& id,
                                        bool recurse=true)=0;
                                virtual ossimConnectableObject* findObject(const ossimConnectableObject* obj,
                                        bool recurse=true)=0;

                                virtual void makeUniqueIds()=0;

                                virtual ossim_uint32 getNumberOfObjects(bool recurse=true)const=0;

                                virtual bool addChild(ossimConnectableObject* attachableObject)=0;
                                virtual bool removeChild(ossimConnectableObject* object)=0;

                                ossimObject*       getObject(){return theBaseObject;}
                                const ossimObject* getObject()const{return theBaseObject;}

                                virtual ossimConnectableObject* getConnectableObject(ossim_uint32 index)=0;

                                void deleteAllChildren();
                                virtual void getChildren(std::vector<ossimConnectableObject*>& children,
                                                bool immediateChildrenOnlyFlag)=0;

        protected:
                                ossimObject* theBaseObject;
                                /* Handling Macro
                                TYPE_DATA */
};
