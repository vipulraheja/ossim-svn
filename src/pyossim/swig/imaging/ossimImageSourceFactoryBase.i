/*-----------------------------------------------------------------------------
Filename        : ossimImageSourceFactoryBase.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageSourceFactoryBase
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimObjectFactory.h>
#include <ossim/imaging/ossimImageSourceFactoryBase.h>

%}

%import "ossim/imaging/ossimImageSource.h";

%rename(__set__) ossimImageSourceFactoryBase::operator=;

class OSSIMDLLEXPORT ossimImageSourceFactoryBase : public ossimObjectFactory
{
        public:
                virtual ossimImageSource* createImageSource(const ossimString& name)const;
                virtual ossimImageSource* createImageSource(const ossimKeywordlist& kwl,
                                const char* prefix=0)const;

        protected:
                // Hide from use.
                ossimImageSourceFactoryBase();
                ossimImageSourceFactoryBase(const ossimImageSourceFactoryBase&);
                const ossimImageSourceFactoryBase& operator=(const ossimImageSourceFactoryBase&);
};
