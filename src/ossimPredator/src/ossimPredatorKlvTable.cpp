#include <ossimPredator/ossimPredatorKlvTable.h>
#include <iostream>
#include <iomanip>

#include <ossim/base/ossimTrace.h>
static const ossimTrace traceDebug("ossimPredatorKlvTable:debug");
static const  ossimPredatorKlvInfoType OSSIM_PREDATOR_UDS_TABLE[]=
{
{KLV_KEY_STREAM_ID,"stream ID",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x01, 0x03, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_ORGANIZATIONAL_PROGRAM_NUMBER,"Organizational Program Number",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x01, 0x03, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_UNIX_TIMESTAMP,"UNIX Timestamp",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x04, 0x07, 0x02, 0x01, 0x01, 0x01, 0x05, 0x00, 0x00}}, // TIME STAMP
{KLV_KEY_USER_DEFINED_UTC_TIMESTAMP, "User Defined UTC", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00}},
{KLV_KEY_USER_DEFINED_TIMESTAMP_MICROSECONDS_1970, "User Defined Timestamp Microseconds since 1970", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x02, 0x01, 0x01, 0x01, 0x05, 0x00, 0x00}},
{KLV_KEY_VIDEO_START_DATE_TIME_UTC, "Video Timestamp Start Date and Time",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x02, 0x01, 0x02, 0x01, 0x01, 0x00, 0x00}},
{KLV_TIMESYSTEM_OFFSET, "Time System Offset From UTC", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x03, 0x01, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00}},
{KLV_UAS_DATALINK_LOCAL_DATASET, "UAS Datalink Local Data Set",{0x06, 0x0E, 0x2B, 0x34, 0x02, 0x0B, 0x01, 0x01, 0x0E, 0x01, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00}},
{KLV_BASIC_UNIVERSAL_METADATA_SET, "Universal Metadata Set",{0x06, 0x0E, 0x2B, 0x34, 0x02, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x02, 0x01, 0x01, 0x00, 0x00}},
{KLV_URL_STRING, "URL String", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_SECURITY_CLASSIFICATION_SET, "Security Classification Set", {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x01, 0x01, 0x01, 0x02, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_BYTE_ORDER, "Byte Order", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x03, 0x01, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00}},
{KLV_KEY_MISSION_NUMBER,"Mission Number",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x01, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_SECURITY_CLASSIFICATION, "Security Classification", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x02, 0x08, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_SECURITY_RELEASE_INSTRUCTIONS, "Release Instructions", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x20, 0x01, 0x02, 0x09, 0x00, 0x00}},
{KLV_KEY_SECURITY_CAVEATS, "Caveats", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x02, 0x08, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_CLASSIFICATION_COMMENT, "Classification Comment", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x02, 0x08, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_ORIGINAL_PRODUCER_NAME, "Original Producer Name", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_HEADING_ANGLE,"Platform Heading Angle",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x07, 0x07, 0x01, 0x10, 0x01, 0x06, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_PITCH_ANGLE,"Platform Pitch Angle",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x07, 0x07, 0x01, 0x10, 0x01, 0x05, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_ROLL_ANGLE, "Platform Roll Angle",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x07, 0x07, 0x01, 0x10, 0x01, 0x04, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_DESIGNATION,"Platform Designation",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_DESIGNATION2,"Platform Designation",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x21, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_IMAGE_SOURCE_SENSOR,"Image Source Sensor",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x04, 0x20, 0x01, 0x02, 0x01, 0x01, 0x00, 0x00}},
{KLV_KEY_IMAGE_COORDINATE_SYSTEM,"Image Coordinate System",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_SENSOR_LATITUDE,"Sensor Latitude",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x02, 0x04, 0x02, 0x00}},
{KLV_KEY_SENSOR_LONGITUDE,"Sensor Longitude",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x02, 0x06, 0x02, 0x00}},
{KLV_KEY_SENSOR_TRUE_ALTITUDE,"Sensor True Altitude",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x02, 0x01, 0x02, 0x02, 0x00, 0x00}},
{KLV_KEY_SENSOR_HORIZONTAL_FOV,"Sensor Horizontal Field Of View",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x02, 0x04, 0x20, 0x02, 0x01, 0x01, 0x08, 0x00, 0x00}},
{KLV_KEY_SENSOR_VERTICAL_FOV1,"Sensor Vertical Field Of View",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x07, 0x04, 0x20, 0x02, 0x01, 0x01, 0x0A, 0x01, 0x00}},
{KLV_KEY_SENSOR_VERTICAL_FOV2,"Sensor Vertical Field Of View",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x04, 0x20, 0x02, 0x01, 0x01, 0x0A, 0x01, 0x00}},
{KLV_KEY_SLANT_RANGE,"Slant Range",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x08, 0x01, 0x01, 0x00, 0x00, 0x00}},
{KLV_KEY_OBLIQUITY_ANGLE,"Obliquity Angle",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x10, 0x01, 0x03, 0x00, 0x00, 0x00}},
{KLV_KEY_ANGLE_TO_NORTH, "Angle To North", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x10, 0x01, 0x02, 0x00, 0x00, 0x00}},
{KLV_KEY_TARGET_WIDTH,"Target Width",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x09, 0x02, 0x01, 0x00, 0x00, 0x00}},
{KLV_KEY_FRAME_CENTER_LATITUDE,"Frame Center Latitude",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x02, 0x01, 0x03, 0x02, 0x00, 0x00}},
{KLV_KEY_FRAME_CENTER_LONGITUDE,"Frame Center Longitude",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x02, 0x01, 0x03, 0x04, 0x00, 0x00}},
{KLV_KEY_FRAME_CENTER_ELEVATION,"Frame Center elevation",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x06, 0x07, 0x01, 0x02, 0x03, 0x10, 0x00, 0x00, 0x00}},
{KLV_KEY_CORNER_LATITUDE_POINT_1,"Corner Latitude Point 1",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x07, 0x01, 0x00}},
{KLV_KEY_CORNER_LONGITUDE_POINT_1,"Corner Longitude Point 1",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x0B, 0x01, 0x00}},
{KLV_KEY_CORNER_LATITUDE_POINT_2,"Corner Latitude Point 2",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x08, 0x01, 0x00}},
{KLV_KEY_CORNER_LONGITUDE_POINT_2,"Corner Longitude Point 2",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x0C, 0x01, 0x00}},
{KLV_KEY_CORNER_LATITUDE_POINT_3,"Corner Latitude Point 3",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x09, 0x01, 0x00}},
{KLV_KEY_CORNER_LONGITUDE_POINT_3,"Corner Longitude Point 3",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x0D, 0x01, 0x00}},
{KLV_KEY_CORNER_LATITUDE_POINT_4,"Corner Latitude Point 4",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x0A, 0x01, 0x00}},
{KLV_KEY_CORNER_LONGITUDE_POINT_4,"Corner Longitude Point 4",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x0E, 0x01, 0x00}},
{KLV_KEY_DEVICE_ABSOLUTE_SPEED,"Device Absolute Speed",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00}},
{KLV_KEY_DEVICE_ABSOLUTE_HEADING,"Device Absolute Heading",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x03, 0x01, 0x01, 0x02, 0x00, 0x00}},
{KLV_KEY_ABSOLUTE_EVENT_START_DATE,"Absolute Event Start Date",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x02, 0x01, 0x02, 0x07, 0x01, 0x00, 0x00}},
{KLV_KEY_SENSOR_ROLL_ANGLE,"Sensor Roll Angle", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x10, 0x01, 0x01, 0x00, 0x00, 0x00}}

};

