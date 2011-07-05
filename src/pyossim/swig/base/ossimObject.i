/*-----------------------------------------------------------------------------
Filename        : ossimObject.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimObject
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <iosfwd>
#include <ossim/base/ossimReferenced.h>
#include <ossim/base/ossimRtti.h>
#include <ossim/base/ossimObject.h>

%}

%import "ossim/base/ossimKeywordlist";
%import "ossim/base/ossimString";

class ossimObject : public ossimReferenced
{
        public:
                ossimObject();
                virtual ~ossimObject();

                virtual ossimObject* dup() const;

                virtual ossimString getShortName()   const;
                virtual ossimString getLongName()    const;
                virtual ossimString getDescription() const;
                virtual ossimString getClassName()   const;

                virtual RTTItypeid getType() const;

                virtual bool canCastTo(ossimObject* obj) const;

                virtual bool canCastTo(const RTTItypeid& id) const;

                virtual bool canCastTo(const ossimString& parentClassName) const;

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0) const;

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

                virtual std::ostream& print(std::ostream& out) const;

                friend OSSIMDLLEXPORT std::ostream& operator<<(std::ostream& out,
                                const ossimObject& obj);

        protected:
                TYPE_DATA
};
