/*-----------------------------------------------------------------------------
 * Filename        : ossimDatumFactoryRegistry.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimDatumFactoryRegistry
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <vector>
#include <ossim/base/ossimConstants.h>                  /* for OSSIM_DLL macro */
#include <ossim/base/ossimDatumFactoryInterface.h> 
#include <ossim/base/ossimDatumFactoryRegistry.h> 
#include <OpenThreads/ReadWriteMutex>

%}

/* Wrapping the class ossimDatumFactoryRegistry */
class ossimDatumFactoryRegistry : public ossimDatumFactoryInterface
{
        public:

                /** destructor */
                ~ossimDatumFactoryRegistry();

                /**
                 * instance method
                 *
                 * @return Point to the instance of the registry.
                 */
                static ossimDatumFactoryRegistry* instance();

                void registerFactory(ossimDatumFactoryInterface* factory);

                virtual const ossimDatum* create(const ossimString& code)const;
                virtual const ossimDatum* create(const ossimKeywordlist& kwl, const char *prefix=0) const;

                virtual void getList(std::vector<ossimString>& list) const;

        protected:

                /** hidden from use default constructor */
                ossimDatumFactoryRegistry();

                /** Single static instance of this class. */
                static ossimDatumFactoryRegistry* theInstance;

                mutable OpenThreads::ReadWriteMutex theFactoryListMutex;
                std::vector<ossimDatumFactoryInterface*> theFactoryList;
};
