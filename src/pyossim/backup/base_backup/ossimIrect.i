/*-----------------------------------------------------------------------------
Filename        : ossimIrect.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimIrect
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <iosfwd>
#include <vector>

#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimCommon.h>
#include <ossim/base/ossimIrect.h>

%}

/* Handling operators */
%rename(__set__) ossimIrect::operator=;
%rename(__ne__) ossimIrect::operator!=;
%rename(__mul__) operator*;
%rename(__cmp__) ossimIrect::operator==;
%rename(__add__) ossimIrect::operator+;
%rename(__sub__) ossimIrect::operator-;
%rename(__iadd__) ossimIrect::operator+=;
%rename(__isub__) ossimIrect::operator-=;
%rename(__imul__) ossimIrect::operator*=;
%rename(__lshift__) operator<<;

%rename(ossimIrect_print) print;

/* Wrapping class ossimIrect */
class ossimIrect
{
        public:
                enum
                {
                        UPPER_LEFT  = 1,
                        LOWER_LEFT  = 2,
                        LOWER_RIGHT = 4,
                        UPPER_RIGHT = 8
                };

                ossimIrect()
                        :
                                theUlCorner(0, 0),
                                theUrCorner(0, 0),
                                theLrCorner(0, 0),
                                theLlCorner(0, 0),
                                theOrientMode(OSSIM_LEFT_HANDED) {}

                ossimIrect(ossimIpt ul_corner,
                                ossimIpt lr_corner,
                                ossimCoordSysOrientMode mode=OSSIM_LEFT_HANDED)
                        :
                                theUlCorner(ul_corner),
                                theUrCorner(lr_corner.x, ul_corner.y),
                                theLrCorner(lr_corner),
                                theLlCorner(ul_corner.x, lr_corner.y),
                                theOrientMode(mode) {}

                ossimIrect(ossim_int32 ul_corner_x,
                                ossim_int32 ul_corner_y,
                                ossim_int32 lr_corner_x,
                                ossim_int32 lr_corner_y,
                                ossimCoordSysOrientMode mode=OSSIM_LEFT_HANDED)
                        :
                                theUlCorner(ul_corner_x, ul_corner_y),
                                theUrCorner(lr_corner_x, ul_corner_y),
                                theLrCorner(lr_corner_x, lr_corner_y),
                                theLlCorner(ul_corner_x, lr_corner_y),
                                theOrientMode(mode) {}

                ossimIrect(const ossimIrect& rect)
                        :
                                theUlCorner(rect.ul()),
                                theUrCorner(rect.ur()),
                                theLrCorner(rect.lr()),
                                theLlCorner(rect.ll()),
                                theOrientMode(rect.orientMode()) {}

                ossimIrect(const ossimDrect& rect);

                /*!
                 * Must compute a bounding rect given these image
                 * points.
                 */
                ossimIrect(const std::vector<ossimIpt>& points,
                                ossimCoordSysOrientMode mode=OSSIM_LEFT_HANDED);

                ossimIrect(const ossimIpt& p1,
                                const ossimIpt& p2,
                                const ossimIpt& p3,
                                const ossimIpt& p4,
                                ossimCoordSysOrientMode=OSSIM_LEFT_HANDED);

                //! Constructs an Irect surrounding the specified point, and of specified size.
                ossimIrect(const ossimIpt& center, 
                                ossim_uint32    size_x, 
                                ossim_uint32    size_y,
                                ossimCoordSysOrientMode mode=OSSIM_LEFT_HANDED);

                /** destructor */
                ~ossimIrect();

                const ossimIrect& operator=  (const ossimIrect& rect);
                const ossimIrect& operator=  (const ossimDrect& rect);
                bool         operator!= (const ossimIrect& rect) const;
                bool         operator== (const ossimIrect& rect) const;

                friend ossimIrect operator*(double scalar, const ossimIrect& rect)
                {
                        return ossimIrect((int)floor(rect.theUlCorner.x*scalar),
                                        (int)floor(rect.theUlCorner.y*scalar),
                                        (int)ceil(rect.theUlCorner.x*scalar+rect.width()*scalar-1),
                                        (int)ceil(rect.theUlCorner.y*scalar+rect.height()*scalar-1),
                                        rect.theOrientMode);
                }

                const ossimIrect& operator*=(ossim_int32 scalar)
                {
                        *this = ossimIrect((theUlCorner.x*scalar),
                                        (theUlCorner.y*scalar),
                                        (theUlCorner.x*scalar+width()*scalar-1),
                                        (theUlCorner.y*scalar+height()*scalar-1),
                                        theOrientMode);
                        return *this;
                }

                ossimIrect operator*(ossim_int32 scalar)const
                {
                        return ossimIrect((theUlCorner.x*scalar),
                                        (theUlCorner.y*scalar),
                                        (theUlCorner.x*scalar+width()*scalar-1),
                                        (theUlCorner.y*scalar+height()*scalar-1),
                                        theOrientMode);
                }

