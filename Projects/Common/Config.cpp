#include "Config.h"

#include <fstream>
#include <json.hpp>

Config::Config() {}

Config::Config(const std::string& name) { OpenFile(name); }

std::shared<nlohmann::json> Config::GetJson() { return m_pJson; }

const std::shared_ptr<nlohmann::json> Config::GetJson() { return m_pJson; }

bool Config::LoadFile() {}

bool Config::IsValid() { return nlohmann::json::accept(m_pJson.get()); }

void Config::OpenFile(const std::string& fileName) {
  // Remove existing Json if possible
  if (m_pJson != nullptr) {
    if (m_pJson.unique()) {
      std::cout << "Config::OpenFile: closing existing json file" << std::endl;
      m_pJson.reset();
    }
    std::cout << "Config::OpenFile: could not close existing json file: json "
                 "still used by application (count: "
              << m_pJson.use_count() << ")" << std::endl;
    return;
  }
  // Parse new Json
  auto f{std::ifstream(fileName)};
  if (f.is_open()) {
    std::cout << "Config::OpenFile: could not open file: " << fileName << "."
              << std::endl;
  } else
    try {
      { m_pJson = nlohmann::parse(f); }
      catch (nlohmann::json::parse_error& e) {
        std::cout << "Config::OpenFile: " << e.what() << std::endl;
      }
    }
}
