//-----------------------------------------------------------------------------
// File:  Init.h
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Class declaration for Init.  Handles ossim initialization.
//
//-----------------------------------------------------------------------------
// $Id: Init.h 19748 2011-06-12 15:34:56Z dburken $

#ifndef pyossimtestInit_HEADER
#define pyossimtestInit_HEADER 1


#include <pyossimtest/Constants.h>

namespace pyossimtest
{
   class Init
   {
   public:

      /** @brief destructor */
      ~Init();

      /**
       * @brief Instance method.
       *
       * @return The instance of this class.
       */
      static pyossimtest::Init* instance();

      /** @brief Initialize method. */
      void initialize();
      
      /**
       * @brief Initialize method.
       *
       * @param argc Argument count.
       *
       * @param argv Array of args.
       */
      void initialize(int argc, char* argv[]);

   private:
      
      /** @brief default constructor - hidden from use */
      Init();

      /** @brief copy constructor - hidden from use */
      Init(const pyossimtest::Init& obj);

      /** @brief assignment operator - hidden from use */ 
      const pyossimtest::Init& operator=(const pyossimtest::Init& obj);

      /** @brief The single static instance of this class. */
      static pyossimtest::Init* m_instance;

      /** Flag to ignore duplicate initialization calls. */
      bool m_initCalledFlag;
   };

} // End of namespace pyossimtest.

#endif /* #ifndef pyossimtestInit_HEADER */
