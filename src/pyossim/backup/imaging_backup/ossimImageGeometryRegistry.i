/*-----------------------------------------------------------------------------
 * Filename        : ossimImageGeometryRegistry.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageGeometryRegistry
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimConstants.h>
#include <ossim/imaging/ossimImageGeometryFactoryBase.h>
#include <ossim/imaging/ossimImageGeometry.h>
#include <ossim/base/ossimFactoryListInterface.h>
#include <ossim/imaging/ossimImageGeometryRegistry.h>

%}

/* Include the required header files */
%import "ossim/base/ossimConstants.h";

/* Handling the vector<ossimDpt> */
%include "std_vector.i"
namespace std
{
//        %template(ossimImageGeometryRegistry_ossimFactoryListInterface) 
//                ossimFactoryListInterface<ossimImageGeometryFactoryBase,
//                ossimImageGeometry>;
        %template(vectorossimString) vector<ossimString>;
};

/* Handling ossimImageMetaDataWriterFactory Assignment operator */
%rename(__set__) ossimImageGeometryRegistry::operator=;

/* Wrapping the class ossimImageGeometryRegistry */
class ossimImageGeometryRegistry : public ossimBaseObjectFactory,
        public ossimFactoryListInterface<ossimImageGeometryFactoryBase,
        ossimImageGeometry>
{
        public:
                virtual ~ossimImageGeometryRegistry(){m_instance=0;}
                static ossimImageGeometryRegistry* instance();

                virtual ossimObject* createObject(const ossimString& typeName)const
                {
                        return createObjectFromRegistry(typeName);
                }

                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix=0)const
                {
                        return createObjectFromRegistry(kwl, prefix);
                }

                virtual bool extendGeometry(ossimImageHandler* handler)const;

                virtual void getTypeNameList(std::vector<ossimString>& typeList)const
                {
                        getAllTypeNamesFromRegistry(typeList);
                }

        protected:
                ossimImageGeometryRegistry()
                        :ossimBaseObjectFactory() {}

                ossimImageGeometryRegistry( const ossimImageGeometryRegistry& rhs )
                        :ossimBaseObjectFactory(rhs) {}

                void operator =(const ossimImageGeometryRegistry&){}
                static ossimImageGeometryRegistry* m_instance;

                /* Ignored due to unclean parsing of MACROS     */
                /* TYPE_DATA                                    */
};
