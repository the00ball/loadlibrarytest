// This is the main DLL file.

#include "stdafx.h"
#include "Dll.h"
#include <iostream>

using namespace std;

Dll::CStaticClassTest * Dll::CStaticClassTest::getInstance()
{
   if (ins == nullptr)
   {
      ins = new CStaticClassTest();
   }
   return ins;
}

void Dll::CStaticClassTest::setAttr(const std::string & value)
{
   m_attr_1 = value;
}

void Dll::CStaticClassTest::printAttr()
{
   cout << m_attr_1 << endl;
}
