/*-----------------------------------------------------------------------------
 * Filename        : ossimNadconNasDatum.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimNadconNasDatum
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimNadconGridDatum.h>
#include <ossim/base/ossimNadconGridFile.h>
#include <ossim/base/ossimNadconNasDatum.h>

%}

class ossimNadconNasDatum : public ossimNadconGridDatum
{
        public:
                ossimNadconNasDatum(const ossimFilename& nadconDirectory);

                // Argument holds the source point and datum.  Returns another
                // point with this datum.
                //
                virtual ossimGpt shift(const ossimGpt    &aPt)const;

};
