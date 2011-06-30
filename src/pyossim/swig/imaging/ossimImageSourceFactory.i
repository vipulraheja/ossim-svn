/*-----------------------------------------------------------------------------
Filename        : ossimImageSourceFactory.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageSourceFactory
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageSourceFactoryBase.h>
#include <ossim/imaging/ossimImageSourceFactory.h>

%}

class ossimImageSourceFactory : public ossimImageSourceFactoryBase
{
        public:
                virtual ~ossimImageSourceFactory();
                static ossimImageSourceFactory* instance();
                virtual ossimObject* createObject(const ossimString& name)const;
                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix=0)const;
                virtual void getTypeNameList(std::vector<ossimString>& typeList)const;

        protected:
                // Hide from use.
                ossimImageSourceFactory();
                ossimImageSourceFactory(const ossimImageSourceFactory&);
                const ossimImageSourceFactory& operator=(ossimImageSourceFactory&);

                static ossimImageSourceFactory* theInstance;
                TYPE_DATA
};
