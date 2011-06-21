// $Id$

#include <string>

#include <omarArrayOfSensorType.h>
#include <omarSensorType.h>

omarArrayOfSensorType::omarArrayOfSensorType()
   : omar2__ArrayOfSensorType()
{
   soap       = 0;
}

omarArrayOfSensorType::~omarArrayOfSensorType()
{
   cleanList();

   // "soap" deleted elsewhere...
}

void omarArrayOfSensorType::cleanList()
{
   std::vector<omar2__SensorType* >::iterator i = SensorType.begin();
   while ( i != SensorType.end() )
   {
      delete (*i);
      (*i) = 0;
      ++i;
   }
   SensorType.clear();
}
