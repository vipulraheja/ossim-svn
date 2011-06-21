#include <oms/DataInfo.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimRegExp.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimContainerProperty.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/projection/ossimProjectionFactoryRegistry.h>
#include <ossim/projection/ossimProjection.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimEcefPoint.h>
#include <ossim/base/ossimEcefVector.h>
#include <ossim/base/ossimGeoPolygon.h>
#include <ossim/base/ossimDate.h>
#include <ossim/support_data/ossimInfoFactoryRegistry.h>
#include <ossim/support_data/ossimInfoBase.h>

#ifdef OSSIM_PREDATOR_VIDEO_ENABLED
#include <ossimPredator/ossimPredatorVideo.h>
#include <ossimPredator/ossimPredatorKlvTable.h>
#endif
#include <sstream>
static ossimString monthToNumericString(const ossimString& month)
{
   ossimString result;
   if(month == "JAN")
   {
      result =  "01";
   }
   else if(month == "FEB")
   {
      result =  "02";
   }
   else if(month == "MAR")
   {
      result =  "03";
   }
   else if(month == "APR")
   {
      result =  "04";
   }
   else if(month == "MAY")
   {
      result =  "05";
   }
   else if(month == "JUN")
   {
      result =  "06";
   }
   else if(month == "JUL")
   {
      result =  "07";
   }
   else if(month == "AUG")
   {
      result =  "08";
   }
   else if(month == "SEP")
   {
      result =  "09";
   }
   else if(month == "OCT")
   {
      result =  "10";
   }
   else if(month == "NOV")
   {
      result =  "11";
   }
   else if(month == "DEC")
   {
      result =  "12";
   }
   
   return result;
}

static ossimString blankOutBinary(const ossimString& s)
{
   ossimString result;
   ossim_uint32 idx;
   for(idx = 0; idx < s.length(); ++idx)
   {
      int test = (int) s[idx];
      if((test >= 0x20) & (test <= 0x7e))
      {
         result += s[idx];
      }
      else
      {
         result += " ";
      }
   }
   
   return result;
}


class ossimXmlOutputKeywordList : public ossimKeywordlist
{
public:
   ossimXmlOutputKeywordList(bool includeMetadataTagName = false)
   :ossimKeywordlist(),
   m_includeMetadataTagName(includeMetadataTagName)
   {
   }
   virtual void writeToStream(std::ostream &out)const
   {
      ossimRefPtr<ossimXmlNode> metadata = new ossimXmlNode;
      metadata->setTag("metadata");
      ossimKeywordlist::KeywordMap::const_iterator iter = m_map.begin();
      while(iter != m_map.end())
      {
         ossimString path = iter->first;
         path = path.substitute(".", "/", true);
         replaceSpecialCharacters(path);
         std::vector<ossimString> splitValues;
         path.split(splitValues,"/");
         if(splitValues.size())
         {
            splitValues[splitValues.size()-1] = splitValues[splitValues.size()-1].downcase();
            ossim_uint32 idx = 0;
            for(idx = 0; idx < splitValues.size()-1;++idx)
            {
               splitValues[idx] = splitValues[idx].upcase();
            }
         }
         path.join(splitValues, "/");
         metadata->addNode(path.c_str(), iter->second);
         ++iter;
      }
      
      if(!m_includeMetadataTagName)
      {
         const ossimXmlNode::ChildListType& children = metadata->getChildNodes();
         ossimXmlNode::ChildListType::const_iterator iter = children.begin();
         while(iter != children.end())
         {
            out << *(iter->get());
            ++iter;
         }
         out << std::endl;
      }
      else 
      {
         out << *(metadata.get())<<std::endl;
      }
      
   }
   void replaceSpecialCharacters(ossimString& value)const
   {
      ossimString::iterator iter = value.begin();
      
      while(iter!=value.end())
      {
         if(!(isdigit(*iter) ||
              isalpha(*iter)||
              (*iter=='/')))
         {
            *iter = '_';
         }
         ++iter;
      }
   }
   bool m_includeMetadataTagName;
};

namespace oms
{
   class DataInfoPrivateData
   {
   public:
      ~DataInfoPrivateData()
      {
         clear();
      }
      void clear()
      {
         theFilename = "";
         theImageHandler = 0;
#ifdef OSSIM_PREDATOR_VIDEO_ENABLED
         
         thePredatorVideo = 0;
         thePredatorVideoFrameInfo = 0;
         theExternalVideoGeometryFile = "";
#endif
      }
      
      std::string formatName() const
      {
#ifdef OSSIM_PREDATOR_VIDEO_ENABLED
         
         if(thePredatorVideo.valid())
         {
            return "mpeg";
         }
         else
#endif
            if (theImageHandler.valid())
            {
               ossimString className = theImageHandler->getClassName();
               className = className.downcase();
               if (className.contains("dted"))
               {
                  return "dted";
               }
               else if (className.contains("tiff"))
               {
                  return "tiff";
               }
               else if (className.contains("generalraster"))
               {
                  return "general_raster";
               }
               else if (className.contains("jpeg"))
               {
                  return "jpeg";
               }
               else if (className.contains("png"))
               {
                  return "png";
               }
               else if (className.contains("nitf"))
               {
                  return "nitf";
               }
               else if (className.contains("srtm"))
               {
                  return "srtm";
               }
               else if (className.contains("nui"))
               {
                  return "nui";
               }
               else if (className.contains("doqq"))
               {
                  return "doqq";
               }
               else if (className.contains("usgsdem"))
               {
                  return "usgsdem";
               }
               else if (className.contains("ccf"))
               {
                  return "ccf";
               }
               else if (className.contains("cibcadrgtile"))
               {
                  if (theImageHandler->getNumberOfOutputBands() == 1)
                  {
                     return "cib";
                  }
                  return "cadrg";
               }
               else if (className.contains("adrgtile"))
               {
                  return "adrg";
               }
               else if (className.contains("erstile"))
               {
                  return "ers";
               }
               
               else if (className.contains("landsattile"))
               {
                  ossimString file = theImageHandler->getFilename();
                  file = file.downcase();
                  if (file.contains("header"))
                  {
                     return "lansat5";
                  }
                  return "landsat7";
               }
               else if (className.contains("gdaltilesource"))
               {
                  ossimString driverName =
                  theImageHandler->getPropertyValueAsString(
                                                            "driver_short_name");
                  driverName = driverName.downcase();
                  if (driverName.contains("hfa"))
                  {
                     return "imagine_hfa";
                  }
                  else if (driverName.contains("jp2"))
                  {
                     return "j2k";
                  }
                  else if (driverName.contains("jpeg2000"))
                  {
                     return "j2k";
                  }
                  else if (driverName.contains("hdf4"))
                  {
                     return "hdf4";
                  }
                  else if (driverName.contains("hdf5"))
                  {
                     return "hdf5";
                  }
                  else if (driverName.contains("bmp"))
                  {
                     return "bmp";
                  }
                  else if (driverName.contains("gif"))
                  {
                     return "gif";
                  }
                  else if (driverName.contains("aaigrid"))
                  {
                     return "aaigrid";
                  }
                  else if (driverName.contains("aig"))
                  {
                     return "aig";
                  }
                  else if (driverName.contains("doq"))
                  {
                     return "doqq";
                  }
               }
               else if (className.contains("tfrd"))
               {
                  return "tfrd";
               }
               else 
               {
                  ossimFilename file(theImageHandler.valid()?theImageHandler->getFilename():"");
                  
                  ossimString ext = file.ext();
                  ext = ext.downcase();
                  if(ext == "jp2")
                  {
                     return "jpeg2000";
                  }
                  else if(ext == "sid")
                  {
                     return "mrsid";
                  }
                  else if(ext == "dem")
                  {
                     return "usgsdem";
                  }
               }
            }
         return "unspecified";
      }
      ossimFilename theFilename;
      ossimRefPtr<ossimImageHandler> theImageHandler;
#ifdef OSSIM_PREDATOR_VIDEO_ENABLED
      ossimRefPtr<ossimPredatorVideo> thePredatorVideo;
      ossimRefPtr<ossimPredatorVideo::FrameInfo> thePredatorVideoFrameInfo;
      ossimFilename                              theExternalVideoGeometryFile;
#endif
   };
}

