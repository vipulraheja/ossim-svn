/*-----------------------------------------------------------------------------
Filename        : ossimImageSourceFactoryRegistry.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageSourceFactoryRegistry
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageSourceFactoryBase.h>
#include <ossim/imaging/ossimImageSourceFactoryRegistry.h>

%}

/* Include the header file  */
%import "ossim/base/ossimConstants.h";

/* Handling ossimImageSourceFactoryRegistry Assignment operator */
%rename(__setattr__) ossimImageSourceFactoryRegistry::operator=;


/* Wrapping class ossimImageSourceFactoryRegistry */
class ossimImageSourceFactoryRegistry : public ossimImageSourceFactoryBase
{
        public:
                static ossimImageSourceFactoryRegistry* instance();
                virtual ~ossimImageSourceFactoryRegistry();
                virtual ossimObject* createObject(const ossimString& name)const;
                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix=0)const;
                virtual void getTypeNameList(std::vector<ossimString>& typeList)const;

                void registerFactory(ossimImageSourceFactoryBase* factory);
                void unregisterFactory(ossimImageSourceFactoryBase* factory);
                bool findFactory(ossimImageSourceFactoryBase* factory)const;

        protected:
                ossimImageSourceFactoryRegistry(); // hide
                ossimImageSourceFactoryRegistry(const ossimImageSourceFactoryRegistry&);//hide
                void operator = (ossimImageSourceFactoryRegistry&);// hide

                static ossimImageSourceFactoryRegistry* theInstance;
                std::vector<ossimImageSourceFactoryBase*> theFactoryList;

                /* Ignored due to unclean parsing of MACROS     */                
                /* TYPE_DATA                                    */
};

extern "C"
{
        OSSIMDLLEXPORT void* ossimImageSourceFactoryRegistryGetInstance();
}
