//----------------------------------------------------------------------------
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Description: Common OSSIM Kakadu messaging definitions.
//
//----------------------------------------------------------------------------
// $Id$

#ifndef ossimKakaduMessaging_HEADER
#define ossimKakaduMessaging_HEADER 1

#include <ostream>
#include <kdu_messaging.h>
#include <ossim/base/ossimNotify.h>

/* ========================================================================= */
/* Set up kakadu messaging services to be sent to ossimNotify.               */
/* ========================================================================= */
class kdu_stream_message : public kdu_message
{
public: // Member classes
   kdu_stream_message(std::ostream *stream, bool throw_exc)
      { this->stream = stream; this->throw_exc = throw_exc; }
   void put_text(const char *string)
      { (*stream) << string; }
   void flush(bool end_of_message=false)
      {
         stream->flush();
         if (end_of_message && throw_exc)
            throw (int) 1;
      }
private: // Data
   std::ostream *stream;
   bool throw_exc;
};

static kdu_stream_message cout_message(&ossimNotify(ossimNotifyLevel_NOTICE),
                                       false);
static kdu_stream_message cerr_message(&ossimNotify(ossimNotifyLevel_NOTICE),
                                       true);
static kdu_message_formatter pretty_cout(&cout_message);
static kdu_message_formatter pretty_cerr(&cerr_message);

#endif /* #ifndef ossimKakaduMessaging_HEADER */
