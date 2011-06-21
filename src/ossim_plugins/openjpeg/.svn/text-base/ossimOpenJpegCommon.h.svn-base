//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description:  Place for common code used by both encoders and decoders
// using the openjpeg library.
//
// This code is namespaced with "ossim".
//
//----------------------------------------------------------------------------
// $Id$

#ifndef ossimOpenJpegCommon_HEADER
#define ossimOpenJpegCommon_HEADER

#include <iosfwd>

// Forward declarations:
struct opj_codestream_info;
struct opj_dparameters;
struct opj_image;
struct opj_image_comp;

namespace ossim
{
   /**
    * Prints codestream info from openjpeg struct opj_codestream_info.
    * 
    * @return std::ostream&
    */
   std::ostream& print(std::ostream& out, const opj_codestream_info& info);
   
   /**
    * Prints decode parameters from openjpeg struct opj_dparameters.
    * 
    * @return std::ostream&
    */
   std::ostream& print(std::ostream& out, const opj_dparameters& param);

   /**
    * Prints opj_image structure.
    * 
    * @return std::ostream&
    */
   std::ostream& print(std::ostream& out, const opj_image& image);

   /**
    * Prints opj_image_comp structure.
    * 
    * @return std::ostream&
    */
   std::ostream& print(std::ostream& out, const opj_image_comp& comp);

} // End of namespace ossim

#endif /* ossimOpenJpegCommon_HEADER */
