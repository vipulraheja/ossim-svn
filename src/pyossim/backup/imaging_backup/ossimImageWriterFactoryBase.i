/*-----------------------------------------------------------------------------
 * Filename        : ossimImageWriterFactoryBase.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageWriterFactoryBase
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimObjectFactory.h>
#include <ossim/base/ossimString.h>
#include <ossim/imaging/ossimImageFileWriter.h>
#include <ossim/imaging/ossimImageWriterFactoryBase.h>
#include <vector>

%}

        /* Include the required header files */
%import "ossim/base/ossimConstants.h"

/* Wrapping the class ossimImageWriterFactoryBase */
class ossimImageWriterFactoryBase : public ossimObjectFactory
{
        public:
                typedef std::vector<ossimRefPtr<ossimImageFileWriter> > ImageFileWriterList;

                virtual ~ossimImageWriterFactoryBase() {}
                virtual ossimImageFileWriter* createWriter(const ossimKeywordlist& kwl,
                                const char *prefix=0)const=0;
                virtual ossimImageFileWriter* createWriter(const ossimString& typeName)const=0;

                virtual void getExtensions(std::vector<ossimString>& result)const=0;

                /*!
                 * getImageTypeList.  This is the actual image type name.  So for
                 * example, ossimTiffWriter has several image types.  Some of these
                 * include tiff_tiled, tiff_tiled_band_separate ... etc.  The ossimGdalWriter
                 * may include gdal_imagine_hfa,gdal_nitf_rgb_band_separate, ... etc
                 * A writer should be able to be instantiated by this name as well as a class name
                 */
                virtual void getImageTypeList(std::vector<ossimString>& imageTypeList)const=0;

                virtual void getImageFileWritersBySuffix(ossimImageWriterFactoryBase::ImageFileWriterList& result,
                                const ossimString& ext)const;

                virtual void getImageFileWritersByMimeType(ossimImageWriterFactoryBase::ImageFileWriterList& result,
                                const ossimString& mimeType)const;

                /* Ignored due to unclean parsing of MACROS     */
                /* TYPE_DATA                                    */
};
