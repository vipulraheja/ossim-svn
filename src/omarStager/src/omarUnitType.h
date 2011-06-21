// $Id$

#ifndef omarUnitType_HEADER
#define omarUnitType_HEADER

#include <soapStagerWebServiceHttpBindingProxy.h>

class omarUnitType : public omar2__UnitType
{
public:
   /** default construtor */
   omarUnitType();

   /** copy constructor */
   omarUnitType(const omarUnitType& obj);

   /** virtual destructor */
   virtual ~omarUnitType();

   void setCode(const std::string& arg);
   std::string getCode() const;

   void setDescription(const std::string& arg);
   std::string getDescription() const;

   void setId(LONG64 arg);
   LONG64 getId() const;
};

#endif /* #ifndef ossimUnitType_HEADER */
