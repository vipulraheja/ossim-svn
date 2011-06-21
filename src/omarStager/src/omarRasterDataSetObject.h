#ifndef omarRasterDataSetObject_HEADER
#define omarRasterDataSetObject_HEADER

#include <soapStagerWebServiceHttpBindingProxy.h>

class omarRasterDataSetObject : public omar2__RasterDataSetObject
{
public:
   /** default constructor */
   omarRasterDataSetObject();

   /** virtual destructor */
   virtual ~omarRasterDataSetObject();

   /**
    * @brief Assigns acquisitionDate to date.
    * @note date memory managed by this object.
    */
   void setAcquisitionDate(time_t* date);
   time_t* getAcquisitionDate() const;

   /**
    * @brief assigns associatedFileSet to fileSet.
    * @note fileSet memory managed by this object.
    */
   void setAssociatedFileSet(omar2__ArrayOfFileObject* fileSet);
   omar2__ArrayOfFileObject* getAssociatedFileSet();

   void setBounds(omar2__GeometryObject* b);
   omar2__GeometryObject* getBounds() const;

   void setGeospatialType(omar2__GeospatialType* type);
   omar2__GeospatialType* getGeospatialType() const;

   void setId(LONG64* arg);
   LONG64* getId() const;

   void setIngestDate(time_t* date);
   time_t* getIngestDate() const;

   void setProductType(omar2__ProductType* type);
   omar2__ProductType* getProductType() const;

   void setRasterEntrySet(omar2__ArrayOfRasterEntryObject* set);
   omar2__ArrayOfRasterEntryObject* getRasterEntrySet() const;

   void setSecurityClassificationType(omar2__SecurityClassificationType* type);
   omar2__SecurityClassificationType* getSecurityClassificationType() const;

   void setSensorType(omar2__SensorType* type);
   omar2__SensorType* getSensorType() const;
};

#endif /* #ifndef #ifndef omarRasterDataSetObject_HEADER_HEADER */
