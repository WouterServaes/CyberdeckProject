///////////////////
// Cyberdeck App
//
//-----------------------

#include "PythonHandler.h"
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
class Config;
class CyberdeckApp final
{
public:
  CyberdeckApp();
  void Run();
  void SignalProcess(const std::string &name, int sig);

private:
  void Start();
  void End();
  static void SignalHandler(int sig);
  void CreateProcesses();
  std::unordered_map<std::string, std::unique_ptr<PythonHandler>>
    m_PythonHandlers;
  std::shared_ptr<Config> m_pConfig;
  static std::atomic<bool> m_IsRunning;
};
