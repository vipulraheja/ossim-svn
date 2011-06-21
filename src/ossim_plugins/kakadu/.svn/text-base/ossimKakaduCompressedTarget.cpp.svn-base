//----------------------------------------------------------------------------
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Description:
//
// Class definition for JPEG2000 (J2K) kdu_compressed_target that uses an
// ostream for writing to the file.
//
//----------------------------------------------------------------------------
// $Id$

#include <ostream>
#include <ossimKakaduCompressedTarget.h>

ossimKakaduCompressedTarget::ossimKakaduCompressedTarget()
   : m_stream(0),
     m_restorePosition()
{
}

ossimKakaduCompressedTarget::~ossimKakaduCompressedTarget()
{
}

void ossimKakaduCompressedTarget::setStream(std::ostream* stream)
{
   m_stream = stream;
}

bool ossimKakaduCompressedTarget::write(const kdu_byte *buf, int num_bytes)
{
   bool result = false;
   if (m_stream)
   {
      m_stream->write((const char*)buf, num_bytes);
      result = m_stream->good();
   }
   return result;
}

bool ossimKakaduCompressedTarget::start_rewrite(kdu_long backtrack)
{
   bool result = false;
   if (m_stream)
   {
      m_restorePosition = m_stream->tellp();
      std::streamoff pos =
         m_restorePosition - static_cast<std::streamoff>(backtrack);
      m_stream->seekp(pos, std::ios_base::beg);
      result = m_stream->good();
   }
   return result;
}

bool ossimKakaduCompressedTarget::end_rewrite()
{
   bool result = false;
   if (m_stream)
   {
      m_stream->seekp(m_restorePosition, std::ios_base::beg);
      result = m_stream->good();
   }
   return result;
}


