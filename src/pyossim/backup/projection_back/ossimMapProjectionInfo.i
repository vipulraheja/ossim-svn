/*-----------------------------------------------------------------------------
 * Filename        : ossimMapProjectionInfo.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimMapProjectionInfo
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimDrect.h>
#include <ossim/base/ossimString.h>
#include <ossim/projection/ossimMapProjectionInfo.h>

%}

/* Handling assignment operator */
%rename(__set__) ossimMapProjectionInfo::operator=;

/* Handling the reserved function print */
%rename(ossimMapProjectionInfo_print) ossimMapProjectionInfo::print;

/* This tells SWIG to treat char ** as a special case */
%typemap(in) char ** 
{
        /* Check if input is a list */
        if (PyList_Check($input)) 
        {
                int size = PyList_Size($input);
                int i = 0;

                /* Allocate memory */
                $1 = (char *) malloc((size+1)*sizeof(char));

                for (i = 0; i < size; i++) 
                {
                        PyObject *o = PyList_GetItem($input,i);

                        if (PyString_Check(o))
                        {
                                $1[i] = PyString_AsString(PyList_GetItem($input,i));
                        }

                        else 
                        {
                                PyErr_SetString(PyExc_TypeError,"List must contain strings");
                                free($1);
                                return NULL;
                        }
                }
                $1[i] = 0;
        } 

        else 
        {
                PyErr_SetString(PyExc_TypeError,"not a list");
                return NULL;
        }
}

/* To return char** from a C function as Python List */
%typemap(out) char*
{
        int i;
        int len = 0;

        while ($1[len])
        {
                len++;
        }

        $result = PyList_New(len);

        for (i = 0; i < len; i++) 
        {
                PyList_SetItem($result, i, PyString_FromString($1[i]));
        }
}

/* Wrapping the class ossimMapProjectionInfo */
class ossimMapProjectionInfo : public ossimObject
{
        public:

                ossimMapProjectionInfo(const ossimMapProjection* proj,
                                const ossimDrect& output_rect);

                virtual ~ossimMapProjectionInfo();

                bool errorStatus() const;

                void getGeom(ossimKeywordlist& kwl, const char* prefix=0)const;

                ossimDpt getMetersPerPixel() const;
                ossimDpt getUsSurveyFeetPerPixel() const;
                ossimDpt getDecimalDegreesPerPixel() const;

                ossimDpt ulEastingNorthingPt() const;
                ossimDpt urEastingNorthingPt() const;
                ossimDpt lrEastingNorthingPt() const;
                ossimDpt llEastingNorthingPt() const;
                
                ossimDpt ulEastingNorthingPtInFt() const;
                ossimDpt urEastingNorthingPtInFt() const;
                ossimDpt lrEastingNorthingPtInFt() const;
                ossimDpt llEastingNorthingPtInFt() const;

                ossimGpt ulGroundPt() const;
                ossimGpt urGroundPt() const;
                ossimGpt lrGroundPt() const;
                ossimGpt llGroundPt() const;

                ossimGpt centerGroundPt() const;
                ossimDpt centerEastingNorthingPt() const;

                ossim_int32 linesPerImage() const;
                ossim_int32 pixelsPerLine() const;

                std::ostream& print(std::ostream& os) const;

                void setPixelType (ossimPixelType type);
                ossimPixelType  getPixelType () const;

                void setOutputFeetFlag (bool flag);

                bool unitsInFeet() const;

                ossimString getImageInfoString () const;
                void setImageInfoString (const ossimString& string);

                const ossimMapProjection* getProjection() const;

                static const char* README_IMAGE_STRING_KW;
                static const char* PIXEL_TYPE_KW;
                static const char* OUTPUT_US_FT_INFO_KW;

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix = 0);
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix = 0) const;

        private:

                /* Do not permit construction with void args. */
                ossimMapProjectionInfo();
                ossimMapProjectionInfo& operator=(const ossimMapProjectionInfo&);

                void initializeMembers (const ossimDrect& output_rect);

                const ossimMapProjection* theProjection;
                mutable bool              theErrorStatus;
                int                       theLinesPerImage;
                int                       thePixelsPerLine;
                ossimGpt                  theCornerGroundPt[4];
                ossimDpt                  theCornerEastingNorthingPt[4];
                ossimGpt                  theCenterGroundPt;
                ossimDpt                  theCenterEastingNorthingPt;
                ossimDrect                theBoundingRect;

                ossimPixelType                 thePixelType;

                bool                      theOutputInfoInFeetFlag;

                ossimString               theImageInfoString;
};
