//----------------------------------------------------------------------------
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Singleton class for queries about things like writer strings
// that should stay the same throughout the session.
//
// $Id: Info.h 11216 2007-06-14 21:20:55Z dburken $
//----------------------------------------------------------------------------
#ifndef omsInfo_HEADER
#define omsInfo_HEADER 1

#include <vector>
#include <string>
#include <oms/Constants.h>

namespace oms
{
   class OMSDLL Info
   {
   public:

      /** @brief destructor */
      ~Info();

      /**
       * @brief Instance method.
       *
       * @return The instance of this class.
       */
      static oms::Info* instance();

      /**
       * @brief Get the list of available writers.
       *
       * @param list The list to initialize with writers.
       */
      void getWriterList(std::vector<std::string>& list) const;

   private:

      /** @brief Initializes theWriterList. */
      void initializeWriterList();

      /** @brief default constructor - hidden from use */
      Info();

      /** @brief copy constructor - hidden from use */
      Info(const oms::Info& obj);

      /** @brief assignment operator - hidden from use */ 
      const oms::Info& operator=(const oms::Info& obj);

      /** @brief The single static instance of this class. */
      static Info* theInstance;

      /** @brief The list of writers. */
      std::vector<std::string> theWriterList;
   };

} // End of namespace oms

#endif /* #ifndef omsInfo_HEADER */
