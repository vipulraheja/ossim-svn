// $Id$

#include <string>

#include <omarArrayOfGeospatialType.h>
#include <omarGeospatialType.h>

omarArrayOfGeospatialType::omarArrayOfGeospatialType()
   : omar2__ArrayOfGeospatialType()
{
   soap       = 0;
}

omarArrayOfGeospatialType::~omarArrayOfGeospatialType()
{
   std::vector<omar2__GeospatialType* >::iterator i = GeospatialType.begin();
   while ( i != GeospatialType.end() )
   {
      delete (*i);
      (*i) = 0;
      ++i;
   }
   GeospatialType.clear();

   // "soap" deleted elsewhere...
}
