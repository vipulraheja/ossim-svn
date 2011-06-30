/*-----------------------------------------------------------------------------
 * Filename        : ossimImageMosaic.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageMosaic 
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageCombiner.h>
#include <ossim/imaging/ossimImageMosaic.h>

%}


/**
 * An image mosaic is a simple combiner that will
 * just do a simple mosaic.  It just checks NULL pix values until it finds a
 * pixel that is not empty and copies it out to the output.  The list will
 * have same size tiles and have the same number of bands.
 */
class ossimImageMosaic : public ossimImageCombiner
{
        public:
                ossimImageMosaic();
                ossimImageMosaic(ossimConnectableObject::ConnectableObjectList& inputSources);

                virtual ossimRefPtr<ossimImageData> getTile(const ossimIrect& origin,
                                ossim_uint32 resLevel=0);

                virtual void initialize();

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

        protected:
                virtual ~ossimImageMosaic();

                void allocate();

                ossimRefPtr<ossimImageData> theTile;

                template <class T> ossimRefPtr<ossimImageData> combine(
                                T, // dummy template variable not used
                                const ossimIrect& tileRect,
                                ossim_uint32 resLevel=0);
                template <class T> ossimRefPtr<ossimImageData> combineNorm(
                                T, // dummy template variable not used
                                const ossimIrect& tileRect,
                                ossim_uint32 resLevel=0);

                TYPE_DATA
};
