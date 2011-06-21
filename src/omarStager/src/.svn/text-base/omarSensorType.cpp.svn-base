// $Id$


#include <string>

#include <omarSensorType.h>

omarSensorType::omarSensorType()
   : omar2__SensorType()
{
   code = new std::string();
   description = new std::string();
   id = new LONG64;
   soap = 0;
}

omarSensorType::omarSensorType(const omarSensorType& obj)
   : omar2__SensorType()
{
   if (this != &obj)
   {
      code         = new std::string();
      description  = new std::string();
      id           = new LONG64;
      *code        = *(obj.code);
      *description = *(obj.description);
      *id          = *(obj.id);
      
      soap = 0;
   }
}

omarSensorType::~omarSensorType()
{
   if (code)
   {
      delete code;
      code = 0;
   }
   if (description)
   {
      delete description;
      description = 0;
   }
   if (id)
   {
      delete id;
      id = 0;
   }

   // "soap" deleted elsewhere...
}

void omarSensorType::setCode(const std::string& arg)
{
   *code = arg;
}

std::string omarSensorType::getCode() const
{
   return *code;
}

void omarSensorType::setDescription(const std::string& arg)
{
   *description = arg;
}

std::string omarSensorType::getDescription() const
{
   return *description;
}

void omarSensorType::setId(LONG64 arg)
{
   *id = arg;
}

LONG64 omarSensorType::getId() const
{
   return *id;
}

