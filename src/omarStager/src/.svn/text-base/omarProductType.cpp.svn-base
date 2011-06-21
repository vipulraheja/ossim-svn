// $Id$

#include <string>

#include <omarProductType.h>

omarProductType::omarProductType()
   : omar2__ProductType()
{
   code = new std::string();
   description = new std::string();
   id = new LONG64;
   soap = 0;
}

omarProductType::omarProductType(const omarProductType& obj )
   : omar2__ProductType()
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

omarProductType::~omarProductType()
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

void omarProductType::setCode(const std::string& arg)
{
   *code = arg;
}

std::string omarProductType::getCode() const
{
   return *code;
}

void omarProductType::setDescription(const std::string& arg)
{
   *description = arg;
}

std::string omarProductType::getDescription() const
{
   return *description;
}

void omarProductType::setId(LONG64 arg)
{
   *id = arg;
}

LONG64 omarProductType::getId() const
{
   return *id;
}