oms::DataInfo::DataInfo() :
thePrivateData(new oms::DataInfoPrivateData)
{
}

oms::DataInfo::~DataInfo()
{
   if (thePrivateData)
   {
      delete thePrivateData;
      thePrivateData = 0;
   }
}
static bool canCheckVideo(const ossimFilename& file)
{
   ossimString ext = file.ext();
   ext = ext.downcase();
   return((ext == "mpg") ||
          (ext == "swf") ||
          (ext == "mpeg") ||
          (ext == "flv")||
          (ext == "avi")||
          (ext == "mp4"));
}

bool oms::DataInfo::open(const std::string& file, bool failIfNoGeometryFlag)
{
   bool result = false;
   
   thePrivateData->clear();
   thePrivateData->theFilename = ossimFilename(file);
   thePrivateData->theImageHandler
   = ossimImageHandlerRegistry::instance()->open(
                                                 thePrivateData->theFilename);
   if (thePrivateData->theImageHandler.valid() == true)
   {
      // Do not do shapes for now.
      if ( (! thePrivateData->theImageHandler->
            getClassName().contains("Ogr") ) &&
          (! thePrivateData->theImageHandler->
           getClassName().contains("ossimVpf")))
      {
         if(failIfNoGeometryFlag)
         {
            ossimRefPtr<ossimImageGeometry> geom = thePrivateData->theImageHandler->getImageGeometry();
            if(geom.valid()&&geom->getProjection())
            {
               result = true;
            }
         }
         else
         {
            result = true;
         }
      }
   }
   else
   {
#ifdef OSSIM_PREDATOR_VIDEO_ENABLED
      if(canCheckVideo(thePrivateData->theFilename) )
      {
         thePrivateData->thePredatorVideo = new ossimPredatorVideo();
         if(thePrivateData->thePredatorVideo->open(
                                                   thePrivateData->theFilename))
         {
            ossimFilename externalGeom = thePrivateData->theFilename;
            externalGeom = externalGeom.setExtension("xml");
            
            if(!externalGeom.exists())
            {
               // check for the first 10 secondsfor a klv.
               // If no KLV then done
               //
               ossim_uint32 frameMax = (thePrivateData->thePredatorVideo->videoFrameRate()*
                                        (ossim::min(10.0, thePrivateData->thePredatorVideo->duration())));
               ossim_uint32 idx = 0;
               for(idx=0;((idx < frameMax)&&!(thePrivateData->thePredatorVideoFrameInfo.valid()));++idx)
               {
                  ossimRefPtr<ossimPredatorVideo::FrameInfo> frameInfo = thePrivateData->thePredatorVideo->nextFrame();
                  if(frameInfo.valid())
                  {
                     if(frameInfo->klvTable())
                     {
                        thePrivateData->thePredatorVideoFrameInfo = frameInfo;
                        //  std::cout << frameInfo->klvTable()->print(std::cout) << std::endl;
                     }
                  }
                  else
                  {
                     break;
                  }
               }
               if(thePrivateData->thePredatorVideoFrameInfo.valid())
               {
                  result = true;
               }
            }
            else
            {
               thePrivateData->theExternalVideoGeometryFile = externalGeom;
               result = true;
            }
         }
      }
#endif
      
   }
   
   if (result == false)
   {
      thePrivateData->clear();
   }
   //   std::cout << "OPEN FILE? " << result << ", " << file << std::endl;
   
   return result;
}

void oms::DataInfo::close()
{
   if (thePrivateData)
   {
      thePrivateData->clear();
   }
}

void appendDateRange(std::string& outputString, const ossimDate& startDate,
                     const ossimDate& endDate, const std::string& indentation,
                     const std::string& separator)
{
   std::ostringstream outStart, outEnd;
   double roundStart = ((int) ((startDate.getSec()
                                + startDate.getFractionalSecond()) * 1000)) / 1000.0;
   double roundEnd =
   ((int) ((endDate.getSec() + endDate.getFractionalSecond()) * 1000))
   / 1000.0;
   outStart << std::setw(4) << std::setfill('0') << startDate.getYear() << "-"
   << std::setw(2) << std::setfill('0') << startDate.getMonth() << "-"
   << std::setw(2) << std::setfill('0') << startDate.getDay() << "T"
   << std::setw(2) << std::setfill('0') << startDate.getHour() << ":"
   << std::setw(2) << std::setfill('0') << startDate.getMin() << ":"
   << std::setw(2) << std::setfill('0') << roundStart << "Z";
   
   outEnd << std::setw(4) << std::setfill('0') << endDate.getYear() << "-"
   << std::setw(2) << std::setfill('0') << endDate.getMonth() << "-"
   << std::setw(2) << std::setfill('0') << endDate.getDay() << "T"
   << std::setw(2) << std::setfill('0') << endDate.getHour() << ":"
   << std::setw(2) << std::setfill('0') << endDate.getMin() << ":"
   << std::setw(2) << std::setfill('0') << roundEnd << "Z";
   
   outputString += (indentation + "<TimeSpan>" + separator + indentation
                    + "   <begin>" + outStart.str() + "</begin>" + separator
                    + indentation + "   <end>" + outEnd.str() + "</end>" + separator
                    + indentation + "</TimeSpan>" + separator);
   
}
#ifdef OSSIM_PREDATOR_VIDEO_ENABLED

void appendToMultiGeometry(std::string& /*result*/,
                           ossimRefPtr<ossimPredatorKlvTable> /*klvTable*/,
                           const std::string& /*indentation*/,
                           const std::string& /*separator*/)
{
   
}

