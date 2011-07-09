/*-----------------------------------------------------------------------------
Filename        : ossimMetadataFileWriter.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimMetadataFileWriter
-----------------------------------------------------------------------------*/

%module pyossim

%{
        
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimProcessInterface.h>
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimObjectEvents.h>
#include <ossim/base/ossimProcessProgressEvent.h>

#include <ossim/imaging/ossimMetadataFileWriter.h>

%}

/* Include the required header files */
%import "ossim/base/ossimConstants.h"

/* Wrapping class ossimMetadataFileWriter */
class ossimMetadataFileWriter :
        public ossimConnectableObject,
        public ossimProcessInterface,
        public ossimConnectableObjectListener
{
        public:
                ossimMetadataFileWriter();


                virtual ossimObject*       getObject();
                virtual const ossimObject* getObject() const;

                virtual void initialize();

                virtual bool execute();

                virtual void setPercentComplete(double percentComplete);

                virtual void setFilename(const ossimFilename& file);

                const ossimFilename& getFilename()const;

                virtual bool loadState(const ossimKeywordlist& kwl, const char* prefix = 0);

                bool canConnectMyInputTo(ossim_int32 inputIndex,
                                const ossimConnectableObject* object) const;

                virtual void disconnectInputEvent(ossimConnectionEvent& event);
                virtual void connectInputEvent(ossimConnectionEvent& event);
                virtual void propertyEvent(ossimPropertyEvent& event);

                virtual void setPixelType(ossimPixelType pixelType);
                virtual ossimPixelType getPixelType() const;

                virtual void setAreaOfInterest(const ossimIrect& areaOfInterest);

                virtual ossimIrect getAreaOfInterest() const;

                virtual void getMetadatatypeList(
                                std::vector<ossimString>& metadatatypeList)const=0;

                virtual bool hasMetadataType(const ossimString& metadataType)const=0;

                virtual void setProperty(ossimRefPtr<ossimProperty> property);
                virtual ossimRefPtr<ossimProperty> getProperty(const ossimString& name)const;
                virtual void getPropertyNames(std::vector<ossimString>& propertyNames)const;
 
        protected:
                virtual ~ossimMetadataFileWriter();
                virtual bool writeFile() = 0;

                ossimImageSource* theInputConnection;
                ossimFilename              theFilename;
                ossimPixelType             thePixelType;
                ossimIrect                 theAreaOfInterest;

                /* Ignored due to unclean parsing of MACROS     */
                /* TYPE_DATA                                    */
};