const ossim_uint8 ossimPredatorKlvTable::theKlvKey[4] = { 0x06,0x0e,0x2b,0x34 };
#define PRINT_KEY(x) printf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", \
(x)[0], (x)[1], (x)[2], (x)[3], (x)[4], (x)[5], (x)[6], (x)[7], (x)[8], (x)[9], (x)[10], (x)[11], (x)[12], (x)[13], (x)[14], (x)[15])

static void printHex(const std::vector<ossim_uint8>& buf)
{
   ossim_uint32 idx = 0;
   while(idx < buf.size())
   {
      printf("%02X ", buf[idx]);
      if((idx%32) == 0)
      {
        // printf("\n");      
      }
      ++idx;
   }
}

bool ossimPredatorKlvTable::addKeys(const std::vector<ossim_uint8>& buffer)
{
   return addKeys(&buffer.front(), buffer.size());
}

ossim_int64 klv_decode_length(const ossim_uint8* buf, ossim_uint32& offset)
{
   ossim_int64 size = buf[offset];
   ossim_uint8 longTest = buf[offset];
   ++offset;
   if (longTest & 0x80)
   { /* long form */
      int bytes_num = longTest & 0x7f;
      /* SMPTE 379M 5.3.4 guarantee that bytes_num must not exceed 8 bytes */
      if (bytes_num > 8)
      {
         return -1;
      }
      size = 0;
      
      while (bytes_num--)
      {
         size = size << 8 | buf[offset];
         ++offset;
      }
   }
   
   return size;
}

ossimPredatorKlvTable::ossimPredatorKlvTable()
{
   theNeedToSwapFlag = theEndian.getSystemEndianType()!=OSSIM_BIG_ENDIAN;
}

