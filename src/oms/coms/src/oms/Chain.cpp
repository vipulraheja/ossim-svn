#include <oms/Chain.h>
#include <ossim/base/ossimObjectFactoryRegistry.h>
#include <ossim/base/ossimProcessInterface.h>
#include <sstream>

oms::Chain::Chain()
{
}

oms::Chain::~Chain()
{
   if(m_rootChain.valid())
   {
      m_rootChain->disconnect();
      m_rootChain = 0;
   }
}

bool oms::Chain::loadChainKwl(const ossimKeywordlist& kwl)
{
   ossimRefPtr<ossimObject> obj;
   try {
      obj = ossimObjectFactoryRegistry::instance()->createObject(kwl);
   }
   catch (...) {
      obj = 0;
   }
   m_rootChain = 0;
   if(obj.valid())
   {
      m_rootChain = dynamic_cast<ossimConnectableObject*>(obj.get());
   }
   
   return m_rootChain.valid();
}

bool oms::Chain::loadChainKwlString(const std::string& kwlString)
{
   bool result = false;
   ossimKeywordlist kwl;
   ossimRefPtr<ossimObject> obj;
   m_rootChain = 0;
   std::istringstream inputStream(kwlString);
   if(kwl.parseStream(inputStream))
   {
      result = loadChainKwl(kwl);
   }
   
   return result;
}

ossimConnectableObject* oms::Chain::getChain()
{
   return m_rootChain.get();
}

const ossimConnectableObject* oms::Chain::getChain()const
{
   return m_rootChain.get();
}

ossimImageSource* oms::Chain::getChainAsImageSource()
{
   return dynamic_cast<ossimImageSource*>(m_rootChain.get());
}

const ossimImageSource* oms::Chain::getChainAsImageSource()const
{
   return dynamic_cast<const ossimImageSource*>(m_rootChain.get());
}

bool oms::Chain::executeChain()
{
   if(!m_rootChain.valid()) return false;
   ossimConnectableObject* obj = m_rootChain->findInputObjectOfType("ossimProcessInterface");
   bool result = false;
   if(obj)
   {
      ossimProcessInterface* inter = PTR_CAST(ossimProcessInterface, obj);
      if(inter)
      {
         result = inter->execute();
      }
   }
   
   return result;
}

void oms::Chain::deleteChain()
{
   if(m_rootChain.valid())
   {
      m_rootChain->disconnect();
      m_rootChain = 0;
   }
}
void oms::Chain::connectMyInputTo(Chain* obj)
{
   if(m_rootChain.valid()&&obj)
   {
      m_rootChain->connectMyInputTo(obj->m_rootChain.get());
   }
}

void oms::Chain::initialize()
{
   ossimSource* imgSrc = PTR_CAST(ossimSource, m_rootChain.get());
   if(imgSrc) imgSrc->initialize();
}

void oms::Chain::print()const
{
   ossimKeywordlist kwl;
   
   if(m_rootChain.valid())
   {
      m_rootChain->saveState(kwl);
      std::cout << kwl << std::endl;
   }
}
