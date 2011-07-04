%module pyossim

%{

#include <ossim/base/ossimString.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimObjectFactory.h>

#include <ossim/projection/ossimProjection.h>
#include <ossim/projection/ossimProjectionFactoryBase.h>
#include <ossim/imaging/ossimImageHandler.h>

%}

class ossimProjectionFactoryBase : public ossimObjectFactory
{
public:
   
   /**
    * takes a filename. This filename can be an image file or
    * it can also be a ossim .geom file.  It could be other
    * forms of geom files as well.  The factories job will be to
    * determine what parser to use and return a projection if
    * successful.
    */
   virtual ossimProjection* createProjection(const ossimFilename& filename,
                                             ossim_uint32 entryIdx)const=0;
   virtual ossimProjection* createProjection(const ossimString& name)const=0;
   virtual ossimProjection* createProjection(const ossimKeywordlist& kwl,
                                             const char* prefix)const=0;
   virtual ossimProjection* createProjection(ossimImageHandler* handler)const;

protected:

   ossimProjection*
   createProjectionFromGeometryFile(const ossimFilename& imageFile,
                                    ossim_uint32 entryIdx)const;
   
TYPE_DATA
};
