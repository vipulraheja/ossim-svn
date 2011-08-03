/*-----------------------------------------------------------------------------
 * Filename        : ossimImageGeometryFactoryBase.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageGeometryFactoryBase
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimBaseObjectFactory.h>
#include <ossim/imaging/ossimImageGeometry.h>
#include <ossim/imaging/ossimImageGeometryFactoryBase.h>
#include <ossim/imaging/ossimImageHandler.h>

%}

/* Include the required header files */
%import "ossim/base/ossimConstants.h"

/* Wrapping the class ossimImageGeometryFactoryBase */
class ossimImageGeometryFactoryBase : public ossimBaseObjectFactory
{
        public: 
                virtual ossimObject* createObject(const ossimString& typeName)const
                {
                        return createGeometry(typeName);
                }

                virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                const char* prefix=0)const
                {
                        return createGeometry(kwl, prefix);
                }

                virtual ossimImageGeometry* createGeometry(const ossimString& typeName)const=0;
                virtual ossimImageGeometry* createGeometry(const ossimKeywordlist& kwl,
                                const char* prefix=0)const=0;
                virtual ossimImageGeometry* createGeometry(const ossimFilename& filename,
                                ossim_uint32 entryIdx)const = 0;
                virtual bool extendGeometry(ossimImageHandler* handler)const=0;
};
