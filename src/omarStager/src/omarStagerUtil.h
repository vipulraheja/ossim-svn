//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Utility class for staging data into the omar database.
//
//----------------------------------------------------------------------------
// $Id$
#ifndef omarStagerUtil_HEADER
#define omarStagerUtil_HEADER

#include <vector>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimRefPtr.h>

class ossimFilename;
class ossimImageHandler;
class omarRasterDataSetObject;
class omarRasterEntryObject;
class omarGeospatialType;
class omarUnitType;
class omarProductType;
class omarSecurityClassificationType;
class omarSensorType;
class ossimGpt;
class ossimDrect;
class ossimProjection;
class ossimString;

class omarStagerUtil
{
public:
   
   /** @brief default constructor */
   omarStagerUtil();

   /** @brief destructor */
   ~omarStagerUtil();

   /**
    * @brief Stages a directory performing walking.
    * @param dir Directory to stage.
    * @return true on success, false on error.
    */
   bool stageDir(const ossimFilename& dir);

   /**
    * @brief Stages a file takes a flag to indicate to caller not to walk
    * directories.
    * 
    * @param file File to stage.
    * 
    * @param isDirectoryBasedFlag This is passed to stageFile method.  We be
    * set to true if the image is a directory based image and the stager
    * should not go on walking this directory.
    * 
    * @return true if file was staged, false if not.
    */
   bool stageFile(const ossimFilename& file, bool& isDirectoryBasedFlag);

   /**
    * @brief Stages a file.
    * 
    * @param file File to stage.
    * 
    * @return true if file was staged, false if not.
    */
   bool stageFile(const ossimFilename& file);

private:

   bool stageFile(ossimRefPtr<ossimImageHandler> ih);

   /** @return true if file is a stagable type. */
   bool isStagable(const ossimFilename& file) const;

   /**
    * @brief Set the associated list of the omarRasterDataSetObject.
    * @param ih Pointer to the image handler.
    * @param rds Pointer to the raster data set.
    * @param isDirectoryBasedImageFlag If true this will add just the image and
    * the directory; else it will attempt to add all associated files to the
    * list.
    */
   void setFileList(ossimRefPtr<ossimImageHandler> ih,
                    omarRasterDataSetObject* rds);

   /**
    * @brief Initializes searchExtList with extensions to search for.
    * @param searchExtList List to initialize.
    */
   void getSearchFileExtensions(std::vector<ossimString>& searchExtList) const;
   
   void setAcqDate(ossimRefPtr<ossimImageHandler> ih,
                   omarRasterDataSetObject* rds);
   
   void setIngestDate(ossimRefPtr<ossimImageHandler> ih,
                      omarRasterDataSetObject* rds);

   void setBounds(ossimRefPtr<ossimImageHandler> ih,
                  omarRasterDataSetObject* rds);

   void setProductType(ossimRefPtr<ossimImageHandler> ih,
                       omarRasterDataSetObject* rds);

   /**
    * Searches theProductTypeList for type belonging to "code".
    * @return pointer if found; else 0.
    */
   omarProductType* findProductType(const ossimString& code) const;

   void setGeospatialType(ossimRefPtr<ossimImageHandler> ih,
                          omarRasterDataSetObject* rds);
   
   void setSecurityClassificationType(ossimRefPtr<ossimImageHandler> ih,
                                      omarRasterDataSetObject* rds);
   
   void setSensorType(ossimRefPtr<ossimImageHandler> ih,
                      omarRasterDataSetObject* rds);

   void stageEntry(ossim_uint32 entryIndex,
                   ossimRefPtr<ossimImageHandler> ih,
                   omarRasterDataSetObject* rds,
                   ossimDrect& boundingRect);
   
   /** Sets gsd units for entry.  Currently hard coded to METERS. */
   void setEntryGsdUnitType(ossimRefPtr<ossimImageHandler> ih,
                            omarRasterEntryObject* entry);
                            
   /**
    * @brief Initializes array of ground points with the valid image vertices
    * converted to wgs84 datum.
    */
   void getEntryValidVerticies(ossimRefPtr<ossimImageHandler> ih,
                               ossimRefPtr<ossimProjection> imageProj,
                               std::vector<ossimGpt>& groundPt);

   /**
    * @brief Updates the boundingRect using groundPoints.  This will be the
    * north up bounding rect expanded.
    */
   void updateBoundingRect(const std::vector<ossimGpt>& groundPoints,
                           ossimDrect& boundingRect);
      
   /**
    * @brief Converts array of ground points to a WKT Polygon string.
    */
   void getWktPolygon(const std::vector<ossimGpt>& vertices,
                      std::string& wktPolyStr) const;

   /**
    * @brief Converts array of ground points to a WKT Polygon string.
    */
   void getWktPolygon(const ossimDrect& rect,
                      std::string& wktPolyStr) const;

   /** @brief Initializes theGeospatialTypeList from database. */
   void initGeospatialTypeList();

   /** @brief Initializes theUnitTypeList from database. */
   void initUnitTypeList();

   /** @brief Initializes theProductTypeList from database. */
   void initProductTypeList();

   /** @brief Initializes theSecurityClassTypeList from database. */
   void initSecurityClassificationTypeList();

   /** @brief Initializes theSensorTypeList from database. */
   void initSensorTypeList();

   /** @return true is "file" is in "list", false if not. */
   bool isInList(const ossimFilename& file,
                 const std::vector<ossimFilename>& list) const;

   
   /**
    * @return true if file is a directory based image and the stager should go
    * on to next directory; false if stager should continue with directory.
    */
   bool isDirectoryBasedImage(ossimRefPtr<ossimImageHandler> ih);

   /**
    * @brief isDotFile method.
    * @return true if file is a dot file.
    */
   bool isDotFile(const ossimFilename& file) const;
   
   /**
    * @brief isDotFile method.
    * @return true if file is a dot file.
    */   
   bool isDotDir(const ossimFilename& dir) const;

   /**
    * @brief list of geospatial types: RASTER, VECTOR
    */
   std::vector<omarGeospatialType* > theGeospatialTypeList;

   /**
    * @brief list of unit types:  PIXEL, METERS, DEGREES, FEET and so on...
    */
   std::vector<omarUnitType* > theUnitTypeList;

   /**
    * @brief list of product types:  RASTER, DTED and so on...
    */
   std::vector<omarProductType* > theProductTypeList;

   /**
    * @brief list of security types:  UNCLASS, SECRET and so on...
    */
   std::vector<omarSecurityClassificationType* > theSecurityClassificationTypeList;

   /**
    * @brief list of sensor types:  SPOT5, LANDSAT_7 and so on...
    */
   std::vector<omarSensorType* > theSensorTypeList;
};


#endif /* #ifndef omarStagerUtil_HEADER */
