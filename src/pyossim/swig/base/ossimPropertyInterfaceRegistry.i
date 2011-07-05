/*-----------------------------------------------------------------------------
 * Filename        : ossimPropertyInterfaceRegistry.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimPropertyInterfaceRegistry
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimObjectFactory.h>
#include <ossim/base/ossimPropertyInterfaceRegistry.h>
#include <ossim/base/ossimRtti.h>

#include <vector>

%}

%import "ossim/base/ossimPropertyInterfaceFactory.h";
%import "ossim/base/ossimPropertyInterface.h";

/* operator = */

class ossimPropertyInterfaceRegistry : public ossimObjectFactory
{
        public:
                virtual ~ossimPropertyInterfaceRegistry();

                static ossimPropertyInterfaceRegistry* instance();

                virtual ossimPropertyInterface* createInterface( const ossimObject* obj ) const;

                /*!
                 * Creates an object given a type name.
                 */
                virtual ossimObject* createObject(const ossimString& typeName)const;

                /*!
                 * Creates and object given a keyword list.
                 */
                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix=0)const;

                /*!
                 * This should return the type name of all objects in all factories.
                 * This is the name used to construct the objects dynamially and this
                 * name must be unique.
                 */
                virtual void getTypeNameList(std::vector<ossimString>& typeList)const;

                bool addFactory( ossimPropertyInterfaceFactory* factory );
                bool registerFactory(ossimPropertyInterfaceFactory* factory);
        protected:
                ossimPropertyInterfaceRegistry()
                        :ossimObjectFactory() {}

                ossimPropertyInterfaceRegistry( const ossimPropertyInterfaceRegistry& rhs )
                        :ossimObjectFactory(rhs) {}

                void operator =(const ossimPropertyInterfaceRegistry&){}
                static ossimPropertyInterfaceRegistry* theInstance;
                vector<ossimPropertyInterfaceFactory*> theFactoryList;

                TYPE_DATA
};

extern "C"
{
        void* ossimPropertyInterfaceRegistryGetInstance();
}
