/*-----------------------------------------------------------------------------
 * Filename        : ossimViewController.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimViewController
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimSource.h>
#include <ossim/base/ossimViewInterface.h>
#include <ossim/base/ossimViewController.h>

%}

/*!
 * All view sources will derive from this class.  For example
 * we can have a mapped view or Perspective view of the scene
 * being rendered.  All sources within the containers are expected
 * to derive from the view interface.
 */
class ossimViewController : public ossimSource
{
        public:

                ossimViewController();

                ossimViewController(ossimObject* owner,
                                ossim_uint32 inputListSize,
                                ossim_uint32 outputListSize,
                                bool   inputListFixedFlag=true,
                                bool   outputListFixedFlag=false);

                virtual ~ossimViewController();

                virtual ossimString getShortName()const;
                virtual ossimString getLongName()const;

                virtual bool propagateView();
                virtual bool setView(ossimObject* object);
                virtual ossimObject* getView();
                virtual const ossimObject* getView()const;
                virtual bool canConnectMyInputTo(ossim_int32 index,
                                const ossimConnectableObject* obj)const;
                virtual const ossimObject* findFirstViewOfType(RTTItypeid typeId)const;
        protected:
                ossimRefPtr<ossimObject> theView;

                /* Ignoring Macro
                TYPE_DATA */
};
