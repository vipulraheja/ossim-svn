/*-----------------------------------------------------------------------------
Filename        : ossimImageMetaDataWriterFactoryBase.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageMetaDataWriterFactoryBase 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimObjectFactory.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/imaging/ossimMetaDataWriterFactoryBase.h;

%}

%import "ossim/imaging/ossimMetadataFileWriter.h";

class ossimImageMetaDataWriterFactoryBase : public ossimObjectFactory
{
        public:
                virtual ossimRefPtr<ossimMetadataFileWriter> createWriter(
                                const ossimString& type)const=0;

                virtual void getMetadatatypeList(
                                std::vector<ossimString>& metadatatypeList) const=0;

        protected:
                ossimImageMetaDataWriterFactoryBase();

                ossimImageMetaDataWriterFactoryBase(
                                const ossimImageMetaDataWriterFactoryBase&);

                const ossimImageMetaDataWriterFactoryBase& operator=(
                                const ossimImageMetaDataWriterFactoryBase&);

                TYPE_DATA
};
