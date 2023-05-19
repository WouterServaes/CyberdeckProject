//////////////
// main file of Serial Framework
// ----------------------------------
#include <Python.h>

#include "CyberdeckApp.h"
#include <chrono>
#include <thread>

void InitPython();
void ExitPython();
// PyThreadState* m_PyMainThreadState;

int main(int argc, char **argv)
{
  InitPython();

  CyberdeckApp app{CyberdeckApp()};
  app.Run();

  ExitPython();
  return 0;
}

void InitPython()
{
  Py_SetProgramName(L"python3");
  Py_Initialize();
}

void ExitPython() { Py_Finalize(); }
