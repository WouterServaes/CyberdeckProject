
#include "PythonHandler.h"
#include "Config.h"
#include "PythonScript.h"
#include <thread>

#define PYTHON_SCRIPT_FOLDER "PythonScripts/"

PythonHandler ::PythonHandler(const std::string &processName,
                              std::shared_ptr<Config> pConfig)
  : ProcessHandler(processName, pConfig),
    m_pPythonScript(std::make_unique<PythonScript>())
{
}

void PythonHandler::StartProcess()
{
  if (m_pPythonScript) {
    m_Thread = std::thread(
      m_pPythonScript->RunScript,
      std::string(PYTHON_SCRIPT_FOLDER + GetName() + std::string(".py")));
  }
}

void PythonHandler::ApplyConfigItems() {}

