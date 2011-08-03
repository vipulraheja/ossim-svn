/*-----------------------------------------------------------------------------
 * Filename        : ossimImageWriter.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageWriter 
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimOutputSource.h>
#include <ossim/base/ossimCommon.h>
#include <ossim/base/ossimIrect.h>

#include <ossim/imaging/ossimImageSourceSequencer.h>
#include <ossim/imaging/ossimImageWriter.h>
#include <ossim/base/ossimOutputSource.h>

%}

%import "ossim/base/ossimConstants.h"

/* Wrapping class ossimImageWriter */
class ossimImageWriter : public ossimOutputSource
{
        public:
                ossimImageWriter(ossimObject* owner=NULL);

                ossimImageWriter(ossimObject* owner,
                                ossim_uint32 numberOfInputs,
                                ossim_uint32 numberOfOutputs,
                                bool inputListIsFixed,
                                bool outputListIsFixed);

                virtual ~ossimImageWriter();

                virtual bool setViewingRect(const ossimIrect &aRect);

                virtual ossimIrect getAreaOfInterest() const;

                virtual void setAreaOfInterest(const ossimIrect& inputAreaOfInterest);

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

        protected:

                ossimIrect theAreaOfInterest;

                /* Ignored due to unclean parsing of MACROS     */                
                /* TYPE_DATA                                    */
};
