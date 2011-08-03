/*-----------------------------------------------------------------------------
 * Filename        : ossimListenerManager.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimListenerManager
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimListenerManager.h>
#include <list>
#include <ossim/base/ossimRtti.h>
#include <ossim/base/ossimListener.h>
#include <ossim/base/ossimEvent.h>

%}

/* Wrapping class ossimListenerManager */
class ossimListenerManager
{
        public:
                ossimListenerManager();

                virtual ~ossimListenerManager();

                virtual void fireEvent(ossimEvent& event);

                virtual bool addListener(ossimListener* listener);
                virtual bool removeListener(ossimListener* listener);

                /*!
                 * Searches the list and sees if a listener is found
                 */
                virtual bool findListener(ossimListener* listener);

        protected:
                ossimListenerManager(const ossimListenerManager& rhs);

                /*!
                 *  Holds the list of listeners.
                 */
                std::list<ossimListener*> theListenerList;
                bool theEnabledFlag;
                mutable std::list<ossimListener*> theDelayedAdd;
                mutable std::list<ossimListener*> theDelayedRemove;
                mutable bool theFireEventFlag;

                /* Ignoring Macro
                TYPE_DATA */
};
