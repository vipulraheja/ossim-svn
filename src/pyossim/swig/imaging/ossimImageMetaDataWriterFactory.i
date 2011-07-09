/*-----------------------------------------------------------------------------
Filename        : ossimImageMetaDataWriterFactory.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageMetaDataWriterFactory 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimRefPtr.h>
#include <ossim/imaging/ossimImageMetaDataWriterFactoryBase.h>
#include <ossim/imaging/ossimImageMetaDataWriterFactory.h>
#include <ossim/imaging/ossimMetadataFileWriter.h>

%}

/* Include the header file containing the declarations to be wrapped */
%import "ossim/base/ossimConstants.h";

/* Handling ossimImageMetaDataWriterFactory Assignment operator */
%rename(__set__) ossimImageMetaDataWriterFactory::operator=;


/* Wrapping class ossimImageMetaDataWriterFactory */
class ossimImageMetaDataWriterFactory:
        public ossimImageMetaDataWriterFactoryBase
{
        public:
                ~ossimImageMetaDataWriterFactory();

                static ossimImageMetaDataWriterFactory* instance();
                virtual ossimObject* createObject(const ossimString& typeName)const;
                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix=0)const;

                virtual ossimRefPtr<ossimMetadataFileWriter> createWriter(
                                const ossimString& type)const;

                virtual void getTypeNameList(std::vector<ossimString>& typeList)const;

                virtual void getMetadatatypeList(
                                std::vector<ossimString>& metadatatypeList) const;

        protected:
                static ossimImageMetaDataWriterFactory* theInstance;

                ossimImageMetaDataWriterFactory();

                ossimImageMetaDataWriterFactory(const ossimImageMetaDataWriterFactory& rhs);

                const ossimImageMetaDataWriterFactory& operator =(
                                const ossimImageMetaDataWriterFactory& rhs);

                /* Ignored due to unclean parsing of MACROS     */                
                /* TYPE_DATA                                    */
};
