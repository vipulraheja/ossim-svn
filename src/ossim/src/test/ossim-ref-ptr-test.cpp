//----------------------------------------------------------------------------
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// Description: Test application for ossimRefPtr class.
// 
//----------------------------------------------------------------------------
// $Id: ossim-ref-ptr-test.cpp 19757 2011-06-17 21:07:40Z dburken $

#include <iostream>
using namespace std;

#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimReferenced.h>
#include <ossim/init/ossimInit.h>

// Referenced object.
class Obj : public ossimReferenced
{
public:
   Obj(){}
   virtual ~Obj(){ cout << "~Obj..." << endl; }
};

// Owns a ref ptr.
class Foo
{
public:
   Foo() : m_refPtr(new Obj) {}
   ~Foo() { m_refPtr = 0; }
   ossimRefPtr<Obj>& getRefPtr() { return m_refPtr; }

private:
   ossimRefPtr<Obj> m_refPtr;
};

// Test app
int main( /* int argc, char* argv[] */ )
{
   ossimInit::instance()->initialize();

   Foo* f = new Foo;

   cout << "count(1): " << f->getRefPtr()->referenceCount() << endl;

   ossimRefPtr<Obj> refPtr2 = f->getRefPtr();

   cout << "count(2): " << f->getRefPtr()->referenceCount() << endl;

   delete f;
   f = 0;

   cout << "count(1): " << refPtr2->referenceCount() << endl;

   refPtr2 = 0; // Should destroy here...

   return 0;
}
