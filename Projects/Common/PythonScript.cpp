#include "PythonScript.h"
#include <Python.h>
#include <cstdio>
#include <iostream>
void PythonScript::RunScript(const std::string &fileName)
{
  FILE *pFile = fopen(fileName.c_str(), "rw");
  if (NULL == pFile) {
    std::cout << "unable to open python script: " << fileName << std::endl;
    return;
  }

  PyRun_SimpleFile(pFile, fileName.c_str());

  if (0 != fclose(pFile)) {
    std::cout << "unable to close python script: " << fileName << std::endl;
  }
}

