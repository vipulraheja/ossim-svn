// $Id$


#include <string>

#include <omarGeospatialType.h>

omarGeospatialType::omarGeospatialType()
   : omar2__GeospatialType()
{
   code = new std::string();
   description = new std::string();
   id = new LONG64;
   soap = 0;
}

omarGeospatialType::omarGeospatialType(const omarGeospatialType& obj )
   : omar2__GeospatialType()
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

omarGeospatialType::~omarGeospatialType()
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

void omarGeospatialType::setCode(const std::string& arg)
{
   *code = arg;
}

std::string omarGeospatialType::getCode() const
{
   return *code;
}

void omarGeospatialType::setDescription(const std::string& arg)
{
   *description = arg;
}

std::string omarGeospatialType::getDescription() const
{
   return *description;
}

void omarGeospatialType::setId(LONG64 arg)
{
   *id = arg;
}

LONG64 omarGeospatialType::getId() const
{
   return *id;
}

