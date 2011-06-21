// $Id$

#ifndef omarProductType_HEADER
#define omarProductType_HEADER

#include <soapStagerWebServiceHttpBindingProxy.h>

class omarProductType : public omar2__ProductType
{
public:
   /** default constructor */
   omarProductType();

   /** copy constructor */
   omarProductType(const omarProductType& obj);

   /** virtual destructor */
   virtual ~omarProductType();

   void setCode(const std::string& arg);
   std::string getCode() const;

   void setDescription(const std::string& arg);
   std::string getDescription() const;

   void setId(LONG64 arg);
   LONG64 getId() const;
};

#endif /* #ifndef ossimProductType_HEADER */
