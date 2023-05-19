///////////////////
// Config
//
// ----------------
#include <cstdio>
#include <json_fwd.hpp>
#include <memory>
#include <string>

class Config final
{
public:
  Config();
  Config(const std::string &fileName);
  ~Config();
  std::shared_ptr<nlohmann::json> GetJson();
  bool LoadFile();
  bool IsValid();

private:
  void OpenFile(const std::string &fileName);
  void CloseFile();
  std::shared_ptr<nlohmann::json> m_pJson;
  FILE *m_pConfigFile;
};

