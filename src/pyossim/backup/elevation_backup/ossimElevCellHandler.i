/*-----------------------------------------------------------------------------
 * Filename        : ossimElevCellHandler.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimElevCellHandler
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimConstants.h>
#include <ossim/elevation/ossimElevSource.h>
#include <ossim/elevation/ossimElevCellHandler.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimIpt.h>

%}

/* Handling operators */
%rename(__set__) ossimElevCellHandler::operator=;

/* Wrapping class ossimElevCellHandler */
class ossimElevCellHandler : public ossimElevSource
{
        public:
                /**
                 * Constructors:
                 */

                ossimElevCellHandler (const char* elev_filename);
                ossimElevCellHandler (const ossimElevCellHandler& src);


                const ossimElevCellHandler& operator=(const ossimElevCellHandler& rhs);
                virtual ossimFilename getFilename() const;


                /**
                 *  METHOD:  getSizeOfElevCell 
                 *  Returns the number of post in the cell.
                 *  Note:  x = longitude, y = latitude
                 */
                virtual ossimIpt getSizeOfElevCell() const = 0;

                /**
                 *  METHOD:  getPostValue
                 *  Returns the value at a given grid point as a double.
                 */
                virtual double getPostValue(const ossimIpt& gridPt) const = 0;

                /**
                 * METHOD: meanSpacingMeters()
                 * Implements pure virtual for. This method is used for deterrming
                 * preferred DEM among multiple overlapping elev sources:
                 */
                virtual double getMeanSpacingMeters() const;

                /**
                 * METHOD: pointIsInsideRect()
                 * Method to check if the ground point elevation is defined:
                 */
                virtual bool pointHasCoverage(const ossimGpt&) const;

                /**
                 * METHODS: accuracyLE90(), accuracyCE90()
                 * Returns the vertical and horizontal accuracy (90% confidence):
                 */
                virtual double getAccuracyLE90(const ossimGpt&) const;
                virtual double getAccuracyCE90(const ossimGpt&) const;

                bool canConnectMyInputTo(ossim_int32 inputIndex,
                                const ossimConnectableObject* object)const;
                virtual void close(){}
                virtual bool open(const ossimFilename&, bool=false){return false;}


        protected:
                ossimElevCellHandler ();
                virtual ~ossimElevCellHandler();

                /**
                 * Virtual method for reading 
                 */
                ossimFilename        theFilename;
                double               theMeanSpacing;  // meters
                double               theAbsLE90;
                double               theAbsCE90;

                /* Ignoring Macro    
                   TYPE_DATA */
};
