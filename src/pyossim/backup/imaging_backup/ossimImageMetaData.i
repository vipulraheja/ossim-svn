/*-----------------------------------------------------------------------------
Filename        : ossimImageMetaData.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageMetaData 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimCommon.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/imaging/ossimImageMetaData.h>

#include <vector>
#include <string>
#include <iosfwd>

%}

/* Handling ossimImageMetaData Assignment operator */
%rename(__set__) ossimImageMetaData::operator=;

/* Include the header file containing the declarations to be wrapped */
%include "ossim/base/ossimConstants.h"
%include "ossim/imaging/ossimImageMetaData.h"

/* Wrapping class ossimImageMetaData*/ 
class ossimImageMetaData
{
        public:
                ossimImageMetaData();
                ossimImageMetaData(ossimScalarType aType,
                                ossim_uint32 numberOfBands);
                ossimImageMetaData(const ossimImageMetaData& rhs);

                virtual ~ossimImageMetaData();

                void clear();

                void clearBandInfo();
                void setDefaultsForArrays();

                void setNumberOfBands(ossim_uint32 numberOfBands);

                ossim_uint32 getNumberOfBands()const;

                void setScalarType(ossimScalarType aType);

                ossimScalarType getScalarType()const;

                double getMinPix(ossim_uint32 band)const;
                
                void setMinPix(ossim_uint32 band, double pix);
                void setMaxPix(ossim_uint32 band, double pix);
                void setNullPix(ossim_uint32 band, double pix);
    
                double getMaxPix(ossim_uint32 band)const;
                double getNullPix(ossim_uint32 band)const;

                
                const double* getMinPixelArray()const;
                const double* getMaxPixelArray()const;
                const double* getNullPixelArray()const;
              
                void setMinValuesValid(bool flag);
                void setMaxValuesValid(bool flag);
                void setNullValuesValid(bool flag);
                bool getMinValuesValidFlag()const;
                bool getMaxValuesValidFlag()const;
                bool getNullValuesValidFlag()const;

                /* renamed to __set__ in Python */
                const ossimImageMetaData& operator=(const ossimImageMetaData& rhs);

                bool isValid()const;

                void assign(const ossimImageMetaData& rhs);

                bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);
                bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;

        protected:
                double* theNullPixelArray;
                double* theMinPixelArray;
                double* theMaxPixelArray;

                bool theMinValuesValidFlag;
                bool theMaxValuesValidFlag;
                bool theNullValuesValidFlag;

                ossimScalarType theScalarType;
                ossim_uint32    theNumberOfBands;

                void loadBandInfo(const ossimKeywordlist& kwl, const char* prefix = 0);
};
