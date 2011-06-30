/*-----------------------------------------------------------------------------
 * Filename        : ossimImageChain.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageChain
 * ---------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimImageChain.h>
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimId.h>
#include <ossim/base/ossimConnectableContainerInterface.h>

%}

class ossimImageChain : public ossimImageSource, 
        public ossimConnectableObjectListener,
        public ossimConnectableContainerInterface
{
        public:
                ossimImageChain();

                virtual ~ossimImageChain();

                ossimConnectableObject* operator[](ossim_uint32 index);

                virtual ossimConnectableObject* getConnectableObject(ossim_uint32 index);

                virtual ossim_int32 indexOf(ossimConnectableObject* obj) const;

                virtual ossimImageSource* getFirstSource();
                virtual ossimObject* getFirstObject();
                virtual ossimImageSource* getLastSource();
                virtual ossimObject* getLastObject();

                bool addFirst(ossimConnectableObject* obj);
                bool addLast(ossimConnectableObject* obj);

                bool deleteFirst();
                bool deleteLast();

                bool insertRight(ossimConnectableObject* newObj,
                                ossimConnectableObject* rightOfThisObj);
                bool insertRight(ossimConnectableObject* newObj,
                                const ossimId& id);
                bool insertLeft(ossimConnectableObject* newObj,
                                const ossimId& id);
                bool insertLeft(ossimConnectableObject* newObj,
                                ossimConnectableObject* leftOfThisObj);

                bool replace(ossimConnectableObject* newObj,
                                ossimConnectableObject* oldObj);

                virtual bool add(ossimConnectableObject* source);

                virtual ossimRefPtr<ossimImageData> getTile(const ossimIrect& tileRect,
                                ossim_uint32 resLevel=0);

                virtual ossim_uint32 getNumberOfInputBands() const;

                virtual ossimScalarType getOutputScalarType() const;

                virtual double getNullPixelValue(ossim_uint32 band=0)const;
                virtual double getMinPixelValue(ossim_uint32 band=0)const;
                virtual double getMaxPixelValue(ossim_uint32 band=0)const;

                virtual void getOutputBandList(std::vector<ossim_uint32>& bandList) const;

                virtual ossim_uint32 getTileWidth()const;

                virtual ossim_uint32 getTileHeight()const;

                virtual ossimIrect getBoundingRect(ossim_uint32 resLevel=0)const;

                virtual void getValidImageVertices(vector<ossimIpt>& validVertices,
                                ossimVertexOrdering ordering=OSSIM_CLOCKWISE_ORDER,
                                ossim_uint32 resLevel=0)const;

                virtual ossimRefPtr<ossimImageGeometry> getImageGeometry();

                virtual void getDecimationFactor(ossim_uint32 resLevel,
                                ossimDpt& result) const;
                virtual void getDecimationFactors(vector<ossimDpt>& decimations) const;

                virtual ossim_uint32 getNumberOfDecimationLevels()const;

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=NULL)const;
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=NULL);

                virtual void initialize();
                virtual void enableSource();
                virtual void disableSource();

                /*
                   bool canConnectMyInputTo(ossim_int32 myInputIndex,
                   const ossimConnectableObject* object)const
                   {
                   if(theImageChainList.size()&&
                   theImageChainList[theImageChainList.size()-1].valid())
                   {
                   ossimConnectableObject* obj = PTR_CAST(ossimConnectableObject, theImageChainList[theImageChainList.size()-1].get());
                   if(obj)
                   {
                   return obj->canConnectMyInputTo(myInputIndex,
                   object);
                   }
                   }
                   else if(!theImageChainList.size())
                   {
                   return true;
                   }
                   return false;
                   }
                 */

                // __CONNECTABLE CONTAINER DEFINTIONS__
                virtual void makeUniqueIds();

                virtual ossim_uint32 getNumberOfObjects(bool recurse=true)const;
                virtual ossim_uint32 getNumberOfSources() const;

                virtual bool addChild(ossimConnectableObject* attachableObject);
                virtual bool removeChild(ossimConnectableObject* object);

                virtual ossimConnectableObject* removeChild(const ossimId& id);

                virtual void getChildren(vector<ossimConnectableObject*>& children,
                                bool immediateChildrenOnlyFlag);
                //__END CONNECTABLE CONTAINER INTERFACE__

                virtual void disconnectInputEvent(ossimConnectionEvent& event);
                virtual void disconnectOutputEvent(ossimConnectionEvent& event);
                virtual void connectInputEvent(ossimConnectionEvent& event);
                virtual void connectOutputEvent(ossimConnectionEvent& event);
                virtual void objectDestructingEvent(ossimObjectDestructingEvent& event);

                virtual void propagateEventToOutputs(ossimEvent& event);
                virtual void propagateEventToInputs(ossimEvent& event);


                virtual void accept(ossimVisitor& visitor);

        protected:
                friend class ossimImageChainChildListener;

                ossimConnectableObject::ConnectableObjectList theImageChainList;

                ossimRefPtr<ossimImageData>     theBlankTile;

                ossimImageChainChildListener*   theChildListener;

                mutable bool theLoadStateFlag;

                bool addAllSources(map<ossimId, vector<ossimId> >& idMapping,
                                const ossimKeywordlist& kwl,
                                const char* prefix = NULL);
                void findInputConnectionIds(vector<ossimId>& result,
                                const ossimKeywordlist& kwl,
                                const char* prefix=NULL);
                bool connectAllSources(const map<ossimId, vector<ossimId> >& idMapping);

                void deleteList();

                //TYPE_DATA
};
