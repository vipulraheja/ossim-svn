// $Id$

#ifndef omarArrayOfSensorType_HEADER
#define omarArrayOfSensorType_HEADER

#include <soapStagerWebServiceHttpBindingProxy.h>
#include <ossim/base/ossimFilename.h>

class omarArrayOfSensorType : public omar2__ArrayOfSensorType
{
public:

   /** @brief default constructor */
   omarArrayOfSensorType();

   /** @brief destructor */
   virtual ~omarArrayOfSensorType();

   void setList(const std::vector<omar2__SensorType* > & list);

   /**
    * @brief Returns the list of files.
    * @param list This list to initialize.
    */
   void getList(std::vector<omar2__SensorType* > & list) const;



private:
   /**
    * @brief Private convenience method to clear
    * omar2__ArrayOfSensorType::SensorType.
    */
   void cleanList();
};

#endif /* #ifndef ossimArrayOfSensorType_HEADER */
