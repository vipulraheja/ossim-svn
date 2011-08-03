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

/* Handling ossimImageSourceFactory Assignment operator */
%rename(__set__) ossimImageSourceFactory::operator=;

/* Wrapping class ossimImageSourceFactory */
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
                /* Hide from use */
                ossimImageSourceFactory();
                ossimImageSourceFactory(const ossimImageSourceFactory&);
                const ossimImageSourceFactory& operator=(ossimImageSourceFactory&);

                static ossimImageSourceFactory* theInstance;
                
                /* Ignored due to unclean parsing of MACROS     */                
                /* TYPE_DATA                                    */
};
