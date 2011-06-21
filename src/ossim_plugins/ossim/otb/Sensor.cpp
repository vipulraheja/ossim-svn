//----------------------------------------------------------------------------
//
// "Copyright Centre National d'Etudes Spatiales"
//
// License:  LGPL
//
// See LICENSE.txt file in the top level directory for more details.
//
//----------------------------------------------------------------------------
// $Id$

#include <otb/Sensor.h>
#include <otb/SensorParams.h>
#include <otb/PlatformPosition.h>

#include <cstring>

namespace ossimplugins
{

Sensor::Sensor() :
   _params(0),
   _position(0)
{  
}

Sensor::Sensor(SensorParams* params, PlatformPosition* position) :
   _params(0),
   _position(0)
{  
   if ( params )
   {
      _params = params->Clone();
   }
   if ( position )
   {
      _position = position->Clone();
   }
}

Sensor::~Sensor()
{
  if(_params != 0)
  {
    delete _params;
  }

  if(_position != 0)
  {
    delete _position;
  }
}
}
