/*-----------------------------------------------------------------------------
 * Filename        : ossimImageViewTransformFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageViewTransformFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimObject.h>
#include <ossim/projection/ossimImageViewTransformFactory.h>

%}

%import "ossim/projection/ossimImageViewTransform.h";
%import "ossim/base/ossimKeywordlist.h";

class ossimImageViewTransformFactory : public ossimObject
{
        public:
                static ossimImageViewTransformFactory* instance();
                virtual ossimImageViewTransform* createTransform(const ossimKeywordlist& kwl,
                                const char* prefix = 0);

        protected:
                ossimImageViewTransformFactory(){}      //hide
                ossimImageViewTransformFactory(const ossimImageViewTransformFactory&){}
                void operator =(const ossimImageViewTransformFactory&){}

                static ossimImageViewTransformFactory* theInstance;

                TYPE_DATA
};
