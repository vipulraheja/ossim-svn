// $Id$

#include <string>

#include <omarSecurityClassificationType.h>

omarSecurityClassificationType::omarSecurityClassificationType()
   : omar2__SecurityClassificationType()
{
   code = new std::string();
   description = new std::string();
   id = new LONG64;
   soap = 0;
}

omarSecurityClassificationType::omarSecurityClassificationType(
   const omarSecurityClassificationType& obj)

   : omar2__SecurityClassificationType()
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

omarSecurityClassificationType::~omarSecurityClassificationType()
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

void omarSecurityClassificationType::setCode(const std::string& arg)
{
   *code = arg;
}

std::string omarSecurityClassificationType::getCode() const
{
   return *code;
}

void omarSecurityClassificationType::setDescription(const std::string& arg)
{
   *description = arg;
}

std::string omarSecurityClassificationType::getDescription() const
{
   return *description;
}

void omarSecurityClassificationType::setId(LONG64 arg)
{
   *id = arg;
}

LONG64 omarSecurityClassificationType::getId() const
{
   return *id;
}

