/*-----------------------------------------------------------------------------
 * Filename        : ossimObjectFactoryRegistry.i 
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimObjectFactoryRegistry
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <vector>

#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimObjectFactory.h>
#include <ossim/base/ossimFactoryListInterface.h>
#include <ossim/base/ossimObjectFactoryRegistry.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimString.h>

%}


/* Handling assignment operator */
%rename(__set__) ossimObjectFactoryRegistry::operator=;

/* Wrapping the class ossimObjectFactoryRegistry */
class ossimObjectFactoryRegistry : public ossimObject,
        public ossimFactoryListInterface<ossimObjectFactory, ossimObject>
{
        public:
                virtual ~ossimObjectFactoryRegistry();
                static ossimObjectFactoryRegistry* instance();

                virtual ossimObject* createObject(const ossimString& name)const
                {
                        return createObjectFromRegistry(name);
                }
                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix=0)const
                {
                        return createObjectFromRegistry(kwl, prefix);
                }

                /*!
                 * Returns a type list of all objects that can be instantiated
                 * through the createObjectMethods above.
                 */
                virtual void getTypeNameList(std::vector<ossimString>& typeList)const
                {
                        getAllTypeNamesFromRegistry(typeList);
                }

                virtual void getTypeNameList(std::vector<ossimString>& typeList,
                                const ossimString& baseType)const;

        protected:
                ossimObjectFactoryRegistry();                                                   //hide
                ossimObjectFactoryRegistry(const ossimObjectFactoryRegistry&):ossimObject(){}   //hide
                void operator =(const ossimObjectFactoryRegistry&){}                            //hide

                /* Ignored due to unclean parsing of MACROS     *
                TYPE_DATA */
};

extern "C"
{
        void* ossimObjectFactoryRegistryGetInstance();
}
