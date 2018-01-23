// App.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <iostream>
#include <stdio.h>

#define MAX_THREADS 2
HANDLE ghMutex;

DWORD WINAPI MyThreadFunction(LPVOID lpParam);

typedef unsigned long int(__cdecl *MYPROC)();

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
   HANDLE  hThreadArray[MAX_THREADS];
   DWORD   dwThreadIdArray[MAX_THREADS];

   // Create a mutex with no initial owner

   ghMutex = CreateMutex(
      NULL,              // default security attributes
      FALSE,             // initially not owned
      NULL);             // unnamed mutex

   if (ghMutex == NULL)
   {
      printf("CreateMutex error: %d\n", GetLastError());
      return 1;
   }

   for (int i = 0; i < MAX_THREADS; i++)
   {
      hThreadArray[i] = CreateThread(
         NULL,                   // default security attributes
         0,                      // use default stack size  
         MyThreadFunction,       // thread function name
         NULL,                   // argument to thread function 
         0,                      // use default creation flags 
         &dwThreadIdArray[i]);   // returns the thread identifier

      if (hThreadArray[i] == NULL)
      {
         printf("CreateThread error: %d\n", GetLastError());
         return 1;
      }
   }

   // Wait until all threads have terminated.

   WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

   // Close all thread handles and free memory allocations.

   for (int i = 0; i < MAX_THREADS; i++)
   {
      CloseHandle(hThreadArray[i]);
   }

   CloseHandle(ghMutex);

   puts("Press any key to continue!!\n");
   getchar();

   return 0;
}

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
   HINSTANCE hinstLib1;
   MYPROC ProcAdd1;
   DWORD dwWaitResult;

   hinstLib1 = LoadLibrary(TEXT("DllTest.dll"));

   if (hinstLib1 != NULL)
   {
      printf("Dll Handler -> %d\n", hinstLib1);

      dwWaitResult = WaitForSingleObject(
         ghMutex,    // handle to mutex
         INFINITE);  // no time-out interval

      switch (dwWaitResult)
      {
         // The thread got ownership of the mutex
      case WAIT_OBJECT_0:
         __try {
            // TODO: get instance

            ProcAdd1 = (MYPROC)GetProcAddress(hinstLib1, "getInstance");

            if (ProcAdd1 != NULL)
            {
               unsigned long int objAddr = (ProcAdd1)();
               printf("Instance Address -> %d\n", objAddr);
            }
         }
         __finally
         {
            // Release ownership of the mutex object
            if (!ReleaseMutex(ghMutex))
            {
               // Handle error.
            }
         }
         break;

         // The thread got ownership of an abandoned mutex
         // The database is in an indeterminate state
      case WAIT_ABANDONED:
         return 1;
      }
   }

   return 0;
}