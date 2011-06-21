
#include <omarRasterDataSetObject.h>

omarRasterDataSetObject::omarRasterDataSetObject()
   :
   omar2__RasterDataSetObject()
{
   acquisitionDate = 0;
   associatedFileSet = 0;
   bounds = 0;
   geospatialType = 0;
   id = 0;
   ingestDate = 0;
   productType = 0;
   rasterEntrySet = 0;
   securityClassificationType = 0;
   sensorType = 0;
   soap = 0;
}

omarRasterDataSetObject::~omarRasterDataSetObject()
{
   if (acquisitionDate)
   {
      delete acquisitionDate;
      acquisitionDate = 0;
   }
   if (associatedFileSet)
   {
      delete associatedFileSet;
      associatedFileSet = 0;
   }
   if (bounds)
   {
      delete bounds;
      bounds = 0;
   }
   if (geospatialType)
   {
      delete geospatialType;
      geospatialType = 0;
   }
   if (id)
   {
      delete id;
      id = 0;
   }
   if (ingestDate)
   {
      delete ingestDate;
      ingestDate = 0;
   }
   if (productType)
   {
      delete productType;
      productType = 0;
   }
   if (rasterEntrySet)
   {
      delete rasterEntrySet;
      rasterEntrySet = 0;
   }
   if (securityClassificationType)
   {
      delete securityClassificationType;
      securityClassificationType = 0;
   }
   if (sensorType)
   {
      delete sensorType;
      sensorType = 0;
   }
   if (sensorType)
   {
      delete sensorType;
      sensorType = 0;
   }
//    if (soap)
//    {
//       delete soap;
//       soap = 0;
//    }
}

void omarRasterDataSetObject::setAcquisitionDate(time_t* date)
{
   if (acquisitionDate)
   {
      delete acquisitionDate;
   }
   acquisitionDate = date;
}

time_t* omarRasterDataSetObject::getAcquisitionDate() const
{
   return acquisitionDate;
}

void omarRasterDataSetObject::setAssociatedFileSet(omar2__ArrayOfFileObject* fileSet)
{
   if (associatedFileSet)
   {
      delete associatedFileSet;
   }
   associatedFileSet = fileSet;
}

omar2__ArrayOfFileObject* omarRasterDataSetObject::getAssociatedFileSet()
{
   return associatedFileSet;
}

void omarRasterDataSetObject::setBounds(omar2__GeometryObject* b)
{
   if (bounds)
   {
      delete bounds;
   }
   bounds = b;
}

omar2__GeometryObject* omarRasterDataSetObject::getBounds() const
{
   return bounds;
}

void omarRasterDataSetObject::setGeospatialType(omar2__GeospatialType* type)
{
   if (geospatialType)
   {
      delete geospatialType;
   }
   geospatialType = type;
}

omar2__GeospatialType* omarRasterDataSetObject::getGeospatialType() const
{
   return geospatialType;
}

void omarRasterDataSetObject::setId(LONG64* arg)
{
   if (id)
   {
      delete id;
   }
   id = arg;
}

LONG64* omarRasterDataSetObject::getId() const
{
   return id;
}

void omarRasterDataSetObject::setIngestDate(time_t* date)
{
   if (ingestDate)
   {
      delete ingestDate;
   }
   ingestDate = date;
}

time_t* omarRasterDataSetObject::getIngestDate() const
{
   return ingestDate;
}

void omarRasterDataSetObject::setProductType(omar2__ProductType* type)
{
   if (productType)
   {
      delete productType;
   }
   productType = type;
}

omar2__ProductType* omarRasterDataSetObject::getProductType() const
{
   return productType;
}

void omarRasterDataSetObject::setRasterEntrySet(omar2__ArrayOfRasterEntryObject* set)
{
   if (rasterEntrySet)
   {
      delete rasterEntrySet;
   }
   rasterEntrySet = set;
}

omar2__ArrayOfRasterEntryObject* omarRasterDataSetObject::getRasterEntrySet() const
{
   return rasterEntrySet;
}

void omarRasterDataSetObject::setSecurityClassificationType(omar2__SecurityClassificationType* type)
{
   if (securityClassificationType)
   {
      delete securityClassificationType;
   }
   securityClassificationType = type;
}

omar2__SecurityClassificationType* omarRasterDataSetObject::getSecurityClassificationType() const
{
   return securityClassificationType;
}

void omarRasterDataSetObject::setSensorType(omar2__SensorType* type)
{
   if (sensorType)
   {
      delete sensorType;
   }
   sensorType = type;
}

omar2__SensorType* omarRasterDataSetObject::getSensorType() const
{
   return sensorType;
}