bool ossimPredatorKlvTable::addKeys(const ossim_uint8* buffer, ossim_uint32 length)
{
   std::vector<ossim_uint8> bufferToParse;
   bufferToParse = theNeedToParseBuffer;
   if(buffer)
   {
      bufferToParse.insert(bufferToParse.end(),
                           buffer,
                           buffer + length);
   }
   theNeedToParseBuffer.clear();
   ossim_uint32 currentIdx = 0;
   ossim_uint32 totalLen = bufferToParse.size();
   const ossim_uint8* bufPtr = &bufferToParse.front();
   if(totalLen < 1) return false;
   while(std::equal(theKlvKey,
                    theKlvKey + 4,
                    &bufPtr[currentIdx])) // while we are looking at klv keys keep parsing
   {
      if((currentIdx+16) >= totalLen)
      {
         theNeedToParseBuffer.clear();
         theNeedToParseBuffer.insert(theNeedToParseBuffer.end(),
                                     &bufPtr[currentIdx],
                                     &bufPtr[totalLen]);
         
         return true;
      }
      ossimPredatorKlvTable::Node node;
      ossim_uint32 saveIdx = currentIdx;
      node.theId = findPredatorKlvIndex(&bufPtr[currentIdx]);
      if(node.theId < 0)
      {
         if(traceDebug())
         {
            ossim_uint32 tempId = currentIdx + 16;
            std::cout << "**************UNDEFINED KEY**************\n";
            std::cout << "WITH SIZE === " << klv_decode_length(bufPtr, tempId) << std::endl;
            PRINT_KEY(&bufPtr[currentIdx]);
         }
         //ossim_uint32 tempId = currentIdx + 16;
         //std::cout << "**************UNDEFINED KEY**************\n";
         //std::cout << "WITH SIZE === " << klv_decode_length(bufPtr, tempId) << std::endl;
         // PRINT_KEY(&bufPtr[currentIdx]);
         //
         //ossim_float32 f = *reinterpret_cast<const ossim_float32*>(&bufPtr[tempId]);
         //theEndian.swap(f);
         //          std::cout << "POSSIBLE VALUE === " << f << std::endl; 
      }
      //PRINT_KEY(&bufPtr[currentIdx]);
      currentIdx += 16;
      int klvLength = klv_decode_length(bufPtr, currentIdx);
      if(klvLength > 0)
      {
         if((currentIdx + klvLength) <= totalLen)
         {
            node.theValue.insert(node.theValue.end(),
                                 &bufPtr[currentIdx], &bufPtr[currentIdx + klvLength]);
            currentIdx += klvLength;
            if(node.theId >=0)
            {
               if((node.theId == KLV_BASIC_UNIVERSAL_METADATA_SET)||
                  (node.theId == KLV_KEY_SECURITY_CLASSIFICATION_SET))
               {
                  theNeedToParseBuffer.insert(theNeedToParseBuffer.end(),
                                              node.theValue.begin(),
                                              node.theValue.end());
                  theNeedToParseBuffer.insert(theNeedToParseBuffer.end(),
                                              &bufPtr[currentIdx],
                                              &bufPtr[totalLen]);
                  
                  return addKeys(0,0);
               }
               else if(node.theId == KLV_UAS_DATALINK_LOCAL_DATASET)
               {
                  addUasDatalinkLocalDataSet(node.theValue);
                  return addKeys(0,0);
               }
               else
               {
                  theKlvParameters.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(node.theId),
                                                         node));
                  //                   std::cout << "VALUE = " << getValueAsString((PredatorKlvIndex)node.theId) << std::endl;
                  //                   std::cout << "SIZE = " << klvLength << std::endl;
               }
            }
         }
         else
         {
            theNeedToParseBuffer.insert(theNeedToParseBuffer.end(),
                                        &bufPtr[saveIdx],
                                        &bufPtr[totalLen]);
            return true;
         }
      }
      if(currentIdx >= totalLen) return false;
   }
   
   return false;
   
}


void ossimPredatorKlvTable::clear()
{
   theKlvParameters.clear();
}

