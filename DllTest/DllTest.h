// DllTest.h

#pragma once

#include <string>
using namespace System;

namespace DllTest {

   public class CStaticClassTest
   {
   private:
      std::string m_attr_1;
      static CStaticClassTest * ins;
   public:
      static CStaticClassTest * getInstance();
      void setAttr(const std::string& value);
      void printAttr();
   };
}
