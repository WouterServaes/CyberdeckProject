///////////////////
// Process Handler
//
//---------------

#include <filesystem>
#include <memory>
#include <string>
#include <thread>

class Config;
class ProcessHandler
{
public:
  ProcessHandler(const std::string &processName,
                 std::shared_ptr<Config> &pConfig);
  ProcessHandler() = delete;
  void StartProcess() = 0;
  void EndProcess() = 0;
  const std::string &GetName();
  bool IsProcessActive();

protected:
  void ApplyConfigItems() = 0;
  void RemoveActiveFile();
  std::thread m_Thread;
  std::shared_ptr<Config> m_pConfig;

private:
  void CreateActiveFile();
  bool IsProcessActive(const std::filesystem::path &pathToFile);
  std::string GetActiveFileName();
  std::string m_Name;
};