void appendVideoGeom(std::string& result,
                     ossimRefPtr<ossimPredatorKlvTable> klvTable,
                     const std::string& indentation,
                     const std::string& separator,
                     const std::string& klvnumber)
{
   ossimGpt wgs84;
   ossimGpt ul;
   ossimGpt ur;
   ossimGpt lr;
   ossimGpt ll;
   ossimString groundGeometry;
   ossimString obliquityAngle;
   ossimString sensorPosition;
   ossimString horizontalFOV;
   ossimString verticalFOV;
   ossimString elevation;
   ossimString sensorDistance;
   
   if(!klvTable->getCornerPoints(ul, ur, lr, ll))
   {
#if 1
      ossim_float64 lat, lon, elev;
      if(klvTable->getFrameCenter(lat, lon, elev))
      {
         ul.latd(lat);
         ul.lond(lon);
         ur = ul;
         lr = ul;
         ll = ul;
      }
      else if(klvTable->getSensorPosition(lat, lon, elev))
      {
         ul.latd(lat);
         ul.lond(lon);
         ur = ul;
         lr = ul;
         ll = ul;
      }
      else
      {
         return;
      }
#else
      return;
#endif
   }
   ul.changeDatum(wgs84.datum());
   ur.changeDatum(wgs84.datum());
   lr.changeDatum(wgs84.datum());
   ll.changeDatum(wgs84.datum());
   // RPALKO -modified to the end of appendVideoGeom
   ossimGeoPolygon geoPoly;
   geoPoly.addPoint(ul);
   geoPoly.addPoint(ur);
   geoPoly.addPoint(lr);
   geoPoly.addPoint(ll);
   double degarea = ossim::abs(geoPoly.area());
   
   groundGeometry+=("POLYGON(("
                    +ossimString::toString(ul.lond())+" "
                    +ossimString::toString(ul.latd())+","
                    +ossimString::toString(ur.lond())+" "
                    +ossimString::toString(ur.latd())+","
                    +ossimString::toString(lr.lond())+" "
                    +ossimString::toString(lr.latd())+","
                    +ossimString::toString(ll.lond())+" "
                    +ossimString::toString(ll.latd())+","
                    +ossimString::toString(ul.lond())+" "
                    +ossimString::toString(ul.latd())+" "
                    +"))"); 
   
   ossim_float32 oangle;
   if(klvTable->getObliquityAngle(oangle)) { 
      obliquityAngle+=(ossimString::toString(oangle));
   }
   else {
      obliquityAngle = "";
   }
   
   ossim_float32 hfov;
   if(klvTable->getHorizontalFieldOfView(hfov)) { 
      horizontalFOV+=(ossimString::toString(hfov));
   }
   else {
      horizontalFOV = "";
   }
   
   ossim_float32 vfov;
   if(klvTable->getVerticalFieldOfView(vfov)) {
      verticalFOV+=(ossimString::toString(vfov));
   } 
   else { 
      verticalFOV = ""; 
   }
   
   ossim_float64 latsp, lonsp, elevsp;
   ossimGpt llsp;
   
   if (klvTable->getSensorPosition(latsp, lonsp, elevsp))
   {
      llsp.latd(latsp);
      llsp.lond(lonsp);
      llsp.changeDatum(wgs84.datum());
      sensorPosition+=("POINT(" 
                       +ossimString::toString(llsp.lond())+" "
                       +ossimString::toString(llsp.latd())
                       +")");
      elevation+=(ossimString::toString(elevsp));
   }
   // Convert degrees squared area to meters squared based on sensor position 
   ossimDpt sensormpd = llsp.metersPerDegree(); 
   ossim_float64 mtrsperlat = sensormpd.y; 
   ossim_float64 mtrsperlon = sensormpd.x;
   double mtrssqdperdegsqd = mtrsperlat * mtrsperlon;
   double area = degarea * mtrssqdperdegsqd;
   ossimString geoArea;
   geoArea+=(ossimString::toString(area));
   
   // using the distance from the sensor to the frame to weed out cases where we have absolutely bogus coordinates in the Predator video
   ossimGpt closept;
   // Use the center of the bottom of the frame as the closest point.
   closept.latd(ll.latd() - ((ll.latd() - lr.latd()) * 0.5));
   closept.lond(ll.lond() - ((ll.lond() - lr.lond()) * 0.5));
   
   ossimEcefPoint start(llsp);
   ossimEcefPoint end(closept);
   
   ossim_float64 distance = (end-start).length();
//   std::cout << "*************************** " << distance/elevation.toDouble() << std::endl;
#if 0   
   ossim_float64 distance = std::pow(std::pow(((llsp.lond() - 
                                                closept.lond()) * mtrsperlon), 2) + std::pow(((llsp.latd() -
                                                                                               closept.latd()) * mtrsperlat), 2), 0.5);
#endif   
   sensorDistance+=(ossimString::toString(distance));
   ossimString videostartutc;
   if (!klvTable->valueAsString(videostartutc, 
                                KLV_KEY_VIDEO_START_DATE_TIME_UTC)) { 
      videostartutc = ""; 
   }
   result += indentation+"<groundGeom area=\""+geoArea.string()+"\" elevation=\""
      +elevation.string()+"\" klvnumber=\""+klvnumber+"\" horizontalFOV=\""
      +horizontalFOV.string()+"\" verticalFOV=\""+verticalFOV.string()+"\" sensorDistance=\""
      +sensorDistance.string()+"\" sensorPosition=\""+sensorPosition.string()+"\" videoStartUTC=\""
      +videostartutc.string()+"\" obliquityAngle=\""+obliquityAngle.string()
      +"\" srs=\"epsg:4326\">"+groundGeometry.string()+"</groundGeom>"+separator;
}
#endif

std::string oms::DataInfo::getInfo() const
{
   std::string result = "";
   if (!thePrivateData)
      return result;
   if (thePrivateData->theImageHandler.valid())
   {
      result += "<oms>\n";
      result += "   <dataSets>\n";
      result += "      <RasterDataSet>\n";
      result += "         <fileObjects>\n";
      result += "            <RasterFile type=\"main\" format=\""
      + thePrivateData->formatName() + "\">\n";
      result += "                <name>" + thePrivateData->theFilename.string() + "</name>\n";
      result += "            </RasterFile>\n";
      result += "         </fileObjects>\n";
      result += "         <rasterEntries>\n";
      appendRasterEntries(result, "            ", "\n");
      result += "         </rasterEntries>\n";
      appendRasterDataSetMetadata(result, "         ", "\n");
      result += "      </RasterDataSet>\n";
      result += "   </dataSets>\n";
      result += "</oms>\n";
   }
#ifdef OSSIM_PREDATOR_VIDEO_ENABLED
   else if(!thePrivateData->theExternalVideoGeometryFile.empty()&&
           thePrivateData->theExternalVideoGeometryFile.exists())
   {
      std::vector<char> buf;
      ossim_uint64 filesize = thePrivateData->theExternalVideoGeometryFile.fileSize();
      if(filesize>0)
      {
         ifstream in(thePrivateData->theExternalVideoGeometryFile.c_str(), std::ios::in|std::ios::binary);
         if(in.good())
         {
            buf.resize(filesize);
            in.read(&buf.front(), filesize);
            
            result = std::string(buf.begin(), buf.end());
         }
      }
   }
   else if(thePrivateData->thePredatorVideoFrameInfo.valid())
   {
      
      ossimDate startDate;
      ossimDate endDate;
      if(thePrivateData->thePredatorVideoFrameInfo->klvTable()->getDate(startDate, true))
      {
         endDate = startDate;
         endDate.addSeconds(thePrivateData->thePredatorVideo->duration());
      }
      result += "<oms>\n";
      result += "   <dataSets>\n";
      result += "      <VideoDataSet>\n";
      result += "         <fileObjects>\n";
      result += "            <VideoFile type=\"main\" format=\""+thePrivateData->formatName()+"\">\n";
      result += "                <name>"+thePrivateData->theFilename.string()+"</name>\n";
      result += "            </VideoFile>\n";
      result += "         </fileObjects>\n";
      result += "         <width>"+ossimString::toString(thePrivateData->thePredatorVideo->imageWidth()).string()+"</width>\n";
      result += "         <height>"+ossimString::toString(thePrivateData->thePredatorVideo->imageHeight()).string()+"</height>\n";
      
      // RPALKO - replaced 1 line with everything to END RPALKO
      result += "         <spatialMetadata>\n"; 
      ossim_uint32 idx = 0;
      // safer to rewind
      thePrivateData->thePredatorVideo->rewind();
      ossimRefPtr<ossimPredatorVideo::KlvInfo> klvInfo = thePrivateData->thePredatorVideo->nextKlv();
      while (klvInfo.valid() && klvInfo->table()) 
      {
         std::string klvnumber = ossimString::toString(idx);
         appendVideoGeom(result, klvInfo->table(),"                  ", "\n", klvnumber);
         klvInfo = thePrivateData->thePredatorVideo->nextKlv();
         idx++; 
      }
      result += "        </spatialMetadata>\n";
      appendDateRange(result, startDate, endDate, "         ", "\n");
      appendVideoDataSetMetadata(result, "         ", "\n");
      result += "      </VideoDataSet>\n";
      result += "   </dataSets>\n";
      result += "</oms>\n";
   }
#endif
   return result;
}

bool oms::DataInfo::isVideo()const
{
   if(!thePrivateData) return false;
#ifdef OSSIM_PREDATOR_VIDEO_ENABLED
   return thePrivateData->thePredatorVideo.valid();
#else
   return false;
#endif
}

bool oms::DataInfo::isImagery()const
{
   if(!thePrivateData) return false;
   return thePrivateData->theImageHandler.valid();
}


