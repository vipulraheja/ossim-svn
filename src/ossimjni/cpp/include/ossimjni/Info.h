//-----------------------------------------------------------------------------
// File:  Info.h
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Class declaration for Info.
//
//-----------------------------------------------------------------------------
// $Id: Info.h 19750 2011-06-13 15:04:07Z dburken $

#ifndef ossimjniInfo_HEADER
#define ossimjniInfo_HEADER 1

#include <ossimjni/Constants.h>
#include <map>
#include <string>

class ossimInfo;

namespace ossimjni
{
   class OSSIMJNIDLL Info
   {
   public:

      /** @brief default constructor. */
      Info();
      
      /** @brief destructor */
      ~Info();

      /**
       * @brief Initial method.
       *
       * Typically called from application prior to execute.  This parses
       * all options and put in keyword list m_kwl.
       * 
       * @param ap Arg parser to initialize from.
       * @return true, indicating process should continue with execute.
       * @note A throw with an error message of "usage" is used to get out when
       * a usage is printed.
       */
      bool initialize(int argc, char* argv[]);

      /**
       * @brief execute method.
       *
       * Performs the actual dump of information.  This executes any options
       * set including image operations, i.e. -i -p --dno and so on.
       * 
       * @note Throws ossimException on error.
       */
      void execute();

      /**
       * @brief getImageInfo Method to open image "file" and get image info
       * in the form of a std::map<std::string, std::string>.
       *
       * Flags turn on various pieces of info.  These equate to options in
       * ossim-info for image information.
       *
       * @param file Image file to get information for.
       * @param dumpFlag      ossim-info -d
       * @param dnoFlag       ossim-info --dno
       * @param imageGeomFlag ossim-info -p
       * @param imageInfoFlag ossim-info -i 
       * @param metaDataFlag  ossim-info -m 
       * @param paletteFlag   ossim-info --palette
       *
       * @note Throws ossimException on error.
       */
      std::map<std::string, std::string> getImageInfo(
         const std::string& file,
         bool dumpFlag,
         bool dnoFlag,
         bool imageGeomFlag,
         bool imageInfoFlag,
         bool metaDataFlag,
         bool paletteFlag) const;

   private:

      ossimInfo* m_info;
   };

} // End of namespace ossimjni.

#endif /* #ifndef ossimjniInfo_HEADER */
