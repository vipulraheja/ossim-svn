/*-----------------------------------------------------------------------------
 * Filename        : ossimObjectFactory.i  
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimObjectFactory 
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <vector>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimObjectFactory.h>

%}

class ossimObjectFactory : public ossimObject
{
        public:
                virtual ~ossimObjectFactory(){}

                /*!
                 * Creates an object given a type name.
                 */
                virtual ossimObject* createObject(const ossimString& typeName)const=0;

                /*!
                 * Creates and object given a keyword list.
                 */
                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix=0)const=0;

                /*!
                 * This should return the type name of all objects in all factories.
                 * This is the name used to construct the objects dynamially and this
                 * name must be unique.
                 */
                virtual void getTypeNameList(std::vector<ossimString>& typeList)const=0;

        protected:
                TYPE_DATA
};
