/*-----------------------------------------------------------------------------
 * Filename        : ossimStringProperty.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimStringProperty
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimProperty.h>
#include <ossim/base/ossimStringProperty.h>
#include <vector>

%}

class ossimStringProperty : public ossimProperty
{
        public:
                ossimStringProperty(const ossimString& name = ossimString(""),
                                const ossimString& value = ossimString(""),
                                bool editableFlag = true,
                                const std::vector<ossimString>& constraintList = std::vector<ossimString>());

                ossimStringProperty(const ossimStringProperty& rhs);

                virtual ossimObject* dup()const;

                virtual const ossimProperty& assign(const ossimProperty& rhs);

                void setEditableFlag(bool flag);
                bool getEditableFlag()const;
                bool isEditable()const;

                void clearConstraints();

                void setConstraints(const std::vector<ossimString>& constraintList);

                void addConstraint(const ossimString& value);
                const std::vector<ossimString>& getConstraints()const;

                bool hasConstraints()const;

                virtual bool setValue(const ossimString& value);

                virtual void valueToString(ossimString& valueResult)const;

        protected:
                ossimString theValue;
                bool        theEditableFlag;
                std::vector<ossimString> theConstraints;

                TYPE_DATA
};
