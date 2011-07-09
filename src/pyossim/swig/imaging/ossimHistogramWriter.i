/*-----------------------------------------------------------------------------
Filename        : ossimHistogramWriter.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimHistogramWriter
-----------------------------------------------------------------------------*/

%module pyossim

%{
        
#include <ossim/base/ossimOutputSource.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimProcessInterface.h>
#include <ossim/base/ossimObjectEvents.h>
#include <ossim/base/ossimProcessProgressEvent.h>
#include <ossim/base/ossimProcessListener.h>
#include <ossim/base/ossimConnectableObjectListener.h>
#include <ossim/base/ossimConnectionEvent.h>
#include <ossim/base/ossimHistogramSource.h>
#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimHistogramWriter.h>
#include <ossim/imaging/ossimImageHistogramSource.h>

#include <fstream>

%}
        
/* Include the required header files */
%import "ossim/base/ossimConstants.h";

/* Wrapping the class ossimHistogramWriter */
class ossimHistogramWriter : public ossimOutputSource,
        public ossimProcessInterface,
        public ossimConnectableObjectListener
{
        public:
                friend class ossimHistogramWriterProcessListener;

                ossimHistogramWriter(ossimImageSource* inputSource=0,
                                ossimObject* owner=0);

                void setAreaOfInterest(const ossimIrect& rect);

                virtual ossimObject* getObject();

                virtual const ossimObject* getObject()const;

                virtual bool execute();

                virtual bool isOpen()const;

                virtual bool open();

                virtual bool open(const ossimFilename& filename);

                virtual void close();

                virtual void setOutputName(const ossimString& outputName);

                virtual void setFilename(const ossimFilename& filename);

                bool canConnectMyInputTo(ossim_int32 inputIndex,
                                const ossimConnectableObject* object)const;

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

                virtual void processProgressEvent(ossimProcessProgressEvent& event);

                virtual void connectInputEvent(ossimConnectionEvent& event);

                virtual void disconnectInputEvent(ossimConnectionEvent& event);

                virtual void abort();


        protected:
                virtual ~ossimHistogramWriter();
                virtual void writeHistogram();
                ossimIrect                           theAreaOfInterest;
                ossimFilename                        theFilename;
                std::ofstream*                       theFileStream;
                ossimHistogramWriterProcessListener* theProcessListener;

                /** stored for abort call only. */
                ossimHistogramSource*                theHistogramSource;
                
                /* Ignored due to unclean parsing of MACROS     */
                /* TYPE_DATA                                    */
};
