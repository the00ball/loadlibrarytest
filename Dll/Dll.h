// Dll.h
#pragma once
#include <string>

using namespace System;

namespace Dll {

	class CStaticClassTest
	{
   private:
      std::string m_attr_1;
      static CStaticClassTest* ins;
   public:
      CStaticClassTest * getInstance();
      void setAttr(const std::string& value);
      void printAttr();
   };
}
