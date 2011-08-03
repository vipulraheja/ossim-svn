/*-----------------------------------------------------------------------------
 * Filename        : ossim2dTo2dTransformRegistry.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossim2dTo2dTransformRegistry
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimObjectFactory.h>
#include <ossim/base/ossimRtti.h>
#include <ossim/base/ossim2dTo2dTransformFactoryBase.h>
#include <ossim/base/ossim2dTo2dTransform.h>
#include <vector>
#include <ossim/base/ossimFactoryListInterface.h>
#include <ossim/base/ossim2dTo2dTransformRegistry.h>

%}

/* Handling operators */
%rename(__set__) ossim2dTo2dTransformRegistry::operator=;


/* Wrapping class ossim2dTo2dTransformRegistry */
class ossim2dTo2dTransformRegistry : public ossimObjectFactory,
        public ossimFactoryListInterface<ossim2dTo2dTransformFactoryBase,
        ossim2dTo2dTransform>
{
        public:
                virtual ~ossim2dTo2dTransformRegistry(){}
                static ossim2dTo2dTransformRegistry* instance();

                
                virtual ossimObject* createObject(const ossimString& typeName)const
                {
                        return createObjectFromRegistry(typeName);
                }
                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix=0)const
                {
                        return createObjectFromRegistry(kwl, prefix);
                }
                
                
                virtual ossim2dTo2dTransform* createTransform(const ossimString& typeName)const
                {
                        return createNativeObjectFromRegistry(typeName);
                }
                virtual ossim2dTo2dTransform* createTransform(const ossimKeywordlist& kwl,
                                const char* prefix=0)const
                {
                        return createNativeObjectFromRegistry(kwl, prefix);
                }

                /*!
                 * This should return the type name of all objects in all factories.
                 * This is the name used to construct the objects dynamially and this
                 * name must be unique.
                 */
                virtual void getTypeNameList(std::vector<ossimString>& typeList)const
                {
                        getAllTypeNamesFromRegistry(typeList);
                }

        protected:
                ossim2dTo2dTransformRegistry()
                        :ossimObjectFactory() {}

                ossim2dTo2dTransformRegistry( const ossim2dTo2dTransformRegistry& rhs )
                        :ossimObjectFactory(rhs) {}

                void operator =(const ossim2dTo2dTransformRegistry&){}
                static ossim2dTo2dTransformRegistry* m_instance;

                /* Ignoring Macro
                   TYPE_DATA */
};
