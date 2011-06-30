/*-----------------------------------------------------------------------------
 * Filename        : ossimImageGeometryFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageGeometryFactory 
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageGeometryFactoryBase.h>
#include <ossim/imaging/ossimImageGeometryFactory.h>

%}

%import "ossim/base/ossim2dTo2dTransform";
%import "ossim/imaging/ossimNitfTileSource.h";
%import "ossim/projection/ossimProjection.h";

class ossimImageGeometryFactory : public ossimImageGeometryFactoryBase
{
        public:
                static ossimImageGeometryFactory* instance();
                virtual ossimImageGeometry* createGeometry(const ossimString& typeName)const;
                virtual ossimImageGeometry* createGeometry(const ossimKeywordlist& kwl,
                                const char* prefix=0)const;
                virtual ossimImageGeometry* createGeometry(const ossimFilename& filename,
                                ossim_uint32 entryIdx)const;
                virtual bool extendGeometry(ossimImageHandler* handler)const;

                virtual void getTypeNameList(std::vector<ossimString>& typeList)const;

                virtual ossim2dTo2dTransform* createTransform(ossimImageHandler* handler)const;

                virtual ossimProjection* createProjection(ossimImageHandler* handler) const;

        protected:
                ossimImageGeometryFactory();

                virtual ossim2dTo2dTransform* createTransformFromNitf(ossimNitfTileSource* handler)const;

                static ossimImageGeometryFactory* m_instance;
};
