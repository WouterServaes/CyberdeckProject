///////////////////
// Cyberdeck App
//
//-----------------------

#include <memory>
#include <string>
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
  void SignalHandler(int sig);
  void CreateProcesses();
  std::unordered_map<std::string, std::unique_ptr<ProcessHandler>>
    m_ProcessHandlers;
  const std::shared_ptr<Config> m_pConfig;
};
