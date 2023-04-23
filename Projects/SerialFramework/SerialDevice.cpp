// Serial device
// --------------------

#include "SerialDevice.h"

#include <Python.h>

#include <cstdio>
#include <iostream>

#define PYTHON_SCRIPT_FOLDER "PythonScripts/"
#define NO_ACTIVE_SCRIPT 0

SerialDevice::SerialDevice(const SerialDevice::SerialDeviceSettings& settings)
    : m_Settings(settings), m_ActiveScriptHash(NO_ACTIVE_SCRIPT) {}

SerialDevice::~SerialDevice() { EndScript(); }

void SerialDevice::RunScript() {
  if (m_ActiveScriptHash) {
    PyObject* main = PyImport_AddModule("__main__");
    if (main != NULL) {
      PyObject* globals = PyModule_GetDict(main);
      PyObject* valuePortId = PyLong_FromLong((long)m_Settings.portId);
      PyObject* valueDeviceId = PyLong_FromLong((long)m_Settings.deviceId);
      PyDict_SetItemString(globals, "portId", valuePortId);
      PyDict_SetItemString(globals, "deviceId", valueDeviceId);
      Py_DECREF(valuePortId);
      Py_DECREF(valueDeviceId);
    }
    std::string filePath{PYTHON_SCRIPT_FOLDER +
                         m_PythonFiles[m_ActiveScriptHash].first};
    FILE* pFile = fopen(filePath.c_str(), "rw");
    if (pFile != NULL) {
      m_PythonFiles[m_ActiveScriptHash].second = pFile;

      PyRun_SimpleFile(m_PythonFiles[m_ActiveScriptHash].second,
                       filePath.c_str());
    }
  }
}

void SerialDevice::EndScript() {
  FILE* pFile = m_PythonFiles[m_ActiveScriptHash].second;
  if (pFile) {
    fclose(pFile);
  }
  m_ActiveScriptHash = NO_ACTIVE_SCRIPT;
}

void SerialDevice::AddPythonScript(const std::string& scriptName) {
  m_PythonFiles.insert(
      std::make_pair(std::hash<std::string>{}(scriptName),
                     SerialDevice::pythonFile(scriptName, NULL)));
}

void SerialDevice::SetActivePythonScript(const std::string& scriptName,
                                         bool runScript) {
  unsigned requestedHash{std::hash<std::string>{}(scriptName)};
  if (m_PythonFiles.find(requestedHash) != m_PythonFiles.end()) {
    if (runScript) {
      EndScript();
    }
    m_ActiveScriptHash = requestedHash;
    if (runScript) {
      RunScript();
    }
  } else {
    std::cout << "Can't set active file, \"" << scriptName
              << "\" does not exist" << std::endl;
  }
}