bool ossimPredatorKlvTable::valueAsString(ossimString& result,
                                          ossimPredatorKlvIndex id)const
{
   bool foundFlag = false;
   klvMapType::const_iterator i = theKlvParameters.find(id);
   if(i != theKlvParameters.end())
   {
      foundFlag = true;
      switch(i->second.theId)
      {
            // convert ossim_uint64 types
         case KLV_KEY_UNIX_TIMESTAMP:
         case KLV_KEY_USER_DEFINED_TIMESTAMP_MICROSECONDS_1970:
         {
            ossim_uint64 value = *reinterpret_cast<const ossim_uint64*>(&(i->second.theValue.front()));
            if(theNeedToSwapFlag)
            {
               theEndian.swap(value);
            }
            result = ossimString::toString(value);
            break;
         }
            // convert string values
         case KLV_KEY_MISSION_NUMBER:
         case KLV_KEY_ORGANIZATIONAL_PROGRAM_NUMBER:
         case KLV_URL_STRING:
         case KLV_KEY_CLASSIFICATION_COMMENT:
         case KLV_KEY_SECURITY_RELEASE_INSTRUCTIONS:
         case KLV_KEY_SECURITY_CAVEATS:
         case KLV_KEY_SECURITY_CLASSIFICATION:
         case KLV_KEY_ORIGINAL_PRODUCER_NAME:
         case KLV_TIMESYSTEM_OFFSET:
         case KLV_KEY_BYTE_ORDER:
         case KLV_KEY_PLATFORM_DESIGNATION:
         case KLV_KEY_PLATFORM_DESIGNATION2:
         case KLV_KEY_IMAGE_SOURCE_SENSOR:
         case KLV_KEY_IMAGE_COORDINATE_SYSTEM:
         case KLV_KEY_ABSOLUTE_EVENT_START_DATE:
         case KLV_KEY_VIDEO_START_DATE_TIME_UTC:
         {
				if(i->second.theValue.size()>0)
				{
					const char* bufPtr = reinterpret_cast<const char*>(&(i->second.theValue.front()));
					result = ossimString(bufPtr,
												bufPtr+i->second.theValue.size());
				}
				else
				{
					result = "";
				}
            break;
         }
            // convert double precision values
         case KLV_KEY_SENSOR_LATITUDE:
         case KLV_KEY_SENSOR_LONGITUDE:
         case KLV_KEY_FRAME_CENTER_LATITUDE:
         case KLV_KEY_FRAME_CENTER_LONGITUDE:
         case KLV_KEY_CORNER_LATITUDE_POINT_1:
         case KLV_KEY_CORNER_LATITUDE_POINT_2:
         case KLV_KEY_CORNER_LATITUDE_POINT_3:
         case KLV_KEY_CORNER_LATITUDE_POINT_4:
         case KLV_KEY_CORNER_LONGITUDE_POINT_1:
         case KLV_KEY_CORNER_LONGITUDE_POINT_2:
         case KLV_KEY_CORNER_LONGITUDE_POINT_3:
         case KLV_KEY_CORNER_LONGITUDE_POINT_4:
         {
            ossim_float64 value = *reinterpret_cast<const ossim_float64*>(&(i->second.theValue.front()));
            if(theNeedToSwapFlag)
            {
               theEndian.swap(value);
            }
            result = ossimString::toString(value);
            break;
         }
         case KLV_KEY_SENSOR_TRUE_ALTITUDE:
         case KLV_KEY_FRAME_CENTER_ELEVATION:
         case KLV_KEY_SLANT_RANGE:
         case KLV_KEY_TARGET_WIDTH:
         case KLV_KEY_SENSOR_ROLL_ANGLE:
         case KLV_KEY_SENSOR_HORIZONTAL_FOV:
         case KLV_KEY_SENSOR_VERTICAL_FOV1:
         case KLV_KEY_SENSOR_VERTICAL_FOV2:
         case KLV_KEY_PLATFORM_HEADING_ANGLE:
         case KLV_KEY_PLATFORM_PITCH_ANGLE:
         case KLV_KEY_PLATFORM_ROLL_ANGLE:
         case KLV_KEY_OBLIQUITY_ANGLE:
         case KLV_KEY_ANGLE_TO_NORTH:
         case KLV_KEY_DEVICE_ABSOLUTE_SPEED:
         case KLV_KEY_DEVICE_ABSOLUTE_HEADING:
         {
            ossim_float32 value = *reinterpret_cast<const ossim_float32*>(&(i->second.theValue.front()));
            
            if(theNeedToSwapFlag)
            {
               theEndian.swap(value);
            }
            result = ossimString::toString(value);
            break;
         }
      }
   }
   return foundFlag;
}

ossimString ossimPredatorKlvTable::valueAsString(ossimPredatorKlvIndex id)const

{
   ossimString result;
   if(valueAsString(result, id))
   {
      return result;
   }
   
   return ossimString("");
}

bool ossimPredatorKlvTable::getCornerPoints(ossimGpt& pt1,
                                            ossimGpt& pt2,
                                            ossimGpt& pt3,
                                            ossimGpt& pt4)const
{
   klvMapType::const_iterator lat1i = theKlvParameters.find(KLV_KEY_CORNER_LATITUDE_POINT_1);
   klvMapType::const_iterator lat2i = theKlvParameters.find(KLV_KEY_CORNER_LATITUDE_POINT_2);
   klvMapType::const_iterator lat3i = theKlvParameters.find(KLV_KEY_CORNER_LATITUDE_POINT_3);
   klvMapType::const_iterator lat4i = theKlvParameters.find(KLV_KEY_CORNER_LATITUDE_POINT_4);
   klvMapType::const_iterator lon1i = theKlvParameters.find(KLV_KEY_CORNER_LONGITUDE_POINT_1);
   klvMapType::const_iterator lon2i = theKlvParameters.find(KLV_KEY_CORNER_LONGITUDE_POINT_2);
   klvMapType::const_iterator lon3i = theKlvParameters.find(KLV_KEY_CORNER_LONGITUDE_POINT_3);
   klvMapType::const_iterator lon4i = theKlvParameters.find(KLV_KEY_CORNER_LONGITUDE_POINT_4);
   
   if((lat1i!=theKlvParameters.end())&&
      (lat2i!=theKlvParameters.end())&&
      (lat3i!=theKlvParameters.end())&&
      (lat4i!=theKlvParameters.end())&&
      (lon1i!=theKlvParameters.end())&&
      (lon2i!=theKlvParameters.end())&&
      (lon3i!=theKlvParameters.end())&&
      (lon4i!=theKlvParameters.end()))
   {
      
      ossim_float64  lat1 = *reinterpret_cast<const ossim_float64*>(&(lat1i->second.theValue.front()));
      ossim_float64  lat2 = *reinterpret_cast<const ossim_float64*>(&(lat2i->second.theValue.front()));
      ossim_float64  lat3 = *reinterpret_cast<const ossim_float64*>(&(lat3i->second.theValue.front()));
      ossim_float64  lat4 = *reinterpret_cast<const ossim_float64*>(&(lat4i->second.theValue.front()));
      ossim_float64  lon1 = *reinterpret_cast<const ossim_float64*>(&(lon1i->second.theValue.front()));
      ossim_float64  lon2 = *reinterpret_cast<const ossim_float64*>(&(lon2i->second.theValue.front()));
      ossim_float64  lon3 = *reinterpret_cast<const ossim_float64*>(&(lon3i->second.theValue.front()));
      ossim_float64  lon4 = *reinterpret_cast<const ossim_float64*>(&(lon4i->second.theValue.front()));
      
      if(theNeedToSwapFlag)
      {
         theEndian.swap(lat1);
         theEndian.swap(lat2);
         theEndian.swap(lat3);
         theEndian.swap(lat4);
         theEndian.swap(lon1);
         theEndian.swap(lon2);
         theEndian.swap(lon3);
         theEndian.swap(lon4);
         
      }
      pt1 = ossimGpt(lat1, lon1);
      pt2 = ossimGpt(lat2, lon2);
      pt3 = ossimGpt(lat3, lon3);
      pt4 = ossimGpt(lat4, lon4);
      
      return true;
   }
   
   return false;
   
}

