// This is the main DLL file.

#include "stdafx.h"

#include "DllTest.h"

using namespace std;

DllTest::CStaticClassTest* DllTest::CStaticClassTest::ins = nullptr;

DllTest::CStaticClassTest * DllTest::CStaticClassTest::getInstance()
{
	if (ins == nullptr)
	{
		ins = new CStaticClassTest();
	}
   return ins;
}

void DllTest::CStaticClassTest::setAttr(const std::string & value)
{
   m_attr_1 = value;
}

void DllTest::CStaticClassTest::printAttr()
{
   printf("%s\n", m_attr_1.c_str());;
}