                const ossimIrect& operator *=(double scalar)
                {
                        *this = ossimIrect((int)floor(theUlCorner.x*scalar),
                                        (int)floor(theUlCorner.y*scalar),
                                        (int)ceil(theUlCorner.x*scalar+width()*scalar-1),
                                        (int)ceil(theUlCorner.y*scalar+height()*scalar-1),
                                        theOrientMode);
                        return *this;
                }

                ossimIrect operator *(double scalar)const
                {
                        return ossimIrect((int)floor(theUlCorner.x*scalar),
                                        (int)floor(theUlCorner.y*scalar),
                                        (int)ceil(theUlCorner.x*scalar+width()*scalar-1),
                                        (int)ceil(theUlCorner.y*scalar+height()*scalar-1),
                                        theOrientMode);
                }

                const ossimIrect& operator *=(const ossimDpt& scalar)
                {
                        *this = ossimIrect((int)floor(theUlCorner.x*scalar.x),
                                        (int)floor(theUlCorner.y*scalar.y),
                                        (int)ceil(theUlCorner.x*scalar.x+width()*scalar.x-1),
                                        (int)ceil(theUlCorner.y*scalar.y+height()*scalar.y-1),
                                        theOrientMode);
                        return *this;
                }

                ossimIrect operator *(const ossimDpt& scalar)const
                {
                        return  ossimIrect((int)floor(theUlCorner.x*scalar.x),
                                        (int)floor(theUlCorner.y*scalar.y),
                                        (int)ceil(theUlCorner.x*scalar.x+width()*scalar.x-1),
                                        (int)ceil(theUlCorner.y*scalar.y+height()*scalar.y-1),
                                        theOrientMode);
                }
                const ossimIrect& operator +=(const ossimIpt& shift)
                {
                        *this = ossimIrect(theUlCorner.x+shift.x,
                                        theUlCorner.y+shift.y,
                                        theLrCorner.x+shift.x,
                                        theLrCorner.y+shift.y,
                                        theOrientMode);
                        return *this;
                }

                const ossimIrect& operator -=(const ossimIpt& shift)
                {
                        *this = ossimIrect(theUlCorner.x-shift.x,
                                        theUlCorner.y-shift.y,
                                        theLrCorner.x-shift.x,
                                        theLrCorner.y-shift.y,
                                        theOrientMode);
                        return *this;
                }

                ossimIrect operator +(const ossimIpt& shift)const
                {
                        return ossimIrect(theUlCorner.x+shift.x,
                                        theUlCorner.y+shift.y,
                                        theLrCorner.x+shift.x,
                                        theLrCorner.y+shift.y,
                                        theOrientMode);
                }

                ossimIrect operator -(const ossimIpt& shift)const
                {
                        return ossimIrect(theUlCorner.x-shift.x,
                                        theUlCorner.y-shift.y,
                                        theLrCorner.x-shift.x,
                                        theLrCorner.y-shift.y,
                                        theOrientMode);
                }


                const ossimIrect& operator +=(const ossimDpt& shift)
                {
                        *this = ossimIrect((int)floor(theUlCorner.x+shift.x),
                                        (int)floor(theUlCorner.y+shift.y),
                                        (int)ceil(theUlCorner.x+shift.x+width()-1),
                                        (int)ceil(theUlCorner.y+shift.y+height()-1),
                                        theOrientMode);
                        return *this;
                }

                const ossimIrect& operator -=(const ossimDpt& shift)
                {
                        *this = ossimIrect((int)floor(theUlCorner.x-shift.x),
                                        (int)floor(theUlCorner.y-shift.y),
                                        (int)ceil(theUlCorner.x-shift.x+width()-1),
                                        (int)ceil(theUlCorner.y-shift.y+height()-1),
                                        theOrientMode);
                        return *this;
                }

                ossimIrect operator +(const ossimDpt& shift)const
                {
                        return ossimIrect((int)floor(theUlCorner.x+shift.x),
                                        (int)floor(theUlCorner.y+shift.y),
                                        (int)ceil(theUlCorner.x+shift.x+width()-1),
                                        (int)ceil(theUlCorner.y+shift.y+height()-1),
                                        theOrientMode);
                }

                ossimIrect operator -(const ossimDpt& shift)const
                {
                        return ossimIrect((int)floor(theUlCorner.x-shift.x),
                                        (int)floor(theUlCorner.y-shift.y),
                                        (int)ceil(theUlCorner.x-shift.x+width()-1),
                                        (int)ceil(theUlCorner.y-shift.y+height()-1),
                                        theOrientMode);
                        return *this;
                }


                const ossimIpt& ul() const { return theUlCorner; }
                const ossimIpt& ur() const { return theUrCorner; }
                const ossimIpt& lr() const { return theLrCorner; }
                const ossimIpt& ll() const { return theLlCorner; }