std::string oms::DataInfo::getImageInfo(int entry)
{
   std::string result = "";
   if (!thePrivateData)
      return result;
   if(!thePrivateData->theImageHandler.valid())
   {
      return result;
   }
   if(!thePrivateData->theImageHandler->setCurrentEntry(entry)) return result;

   if (thePrivateData->theImageHandler.valid())
   {
      result += "<oms>\n";
      result += "   <dataSets>\n";
      result += "      <RasterDataSet>\n";
      result += "         <fileObjects>\n";
      result += "            <RasterFile type=\"main\" format=\""
      + thePrivateData->formatName() + "\">\n";
      result += "                <name>" + thePrivateData->theFilename.string() + "</name>\n";
      result += "            </RasterFile>\n";
      result += "         </fileObjects>\n";
      result += "         <rasterEntries>\n";
      if(entry < 0)
      {
         appendRasterEntries(result, "            ", "\n");
      }
      else 
      {
         appendRasterEntry(result, "            ", "\n"); 
      }
//      appendRasterEntryDateTime(result, "            ", "\n");
      
      result += "         </rasterEntries>\n";
      appendRasterDataSetMetadata(result, "         ", "\n");
      result += "      </RasterDataSet>\n";
      result += "   </dataSets>\n";
      result += "</oms>\n";
   }

   return result;
      
}

std::string oms::DataInfo::getVideoInfo()
{
   std::string result;
#ifdef OSSIM_PREDATOR_VIDEO_ENABLED
   if(!thePrivateData->theExternalVideoGeometryFile.empty()&&
           thePrivateData->theExternalVideoGeometryFile.exists())
   {
      std::vector<char> buf;
      ossim_uint64 filesize = thePrivateData->theExternalVideoGeometryFile.fileSize();
      if(filesize>0)
      {
         ifstream in(thePrivateData->theExternalVideoGeometryFile.c_str(), std::ios::in|std::ios::binary);
         if(in.good())
         {
            buf.resize(filesize);
            in.read(&buf.front(), filesize);
            
            result = std::string(buf.begin(), buf.end());
         }
      }
   }
   else if(thePrivateData->thePredatorVideoFrameInfo.valid())
   {
      
      ossimDate startDate;
      ossimDate endDate;
      if(thePrivateData->thePredatorVideoFrameInfo->klvTable()->getDate(startDate, true))
      {
         endDate = startDate;
         endDate.addSeconds(thePrivateData->thePredatorVideo->duration());
      }
      result += "<oms>\n";
      result += "   <dataSets>\n";
      result += "      <VideoDataSet>\n";
      result += "         <fileObjects>\n";
      result += "            <VideoFile type=\"main\" format=\""+thePrivateData->formatName()+"\">\n";
      result += "                <name>"+thePrivateData->theFilename.string()+"</name>\n";
      result += "            </VideoFile>\n";
      result += "         </fileObjects>\n";
      result += "         <width>"+ossimString::toString(thePrivateData->thePredatorVideo->imageWidth()).string()+"</width>\n";
      result += "         <height>"+ossimString::toString(thePrivateData->thePredatorVideo->imageHeight()).string()+"</height>\n";
      
      // RPALKO - replaced 1 line with everything to END RPALKO
      result += "         <spatialMetadata>\n"; 
      ossim_uint32 idx = 0;
      // safer to rewind
      thePrivateData->thePredatorVideo->rewind();
      ossimRefPtr<ossimPredatorVideo::KlvInfo> klvInfo = thePrivateData->thePredatorVideo->nextKlv();
      while (klvInfo.valid() && klvInfo->table()) 
      {
         std::string klvnumber = ossimString::toString(idx);
         appendVideoGeom(result, klvInfo->table(),"                  ", "\n", klvnumber);
         klvInfo = thePrivateData->thePredatorVideo->nextKlv();
         idx++; 
      }
      result += "        </spatialMetadata>\n";
      appendDateRange(result, startDate, endDate, "         ", "\n");
      appendVideoDataSetMetadata(result, "         ", "\n");
      result += "      </VideoDataSet>\n";
      result += "   </dataSets>\n";
      result += "</oms>\n";
   }
#endif
   
   return result;
}


void oms::DataInfo::appendRasterEntry(std::string& outputString,
                                        const std::string& indentation, const std::string& separator) const
{
   
   ossimIrect rect = thePrivateData->theImageHandler->getBoundingRect();
   outputString += indentation + "<RasterEntry>" + separator;
   appendAssociatedRasterEntryFileObjects(outputString, indentation
                                          + "   ", separator);
   outputString += indentation + "   <entryId>" + ossimString::toString(thePrivateData->theImageHandler->getCurrentEntry()).string() + "</entryId>" + separator;
   outputString += indentation + "   <width>" + ossimString::toString(
      rect.width()).string() + "</width>" + separator;
   outputString += indentation + "   <height>" + ossimString::toString(
      rect.height()).string() + "</height>" + separator;
   outputString
   += indentation + "   <numberOfBands>"
   + ossimString::toString(
      thePrivateData->theImageHandler->getNumberOfInputBands()).string()
   + "</numberOfBands>" + separator;
   outputString
   += indentation + "   <numberOfResLevels>"
      + ossimString::toString(
         thePrivateData->theImageHandler->getNumberOfDecimationLevels()).string()
   + "</numberOfResLevels>" + separator;
   appendBitDepthAndDataType(outputString, indentation + "   ", separator);
   appendGeometryInformation(outputString, indentation + "   ", separator);
//   appendRasterEntryDateTime(outputString, indentation + "   ", separator);
   appendRasterEntryMetadata(outputString, indentation + "   ", "\n");
   
   outputString += indentation + "</RasterEntry>" + separator;
   
}

void oms::DataInfo::appendRasterEntries(std::string& outputString,
                                        const std::string& indentation, const std::string& separator) const
{
   ossim_uint32 numberOfEntries =
   thePrivateData->theImageHandler->getNumberOfEntries();
   ossim_uint32 idx = 0;
   
   for (idx = 0; idx < numberOfEntries; ++idx)
   {
      if(thePrivateData->theImageHandler->setCurrentEntry(idx))
      {
         appendRasterEntry(outputString, indentation, separator);
      }
   }
}

void oms::DataInfo::appendAssociatedRasterEntryFileObjects(
                                                           std::string& outputString, const std::string& indentation,
                                                           const std::string& separator) const
{
   ossimFilename kmlFile(thePrivateData->theImageHandler->getFilename());
   ossimFilename overviewFile =
   thePrivateData->theImageHandler->createDefaultOverviewFilename();
   ossimFilename overview2File =
   thePrivateData->theImageHandler->getFilename() + ".ovr";
   ossimFilename histogramFile =
   thePrivateData->theImageHandler->createDefaultHistogramFilename();
   ossimFilename
   validVerticesFile =
   thePrivateData->theImageHandler->createDefaultValidVerticesFilename();
   ossimFilename geomFile =
   thePrivateData->theImageHandler->createDefaultGeometryFilename();
   ossimFilename metadataFile =
   thePrivateData->theImageHandler->createDefaultMetadataFilename();
   
   // we will only support for now kml files associated at the entire file level and
   // not individual entries.
   //
   kmlFile = kmlFile.setExtension("kml");
   
   bool associatedFilesFlag = (overviewFile.exists() || overview2File.exists() || histogramFile.exists()
                               || validVerticesFile.exists() || geomFile.exists()
                               || metadataFile.exists()||kmlFile.exists());
   if (associatedFilesFlag)
   {
      outputString += indentation + "<fileObjects>" + separator;
      
      if (overviewFile.exists())
      {
         outputString += indentation
            + "   <RasterEntryFile type=\"overview\">" + separator
            + indentation + "      <name>" + overviewFile.string() + "</name>"
            + separator + indentation + "   </RasterEntryFile>"
            + separator;
      }
      else if (overview2File.exists())
      {
         outputString += indentation
            + "   <RasterEntryFile type=\"overview\">" + separator
            + indentation + "      <name>" + overview2File.string() + "</name>"
            + separator + indentation + "   </RasterEntryFile>"
            + separator;
      }
      if (histogramFile.exists())
         if (histogramFile.exists())
         {
            outputString += indentation
               + "   <RasterEntryFile type=\"histogram\">" + separator
               + indentation + "      <name>" + histogramFile.string() + "</name>"
               + separator + indentation + "   </RasterEntryFile>"
               + separator;
         }
      if (validVerticesFile.exists())
      {
         outputString += indentation
            + "   <RasterEntryFile type=\"valid_vertices\">"
            + separator + indentation + "      <name>"
            + validVerticesFile.string() + "</name>" + separator + indentation
            + "   </RasterEntryFile>" + separator;
      }
      if (geomFile.exists())
      {
         outputString += indentation + "   <RasterEntryFile type=\"geom\">"
            + separator + indentation + "      <name>" + geomFile.string()
            + "</name>" + separator + indentation
            + "   </RasterEntryFile>" + separator;
      }
      if (metadataFile.exists())
      {
         outputString += indentation + "   <RasterEntryFile type=\"omd\">"
            + separator + indentation + "      <name>" + metadataFile.string()
            + "</name>" + separator + indentation
            + "   </RasterEntryFile>" + separator;
      }
      if (kmlFile.exists())
      {
         outputString += indentation
            + "   <RasterEntryFile type=\"kml\">" + separator
            + indentation + "      <name>" + kmlFile.string() + "</name>"
            + separator + indentation + "   </RasterEntryFile>"
            + separator;
      }
      outputString += indentation + "</fileObjects>" + separator;
   }
}

