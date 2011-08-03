/*-----------------------------------------------------------------------------
 * Filename        : ossimElevationDatabaseFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimElevationDatabaseFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/elevation/ossimElevationDatabaseFactoryBase.h>
#include <ossim/elevation/ossimElevationDatabaseFactory.h>
%}

class ossimElevationDatabaseFactory : public ossimElevationDatabaseFactoryBase
{
        public:
                ossimElevationDatabaseFactory()
                {
                        m_instance = this;
                }
                static ossimElevationDatabaseFactory* instance();

                ossimElevationDatabase* createDatabase(const ossimString& typeName)const;
                ossimElevationDatabase* createDatabase(const ossimKeywordlist& kwl,
                                const char* prefix=0)const;
                virtual ossimElevationDatabase* open(const ossimString& connectionString)const;
                virtual void getTypeNameList(std::vector<ossimString>& typeList)const;
        protected:
                static ossimElevationDatabaseFactory* m_instance;
};
