//////////////
// main file of Serial Framework
// ----------------------------------
#include <Python.h>

#include "Config.h"
#include "PythonHandler.h"
#include <chrono>
#include <thread>

void InitPython();
void ExitPython();
// PyThreadState* m_PyMainThreadState;

int main(int argc, char **argv)
{
  InitPython();
  std::shared_ptr<Config> config{};
  config = std::make_shared<Config>(Config());
  PythonHandler pythonHandler{PythonHandler("testLedMatrix", config)};
  pythonHandler.Start();

  std::this_thread::sleep_for(std::chrono::seconds(25));

  pythonHandler.End();

  ExitPython();
  return 0;
}

void InitPython()
{
  Py_SetProgramName(L"python3");
  Py_Initialize();
}

void ExitPython() { Py_Finalize(); }