bool ossimPredatorKlvTable::getFrameCenter(ossim_float64& lat,
                                           ossim_float64& lon,
                                           ossim_float64& elevation)const
{
   klvMapType::const_iterator lati  = theKlvParameters.find(KLV_KEY_FRAME_CENTER_LATITUDE);
   klvMapType::const_iterator loni  = theKlvParameters.find(KLV_KEY_FRAME_CENTER_LONGITUDE);
   klvMapType::const_iterator elevi = theKlvParameters.find(KLV_KEY_FRAME_CENTER_ELEVATION);
   
   if((lati != theKlvParameters.end())&&
      (loni != theKlvParameters.end()))
   {
      lat =  *reinterpret_cast<const ossim_float64*>(&(lati->second.theValue.front()));
      lon =  *reinterpret_cast<const ossim_float64*>(&(loni->second.theValue.front()));
      ossim_float32 elev = 0;
      if(elevi != theKlvParameters.end())
      {
         elev = *reinterpret_cast<const ossim_float32*>(&(elevi->second.theValue.front()));
         if(theNeedToSwapFlag)
         {
            theEndian.swap(elev);
         }
      }
      if(theNeedToSwapFlag)
      {
         theEndian.swap(lat);
         theEndian.swap(lon);
      }
      elevation = elev;
      return true;
   }
   
   return false;
}

