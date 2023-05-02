///////////////////
// Config
//
// ----------------
#include <json_fwd.hpp>
#include <memory>
#include <string>

class Config : final
{
public:
  Config();
  Config(const std::string &fileName);
  std::shared_ptr<nlohmann::json> GetJson();
  const std::shared_ptr<nlohmann::json> GetJson();
  bool LoadFile();
  bool IsValid();

private:
  void OpenFile(const std::string &fileName);
  shared_ptr<nlohmann::json> m_pJson;
};

