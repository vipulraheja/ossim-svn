/*-----------------------------------------------------------------------------
Filename        : ossimImageWriterFactory.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageWriterFactory
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageWriterFactoryBase.h>
#include <ossim/imaging/ossimImageWriterFactory.h>

%}        

/* Wrapping the class ossimImageWriterFactory */
class ossimImageWriterFactory: public ossimImageWriterFactoryBase
{
        public:
                virtual ~ossimImageWriterFactory();
                static ossimImageWriterFactory* instance();

                ossimImageFileWriter *createWriterFromExtension(const ossimString& fileExtension)const;
                virtual ossimImageFileWriter* createWriter(const ossimKeywordlist& kwl,
                                const char *prefix=0)const;
                virtual ossimImageFileWriter* createWriter(const ossimString& typeName)const;

                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char *prefix=0)const;
                virtual ossimObject* createObject(const ossimString& typeName)const;

                virtual void getExtensions(std::vector<ossimString>& result)const;

                virtual void getTypeNameList(std::vector<ossimString>& typeList)const;

                /*!
                 * getImageTypeList.  This is the actual image type name.  So for
                 * example, ossimTiffWriter has several image types.  Some of these
                 * include TIFF_TILED, TIFF_TILED_BAND_SEPARATE ... etc.  The
                 * ossimGdalWriter
                 * may include GDAL_IMAGINE_HFA, GDAL_RGB_NITF, GDAL_JPEG20000, ... etc
                 * A writer should be able to be instantiated by this name as well as a
                 * class name
                 */
                virtual void getImageTypeList(std::vector<ossimString>& imageTypeList)const;

                virtual void getImageFileWritersBySuffix(ossimImageWriterFactoryBase::ImageFileWriterList& result,
                                const ossimString& ext)const;
                virtual void getImageFileWritersByMimeType(ossimImageWriterFactoryBase::ImageFileWriterList& result,
                                const ossimString& mimeType)const;
        protected:
                ossimImageWriterFactory() {}

                static ossimImageWriterFactory* theInstance;

                ossimImageFileWriter* createFromMimeType(const ossimString& mimeType)const;
                bool isImageTypeName(const ossimString& name)const;
};
