/*-----------------------------------------------------------------------------
 * Filename        : ossimConnectableObject.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimConnectableObject
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <vector>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimId.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimListenerManager.h>
#include <ossim/base/ossimPropertyInterface.h>
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimRefPtr.h>

%}

/* Wrapping class ossimConnectableObject */
class ossimConnectableObject : public ossimObject,
        public ossimListenerManager,
        public ossimPropertyInterface
{
        public:
                typedef std::vector<ossimRefPtr<ossimConnectableObject> > ConnectableObjectList;
                enum ossimConnectableObjectDirectionType
                {
                        CONNECTABLE_DIRECTION_NONE   = 0,
                        CONNECTABLE_DIRECTION_INPUT  = 1,
                        CONNECTABLE_DIRECTION_OUTPUT = 2
                };

                /**
                 * Base constructor of this object.
                 */
                ossimConnectableObject(ossimObject* owner=0);
                ossimConnectableObject(ossimObject* owner,
                                ossim_int32 inputListSize,
                                ossim_int32 outputListSize,
                                bool inputListIsFixedFlag=true,
                                bool outputListIsFixedFlag=true);

                virtual ~ossimConnectableObject();
                
                /**
                 * All connectable objects will have id's.  This allows us to
                 * set the id of this object.
                 */
                void setId(const ossimId& id){theId = id;}

                /**
                 * Will allow us to get this object's id.
                 */
                const ossimId& getId()const{return theId;}

                /**
                 * Fetches the current owner, most likely a container but not limited to one.
                 */
                const ossimObject* getOwner() const { return theOwner; }

                /**
                 * Permits changing the object's owner.
                 */
                virtual void changeOwner(ossimObject* owner);

                virtual void setDescription(const ossimString& description);
                virtual ossimString getDescription()const;

                virtual bool isConnected(ossimConnectableObjectDirectionType direction = CONNECTABLE_DIRECTION_INPUT)const;


                /* Ignoring Deprecated
                OSSIM_DEPRECATE_METHOD(virtual ossimConnectableObject* findConnectableObject(const ossimId& id));
                OSSIM_DEPRECATE_METHOD(virtual ossimConnectableObject* findObjectOfType(RTTItypeid typeId,
                                        ossimConnectableObjectDirectionType directionType,
                                        bool recurse = true));
                OSSIM_DEPRECATE_METHOD(virtual ossimConnectableObject* findObjectOfType(const ossimString& obj,
                                        ossimConnectableObjectDirectionType directionType,
                                        bool recurse = true));
                OSSIM_DEPRECATE_METHOD(virtual ossimConnectableObject* findInputObjectOfType(
                                        const ossimString& className));
                */                                        


                virtual ossim_int32 findInputIndex(const ossimConnectableObject* object);
                virtual ossim_int32 findInputIndex(const ossimId& id);
                virtual ossim_int32 findOutputIndex(const ossimConnectableObject* object);
                virtual ossim_int32 findOutputIndex(const ossimId& id);


                virtual ossim_int32 getMyInputIndexToConnectTo(ossimConnectableObject* object)const;
                virtual ossim_int32 getMyOutputIndexToConnectTo(ossimConnectableObject* object)const;


                virtual bool canConnectMyInputTo(ossim_int32 myInputIndex,
                                const ossimConnectableObject* object)const=0;
                virtual bool canConnectMyOutputTo(ossim_int32 myOutputIndex,
                                const ossimConnectableObject* object)const;


                virtual void disconnect(ossimConnectableObject* object=0);
                virtual void disconnect(const ossimId& id);


                virtual ossimRefPtr<ossimConnectableObject> disconnectMyInput(ossim_int32 inputIndex,
                                bool disconnectOutputFlag=true,
                                bool createEventFlag = true);
                virtual void disconnectMyInput(ossimConnectableObject* input,
                                bool disconnectOutputFlag=true,
                                bool createEventFlag = true);
                virtual void disconnectMyInputs(
                                ConnectableObjectList& inputList,
                                bool disconnectOutputFlag=true,
                                bool createEventFlag=true);
                

                virtual ossimRefPtr<ossimConnectableObject> disconnectMyOutput(ossim_int32 outputIndex,
                                bool disconnectInputFlag=true,
                                bool createEventFlag = true);
                virtual void disconnectMyOutput(ossimConnectableObject* output,
                                bool disconnectInputFlag=true,
                                bool createEventFlag=true);
                virtual void disconnectMyOutputs(
                                ConnectableObjectList& outputList,
                                bool disconnectOutputFlag=true,
                                bool createEventFlag=true);


                virtual void disconnectAllInputs();
                virtual void disconnectAllOutputs();
                

                virtual ossim_int32 connectMyInputTo(ossimConnectableObject* inputObject,
                                bool makeOutputConnection=true,
                                bool createEventFlag=true);
                virtual ossim_int32 connectMyInputTo(ossim_int32 inputIndex,
                                ossimConnectableObject* inputObject,
                                bool makeOutputConnection=true,
                                bool createEventFlag=true);
                virtual bool connectMyInputTo(
                                ConnectableObjectList& inputList,
                                bool makeOutputConnection=true,
                                bool createEventFlag = true);   


                virtual ossim_int32 connectMyOutputTo(ossimConnectableObject* outputObject,
                                bool makeInputConnection=true,
                                bool createEventFlag=true);
                virtual bool connectMyOutputTo(
                                ConnectableObjectList& outputList,
                                bool makeInputConnection=true,
                                bool createEventFlag=true);
                virtual bool connectInputList(
                                ConnectableObjectList& inputList);
                virtual bool connectOutputList(
                                ConnectableObjectList& outputList);

                
                virtual ossim_uint32 getNumberOfInputs()const
                {
                        return (ossim_uint32)theInputObjectList.size();
                }
                virtual ossim_uint32 getNumberOfOutputs()const
                {
                        return (ossim_uint32)theOutputObjectList.size();
                }
                
                
                ossimConnectableObject* getInput(ossim_uint32 index=0);   
                const ossimConnectableObject* getInput(ossim_uint32 index=0)const;
                ossimConnectableObject* getOutput(ossim_uint32 index=0);
                const ossimConnectableObject* getOutput(ossim_uint32 index=0)const;


                virtual void setNumberOfInputs(ossim_int32 numberOfInputs);

                virtual bool getInputListIsFixedFlag()const
                {
                        return theInputListIsFixedFlag;
                }
                virtual bool getOutputListIsFixedFlag()const
                {
                        return theOutputListIsFixedFlag;
                }

                virtual void setNumberOfOutputs(ossim_int32 numberOfInputs);


                const ConnectableObjectList& getInputList()const
                {
                        return theInputObjectList;
                }
                const ConnectableObjectList& getOutputList()const
                {
                        return theOutputObjectList;
                }
                ConnectableObjectList& getInputList()
                {
                        return theInputObjectList;
                }
                ConnectableObjectList& getOutputList()
                {
                        return theOutputObjectList;
                }


                /* Ignoring Deprecated
                OSSIM_DEPRECATE_METHOD(virtual void findAllObjectsOfType(ConnectableObjectList& result, const RTTItypeid& typeInfo, bool recurse=true) );
                OSSIM_DEPRECATE_METHOD(virtual void findAllObjectsOfType(ConnectableObjectList& result,
                                        const ossimString& className,
                                        bool recurse=true));
                OSSIM_DEPRECATE_METHOD(virtual void findAllInputsOfType(
                                        ConnectableObjectList& result,
                                        const RTTItypeid& typeInfo,
                                        bool propagateToInputs=true,
                                        bool recurseChildren=false));
                OSSIM_DEPRECATE_METHOD(virtual void findAllInputsOfType(
                                        ConnectableObjectList& result,
                                        const ossimString& className,
                                        bool propagateToInputs=true,
                                        bool recurseChildren=false));
                OSSIM_DEPRECATE_METHOD(virtual void findAllOutputsOfType(
                                        ConnectableObjectList& result,
                                        const ossimString& className,
                                        bool propagateToOutputs=true,
                                        bool recurseChildren=false));
                OSSIM_DEPRECATE_METHOD(virtual void findAllOutputsOfType(
                                        ConnectableObjectList& result,
                                        const RTTItypeid& typeInfo,
                                        bool propagateToOutputs=true,
                                        bool recurseChildren=false));
                 */


                virtual void propagateEventToOutputs(ossimEvent& event);
                virtual void propagateEventToInputs(ossimEvent& event);


                /* ------------------- PROPERTY INTERFACE -------------------- */
                virtual void setProperty(ossimRefPtr<ossimProperty> property);
                virtual void setProperty(const ossimString& name, const ossimString& value);
                virtual ossimRefPtr<ossimProperty> getProperty(const ossimString& name)const;
                virtual void getPropertyNames(std::vector<ossimString>& propertyNames)const;
                /* ------------------ PROPERTY INTERFACE END ------------------- */


                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix = 0);

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix = 0)const;

                
                virtual ossim_uint32 saveStateOfAllInputs(ossimKeywordlist& kwl,
                                bool saveThisStateFlag=true,
                                ossim_uint32 objectIndex=1,
                                const char* prefix=0) const;
                
                
                bool moveInputUp(const ossimId& id);
                bool moveInputDown(const ossimId& id);
                bool moveInputToTop(const ossimId& id);
                bool moveInputToBottom(const ossimId& id);

                virtual void accept(ossimVisitor& visitor);


        protected:

                ossimId      theId;
                ossimString  theDescription;
                ossimObject* theOwner;

                bool theInputListIsFixedFlag;
                bool theOutputListIsFixedFlag;
                
                ConnectableObjectList     theInputObjectList;
                ConnectableObjectList     theOutputObjectList;

        private:
                /* Ignoring Macro
                TYPE_DATA */
};