void oms::DataInfo::appendBitDepthAndDataType(std::string& outputString,
                                              const std::string& indentation, const std::string& separator) const
{
   ossim_uint32 bits = 0;
   ossimString dataType;
   switch (thePrivateData->theImageHandler->getOutputScalarType())
   {
      case OSSIM_UINT8:
      {
         bits = 8;
         dataType = "uint";
         break;
      }
      case OSSIM_SINT8:
      {
         bits = 8;
         dataType = "sint";
         break;
      }
      case OSSIM_UINT16:
      {
         bits = 16;
         dataType = "uint";
         break;
      }
      case OSSIM_SINT16:
      {
         bits = 16;
         dataType = "sint";
         break;
      }
      case OSSIM_USHORT11:
      {
         bits = 11;
         dataType = "uint";
         break;
      }
      case OSSIM_SINT32:
      {
         bits = 32;
         dataType = "sint";
         break;
      }
      case OSSIM_UINT32:
      {
         bits = 32;
         dataType = "uint";
         break;
      }
      case OSSIM_FLOAT32:
      {
         bits = 32;
         dataType = "float";
         break;
      }
      case OSSIM_FLOAT64:
      {
         bits = 64;
         dataType = "float";
         break;
      }
      default:
      {
         dataType = "unknown";
         break;
      }
   }
   outputString += indentation + "<bitDepth>" + ossimString::toString(bits).string()
      + "</bitDepth>" + separator;
   outputString += indentation + "<dataType>" + dataType.string() + "</dataType>"
      + separator;
}

void oms::DataInfo::appendGeometryInformation(std::string& outputString,
                                              const std::string& indentation, const std::string& separator) const
{
   ossimIrect rect = thePrivateData->theImageHandler->getBoundingRect();
   ossimKeywordlist kwl;
   ossimRefPtr<ossimImageGeometry> geom = thePrivateData->theImageHandler->getImageGeometry();
   ossimGpt wgs84;
   ossimString groundGeometry;
   ossimString validGroundGeometry;
   
   if (geom.valid()&&geom->getProjection())
   {
      ossimDpt gsd = geom->getMetersPerPixel();
      outputString += indentation + "<gsd unit=\"meters\" dx=\"" +
         ossimString::toString(gsd.x,15).string() + "\" dy=\"" +
         ossimString::toString(gsd.y,15).string() + "\"/>" + separator;
      ossimGpt ul;
      ossimGpt ur;
      ossimGpt lr;
      ossimGpt ll;
      geom->localToWorld(rect.ul(), ul);
      geom->localToWorld(rect.ur(), ur);
      geom->localToWorld(rect.lr(), lr);
      geom->localToWorld(rect.ll(), ll);
      
      if (ul.isLatNan() || ul.isLonNan() || ur.isLatNan() || ur.isLonNan()
          || lr.isLatNan() || lr.isLonNan() || ll.isLatNan()
          || ll.isLonNan())
      {
         return;
      }
      ul.changeDatum(wgs84.datum());
      ur.changeDatum(wgs84.datum());
      lr.changeDatum(wgs84.datum());
      ll.changeDatum(wgs84.datum());
      
      groundGeometry += ("POLYGON((" + ossimString::toString(ul.lond()) + " "
                         + ossimString::toString(ul.latd()) + ","
                         + ossimString::toString(ur.lond()) + " "
                         + ossimString::toString(ur.latd()) + ","
                         + ossimString::toString(lr.lond()) + " "
                         + ossimString::toString(lr.latd()) + ","
                         + ossimString::toString(ll.lond()) + " "
                         + ossimString::toString(ll.latd()) + ","
                         + ossimString::toString(ul.lond()) + " "
                         + ossimString::toString(ul.latd()) + "))");
      outputString += indentation + "<groundGeom srs=\"epsg:4326\">"
         + groundGeometry.string() + "</groundGeom>" + separator;
      
      outputString += indentation + "<TiePointSet version='1'>" + separator;
      outputString += indentation + "   " + "<Image>" + separator;
      outputString += indentation + "      " + "<coordinates>";
      outputString += ossimString::toString(rect.ul().x).string() + "," +
         ossimString::toString(rect.ul().y).string() + " ";
      outputString += ossimString::toString(rect.ur().x).string() + "," +
         ossimString::toString(rect.ur().y).string() + " ";
      outputString += ossimString::toString(rect.lr().x).string() + "," +
         ossimString::toString(rect.lr().y).string() + " ";
      outputString += ossimString::toString(rect.ll().x).string() + "," +
         ossimString::toString(rect.ll().y).string();
      outputString += "</coordinates>" + separator;
      outputString += indentation + "   " + "</Image>" + separator;
      outputString += indentation + "   " + "<Ground>" + separator;
      outputString += indentation + "      " + "<coordinates>";
      outputString += ossimString::toString(ul.lond()).string() + "," +
         ossimString::toString(ul.latd()).string() + " ";
      outputString += ossimString::toString(ur.lond()).string() + "," +
         ossimString::toString(ur.latd()).string() + " ";
      outputString += ossimString::toString(lr.lond()).string() + "," +
         ossimString::toString(lr.latd()).string() + " ";
      outputString += ossimString::toString(ll.lond()).string() + "," +
         ossimString::toString(ll.latd()).string();
      outputString += "</coordinates>" + separator;
      outputString += indentation + "   " + "</Ground>" + separator;
      outputString += indentation + "</TiePointSet>" + separator;
   }
}
void appendMetadataTag(ossimRefPtr<ossimProperty> property,
                       std::string& outputString, const std::string& indentation,
                       const std::string& separator)
{
   if (property.valid())
   {
      ossimContainerProperty* container =
      dynamic_cast<ossimContainerProperty*> (property.get());
      if (container)
      {
         ossim_uint32 idx = 0;
         ossim_uint32 n = container->getNumberOfProperties();
         if (container->getName() == "tags")
         {
            for (idx = 0; idx < n; ++idx)
            {
               ossimRefPtr<ossimProperty> prop = container->getProperty(
                                                                        idx);
               if (prop.valid())
               {
                  appendMetadataTag(prop.get(), outputString,
                                    indentation, separator);
               }
            }
         }
         else
         {
            ossimString containerName = container->getName();
            ossimString newIndentation = indentation + "   ";
            
            outputString += indentation + "<tag name=\"" + containerName.string()
               + "\">" + separator;
            
            ossimKeywordlist coeffs;
            
            for (idx = 0; idx < n; ++idx)
            {
               ossimRefPtr<ossimProperty> prop = container->getProperty(idx);
               if (prop.valid())
               {
                  ossimString childName = prop->getName();
                  
                  // Add some special handling for NITF coefficients
                  // Consolidate into a single tag
                  if (containerName == "RPC00B" && childName.match(
                                                                   ".*COEFF.*") != "")
                  {
                     coeffs.add(childName, prop->valueToString());
                  }
                  else
                  {
                     appendMetadataTag(prop.get(), outputString,
                                       newIndentation, separator);
                  }
               }
            }
            
            //  Add the consolidated coeffs, if they exist
            if (coeffs.getSize() > 0)
            {
               std::vector<ossimString> namedSet;
               
               namedSet.push_back("LINE_DEN");
               namedSet.push_back("LINE_NUM");
               namedSet.push_back("SAMP_DEN");
               namedSet.push_back("SAMP_NUM");
               
               for (int i = 0, size = namedSet.size(); i < size; i++)
               {
                  outputString += newIndentation.string();
                  outputString += "<tag name=\"" + namedSet[i].string() + "\">";
                  
                  std::vector<ossimString> namedCoeffs =
                  coeffs.findAllKeysThatContains(namedSet[i]);
                  
                  for (int j = 0, size = namedCoeffs.size(); j < size; j++)
                  {
                     outputString += namedCoeffs[j].afterRegExp(namedSet[i] + "_COEFF_").string();
                     
                     outputString += "=";
                     outputString += coeffs.find(namedCoeffs[j]);
                     
                     if (j < size - 1)
                        outputString += ", ";
                  }
                  
                  outputString += "</tag>";
                  outputString += separator;
               }
            }
            
            outputString += indentation + "</tag>" + separator;
         }
      }
      else
      {
         ossimString value = property->valueToString().trim();
         
         // Only add the tag if it has a value
         if (!value.empty())
         {
            outputString += indentation + "<tag name=\""
               + property->getName().string() + "\">" + value.string() + "</tag>"
               + separator;
         }
      }
   }
}

