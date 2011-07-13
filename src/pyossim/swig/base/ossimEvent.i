/*-----------------------------------------------------------------------------
 * Filename        : ossimEvent.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimEvent
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimEventIds.h>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimEvent.h>

%}

class ossimEvent : public ossimObject
{
        public:
                enum PropagationType
                {
                        PROPAGATION_NONE = 0,
                        PROPAGATION_INPUT = 1,
                        PROPAGATION_OUTPUT = 2
                };

                /**
                 * @param object The object associated with the event if any.
                 *
                 * @param id The event id.
                 */
                ossimEvent(ossimObject* object=NULL,
                                long id=OSSIM_EVENT_NULL_ID);

                ossimEvent(const ossimEvent& rhs);

                long getId()const;
                void setId(long id);

                bool isConsumed()const;
                void setConsumedFlag(bool flag=true);
                void consume();

                /**
                 * This is the originating object that originally 
                 * produced the event.
                 */
                const ossimObject* getObject()const;
                ossimObject*       getObject();
                const ossimObject* getCurrentObject()const;
                ossimObject*       getCurrentObject();

                void setObject(ossimObject* object);
                void setCurrentObject(ossimObject* object);

                void setPropagationType(PropagationType type);
                bool isPropagatingToOutputs()const;
                bool isPropagatingToInputs()const;

        protected:
                ossimObject* theObject;
                ossimObject* theCurrentObject;
                long         theId;
                bool         theIsConsumedFlag;
                PropagationType thePropagationType;

                /* Ignored Macro 
                TYPE_DATA */
};
