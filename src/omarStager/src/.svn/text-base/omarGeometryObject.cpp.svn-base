// $Id$

#include <string>

#include <omarGeometryObject.h>

omarGeometryObject::omarGeometryObject()
   : omar2__GeometryObject()
{
   srsCode = new int;
   wktString = new std::string();
   soap = 0;
}

omarGeometryObject::~omarGeometryObject()
{
   if (srsCode)
   {
      delete srsCode;
      srsCode = 0;
   }
   if (wktString)
   {
      delete wktString;
      wktString = 0;
   }

   // "soap" deleted elsewhere...
}

void omarGeometryObject::setSrsCode(int code)
{
   *srsCode = code;
}

int omarGeometryObject::getSrsCode() const
{
   return *srsCode;
}

void omarGeometryObject::setWktString(const std::string& str)
{
   *wktString = str;
}

std::string omarGeometryObject::getWktString() const
{
   return *wktString;
}
