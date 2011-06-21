// $Id$

#include <omarArrayOfRasterEntryObject.h>

omarArrayOfRasterEntryObject::omarArrayOfRasterEntryObject()
   : omar2__ArrayOfRasterEntryObject()
{
}

omarArrayOfRasterEntryObject::~omarArrayOfRasterEntryObject()
{
   std::vector<omar2__RasterEntryObject*>::iterator i =
      RasterEntryObject.begin();
   while (i != RasterEntryObject.end())
   {
      if (*i)
      {
         delete (*i);
         (*i) = 0;
      }
      ++i;
   }
}
