#ifndef omarRasterEntryObject_HEADER
#define omarRasterEntryObject_HEADER

#include <soapStagerWebServiceHttpBindingProxy.h>

class omarRasterEntryObject : public omar2__RasterEntryObject
{
public:
   omarRasterEntryObject();
   virtual ~omarRasterEntryObject();

   void setEntryId(int arg);
   int getEntryId() const;

   void setGsdUnitType(omar2__UnitType* arg);
   omar2__UnitType* getGsdUnitType() const;

   void setGsdX(const double& x);
   void getGsdX(double& x) const;

   void setGsdY(const double& y);
   void getGsdY(double& y) const;

   void setHeight(int h);
   int  getHeight() const;
   
   void setHistogramAvailableFlag(bool flag);
   bool getHistogramAvailableFlag() const;

   void setId(LONG64 arg);
   LONG64 getId() const;

   void setNumberOfBands(int b);
   int  getNumberOfBands() const;

   void setOverviewAvailableFlag(bool flag);
   bool getOverviewAvailableFlag() const;

   void setValidVertices(omar2__GeometryObject* v);
   omar2__GeometryObject* getValidVertices() const;
 
   void setWidth(int w);
   int  getWidth() const;
};

#endif /* #ifndef #ifndef omarRasterEntryObject_HEADER_HEADER */
