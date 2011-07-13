/*-----------------------------------------------------------------------------
 * Filename        : ossimObjectDestructingEvent.i 
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimObjectDestructingEvent
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimEvent.h>
#include <ossim/base/ossimEventIds.h>
#include <ossim/base/ossimObjectDestructingEvent.h>

%}

class ossimObjectDestructingEvent : public ossimEvent
{
        public:
                ossimObjectDestructingEvent(ossimObject* objectDestructing=NULL)
                        :ossimEvent(objectDestructing, OSSIM_EVENT_OBJECT_DESTRUCTING_ID) {}
                virtual ossimObject* dup()const{return new ossimObjectDestructingEvent(*this);}

                /* Ignoring
                   TYPE_DATA */
};