bool ossimPredatorKlvTable::getSensorPosition(ossim_float64& lat,
                                              ossim_float64& lon,
                                              ossim_float64& elevation)const
{
   klvMapType::const_iterator lati  = theKlvParameters.find(KLV_KEY_SENSOR_LATITUDE);
   klvMapType::const_iterator loni  = theKlvParameters.find(KLV_KEY_SENSOR_LONGITUDE);
   klvMapType::const_iterator elevi = theKlvParameters.find(KLV_KEY_SENSOR_TRUE_ALTITUDE);
   
   if((lati != theKlvParameters.end())&&
      (loni != theKlvParameters.end())&&
      (elevi != theKlvParameters.end()))
   {
      lat =  *reinterpret_cast<const ossim_float64*>(&(lati->second.theValue.front()));
      lon =  *reinterpret_cast<const ossim_float64*>(&(loni->second.theValue.front()));
      ossim_float32 elev = *reinterpret_cast<const ossim_float32*>(&(elevi->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(lat);
         theEndian.swap(lon);
         theEndian.swap(elev);
      }     
      elevation = elev;//*0.304801;
      return true;
   }
   
   return false;
}

bool ossimPredatorKlvTable::getPlatformOrientation(ossim_float32& heading,
                                                   ossim_float32& pitch,
                                                   ossim_float32& roll)const
{
   heading = valueAsString(KLV_KEY_PLATFORM_HEADING_ANGLE).toFloat32();
   pitch = valueAsString(KLV_KEY_PLATFORM_PITCH_ANGLE).toFloat32();
   roll = valueAsString(KLV_KEY_PLATFORM_ROLL_ANGLE).toFloat32();
   
   return true;
}

bool ossimPredatorKlvTable::getSensorRollAngle(ossim_float32& angle)const
{
   ossimString value = valueAsString(KLV_KEY_SENSOR_ROLL_ANGLE);
   if(!value.empty())
   {
      angle = value.toFloat32();
   }
   
   return !value.empty();
}

bool ossimPredatorKlvTable::getObliquityAngle(ossim_float32& angle)const
{
   klvMapType::const_iterator value  = theKlvParameters.find(KLV_KEY_OBLIQUITY_ANGLE);
   angle = 0.0;
   if(value!=theKlvParameters.end())
   {
      angle =  *reinterpret_cast<const ossim_float32*>(&(value->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(angle);
      }
   }
   
   return (value!=theKlvParameters.end());
}

bool ossimPredatorKlvTable::getSlantRange(ossim_float32& range)const
{
   klvMapType::const_iterator value  = theKlvParameters.find(KLV_KEY_SLANT_RANGE);
   range = 0.0;
   if(value!=theKlvParameters.end())
   {
      range =  *reinterpret_cast<const ossim_float32*>(&(value->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(range);
      }
   }
   
   return (value!=theKlvParameters.end());
   
}
bool ossimPredatorKlvTable::getHorizontalFieldOfView(ossim_float32& hfov)const
{
   klvMapType::const_iterator value  = theKlvParameters.find(KLV_KEY_SENSOR_HORIZONTAL_FOV);
   hfov = 0.0;
   if(value!=theKlvParameters.end())
   {
      hfov =  *reinterpret_cast<const ossim_float32*>(&(value->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(hfov);
      }
   }
   
   return (value!=theKlvParameters.end());
}

bool ossimPredatorKlvTable::getVerticalFieldOfView(ossim_float32& vfov)const
{
   klvMapType::const_iterator value  = theKlvParameters.find(KLV_KEY_SENSOR_VERTICAL_FOV1);
   if(value == theKlvParameters.end())
   {
      value  = theKlvParameters.find(KLV_KEY_SENSOR_VERTICAL_FOV2);
   }
   vfov = 0.0;
   if(value!=theKlvParameters.end())
   {
      vfov =  *reinterpret_cast<const ossim_float32*>(&(value->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(vfov);
      }
   }
   
   return (value!=theKlvParameters.end());
}

bool ossimPredatorKlvTable::getAngleToNorth(ossim_float32& angleToNorth)const
{
   klvMapType::const_iterator value  = theKlvParameters.find(KLV_KEY_ANGLE_TO_NORTH);
   angleToNorth = 0.0;
   if(value!=theKlvParameters.end())
   {
      angleToNorth =  *reinterpret_cast<const ossim_float32*>(&(value->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(angleToNorth);
      }
   }
   
   return (value!=theKlvParameters.end());
   
}

bool ossimPredatorKlvTable::getTargetWidthInMeters(ossim_float32& targetWidth)const
{
   ossimString value = valueAsString(KLV_KEY_TARGET_WIDTH);
   
   targetWidth = value.toFloat32();
   
   return !value.empty();
}

ossimString ossimPredatorKlvTable::getUtcTimestamp()const
{
   return valueAsString(KLV_KEY_VIDEO_START_DATE_TIME_UTC);
}


bool ossimPredatorKlvTable::getUnixEpocTimestamp(ossim_int64& timestamp)const
{
   klvMapType::const_iterator timei  = theKlvParameters.find(KLV_KEY_USER_DEFINED_TIMESTAMP_MICROSECONDS_1970);
   if(timei == theKlvParameters.end())
   {
      timei  = theKlvParameters.find(KLV_KEY_UNIX_TIMESTAMP);
   }
   if(timei != theKlvParameters.end())
   {
      timestamp =  *reinterpret_cast<const ossim_uint64*>(&(timei->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(timestamp);
      }
      return true;
   }
   
   return false;
}

bool ossimPredatorKlvTable::getUnixEpocTimestampInSeconds(ossim_int64& seconds,
                                                          ossim_float64& fractionalPart)const
{
   ossim_int64 epocInMicroseconds;
   bool result = getUnixEpocTimestamp(epocInMicroseconds);
   ossim_float64 fractionalSeconds = static_cast<ossim_float64>(epocInMicroseconds*1e-6);
   seconds = static_cast<ossim_uint64>(fractionalSeconds);
   fractionalPart = fractionalSeconds - seconds;
   
   return result;
}

bool ossimPredatorKlvTable::getUnixEpocTimestampInFractionalSeconds(ossim_float64& fractionalSeconds)const
{
   ossim_int64 epocInMicroseconds;
   bool result = getUnixEpocTimestamp(epocInMicroseconds);
   fractionalSeconds = static_cast<ossim_float64>(epocInMicroseconds/10e-6);
   
   return result;
}

bool ossimPredatorKlvTable::getDate(ossimDate& d, bool shiftToGmtZero)const
{
   bool result = getDateUsingUtc(d, shiftToGmtZero);
   
   if(!result)
   {
      result = getDateUsingEpoc(d);
   }
   return result;
}

bool ossimPredatorKlvTable::getDateUsingEpoc(ossimDate& d)const
{
   bool result = false;
   ossim_int64 t;
   ossim_float64 fraction=0;
   
   if(getUnixEpocTimestampInSeconds(t, fraction))
   {
      result = true;
      d.setTimeNoAdjustmentGivenEpoc(t);
      d.setFractionalSecond(fraction);
   }
   
   return result;
}

bool ossimPredatorKlvTable::getDateUsingUtc(ossimDate& d, bool shiftToGmtZero)const
{
   bool result = false;
   ossimString utc = getUtcTimestamp();
   if(utc.size() > 0)
   {
      result = d.setIso8601(utc, shiftToGmtZero);
   }
   return result;
}

int ossimPredatorKlvTable::findPredatorKlvIndex(const ossim_uint8* buf)const
{
   ossim_int32 idx = 0;
   
   for(idx = 0; idx < KLV_KEY_TOTAL; ++idx)
   {
      if(std::equal(buf,
                    buf+16,
                    OSSIM_PREDATOR_UDS_TABLE[idx].theKey))
      {
         return idx;
      }
   }
   
   return -1;
}
void ossimPredatorKlvTable::loadVariableDataNullTerminated(std::vector<ossim_uint8>& result, 
                                                           const std::vector<ossim_uint8>& buf, 
                                                           ossim_uint32& idx)const
{
   while((idx < buf.size())&&(buf[idx] != '\0'))
   {
      result.push_back(buf[idx]);
      ++idx;
   }
   if(idx < buf.size())
   {
      ++idx;
   }
}

void ossimPredatorKlvTable::addUasDatalinkLocalDataSet(const std::vector<ossim_uint8>& buffer)
{
   if(buffer.size() == 0) return;
   ossim_uint32 idx = 0;
   bool done = false;
   while(!done&&((idx+2) < buffer.size()))
   {
      ossim_uint32 key= buffer[idx++];
      ossim_uint32 length= buffer[idx++];
      switch(key)
      {
         case 1:
         {
            
            break;
         }
         case 2: // unix timestamp
         {
            Node n(KLV_KEY_UNIX_TIMESTAMP,
                   std::vector<ossim_uint8>(buffer.front()+idx,
                                            buffer.front()+idx+length));
            theKlvParameters.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                   n));
            
            break;
         }
         case 3:
         {
            //            std::cout << "MISSION ID!!" << std::endl;
            break;
         }
         case 4:
         {
//            std::cout << "PLATFORM TAIL NUMBER!!" << std::endl;
            break;
         }
         case 5:
         {
            ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
           // double heading  = 360.0*(buf)/(double)((1<<16) - 1);
//            std::cout << "HEADING == " << heading << std::endl;
            //            std::cout << "PLATFORM HEADING!!" << std::endl;
            break;
         }
         case 6:
         {
            ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
            //double value  = 20.0*(buf)/(double)((1<<15) - 1);
//            std::cout << "PITCH == " << value << std::endl;
            //            std::cout << "PLATFORM PITCH!!" << std::endl;
            break;
         }
         case 7:
         {
            ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
            //double value  = 50.0*((buf)/(double)((1<<15) - 1));
            //std::cout << "ROLL == " << value << std::endl;
            //            std::cout << "PLATFORM ROLL!!" << std::endl;
            break;
         }
         case 8:
         {
//            std::cout << "PLATFORM TRUE AIRSPEED!!" << std::endl;
            break;
         }
         case 9:
         {
//            std::cout << "PLATFORM INDICATED AIRSPEED!!" << std::endl;
            break;
         }
         case 10:
         {
            //            std::cout << "PLATFORM DESIGNATION!!" << std::endl;
            break;
         }
         case 11:
         {
            //            std::cout << "IMAGE SOURCE SENSOR!!" << std::endl;
            break;
         }
         case 12:
         {
//            std::cout << "IMAGE COORDINATE SYSTEM!!" << std::endl;
            break;
         }
         case 13:
         {
            ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
            //double value  = 90.0*((buf)/(double)((1<<31) - 1));
//            std::cout << "LAT == " << value << std::endl;
            //            std::cout << "SENSOR LAT!!" << std::endl;
            break;
         }
         case 14:
         {
            ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
            //double value  = 180.0*((buf)/(double)((1<<31) - 1));
//            std::cout << "LON == " << value << std::endl;
            //            std::cout << "SENSOR LON!!" << std::endl;
            break;
         }
         case 15:
         {
            ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
            //double value  = 19900*((buf)/(double)((1<<16) - 1)) - 900;
//            std::cout << "ALTITUDE == " << value << std::endl;
//            std::cout << "SENSOR TRUE ALTITUDE!!" << std::endl;
            break;
         }
         case 16:
         {
            ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
            //double value  = 180.0*((buf)/(double)((1<<16) - 1));
//            std::cout << "HFOV == " << value << std::endl;
            //            std::cout << "SENSOR HORIZONTAL FOV!!" << std::endl;
            break;
         }
         case 17:
         {
            ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
            //double value  = 180.0*((buf)/(double)((1<<16) - 1));
//            std::cout << "VFOV == " << value << std::endl;
            //            std::cout << "SENSOR VERTICAL FOV!!" << std::endl;
            break;
         }
         case 18:
         {
            ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
            
            //double value  = 360.0*((buf)/(double)(0xFFFFFFFF));
//            std::cout << "REALATIVE AZIMUTH == " << value << std::endl;
            //            std::cout << "SENSOR REALTIVE AZIMUTH ANGLE!!" << std::endl;
            break;
         }
         case 19:
         {
            ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
            //double value  = 180.0*((buf)/(double)((1<<31)-1));
//            std::cout << "REALATIVE DEPRESSION == " << value << std::endl;
            break;
         }
         case 20:
         {
            ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
            //double value  = 360*((buf)/(double)(0xFFFFFFFF));
//            std::cout << "REALATIVE roll == " << value << std::endl;
            //            std::cout << "SENSOR REALTIVE ROLL ANGLE!!" << std::endl;
            break;
         }
         case 21:
         {
            ossim_uint32 buf = *reinterpret_cast<const ossim_uint32*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
            //double value  = 5000000.0*((buf)/(double)(0xFFFFFFFF));
//            std::cout << "SLANT range == " << value << std::endl;
            //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
            break;
         }
         case 22:
         {
            ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
            if(theNeedToSwapFlag)
            {
               theEndian.swap(buf);
            }
            //double value  = 10000.0*((buf)/(double)(0xFFFF));
//            std::cout << "TARGET width == " << value << std::endl;
            //            std::cout << "TARGET WIDTH!!" << std::endl;
            break;
         }
         case 23:
         {
            //            std::cout << "FRAME CENTER LAT!!" << std::endl;
            break;
         }
         case 24:
         {
            //            std::cout << "FRAME CENTER LON!!" << std::endl;
            break;
         }
         case 25:
         {
//            std::cout << "FRAME CENTER ELEV!!" << std::endl;
            break;
         }
         case 26:
         {
//            std::cout << "offset corner lat 1!!" << std::endl;
            break;
         }
         case 27:
         {
//            std::cout << "offset corner lon 1!!" << std::endl;
            break;
         }
         case 28:
         {
//            std::cout << "offset corner lat 2!!" << std::endl;
            break;
         }
         case 29:
         {
//            std::cout << "offset corner lon 2!!" << std::endl;
            break;
         }
         case 30:
         {
//            std::cout << "offset corner lat 3!!" << std::endl;
            break;
         }
         case 31:
         {
//            std::cout << "offset corner lon 3!!" << std::endl;
            break;
         }
         case 32:
         {
//            std::cout << "offset corner lat 4!!" << std::endl;
            break;
         }
         case 33:
         {
//            std::cout << "offset corner lon 5!!" << std::endl;
            break;
         }
         case 34:
         {
//            std::cout << "ICING DETECTED!!" << std::endl;
            break;
         }
         case 35:
         {
//            std::cout << "WIND DIRECTION!!" << std::endl;
            break;
         }
         case 36:
         {
//            std::cout << "WIND SPEED!!" << std::endl;
            break;
         }
         case 37:
         {
//            std::cout << "Static Pressure!!" << std::endl;
            break;
         }
         case 38:
         {
//            std::cout << "DENSITY ALTITUDE!!" << std::endl;
            break;
         }
         case 39:
         {
//            std::cout << "OUTSIDE AIR TEMP!!" << std::endl;
            break;
         }
         case 40:
         {
//            std::cout << "Target Location Latitude!!" << std::endl;
            break;
         }
         case 41:
         {
//            std::cout << "Target Location Longitude!!" << std::endl;
            break;
         }
         case 42:
         {
//            std::cout << "Target Location Elevation!!" << std::endl;
            break;
         }
         case 43:
         {
//            std::cout << "Target track gate width!!" << std::endl;
            break;
         }
         case 44:
         {
//            std::cout << "Target track gate height!!" << std::endl;
            break;
         }
         case 45:
         {
//            std::cout << "Target Error esitimate CE90!!" << std::endl;
            break;
         }
         case 46:
         {
//            std::cout << "Target Error esitimate LE90!!" << std::endl;
            break;
         }
         case 47:
         {
//            std::cout << "Generic Flag Data 01!!" << std::endl;
            break;
         }
         case 48:
         {
//            std::cout << "Security Local Dataset!!" << std::endl;
            break;
         }
         case 49:
         {
//            std::cout << "Differential pressure!!" << std::endl;
            break;
         }
         case 50:
         {
//            std::cout << "Platform angle of attack!!" << std::endl;
            break;
         }
         case 51:
         {
//            std::cout << "Platform vertical speed!!" << std::endl;
            break;
         }
         case 52:
         {
//            std::cout << "Platform side slip angle!!" << std::endl;
            break;
         }
         case 53:
         {
            // airfiled barometrc pressure
            break;
         }
         case 54:
         {
            // airfiled elevation
            break;
         }
         case 55:
         {
            // relative humidity
            break;
         }
         case 56:
         {
            // platform ground speed
            break;
         }
         case 57:
         {
            // ground range
            break;
         }
         case 58:
         {
            // platform fuel remaining
            break;
         }
         case 59:
         {
            // platform call sign
            break;
         }
         case 60:
         {
            // weapon load
            break;
         }
         case 61:
         {
            // weapon fired
            break;
         }
         case 62:
         {
            // Laser PRF Code
            break;
         }
         case 63:
         {
            //Sensor Field of View Name
            break;
         }
         case 64:
         {
            // platform magnetic heading
            break;
         }
         case 65:
         {
            // UAS LDS Version Number
            break;
         }
         case 66:
         {
            // target locatio covariance matrix
            break;
         }
         case 67:
         {
            // alternate platform latitude
            break;
         }
         case 68:
         {
            // alternate platform longitude
            break;
         }
         case 69:
         {
            // alternate platform altitude
            break;
         }
         case 70:
         {
            // alternate platform name
            break;
         }
         case 71:
         {
            // alternate platform heading
            break;
         }
         case 72:
         {
//            std::cout << "EVENT START TIME!!" << std::endl;
            break;
         }
         default:
         {
//            std::cout << "KEY NOT HANDLED "  <<key  << std::endl;  
            break;
         }
      }
      idx +=length;
   }
}

std::ostream& ossimPredatorKlvTable::print(std::ostream& out)const
{
   klvMapType::const_iterator iter = theKlvParameters.begin();
   while(iter!=theKlvParameters.end())
   {
      out << OSSIM_PREDATOR_UDS_TABLE[(*iter).second.theId].theName << ": " << valueAsString((*iter).first) << std::endl;
      ++iter;
   }
   
   return out;
}

