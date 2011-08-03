/*-----------------------------------------------------------------------------
Filename        : ossimJpegWriter.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimJpegWriter 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageFileWriter.h>
#include <ossim/imaging/ossimJpegWriter.h>
#include <ossim/base/ossimKeywordlist.h>

%}

/* Wrapping the class ossimJpegWriter */
class ossimJpegWriter : public ossimImageFileWriter
{
        public:
                /** default constructor */
                ossimJpegWriter();

                virtual void getImageTypeList(std::vector<ossimString>& imageTypeList)const;

                virtual void  setQuality(ossim_int32 quality);

                virtual bool isOpen()const;   

                virtual bool open();
                virtual void close();

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

                virtual void setProperty(ossimRefPtr<ossimProperty> property);
                virtual ossimRefPtr<ossimProperty> getProperty(const ossimString& name)const;

                virtual void getPropertyNames(std::vector<ossimString>& propertyNames)const;

                virtual ossimString getExtension() const;

                bool hasImageType(const ossimString& imageType) const;

        protected:
                /** virtual destructor */
                virtual ~ossimJpegWriter();


        private:
                virtual bool writeFile();

                ossim_int32 theQuality;
                FILE*       theOutputFilePtr;

                /* Ignored due to unclean parsing of MACROS */
                /* TYPE_DATA    */
};
