//----------------------------------------------------------------------------
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description:  Simple container class to encapsulate image info.
//
//----------------------------------------------------------------------------
// $Id: ImageInfo.h 12991 2008-06-04 19:14:59Z gpotts $
#ifndef omsImageInfo_HEADER
#define omsImageInfo_HEADER 1

#include <vector>
#include <string>
#include <oms/Constants.h>
#include <oms/Object.h>

namespace oms
{
   class  DataInfoPrivateData;
   class OMSDLL DataInfo : public oms::Object
   {
   public:
      /** default constructor */
      DataInfo();
   
      /** destructor */
      virtual ~DataInfo();


      /**
       * @brief Open method.
       * @param file File to open.
       * @return true on success, false on error.
       */
      bool open(const std::string& file, bool failIfNoGeometryFlag=true);
      void close();
      bool isVideo()const;
      bool isImagery()const;
      std::string getInfo()const;
      std::string getImageInfo(int entry=-1);
      std::string getVideoInfo();
      
   private:
      std::string convertIdatimToXmlDate(const std::string& idatim)const;
      std::string convertAcqDateToXmlDate(const std::string& idatim)const;
      void appendRasterEntry(std::string& outputString,
                             const std::string& indentation,
                             const std::string& separator)const;
      void appendRasterEntries(std::string& outputString,
                               const std::string& indentation,
                               const std::string& separator)const;
      void appendAssociatedRasterEntryFileObjects(std::string& outputString,
                                                  const std::string& indentation,
                                                  const std::string& separator)const;
      void appendBitDepthAndDataType(std::string& outputString,
                                     const std::string& indentation,
                                     const std::string& separator)const;
      void appendGeometryInformation(std::string& outputString,
                                     const std::string& indentation,
                                     const std::string& separator)const;
      void appendRasterDataSetMetadata(std::string& outputString,
                                       const std::string& indentation,
                                       const std::string& separator)const;
      void appendVideoDataSetMetadata(std::string& outputString,
                                       const std::string& indentation,
                                       const std::string& separator)const;
      void appendRasterEntryDateTime(std::string& outputString,
                                     const std::string& indentation,
                                     const std::string& separator)const;
      void appendRasterEntryMetadata(std::string& outputString,
                                     const std::string& indentation,
                                     const std::string& separator)const;
      
      DataInfoPrivateData* thePrivateData;
    };

} // end of namespace oms

#endif /* End of #ifndef omsImageInfo_HEADER */