                const ossimIrect& changeOrientationMode(ossimCoordSysOrientMode mode)
                {
                        // if we are already in the orientation then return
                        //
                        if(mode == theOrientMode) return *this;
                        if(mode == OSSIM_LEFT_HANDED)
                        {
                                // we must be right handed so change to left handed
                                *this = ossimIrect(theUlCorner.x,
                                                theLlCorner.y,
                                                theLrCorner.x,
                                                theUlCorner.y,
                                                OSSIM_LEFT_HANDED);
                        }
                        else
                        {
                                // we must be left handed so change to RIGHT handed
                                *this = ossimIrect(theUlCorner.x,
                                                theLlCorner.y,
                                                theLrCorner.x,
                                                theUlCorner.y,
                                                OSSIM_RIGHT_HANDED);
                        }
                        theOrientMode = mode;

                        return *this;
                }
                void getBounds(ossim_int32& minx, ossim_int32& miny,
                                ossim_int32& maxx, ossim_int32& maxy)const
                {
                        minx = theUlCorner.x;
                        maxx = theLrCorner.x;
                        if(theOrientMode == OSSIM_LEFT_HANDED)
                        {
                                miny = theUlCorner.y;
                                maxy = theLrCorner.y;
                        }
                        else
                        {
                                maxy = theUlCorner.y;
                                miny = theLrCorner.y;
                        }
                }

                /*!
                 * Initializes center_point with center of the rectangle.
                 * Makes center_point nan if this rectangle has nans.
                 */
                void getCenter(ossimDpt& center_point) const;

                void makeNan()
                {
                        theUlCorner.makeNan();
                        theLlCorner.makeNan();
                        theLrCorner.makeNan();
                        theUrCorner.makeNan();
                }

                bool hasNans()const{ return (theUlCorner.hasNans() ||
                                theLlCorner.hasNans() ||
                                theLrCorner.hasNans() ||
                                theUrCorner.hasNans());}

                bool isNan()const{ return (theUlCorner.isNan() &&
                                theLlCorner.isNan() &&
                                theLrCorner.isNan() &&
                                theUrCorner.isNan());}

                /***
                // This class supports both left and right-handed coordinate systems. For
                // both, the positive x-axis extends to the "right".
                ***/
                ossimCoordSysOrientMode orientMode() const { return theOrientMode; }
                void setOrientMode(ossimCoordSysOrientMode mode) { theOrientMode = mode; }

                void stretchToTileBoundary(const ossimIpt& tileWidthHeight);

                               ossimString toString()const;

                bool toRect(const ossimString& rectString);


                const ossimIrect& expand(const ossimIpt& padding);

                //! Guarantees that this rect will be at least w X h big. If smaller than specified, the 
                //! corresponding side will be stretched equally in + and - direction to meet required size.
                //! Returns TRUE if resizing occurred.
                bool insureMinimumSize(const ossimIpt& width_height);

                ossim_uint32 area()const
                {
                        return width()*height();
                }

                void set_ul(const ossimIpt& pt);
                void set_ur(const ossimIpt& pt);
                void set_lr(const ossimIpt& pt);
                void set_ll(const ossimIpt& pt);
                void set_ulx(ossim_int32 x);
                void set_uly(ossim_int32 y);
                void set_urx(ossim_int32 x);
                void set_ury(ossim_int32 y);
                void set_lrx(ossim_int32 x);
                void set_lry(ossim_int32 y);
                void set_llx(ossim_int32 x);
                void set_lly(ossim_int32 y);
                
                bool pointWithin(const ossimIpt& pt) const;

                bool intersects(const ossimIrect& rect) const;

                bool completely_within(const ossimIrect& rect) const;

                ossimCoordSysOrientMode orientationMode()const{return theOrientMode;}
                
                ossim_uint32 height() const
                {
                        ossim_int32 h = theLlCorner.y - theUlCorner.y;
                        if (h < 0)
                        {
                                h = -h;
                        }
                        return static_cast<ossim_uint32>( h + 1 );
                }

                ossim_uint32 width()  const
                {
                        ossim_int32 w = theLrCorner.x - theLlCorner.x;
                        if (w < 0)
                        {
                                w = -w;
                        }
                        return static_cast<ossim_uint32>( w + 1 );
                }

                ossimIpt size() const { return ossimIpt(width(), height()); }

                ossimIrect clipToRect(const ossimIrect& rect)const;

                inline ossimIpt midPoint()const;

                void print(std::ostream& os) const;

                ossimIrect combine(const ossimIrect& rect)const;

                friend std::ostream& operator<<(std::ostream& os,
                                const ossimIrect& rect);

                bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;
                bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);
        private:

                /***
                // Private data members representing the rectangle corners.
                ***/
                ossimIpt theUlCorner;
                ossimIpt theUrCorner;
                ossimIpt theLrCorner;
                ossimIpt theLlCorner;

                ossimCoordSysOrientMode  theOrientMode;
};
