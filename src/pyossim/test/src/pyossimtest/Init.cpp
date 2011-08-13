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

#include <pyossimtest/Init.h>

#include <ossim/base/ossimArgumentParser.h>
#include <ossim/init/ossimInit.h>

pyossimtest::Init* pyossimtest::Init::m_instance = 0;

pyossimtest::Init::~Init()
{
}

pyossimtest::Init* pyossimtest::Init::instance()
{
   if (!m_instance)
   {
      m_instance = new pyossimtest::Init;
   }
   return m_instance;
}

void pyossimtest::Init::initialize(int argc, char* argv[])
{
   if(!m_initCalledFlag)
   {
      m_initCalledFlag = true;
      ossimArgumentParser ap(&argc, argv);
      ossimInit::instance()->addOptions(ap);
      ossimInit::instance()->initialize(ap);
   }
}

void pyossimtest::Init::initialize()
{
   if(!m_initCalledFlag)
   {
      m_initCalledFlag = true;
      ossimInit::instance()->initialize();
   }
}

pyossimtest::Init::Init() :
   m_initCalledFlag(false)
{
}

pyossimtest::Init::Init(const pyossimtest::Init& obj) :
   m_initCalledFlag(obj.m_initCalledFlag)
{
}

const pyossimtest::Init& pyossimtest::Init::operator=(const pyossimtest::Init& obj)
{
   if ( this != &obj )
   {
      m_initCalledFlag = obj.m_initCalledFlag;
   }
   return *this;
}
