/*-----------------------------------------------------------------------------
 * Filename        : ossimProjectionViewControllerFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimProjectionViewControllerFactory 
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimBaseObjectFactory.h>
#include <ossim/base/ossimString.h>

#include <ossim/projection/ossimProjectionViewControllerFactory.h>

%}

/* Wrapping class ossimProjectionViewControllerFactory */
class ossimProjectionViewControllerFactory : public ossimObjectFactory
{
        public:
                static ossimProjectionViewControllerFactory* instance();

                virtual ossimViewController* createViewController(const ossimString& name)const;
                virtual ossimViewController* createViewController(const ossimKeywordlist& kwl,
                                const char* prefix)const;

                virtual ossimObject* createObject(const ossimString& typeName)const;
                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix)const;

                virtual void getTypeNameList(std::vector<ossimString>& typeList)const;

        protected:
                ossimProjectionViewControllerFactory(){}
                ossimProjectionViewControllerFactory(const ossimProjectionViewControllerFactory& /* rhs */){}

                static ossimProjectionViewControllerFactory* theInstance;

                /* Ignoring Macro 
                TYPE_DATA */
};