void oms::DataInfo::appendRasterDataSetMetadata(std::string& outputString,
                                                const std::string& indentation,
                                                const std::string& separator) const
{
   std::vector<ossimRefPtr<ossimProperty> > properties;
   thePrivateData->theImageHandler->getPropertyList(properties);
   if (properties.size())
   {
      ossim_uint32 idx = 0;
      for (idx = 0; idx < properties.size(); ++idx)
      {
         if (properties[idx]->getName() == "file_header")
         {
            outputString += indentation + "<metadata>" + separator;
            ossim_uint32 idx2 = 0;
            ossimContainerProperty
            * container =
            dynamic_cast<ossimContainerProperty*> (properties[idx].get());
            if (container)
            {
               ossim_uint32 n = container->getNumberOfProperties();
               for (idx2 = 0; idx2 < n; ++idx2)
               {
                  ossimRefPtr<ossimProperty> prop =
                  container->getProperty(idx2);
                  if (prop.valid())
                  {
                     appendMetadataTag(prop.get(), outputString,
                                       indentation + "   ", separator);
                  }
               }
            }
            outputString += indentation + "</metadata>" + separator;
         }
      }
   }
}

void oms::DataInfo::appendVideoDataSetMetadata(std::string& outputString,
                                               const std::string& indentation, const std::string& separator) const
{
#ifdef OSSIM_PREDATOR_VIDEO_ENABLED
   if(thePrivateData->thePredatorVideoFrameInfo.valid()&&
      thePrivateData->thePredatorVideoFrameInfo->klvTable())
   {
      ossimRefPtr<ossimPredatorKlvTable> klvTable = thePrivateData->thePredatorVideoFrameInfo->klvTable();
      ossimString value;
      ossimString securityClassification;
      //      ossimString grazingAngle;
      //      ossimString azimuthAngle;
      ossimString missionNumber;
      outputString += indentation + "<metadata>" + separator;
      if(klvTable->valueAsString(value, KLV_KEY_ORGANIZATIONAL_PROGRAM_NUMBER))
      {
         value = value.trim();
         if(!value.empty())
         {
            outputString += indentation + "   <organizationalProgramNumber>" +
               blankOutBinary(value).trim().string() + "</organizationalProgramNumber>" +
               separator; 
         }
      }
      if(klvTable->valueAsString(value, KLV_KEY_SECURITY_CLASSIFICATION))
      {
         value = value.trim();
         if(!value.empty())
         {
            value = value.downcase();
            if(value.contains("unclas"))
            {
               securityClassification = "U";
            }
            else if(value.contains("top"))
            {
               securityClassification = "T";
            }
            else if(value.contains("secret"))
            {
               securityClassification = "S";
            }
            else 
            {
               securityClassification = value;
            }
         }
      }
      if(klvTable->valueAsString(value, KLV_KEY_SECURITY_RELEASE_INSTRUCTIONS))
      {
         value = value.trim();
         if(!value.empty())
         {
            outputString += indentation + "   <releaseInstructions>" + value.string() +
               "</releaseInstructions>" + separator; 
         }
      }
      if(klvTable->valueAsString(value, KLV_KEY_SECURITY_CAVEATS))
      {
         value = value.trim();
         if(!value.empty())
         {
            outputString += indentation + "   <securityCaveats>" + value.string() +
               "</securityCaveats>" + separator; 
         }
      }
      if(klvTable->valueAsString(value, KLV_KEY_CLASSIFICATION_COMMENT))
      {
         value = value.trim();
         if(!value.empty())
         {
            outputString += indentation + "   <classificationComment>" + value.string() + "</classificationComment>" + separator; 
         }
      }
      if(klvTable->valueAsString(value, KLV_KEY_ORIGINAL_PRODUCER_NAME))
      {
         value = value.trim();
         if(!value.empty())
         {
            outputString += indentation + "   <originalProducerName>" + value.string() + "</originalProducerName>" + separator; 
         }
      }
      if(klvTable->valueAsString(value, KLV_KEY_IMAGE_SOURCE_SENSOR))
      {
         value = value.trim();
         if(!value.empty())
         {
            outputString += indentation + "   <imageSourceSensor>" + value.string() + "</imageSourceSensor>" + separator; 
         }
      }
      //      if(!klvTable->valueAsString(azimuthAngle, KLV_KEY_DEVICE_ABSOLUTE_HEADING))
      //      {
      //         if(!klvTable->valueAsString(azimuthAngle, KLV_KEY_ANGLE_TO_NORTH))
      //         {
      //            klvTable->valueAsString(azimuthAngle, KLV_KEY_PLATFORM_HEADING_ANGLE);
      //         }
      //      }
      //      if(klvTable->valueAsString(grazingAngle,KLV_KEY_OBLIQUITY_ANGLE))
      //      {
      //         grazingAngle = ossimString::toString(90.0 - grazingAngle.toDouble());
      //      }
      klvTable->valueAsString(missionNumber, KLV_KEY_MISSION_NUMBER);
      
      outputString += indentation + "   <securityClassification>" + securityClassification.string()
         + "</securityClassification>" + separator; 
      //      outputString += indentation + "   <azimuthAngle>" + azimuthAngle + "</azimuthAngle>" + separator; 
      //      outputString += indentation + "   <grazingAngle>" + grazingAngle + "</grazingAngle>" + separator; 
      outputString += indentation + "   <missionId>" + missionNumber.string() + "</missionId>" +
         separator; 
      outputString += indentation + "   <fileType>" + thePrivateData->formatName() +
         "</fileType>" + separator; 
      outputString += indentation + "   <filename>" + thePrivateData->theFilename.string() +
         "</filename>" + separator; 
      
#if 0
      outputString += indentation + "   <imageId>" + imageId + "</imageId>" + separator; 
      outputString += indentation + "   <sensorId>" + sensorId + "</sensorId>" + separator; 
      outputString += indentation + "   <countryCode>" + countryCode + "</countryCode>" + separator; 
      outputString += indentation + "   <imageCategory>" + imageCategory + "</imageCategory>" + separator; 
      outputString += indentation + "   <grazingAngle>" + grazingAngle + "</grazingAngle>" + separator; 
      outputString += indentation + "   <title>" + title + "</title>" + separator; 
      outputString += indentation + "   <organization>" + organization + "</organization>" + separator; 
      outputString += indentation + "   <description>" + description + "</description>" + separator; 
      outputString += indentation + "   <niirs>" + niirs + "</niirs>" + separator; 
      outputString += indentation + "   <fileType>" + thePrivateData->formatName() + "</fileType>" + separator; 
      outputString += indentation + "   <className>" + (thePrivateData->theImageHandler.valid()?thePrivateData->theImageHandler->getClassName():ossimString("")) + "</className>" + separator; 
#endif
      outputString += indentation + "</metadata>" + separator;
   }
#endif
}

