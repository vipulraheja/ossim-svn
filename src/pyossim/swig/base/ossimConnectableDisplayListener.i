/*-----------------------------------------------------------------------------
 * Filename        : ossimConnectableDisplayListener.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimConnectableDisplayListener
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimListener.h>
#include <ossim/base/ossimConnectableDisplayListener.h>

%}        

/**
 * This class is intended for connectable displays that wants to be a
 * ossimConnectableObjectListener and a ossimDisplayEventListener to avoid
 * a triangle inheritance.
 */
class ossimConnectableDisplayListener : public ossimListener
{
        public:

                /** default constructor */
                ossimConnectableDisplayListener();

                virtual void processEvent(ossimEvent& event);

                /** @param event Event to handle signifying an object destroying. */
                virtual void objectDestructingEvent(ossimObjectDestructingEvent& event);

                /** @param event Event to handle signifying an object connecting. */
                virtual void connectionEvent(ossimConnectionEvent& event);

                /** @param event Event to handle signifying a disconnect input event. */
                virtual void disconnectInputEvent(ossimConnectionEvent& event);
                virtual void disconnectOutputEvent(ossimConnectionEvent& event);
                virtual void connectInputEvent(ossimConnectionEvent& event);
                virtual void connectOutputEvent(ossimConnectionEvent& event);

                virtual void propertyEvent(ossimPropertyEvent& event);
                virtual void displayListEvent(ossimDisplayListEvent&);
                virtual void displayRefreshEvent(ossimDisplayRefreshEvent&);
                virtual void refreshEvent(ossimRefreshEvent& event);

                /**
                 * Container Events:
                 * Typically isued by objects that contain children.  If anyone is
                 * interested, can latch on to this event.  Other objects within the
                 * system might be interest in this event even 
                 */
                virtual void addObjectEvent(ossimContainerEvent& event);
                virtual void removeObjectEvent(ossimContainerEvent& event);

                /* Ignoring Macro
                TYPE_DATA */
};
