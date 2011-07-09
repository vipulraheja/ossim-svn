/*-----------------------------------------------------------------------------
Filename        : ossimImageMetaDataWriterRegistry.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageMetaDataRegistry 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimRefPtr.h>

#include <ossim/imaging/ossimImageMetaDataWriterFactoryBase.h>
#include <ossim/imaging/ossimMetadataFileWriter.h>
#include <ossim/imaging/ossimImageMetaDataWriterRegistry.h>

%}

/* Handling the std::exception */
%include "exception.i"
%exception
{
        try
        {
                $action
        }
        catch(const std::exception& e)
        {
                SWIG_exception(SWIG_RuntimeError, e.what());
        }
}

/* Handling ossimImageMetaDataWriterRegistry Assignment operator */
%rename(__set__) ossimImageMetaDataWriterRegistry::operator=;

/* Include the header file containing the declarations to be wrapped */
%import "ossim/base/ossimConstants.h";

/* Wrapping the file */
%include "ossim/imaging/ossimImageMetaDataWriterRegistry.h"


/*
class ossimImageMetaDataWriterRegistry : 
        public ossimImageMetaDataWriterFactoryBase
{
        public:
                ~ossimImageMetaDataWriterRegistry();

                static ossimImageMetaDataWriterRegistry* instance();

                void registerFactory(ossimImageMetaDataWriterFactoryBase* factory);
                void unregisterFactory(ossimImageMetaDataWriterFactoryBase* factory);
                bool findFactory(ossimImageMetaDataWriterFactoryBase* factory)const;
                
                virtual ossimObject* createObject(const ossimString& typeName)const;

                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix=0)const;

                virtual ossimRefPtr<ossimMetadataFileWriter> createWriter(
                                const ossimString& type)const;

                virtual void getTypeNameList(std::vector<ossimString>& typeList)const;

                virtual void getMetadatatypeList(
                                std::vector<ossimString>& metadatatypeList)const;

        protected:
                ossimImageMetaDataWriterRegistry();

                ossimImageMetaDataWriterRegistry(
                                const ossimImageMetaDataWriterRegistry& rhs);

                const ossimImageMetaDataWriterRegistry& operator=(
                                const ossimImageMetaDataWriterRegistry &rhs);

                // static ossimImageMetaDataWriterRegistry* theInstance;
                std::vector<ossimImageMetaDataWriterFactoryBase*> theFactoryList;
};


extern "C"
{
        OSSIMDLLEXPORT void* ossimImageMetaDataWriterRegistryGetInstance();
}*/
