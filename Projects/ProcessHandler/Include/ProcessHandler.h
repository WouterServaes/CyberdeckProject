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
                 std::shared_ptr<Config> pConfig);
  ProcessHandler() = delete;
  virtual ~ProcessHandler();
  void Start();
  void End();
  const std::string &GetName();
  bool IsProcessActive();

protected:
  virtual void ApplyConfigItems() = 0;
  virtual void StartProcess() = 0;
  virtual void EndProcess();
  std::thread m_Thread;
  std::shared_ptr<Config> m_pConfig;

private:
  void RemoveActiveFile();
  void CreateActiveFile();
  bool IsProcessActive(const std::filesystem::path &pathToFile);
  std::string GetActiveFileName();
  std::string m_Name;
};
