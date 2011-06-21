// $Id$

#ifndef omarGeospatialType_HEADER
#define omarGeospatialType_HEADER

#include <soapStagerWebServiceHttpBindingProxy.h>

class omarGeospatialType : public omar2__GeospatialType
{
public:
   /** default constructor */
   omarGeospatialType();

   /** copy constructor */
   omarGeospatialType( const omarGeospatialType& obj );

   /** virtual destructor */
   virtual ~omarGeospatialType();

   void setCode(const std::string& arg);
   std::string getCode() const;

   void setDescription(const std::string& arg);
   std::string getDescription() const;

   void setId(LONG64 arg);
   LONG64 getId() const;
};

#endif /* #ifndef ossimGeospatialType_HEADER */
