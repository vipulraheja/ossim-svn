/*-----------------------------------------------------------------------------
 * Filename        : ossimListener.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimListener
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimListener.h>
#include <ossim/base/ossimEvent.h>

%}


/*!
 * Base class for all listners.  Listners nned to derive from this
 * class and override the processEvent method.
 */
class ossimListener
{
        public:

                ossimListener();

                virtual ~ossimListener();

                /**
                 * ProcessEvent.  The defaul is to do nothing.  Derived
                 * classes need to override this class.
                 */
                virtual void processEvent(ossimEvent& event);

                void enableListener();
                void disableListener();

                void setListenerEnableFlag(bool flag);
                bool isListenerEnabled() const;
                bool getListenerEnableFlag() const;

        protected:
                bool theListenerEnableFlag;

                /* ignored Macro
                TYPE_DATA */
};
