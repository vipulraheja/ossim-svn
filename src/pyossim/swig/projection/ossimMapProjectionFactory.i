/*-----------------------------------------------------------------------------
 * Filename        : ossimMapProjectionFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimMapProjectionFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/projection/ossimProjectionFactoryBase.h>
#include <ossim/projection/ossimProjectionFactory.h>
#include <ossim/projection/ossimMapProjectionFactory.h>

%}

%import "ossim/projection/ossimProjection.h";
%import "ossim/base/ossimString.h";

class ossimMapProjectionFactory : public ossimProjectionFactoryBase
{
        public:
                static ossimMapProjectionFactory* instance();

                virtual ossimProjection* createProjection(const ossimFilename& filename,
                                ossim_uint32 entryIdx)const;
                virtual ossimProjection* createProjection(const ossimString& name)const;
                virtual ossimProjection* createProjection(const ossimKeywordlist& kwl,
                                const char* prefix = 0)const;
                virtual ossimObject* createObject(const ossimString& typeName)const;

                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix=0)const;

                virtual void getTypeNameList(std::vector<ossimString>& typeList)const;

        protected:
                ossimMapProjectionFactory() {}
                static ossimMapProjectionFactory*  theInstance;
};
