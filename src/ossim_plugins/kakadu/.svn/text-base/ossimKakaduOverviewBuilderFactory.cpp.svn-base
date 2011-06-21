//----------------------------------------------------------------------------
// 
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Description: The ossim kakadu overview builder factory.
//
//----------------------------------------------------------------------------
// $Id: ossimKakaduOverviewBuilderFactory.cpp 9944 2006-11-23 19:31:14Z dburken $

#include <ossimKakaduOverviewBuilderFactory.h>
#include <ossimKakaduNitfOverviewBuilder.h>

ossimKakaduOverviewBuilderFactory*
ossimKakaduOverviewBuilderFactory::theInstance = 0;

ossimKakaduOverviewBuilderFactory* ossimKakaduOverviewBuilderFactory::instance()
{
   if ( !theInstance )
   {
      theInstance = new ossimKakaduOverviewBuilderFactory();
   }
   return theInstance;
}

ossimKakaduOverviewBuilderFactory::~ossimKakaduOverviewBuilderFactory()
{
   theInstance = 0;
}

ossimOverviewBuilderBase* ossimKakaduOverviewBuilderFactory::createBuilder(
   const ossimString& typeName) const
{
   ossimRefPtr<ossimOverviewBuilderBase> result = new  ossimKakaduNitfOverviewBuilder();
   if ( result->hasOverviewType(typeName) == false )
   {
      result = 0;
   }
   
   return result.release();
}

void ossimKakaduOverviewBuilderFactory::getTypeNameList(
   std::vector<ossimString>& typeList) const
{
   ossimRefPtr<ossimOverviewBuilderBase> builder = new  ossimKakaduNitfOverviewBuilder();
   builder->getTypeNameList(typeList);
   builder = 0;
}

ossimKakaduOverviewBuilderFactory::ossimKakaduOverviewBuilderFactory()
{
}

ossimKakaduOverviewBuilderFactory::ossimKakaduOverviewBuilderFactory(
   const ossimKakaduOverviewBuilderFactory& /* obj */)
{
}

void ossimKakaduOverviewBuilderFactory::operator=(
   const ossimKakaduOverviewBuilderFactory& /* rhs */)
{
}
