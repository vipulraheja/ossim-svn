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

#include <iostream>
#include <iomanip>
#include <openjpeg.h>
#include <ossimOpenJpegCommon.h>
#include <ossim/base/ossimString.h>

std::ostream& ossim::print(std::ostream& out, const opj_codestream_info& info)
{
   // Capture stream flags since we are going to mess with them.
   std::ios_base::fmtflags f = out.flags();
   
   const int W = 20;
   
   out << std::setiosflags(std::ios_base::right) << std::setfill(' ')
       << "opj_codestream_info:\n\n"
       << std::setw(W) << "D_max: "
       << info.D_max << "\n"
       << std::setw(W) << "packno: "
       << info.packno << "\n"
       << std::setw(W) << "index_write: "
       <<info.index_write << "\n"
       << std::setw(W) << "image_w: "
       << info.image_w << "\n"
       << std::setw(W) << "image_h: "
       << info.image_h << "\n"
       << std::setw(W) << "proj: "
       << info.prog << "\n"
       << std::setw(W) << "tile_x: "
       << info.tile_x << "\n"
       << std::setw(W) << "tile_y: "
       << info.tile_y << "\n"
       << std::setw(W) << "tile_Ox: "
       << info.tile_Ox << "\n"
       << std::setw(W) << "tile_Oy: "
       << info.tile_Oy << "\n"
       << std::setw(W) << "tw: "
       << info.tw << "\n"
       << std::setw(W) << "th: "
       << info.th << "\n"
       << std::setw(W) << "numcomps: "
       << info.numcomps << "\n"
       << std::setw(W) << "numlayers: "
       << info.numlayers << "\n";

   for (int i = 0; i < info.numcomps; ++i)
   {
      std::string s = "numdecompos[";
      s += ossimString::toString(i).string();
      s += "]: ";
      out << std::setw(W) << s << info.numdecompos[i] << "\n";
   }

   out << std::setw(W) << "marknum: "
       << info.marknum << "\n"
      // << std::setw(W) << "marker: " << info.marker << "\n"
       << std::setw(W) << "maxmarknum: "
       << info.maxmarknum << "\n"
       << std::setw(W) << "main_head_start: "
       << info.main_head_start << "\n"
       << std::setw(W) << "main_head_end: "
       << info.main_head_end << "\n"
       << std::setw(W) << "codestream_size: "
       << info.codestream_size << "\n"
      // << "tile: " << info.tile
       << std::endl;

   // Set the flags back.
   out.flags(f);

   return out;
}

std::ostream& ossim::print(std::ostream& out, const opj_dparameters& param)
{
   // Capture stream flags since we are going to mess with them.
   std::ios_base::fmtflags f = out.flags();

   const int W = 20;

   out << std::setiosflags(std::ios_base::right) << std::setfill(' ')
       << "opj_dparameters:\n\n"
       << std::setw(W) << "cp_reduce: "
       << param.cp_reduce << "\n"
       << std::setw(W) << "cp_layer: "
       << param.cp_layer << "\n"
       << std::setw(W) << "infile: "
       << param.infile << "\n"
       << std::setw(W) << "outfile: "
       << param.outfile << "\n"
       << std::setw(W) << "decod_format: "
       << param.decod_format << "\n"
       << std::setw(W) << "cod_format: "
       << param.cod_format << "\n"
       << std::setw(W) << "jpwl_correct: "
       << param.jpwl_correct << "\n"
       << std::setw(W) << "jpwl_exp_comps: "
       << param.jpwl_exp_comps << "\n"
       << std::setw(W) << "jpwl_max_tiles: "
       << param.jpwl_max_tiles << "\n"
       << std::setw(W) << "cp_limit_decoding: "
      // << param.cp_limit_decoding fix (drb)
       << std::endl;
   // Set the flags back.
   out.flags(f);

   return out;
}

std::ostream& ossim::print(std::ostream& out, const opj_image& image)
{
   // Capture stream flags since we are going to mess with them.
   std::ios_base::fmtflags f = out.flags();

   const int W = 20;

   out << std::setiosflags(std::ios_base::right) << std::setfill(' ')
       << "opj_image:\n\n"
       << std::setw(W) << "x0: "
       << image.x0 << "\n"
       << std::setw(W) << "y0: "
       << image.y0 << "\n"
       << std::setw(W) << "x1: "
       << image.x1 << "\n"
       << std::setw(W) << "y1: "
       << image.y1 << "\n"
       << std::setw(W) << "numcomps: "
       << image.numcomps << "\n"
       << std::setw(W) << "color_space: "
       << int(image.color_space) << "\n";

   for (int i = 0; i < image.numcomps; ++i)
   {
      std::string s = "comps[";
      s += ossimString::toString(i).string();
      s += "]: ";
      out << s << std::endl;
         
      print(out, (image.comps[i]));
   }

   out << std::endl;
      
   // Set the flags back.
   out.flags(f);

   return out;
}

std::ostream& ossim::print(std::ostream& out, const opj_image_comp& comp)
{
   // Capture stream flags since we are going to mess with them.
   std::ios_base::fmtflags f = out.flags();

   const int W = 20;

   out << std::setiosflags(std::ios_base::right) << std::setfill(' ')
       << "opj_image_comp:\n\n"
       << std::setw(W) << "dx: "
       << comp.dx << "\n"
       << std::setw(W) << "dy: "
       << comp.dy << "\n"
       << std::setw(W) << "w: "
       << comp.w << "\n"
       << std::setw(W) << "h: "
       << comp.h << "\n"
       << std::setw(W) << "x0: "
       << comp.x0 << "\n"
       << std::setw(W) << "y0: "
       << comp.y0 << "\n"
       << std::setw(W) << "prec: "
       << comp.prec << "\n"
       << std::setw(W) << "bpp: "
      //  << comp.bpp << "\n" fix (drb) 
       << std::setw(W) << "sgnd: "
       << comp.sgnd << "\n"
       << std::setw(W) << "resno_decoded: "
       << comp.resno_decoded << "\n"
       << std::setw(W) << "factor: "
       << comp.factor
       << std::endl;
      
   // Set the flags back.
   out.flags(f);

   return out;
}
