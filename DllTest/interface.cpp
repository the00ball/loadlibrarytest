#include "Stdafx.h"
#include "DllTest.h"

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

__declspec(dllexport) unsigned long int __cdecl getInstance()
{
	return (unsigned long int)DllTest::CStaticClassTest::getInstance();
}

#ifdef __cplusplus
}
#endif