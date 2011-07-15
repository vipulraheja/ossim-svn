/*-----------------------------------------------------------------------------
 * Filename        : ossimConnectableObjectListener.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimConnectableObjectListener
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimListener.h>
#include <ossim/base/ossimConnectionEvent.h>
#include <ossim/base/ossimObjectDestructingEvent.h>
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimPropertyEvent.h>
#include <ossim/base/ossimContainerEvent.h>
#include <ossim/base/ossimRefreshEvent.h>

%}

/* Wrapping the class ossimConnectableObjectListener */
class ossimConnectableObjectListener : public ossimListener
{
        public:
                ossimConnectableObjectListener():ossimListener(){}
                virtual ~ossimConnectableObjectListener(){}

                virtual void processEvent(ossimEvent& event);

                virtual void objectDestructingEvent(ossimObjectDestructingEvent& /*event*/) {}
                virtual void connectionEvent(ossimConnectionEvent& /* event */) {}
                virtual void disconnectInputEvent(ossimConnectionEvent& /* event */) {}
                virtual void disconnectOutputEvent(ossimConnectionEvent& /* event */) {}
                virtual void connectInputEvent(ossimConnectionEvent& /* event */) {}
                virtual void connectOutputEvent(ossimConnectionEvent& /* event */) {}

                virtual void propertyEvent(ossimPropertyEvent& /* event */) {}

                /*!
                 * Typically isued by objects that contain children.  If anyone is
                 * interested, can latch on to this event.  Other objects within the
                 * system might be interest in this event even 
                 */
                virtual void addObjectEvent(ossimContainerEvent& /* event */) {}

                virtual void removeObjectEvent(ossimContainerEvent& /* event */) {}

                virtual void refreshEvent(ossimRefreshEvent& ) {}

                /* Ignoring Macro
                TYPE_DATA */
};
