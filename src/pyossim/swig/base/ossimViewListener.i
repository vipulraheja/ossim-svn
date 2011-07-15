/*-----------------------------------------------------------------------------
 * Filename        : ossimViewListener.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimViewListener
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimListener.h>
#include <ossim/base/ossimViewEvent.h>
#include <ossim/base/ossimViewListener.h>

%}

/* Wrapping class ossimViewListener */
class ossimViewListener : public ossimListener
{
        public:
                ossimViewListener():ossimListener(){}
                virtual ~ossimViewListener(){}

                virtual void processEvent(ossimEvent& event);
                virtual void viewScaleChangeEvent(ossimViewEvent& /* event */)   {}
                virtual void viewTypeChangeEvent(ossimViewEvent& /* event */)    {}
                virtual void viewEvent(ossimViewEvent& /* event */ )             {}
                virtual void viewTransformChangeEvent(ossimViewEvent& /* event */) {}

                virtual void allViewEvents(ossimViewEvent& /* event */)          {}

                /* Ignoring Macro
                TYPE_DATA */
};
