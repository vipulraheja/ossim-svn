/*-----------------------------------------------------------------------------
 * Filename        : ossimFontFactoryRegistry.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimFontFactoryRegistry
 * -----------------------------------------------------------------------------*/

%module pyossim

%import "ossim/font/ossimGdSansBold.inc"

%{

#include <vector>
#include <ossim/base/ossimFontInformation.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/font/ossimFontFactoryBase.h>
#include <ossim/font/ossimFontFactoryRegistry.h>
#include <ossim/font/ossimFont.h>
#include <ossim/base/ossimRefPtr.h>

%}



/* Handling operators */
%rename(__set__) ossimFontFactoryRegistry::operator=;


/* Wrapping class ossimFontFactoryRegistry */
class ossimFontFactoryRegistry
{
        public:
                static ossimFontFactoryRegistry* instance();

                bool registerFactory(ossimFontFactoryBase* factory);
                void unregisterFactory(ossimFontFactoryBase* factory);
                bool findFactory(ossimFontFactoryBase* factory)const;

                ossimFont* createFont(const ossimFontInformation& information)const;
                ossimFont* createFont(const ossimFilename& file)const;

                /*!
                 * Returns all font information.
                 */
                void getFontInformation(std::vector<ossimFontInformation>& informationList)const;

                /*!
                 * Matches the entire string.  Does a case insensitive match.
                 */ 
                void getFontInformationFamilyName(std::vector<ossimFontInformation>& informationList,
                                const ossimString& familyName)const;

                /*!
                 * Matches the sub-string.  Does a case insensitive match.
                 */ 
                void getFontInformationContainingFamilyName(std::vector<ossimFontInformation>& informationList,
                                const ossimString& familyName)const;

                /*!
                 * This font should not be deleted.  It returns the default font.  If you
                 * want to make a copy then just call the dup method on
                 * font.
                 */
                ossimFont* getDefaultFont()const;

        protected:
                mutable ossimRefPtr<ossimFont> theDefaultFont;

                //static ossimFontFactoryRegistry* theInstance;

                std::vector<ossimFontFactoryBase*> theFactoryList;

                ossimFontFactoryRegistry();

        private:
                ossimFontFactoryRegistry(const ossimFontFactoryRegistry& rhs);
                void operator =(const ossimFontFactoryRegistry& rhs);
};
