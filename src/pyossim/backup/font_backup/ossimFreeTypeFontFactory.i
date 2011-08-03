/*-----------------------------------------------------------------------------
 * Filename        : ossimFreeTypeFontFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimFreeTypeFontFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/font/ossimFontFactoryBase.h>
#include <ossim/font/ossimFreeTypeFontFactory.h>
%}

/* Handling operators */
%rename(__set__) ossimFreeTypeFontFactory::operator=;


/* Wrapping class ossimFreeTypeFontInformation */
class ossimFreeTypeFontInformation
{
        public:
                ossimFreeTypeFontInformation(const ossimFilename& file,
                                const ossimFontInformation& info)
                        :theFilename(file),
                        theFontInformation(info) {}

                ossimFilename        theFilename;
                ossimFontInformation theFontInformation;
};

/* Wrapping class ossimFreeTypeFontFactory */
class ossimFreeTypeFontFactory : public ossimFontFactoryBase
{
        public:
                virtual ~ossimFreeTypeFontFactory();
                static ossimFreeTypeFontFactory* instance();
                virtual ossimFont* createFont(const ossimFontInformation& information)const;
                virtual ossimFont* createFont(const ossimFilename& file)const;
                virtual void getFontInformation(std::vector<ossimFontInformation>& informationList)const;

                bool addFile(const ossimFilename& file);

        protected:
                ossimFreeTypeFontFactory();

                static ossimFreeTypeFontFactory* theInstance;
                std::vector<ossimFreeTypeFontInformation> theFontInformationList;

                void initializeDefaults();
        private:
                ossimFreeTypeFontFactory(const ossimFreeTypeFontFactory& /*rhs*/){}
                void operator =(const ossimFreeTypeFontFactory& /*rhs*/){}

};
