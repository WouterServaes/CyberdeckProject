///////////////////
// PythonHandler
// Process handler for python processes
//===================================
#include "ProcessHandler.h"
#include "PythonScript.h"
#include <memory>
#include <string>
class Config;

class PythonHandler : public ProcessHandler
{
public:
  PythonHandler(const std::string &processName,
                std::shared_ptr<Config> pConfig);

private:
  virtual void ApplyConfigItems() override;
  virtual void StartProcess() override;

  std::unique_ptr<PythonScript> m_pPythonScript;
};

