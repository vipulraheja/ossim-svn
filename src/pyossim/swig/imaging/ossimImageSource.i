/*-----------------------------------------------------------------------------
Filename        : ossimImageSource.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageSource 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimConstants.h>
#include <ossim/imaging/ossimImageData.h>
#include <ossim/imaging/ossimImageGeometry.h>
#include <ossim/imaging/ossimImageSource.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimRefPtr.h>

%}

/* Handling ossimImageSource Assignment operator */
%rename(__set__) ossimImageSource::operator=;

/* Include the header file containing the constants */
%import "ossim/base/ossimConstants.h"

/* Wrapping the ossimImageSource class */
class ossimImageSource : public ossimSource
{
        public:
                ossimImageSource(ossimObject* owner = 0);
                ossimImageSource(ossimObject* owner,
                                ossim_uint32 inputListSize,
                                ossim_uint32 outputListSize,
                                bool inputListIsFixedFlag=true,
                                bool outputListIsFixedFlag=true);
                
                
                virtual ~ossimImageSource();


                virtual ossimRefPtr<ossimImageData> getTile(const ossimIpt& origin,
                                ossim_uint32 resLevel=0);
                virtual ossimRefPtr<ossimImageData> getTile(const ossimIrect& rect,
                                ossim_uint32 resLevel=0);

                virtual bool getTile(ossimImageData* result, ossim_uint32 resLevel=0);

                virtual ossimObject* getObject() { return this; }
                virtual const ossimObject* getObject() const { return this; }

                
                virtual void getDecimationFactor(ossim_uint32 resLevel,
                                ossimDpt& result)const;
                virtual void getDecimationFactors(std::vector<ossimDpt>& decimations) const;

                virtual ossim_uint32 getNumberOfDecimationLevels() const;
                virtual ossim_uint32 getNumberOfInputBands() const = 0;
                virtual ossim_uint32 getNumberOfOutputBands() const;

                virtual void getOutputBandList(std::vector<ossim_uint32>& bandList) const;

                virtual ossimScalarType getOutputScalarType() const;

                virtual ossim_uint32 getTileWidth() const;
                virtual ossim_uint32 getTileHeight() const;

                virtual double getNullPixelValue(ossim_uint32 band=0)const;
                virtual double getMinPixelValue(ossim_uint32 band=0)const;
                virtual double getMaxPixelValue(ossim_uint32 band=0)const;

                virtual ossimIrect getBoundingRect(ossim_uint32 resLevel=0) const;

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

                virtual void getValidImageVertices(std::vector<ossimIpt>& validVertices,
                                ossimVertexOrdering ordering=OSSIM_CLOCKWISE_ORDER,
                                ossim_uint32 resLevel=0)const;

                virtual ossimRefPtr<ossimImageGeometry> getImageGeometry();

                virtual void setImageGeometry(const ossimImageGeometry* geom);

                virtual void saveImageGeometry() const;
                virtual void saveImageGeometry(const ossimFilename& geometry_file) const;

                virtual void initialize()=0;

                virtual ossimRefPtr<ossimProperty> getProperty(const ossimString& name)const;
        
                virtual void setProperty(ossimRefPtr<ossimProperty> property);
                virtual void getPropertyNames(std::vector<ossimString>& propertyNames)const;

                virtual bool isIndexedData() const;

  
        protected:
                ossimImageSource (const ossimImageSource& rhs);
                const ossimImageSource& operator= (const ossimImageSource&);

        
        private:
                /* Ignored due to unclean parsing of MACROS     */
                /* TYPE_DATA                                    */
};