static ossimString monthStringToNumberString(const ossimString& monthString)
{
   if (monthString == "jan")
   {
      return "01";
   }
   else if (monthString == "feb")
   {
      return "02";
   }
   else if (monthString == "mar")
   {
      return "03";
   }
   else if (monthString == "apr")
   {
      return "04";
   }
   else if (monthString == "may")
   {
      return "05";
   }
   else if (monthString == "jun")
   {
      return "06";
   }
   else if (monthString == "jul")
   {
      return "07";
   }
   else if (monthString == "aug")
   {
      return "08";
   }
   else if (monthString == "sep")
   {
      return "09";
   }
   else if (monthString == "oct")
   {
      return "10";
   }
   else if (monthString == "nov")
   {
      return "11";
   }
   else if (monthString == "dec")
   {
      return "12";
   }
   return "";
}

std::string oms::DataInfo::convertIdatimToXmlDate(const std::string& idatim) const
{
   ossimString result = "";
   
   if (idatim.size() == 14)
   {
      if (idatim[8] == 'Z')
      {
         
         ossimString day(idatim.begin(), idatim.begin() + 2);
         ossimString hour(idatim.begin() + 2, idatim.begin() + 4);
         ossimString m(idatim.begin() + 4, idatim.begin() + 6);
         ossimString sec(idatim.begin() + 6, idatim.begin() + 8);
         // skip one character for Zulu "Z" so go to index 9
         ossimString month(idatim.begin() + 9, idatim.begin() + 12);
         ossimString year(idatim.begin() + 12, idatim.begin() + 14);
         month = monthStringToNumberString(month.downcase());
         
         if (year.toUInt32() > 60)
         {
            result += "19";
         }
         else
         {
            result += "20";
         }
         result += year + "-";
         result += month + "-";
         result += day + "T";
         result += hour + ":";
         result += m + ":";
         result += sec + "Z";
      }
      else
      {
         ossimString year(idatim.begin(), idatim.begin() + 4);
         ossimString month(idatim.begin() + 4, idatim.begin() + 6);
         ossimString day(idatim.begin() + 6, idatim.begin() + 8);
         ossimString hour(idatim.begin() + 8, idatim.begin() + 10);
         ossimString m(idatim.begin() + 10, idatim.begin() + 12);
         ossimString sec(idatim.begin() + 12, idatim.begin() + 14);
         result += year + "-";
         result += month + "-";
         result += day + "T";
         result += hour + ":";
         result += m + ":";
         result += sec + "Z";
      }
   }
   
   return result;
}

std::string oms::DataInfo::convertAcqDateToXmlDate(const std::string& value) const
{
   if (value.size() == 8) // assume 4 character year 2 month and 2 day format
   {
      return (ossimString(value.begin(), value.begin() + 4) + "-"
              + ossimString(value.begin() + 4, value.begin() + 6) + "-"
              + ossimString(value.begin() + 6, value.begin() + 8));
   }
   if (value.size() == 14) // assume 4 character year 2 month and 2 day 2 hour 2 minute 2 seconds
   {
      return (ossimString(value.begin(), value.begin() + 4) + "-"
              + ossimString(value.begin() + 4, value.begin() + 6) + "-"
              + ossimString(value.begin() + 6, value.begin() + 8) + "T"
              + ossimString(value.begin() + 8, value.begin() + 10) + ":"
              + ossimString(value.begin() + 10, value.begin() + 12) + ":"
              + ossimString(value.begin() + 12, value.begin() + 14) + "Z");
   }
   return "";
}



void oms::DataInfo::appendRasterEntryDateTime(std::string& outputString,
                                              const std::string& indentation, const std::string& separator) const
{
   ossimRefPtr<ossimProperty> prop;
   ossimString dateValue =
   convertIdatimToXmlDate(
                          thePrivateData->theImageHandler->getPropertyValueAsString(
                                                                                    "idatim"));
   
   if (dateValue.empty())
   {
      dateValue = convertAcqDateToXmlDate(
                                          thePrivateData->theImageHandler->getPropertyValueAsString(
                                                                                                    "acquisition_date"));
   }
   // this part is better done in JAVA land and not here.  I will take this out for now
#if 0
   if(dateValue.empty()&&thePrivateData->theImageHandler.valid())
   {
      ossimString filename = thePrivateData->theImageHandler->getFilename();
      filename = filename.upcase();
      ossimRegExp regexp1("[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]");
      ossimRegExp regexp2("[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][T][0-9][0-9][0-9][0-9][0-9][0-9]");
      ossimRegExp regexp3("[0-9][0-9]-(JAN|FEB|MAR|APR|MAY|JUN|JUL|AUG|SEP|OCT|NOV|DEC)-[0-9][0-9][0-9][0-9]");
      ossimRegExp regexp4("[0-9][0-9][0-9][0-9]-(JAN|FEB|MAR|APR|MAY|JUN|JUL|AUG|SEP|OCT|NOV|DEC)-[0-9][0-9]");
      
     // lets try a pattern in the file name
      //
      ossimString month, day, year, hours="00", minutes="00", seconds="00";
      
      if(regexp1.find(filename.c_str()))
      {
         ossimString value(regexp1.match(0));
         year = value.substr(0, 4);
         month = value.substr(4, 2);
         day = value.substr(6, 2);
         hours = value.substr(8, 2);
         minutes = value.substr(10, 2);
         seconds = value.substr(12);
      }
      else if(regexp2.find(filename.c_str()))
      {
         ossimString value(regexp2.match(0));
         year = value.substr(0, 4);
         month = value.substr(4, 2);
         day = value.substr(6, 2);
         hours = value.substr(9, 2);
         minutes = value.substr(11, 2);
         seconds = value.substr(13);
      }
      else if(regexp3.find(filename.c_str()))
      {
         std::vector<ossimString> splitArray;
         ossimString value(regexp3.match(0));
         value.split(splitArray, "-");
         if(splitArray.size() >2)
         {
            month = monthToNumericString(splitArray[1]);
            day   = splitArray[0];
            year  = splitArray[2];
         }

      }
      else if(regexp4.find(filename.c_str()))
      {
         std::vector<ossimString> splitArray;
         ossimString value(regexp4.match(0));
         value.split(splitArray, "-");
         if(splitArray.size() >2)
         {
            month = monthToNumericString(splitArray[1]);
            day   = splitArray[2];
            year  = splitArray[0];
         }
      }
      
      if(!month.empty()&&!day.empty()&&!year.empty())
      {
         dateValue = year+"-"+month+"-"+day+"T" + hours + ":" + minutes + ":" + seconds +"Z";
      }
   }
#endif
   if (!dateValue.empty())
   {
      outputString += indentation + "<TimeStamp>" + separator;
      outputString += indentation + "   <when>" + dateValue.string() + "</when>" + separator;
      outputString += indentation + "</TimeStamp>" + separator;
   }
}

