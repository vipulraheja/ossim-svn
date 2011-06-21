//----------------------------------------------------------------------------
// File:  Init.h
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Class declaration for Init.  Handles ossim initialization.
//
//----------------------------------------------------------------------------
// $Id: Init.cpp 19748 2011-06-12 15:34:56Z dburken $

#include <ossimjni/Init.h>

#include <ossim/base/ossimArgumentParser.h>
#include <ossim/init/ossimInit.h>

ossimjni::Init* ossimjni::Init::m_instance = 0;

ossimjni::Init::~Init()
{
}

ossimjni::Init* ossimjni::Init::instance()
{
   if (!m_instance)
   {
      m_instance = new ossimjni::Init;
   }
   return m_instance;
}

void ossimjni::Init::initialize(int argc, char* argv[])
{
   if(!m_initCalledFlag)
   {
      m_initCalledFlag = true;
      ossimArgumentParser ap(&argc, argv);
      ossimInit::instance()->addOptions(ap);
      ossimInit::instance()->initialize(ap);
   }
}

void ossimjni::Init::initialize()
{
   if(!m_initCalledFlag)
   {
      m_initCalledFlag = true;
      ossimInit::instance()->initialize();
   }
}

ossimjni::Init::Init() :
   m_initCalledFlag(false)
{
}

ossimjni::Init::Init(const ossimjni::Init& obj) :
   m_initCalledFlag(obj.m_initCalledFlag)
{
}

const ossimjni::Init& ossimjni::Init::operator=(const ossimjni::Init& obj)
{
   if ( this != &obj )
   {
      m_initCalledFlag = obj.m_initCalledFlag;
   }
   return *this;
}



