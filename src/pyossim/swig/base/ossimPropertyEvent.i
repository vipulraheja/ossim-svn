/*-----------------------------------------------------------------------------
 * Filename        : ossimPropertyEvent.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimPropertyEvent
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimEvent.h>
#include <ossim/base/ossimPropertyEvent.h>

%}

class ossimPropertyEvent : public ossimEvent
{
        public:
                ossimPropertyEvent(ossimObject* object) // the event id
                        :ossimEvent(object, OSSIM_EVENT_PROPERTY_ID) {}

                virtual ossimObject* dup()const{return new ossimPropertyEvent(*this);}
};