void oms::DataInfo::appendRasterEntryMetadata(std::string& outputString,
                                              const std::string& indentation, const std::string& separator) const
{
   ossimString dateValue = "";
   outputString += indentation + "<metadata>" + separator;
   ossimRefPtr<ossimInfoBase> info = ossimInfoFactoryRegistry::instance()->create(thePrivateData->theFilename);
   if(info.valid())
   {
      ossimString imageId;
      ossimString beNumber;
      ossimString imageRepresentation;
      ossimString targetId;
      ossimString productId;
      ossimString sensorId;
      ossimString missionId;
      ossimString countryCode;
      ossimString imageCategory;
      ossimString azimuthAngle;
      ossimString grazingAngle;
      ossimString securityClassification;
      ossimString title;
      ossimString organization;
      ossimString description;
      ossimString niirs;
      
      
      ossimKeywordlist kwl;
      ossimKeywordlist kwl2;
      ossimXmlOutputKeywordList kwl3;
      //      kwl.removeKeysThatMatch("[^.*image"+ossimString::toString(thePrivateData->theImageHandler->getCurrentEntry()) +
      //                              "]");
      info->getKeywordlist(kwl);
      kwl3.getMap() =  kwl.getMap();
      kwl3.removeKeysThatMatch(".*\\.image.*\\..*");
      kwl.extractKeysThatMatch(kwl2,".*\\.image"+ossimString::toString(thePrivateData->theImageHandler->getCurrentEntry()) + "\\..*");
      ossimKeywordlist::KeywordMap::iterator iter = kwl2.getMap().begin();
      while(iter != kwl2.getMap().end())
      {
         ossimString k = iter->first;
         
         k = k.substitute(".image"+ossimString::toString(thePrivateData->theImageHandler->getCurrentEntry()), "");
         kwl3.getMap().insert(make_pair(k.string(), iter->second));
         ++iter;
      }
      kwl.downcaseKeywords();
      kwl3.downcaseKeywords();
      
      if(kwl3.getSize()>0)
      {
         grazingAngle ="90.0";
         azimuthAngle ="0.0";
         ossimString imagePrefix = "image" + ossimString::toString(thePrivateData->theImageHandler->getCurrentEntry()) + ".";
         
         if(kwl3.find("nitf.fhdr")) // are we nitf
         {
            if(!kwl3.find("nitf.rpf.byte_order")) // if we are not a cib/cadrg a.toc file
            {
               ossimString nitfPrefix = ossimString("nitf.");//+imagePrefix;
               if(ossimString(kwl3.find("nitf.fhdr")).contains("NITF02.0"))
               {
                  title = ossimString(kwl3.find(nitfPrefix+"ititle"));
               }
               else 
               {
                  title = ossimString(kwl3.find(nitfPrefix+"iid2"));
               }
               // parse nitf information
               securityClassification = ossimString(kwl3.find(nitfPrefix+"isclas"));
               targetId = ossimString(kwl3.find(nitfPrefix+"tgtid"));
               if(!targetId.empty())
               {
                  if(targetId.size() >=10)
                  {
                     // should be a 17 character ID
                     //
                     beNumber    = ossimString(targetId.begin(), targetId.begin()+10);
                     if(targetId.size() >=17)
                     {
                        countryCode = ossimString(targetId.begin()+15, targetId.end());
                     }
                  }
               }
               targetId = targetId.trim();
               missionId = ossimString(kwl3.find(nitfPrefix+"isorce"));
               imageCategory = ossimString(kwl3.find(nitfPrefix+"icat"));
               imageRepresentation = ossimString(kwl3.find(nitfPrefix+"irep"));
               imageId = ossimString(kwl3.find(nitfPrefix+"iid"));
               countryCode = ossimString(kwl3.find(nitfPrefix+"stdidc.country"));
               if(missionId.empty())
               {
                  countryCode = ossimString(kwl3.find(nitfPrefix+"stdidc.mission"));
               }
               azimuthAngle = ossimString(kwl3.find(nitfPrefix+"use00a.angletonorth"));
               grazingAngle = ossimString(kwl3.find(nitfPrefix+"use00a.oblang"));
               if(!grazingAngle.empty())
               {
                  grazingAngle = ossimString::toString(90.0 - grazingAngle.toDouble());
               }
               organization = ossimString(kwl3.find("nitf.oname"));
            }
            else 
            {
               ossimString nitfPrefix = ossimString("nitf.rpf.")+imagePrefix;
               securityClassification = ossimString(kwl3.find(nitfPrefix+"SecurityClassification"));
               productId = ossimString(kwl3.find(nitfPrefix+"ProductDataType"))+(ossimString(kwl.find(nitfPrefix+"Scale")));
               countryCode = ossimString(kwl3.find(nitfPrefix+"CountryCode"));
               organization = ossimString(kwl3.find("nitf.oname"));
            }
         }
         else if(kwl3.find("dted.uhl.recognition_sentinel"))
         {
            grazingAngle = "90.0";
            azimuthAngle = ossimString(kwl3.find("dted.dsi.orientation"));
            securityClassification = ossimString(kwl3.find("dted.dsi.security_code"));
            productId = kwl3.find("dted.dsi.product_level");
            
            if(productId.downcase().contains("rted"))
            {
               ossimString numberOfLatPoints(kwl3.find("dted.uhl.number_of_lat_points"));
               if(!numberOfLatPoints.empty())
               {
                  if(numberOfLatPoints == "3601")
                  {
                     productId = "DTED2";
                  }
                  else if(numberOfLatPoints == "1201")
                  {
                     productId = "DTED1";
                  }
                  else if(numberOfLatPoints == "0121")
                  {
                     productId = "DTED0";
                  }
                  else 
                  {
                     productId = "DTED";
                  }
                  
               }
            }
            organization = ossimString(kwl3.find("dted.dsi.producer_code"));
         }
         else if(kwl3.find("tiff.date_time"))
         {
            ossimString tiffDate(kwl3.find("tiff.date_time"));
            std::vector<ossimString> splitArray;
            tiffDate.split(splitArray, " ");
            if(splitArray.size() > 0)
            {
               dateValue = splitArray[0].substitute(":", "-", true);
               if(splitArray.size() > 1)
               {
                  dateValue += "T";
                  dateValue += splitArray[1];
                  dateValue += "Z";
               }
               else 
               {
                  dateValue += "T00:00:00Z";
               }
            }
         }
         outputString += indentation + "   <filename>" + thePrivateData->theFilename.string() +
            "</filename>" + separator; 
         outputString += indentation + "   <imageId>" + imageId.string() + "</imageId>" +
            separator; 
         outputString += indentation + "   <imageRepresentation>" + imageRepresentation.string() +
            "</imageRepresentation>" + separator; 
         outputString += indentation + "   <targetId>" + targetId.string() + "</targetId>" +
            separator; 
         outputString += indentation + "   <productId>" + productId.string() + "</productId>" +
            separator; 
         outputString += indentation + "   <beNumber>" + beNumber.string() + "</beNumber>" +
            separator; 
         outputString += indentation + "   <sensorId>" + sensorId.string() + "</sensorId>" +
            separator; 
         outputString += indentation + "   <missionId>" + missionId.string() + "</missionId>" +
            separator; 
         outputString += indentation + "   <countryCode>" + countryCode.string() +
            "</countryCode>" + separator; 
         outputString += indentation + "   <imageCategory>" + imageCategory.string() +
            "</imageCategory>" + separator; 
         outputString += indentation + "   <azimuthAngle>" + azimuthAngle.string() +
            "</azimuthAngle>" + separator; 
         outputString += indentation + "   <grazingAngle>" + grazingAngle.string() +
            "</grazingAngle>" + separator; 
         outputString += indentation + "   <securityClassification>" +
            securityClassification.string() + "</securityClassification>" + separator; 
         outputString += indentation + "   <title>" + title.string() + "</title>" + separator; 
         outputString += indentation + "   <organization>" + organization.string() +
            "</organization>" + separator; 
         outputString += indentation + "   <description>" + description.string() +
            "</description>" + separator; 
         outputString += indentation + "   <niirs>" + niirs.string() + "</niirs>" + separator; 
         std::ostringstream out;
         out << kwl3;
         outputString += out.str() + separator;
         
      }
   }
   outputString += indentation + "   <fileType>" + thePrivateData->formatName() + "</fileType>" + separator; 
   outputString += indentation + "   <className>" + (thePrivateData->theImageHandler.valid()?thePrivateData->theImageHandler->getClassName().string():ossimString("").string()) + "</className>" + separator; 
   outputString += indentation + "</metadata>" + separator;
  
   if (!dateValue.empty())
   {
      outputString += indentation + "<TimeStamp>" + separator;
      outputString += indentation + "   <when>" + dateValue.string() + "</when>"
      + separator;
      outputString += indentation + "</TimeStamp>" + separator;
      
   }
   else 
   {
      ossimString alreadyHasDate;
      appendRasterEntryDateTime(alreadyHasDate,
                                "", "");
      outputString += alreadyHasDate.string();
      
   }
}

