// $Id$

#ifndef omarSecurityClassificationType_HEADER
#define omarSecurityClassificationType_HEADER

#include <soapStagerWebServiceHttpBindingProxy.h>

class omarSecurityClassificationType : public omar2__SecurityClassificationType
{
public:
   /** default construtor */
   omarSecurityClassificationType();

   /** copy construtor */
   omarSecurityClassificationType(const omarSecurityClassificationType& obj);

   /** virtual destructor */
   virtual ~omarSecurityClassificationType();

   void setCode(const std::string& arg);
   std::string getCode() const;

   void setDescription(const std::string& arg);
   std::string getDescription() const;

   void setId(LONG64 arg);
   LONG64 getId() const;
};

#endif /* #ifndef ossimSecurityClassificationType_HEADER */
