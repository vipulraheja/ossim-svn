//----------------------------------------------------------------------------
// File: Constants.h
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description:  Constants for pyossimtest c++ library.
//
//----------------------------------------------------------------------------
// $Id: Constants.h 19748 2011-06-12 15:34:56Z dburken $

#ifndef pyossimtestConstants_HEADER
#define pyossimtestConstants_HEADER 1

/**
 * DLL IMPORT/EXORT SECTION
 */
#if defined(__MINGW32__) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__VISUALC__) || defined(__BORLANDC__) || defined(__WATCOMC__)
#  define PYOSSIMTESTEXPORT __declspec(dllexport)
#  define PYOSSIMTESTIMPORT __declspec(dllimport)
#  ifdef PYOSSIMTEST_LIBRARY
#    define PYOSSIMTESTDLL       PYOSSIMTESTEXPORT
#  else
#    define PYOSSIMTESTDLL      PYOSSIMTESTIMPORT
#  endif
#else /* not #if defined(_MSC_VER) */
#  define PYOSSIMTESTEXPORT
#  define PYOSSIMTESTIMPORT
#  define PYOSSIMTESTDLL
#endif /* #if defined(_MSC_VER) */

// Primative data type typedefs
typedef char               pyossimtest_int8;
typedef signed char        pyossimtest_sint8;
typedef unsigned char      pyossimtest_uint8;

typedef short              pyossimtest_int16;
typedef unsigned short     pyossimtest_uint16;
typedef signed short       pyossimtest_sint16;

typedef int                pyossimtest_int32;
typedef unsigned int       pyossimtest_uint32;
typedef signed int         pyossimtest_sint32;

typedef long long          pyossimtest_int64;
typedef unsigned long long pyossimtest_uint64;
typedef signed long long   pyossimtest_sint64;

typedef float              pyossimtest_float32;
typedef double             pyossimtest_float64;

#endif /* #ifndef pyossimtestConstants_HEADER */
