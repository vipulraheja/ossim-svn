/*-----------------------------------------------------------------------------
 * Filename        : ossimPropertyInterface.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimPropertyInterface
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimProperty.h>
#include <ossim/base/ossimPropertyInterface.h>

%}

class ossimPropertyInterface
{
        public:
                ossimPropertyInterface() {}

                virtual ~ossimPropertyInterface() {}

                virtual void setProperty(const ossimString& name,
                                const ossimString& value);
                virtual void setProperty(ossimRefPtr<ossimProperty> property);
                virtual ossimRefPtr<ossimProperty> getProperty(const ossimString& name)const; 
                virtual ossimString getPropertyValueAsString(const ossimString& name)const;
                virtual void getPropertyNames(std::vector<ossimString>& propertyNames)const;
                void getPropertyList(std::vector<ossimRefPtr<ossimProperty> >& propertyList)const;
                void setProperties(std::vector<ossimRefPtr<ossimProperty> >& propertyList);

        protected:

                /* Macro Ignored 
                TYPE_DATA */
};
