/*-----------------------------------------------------------------------------
Filename        : ossimProjectionFactoryRegistry.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : 
-----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimObjectFactory.h>
#include <ossim/base/ossimFactoryListInterface.h>
#include <ossim/base/ossimPropertyInterface.h>

#include <ossim/projection/ossimProjection.h>
#include <ossim/projection/ossimProjectionFactoryRegistry.h>
#include <ossim/projection/ossimProjectionFactoryBase.h>
%}


class ossimProjectionFactoryRegistry : public ossimObjectFactory
{
        public:
                virtual ~ossimProjectionFactoryRegistry();

                static ossimProjectionFactoryRegistry* instance();

                ossimProjection* createProjection(const ossimFilename& filename,
                                ossim_uint32 entryIdx) const;
               
                ossimProjection* createProjection(const ossimString& name) const
                {
                        return createNativeObjectFromRegistry(name);
                }
                
                ossimProjection* createProjection(const ossimKeywordlist& kwl,
                                const char* prefix=NULL) const;

                virtual ossimProjection* createProjection(ossimImageHandler* handler)const;
                
                virtual ossimObject* createObject(const ossimString& typeName)const
                {
                        return createObjectFromRegistry(typeName);
                }

                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix=0) const
                {
                        return createObjectFromRegistry(kwl, prefix);
                }

                virtual void getTypeNameList(std::vector<ossimString>& typeList)const
                {
                        getAllTypeNamesFromRegistry(typeList);
                }

        protected:
                ossimProjectionFactoryRegistry();
                ossimProjectionFactoryRegistry(const ossimProjectionFactoryRegistry& rhs);
                void operator = (const ossimProjectionFactoryRegistry&);

                static ossimProjectionFactoryRegistry* m_instance;
                void initializeDefaults();
};
