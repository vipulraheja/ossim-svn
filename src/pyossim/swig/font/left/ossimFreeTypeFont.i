/*-----------------------------------------------------------------------------
 * Filename        : ossimFreeTypeFont.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimFreeTypeFont
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/ossimConfig.h> /* To pick up OSSIM_HAS_FREETYPE. */

#include <ossim/font/ossimFont.h>
#include <ossim/font/ossimFreeTypeFont.h>

#include <ossim/base/ossimFilename.h>

%}

typedef struct  TGlyph_
{
        FT_UInt    glyph_index;         /* glyph index in face      */
        FT_Vector  pos;                 /* position of glyph origin */
        FT_Glyph   image;               /* glyph image              */

} TGlyph, *PGlyph;

class ossimFreeTypeFont: public ossimFont
{
        public:
                ossimFreeTypeFont(const ossimFilename& fontFile);
                ossimFreeTypeFont(const ossimFreeTypeFont& rhs);

                virtual ossimObject* dup()const
                {
                        return new ossimFreeTypeFont(*this);
                }

                virtual const ossim_uint8* getBuf()const
                {
                        return theOutputBuffer;
                }

                void layoutGlyphs(vector<TGlyph>& glyphs,
                                const ossimString& s );

                virtual const ossim_uint8* rasterize();
                void getBoundingBox(ossimIrect& box);

                long getNumberOfFaces()const
                {
                        if(theFontFace)
                        {
                                return theFontFace->num_faces;
                        }
                        return 0;
                }
                void setCurrentFace(long index);

                /*!
                 * Fonts found in files .FNT and .PCF are fixed
                 */
                bool isFixed()const
                {
                        if(theFontFace)
                        {
                                return (theFontFace->num_fixed_sizes > 0);
                        }
                        return false;
                }

                virtual void getFixedSizes(vector<ossimIpt>& sizeArray)const;

                /*!
                 * Will enable kerning support.  This is enabled
                 * by default.  This is for true type fonts and
                 * if its available for the current font this
                 * will tell us to make sure we use it.  This
                 * adjusts spacing between pairs of glyphs.
                 */
                virtual void enableKerningSupport()
                {
                        theKerningEnabledFlag = true;
                        theBoundingRectIsValid = false;
                }

                /*!
                 * Will disable kerning support.  
                 */   
                virtual void disableKerningSupport()
                {
                        theKerningEnabledFlag = false;
                        theBoundingRectIsValid = false;
                }

                virtual void setHorizontalVerticalShear(double horizontalShear,
                                double verticalShear)
                {
                        ossimFont::setHorizontalVerticalShear(horizontalShear,
                                        verticalShear);
                        theBoundingRectIsValid = false;
                }
                virtual void setScale(double horizontal,
                                double vertical)
                {
                        ossimFont::setScale(horizontal,
                                        vertical);
                        theBoundingRectIsValid = false;
                }

                virtual void setPixelSize(int horizontalPixelSize,
                                int verticalPixelSize)
                {
                        ossimFont::setPixelSize(horizontalPixelSize,
                                        verticalPixelSize);
                        theBoundingRectIsValid = false;
                }
                virtual void setPixelSize(int pixelSize)
                {
                        ossimFont::setPixelSize(pixelSize);
                        theBoundingRectIsValid = false;         
                }

                virtual void setDeviceDpi(int horizontalDeviceUnits,
                                int verticalDeviceUnits)
                {
                        ossimFont::setDeviceDpi(horizontalDeviceUnits,
                                        verticalDeviceUnits);
                        theBoundingRectIsValid = false;
                }
                virtual void setString(const ossimString& s)
                {
                        ossimFont::setString(s);
                        theBoundingRectIsValid = false;
                        theNeedToLayoutGlyphsFlag = true;
                }

                const FT_Face getFontFace()const
                {
                        return theFontFace;
                }
        protected:
                virtual ~ossimFreeTypeFont();

                FT_Face       theFontFace;
                FT_Library    theLibrary;
                FT_Matrix     theMatrix;

                ossimFilename theFontFile;

                ossim_uint8*  theOutputBuffer;
                long          theBufferSize;
                bool          theKerningEnabledFlag;
                bool          theNeedToLayoutGlyphsFlag;
                FT_Vector     theStringCenter;
                ossimIpt      theShift;
                /*!
                 * Pre-compute all glyphs but don't render it
                 */
                vector<TGlyph> theStringLayout;

                /*!
                 * We will precompute the bounding rect only when we have to.
                 * this will avoid re-computing on all rasterization calls.  We
                 * will use the dirty flag to tell us if we need to re-compute.
                 */
                mutable ossimIrect    thePrecomputedBoundingRect;


                /*!
                 * Used to tell us when we need to recompute.
                 */
                mutable bool          theBoundingRectIsValid;
                void layoutGlyphs(const ossimString& s);

                void setBaseClassInformation();
                void setupForRasterization();
                void allocateBuffer();

                void drawBitmap(FT_Bitmap* bitmap,
                                const ossimIrect& bufRect,
                                const ossimIrect& glyphBox);

                void computeGlyphBox(FT_Glyph,
                                ossimIrect& box)const;
                void deleteGlyphs(vector<TGlyph>& glyphs);

                /* Ignoring Macro
                TYPE_DATA */
};
