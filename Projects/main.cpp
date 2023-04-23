//////////////
// main file of Serial Framework
// ----------------------------------
#include <Python.h>

#include "SerialDevice.h"

void InitPython();
void ExitPython();
// PyThreadState* m_PyMainThreadState;

int main(int argc, char** argv) {
  InitPython();

  SerialDevice::SerialDeviceSettings settings;
  settings.name = "LedMatrix Device";
  settings.portId = 1;
  settings.portId = 1;
  SerialDevice testDevice = SerialDevice(settings);
  testDevice.AddPythonScript("testLedMatrix.py");
  testDevice.SetActivePythonScript("testLedMatrix.py", true);
  testDevice.EndScript();
  ExitPython();
  return 1;
}

void InitPython() {
  Py_SetProgramName(L"python3");
  Py_Initialize();
}

void ExitPython() { Py_Finalize(); }
