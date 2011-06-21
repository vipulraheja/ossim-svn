// $Id$

#include <omarRasterEntryObject.h>


omarRasterEntryObject::omarRasterEntryObject()
   :
   omar2__RasterEntryObject()
{
   entryId            = new int;
   gsdUnit            = 0;
   gsdX               = new double;
   gsdY               = new double;
   height             = new int;
   histogramAvailable = new bool;
   id                 = 0;
   numberOfBands      = new int;
   overviewAvailable  = new bool;
   validVertices      = 0;
   width              = new int;
   *entryId            = 0;
   *gsdX               = 0.0;
   *gsdY               = 0.0;
   *height             = 0;
   *histogramAvailable = false;
   *numberOfBands      = 0;
   *overviewAvailable  = false;
   *width              = 0;
   soap                = 0;
}

omarRasterEntryObject::~omarRasterEntryObject()
{
   if (entryId)
   {
      delete entryId;
      entryId = 0;
   }
   if (gsdUnit)
   {
      delete gsdUnit;
      gsdUnit = 0;
   }
   if (gsdX)
   {
      delete gsdX;
      gsdX = 0;
   }
   if (gsdY)
   {
      delete gsdY;
      gsdY = 0;
   }
   if (height)
   {
      delete height;
      height = 0;
   }
   if (histogramAvailable)
   {
      delete histogramAvailable;
      histogramAvailable = 0;
   }
   if (id)
   {
      delete id;
      id = 0;
   }
   if (numberOfBands)
   {
      delete numberOfBands;
      numberOfBands = 0;
   }
   if (overviewAvailable)
   {
      delete overviewAvailable;
      overviewAvailable = 0;
   }
   if (validVertices)
   {
      delete validVertices;
      validVertices = 0;
   }
   if (width)
   {
      delete width;
      width = 0;
   }

   // soap deleted elsewhere...
//    if (soap)
//    {
//       delete soap;
//       soap = 0;
//    }
}

void omarRasterEntryObject::setEntryId(int arg)
{
   *entryId = arg;
}

int omarRasterEntryObject::getEntryId() const
{
   return *entryId;
}

void omarRasterEntryObject::setGsdUnitType(omar2__UnitType* arg)
{
   if (gsdUnit)
   {
      delete gsdUnit;
   }
   gsdUnit = arg;
}

omar2__UnitType* omarRasterEntryObject::getGsdUnitType() const
{
   return gsdUnit;
}

void omarRasterEntryObject::setGsdX(const double& x)
{
   *gsdX = x;
}

void omarRasterEntryObject::getGsdX(double& x) const
{
   x = *gsdX;
}

void omarRasterEntryObject::setGsdY(const double& y)
{
   *gsdY = y;
}

void omarRasterEntryObject::getGsdY(double& y) const
{
   y = *gsdY;
}

void omarRasterEntryObject::setHeight(int h)
{
   *height = h;
}

int  omarRasterEntryObject::getHeight() const
{
   return *height;
}

void omarRasterEntryObject::setHistogramAvailableFlag(bool flag)
{
   *histogramAvailable = flag;
}

bool omarRasterEntryObject::getHistogramAvailableFlag() const
{
   return *histogramAvailable;
}

void omarRasterEntryObject::setId(LONG64 arg)
{
   *id = arg;
}

LONG64 omarRasterEntryObject::getId() const
{
   return *id;
}

void omarRasterEntryObject::setNumberOfBands(int b)
{
   *numberOfBands = b;
}

int omarRasterEntryObject::getNumberOfBands() const
{
   return *numberOfBands;
}

void omarRasterEntryObject::setOverviewAvailableFlag(bool flag)
{
   *overviewAvailable = flag;
}

bool omarRasterEntryObject::getOverviewAvailableFlag() const
{
   return *overviewAvailable;
}

void omarRasterEntryObject::setValidVertices(omar2__GeometryObject* v)
{
   if (validVertices)
   {
      delete validVertices;
   }
   validVertices = v;
}

omar2__GeometryObject* omarRasterEntryObject::getValidVertices() const
{
   return validVertices;
}

void omarRasterEntryObject::setWidth(int w)
{
   *width = w;
   
}

int  omarRasterEntryObject::getWidth() const
{
   return *width;
}
