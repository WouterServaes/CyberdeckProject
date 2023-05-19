#include "Config.h"

#include <iostream>
#include <json.hpp>

Config::Config() : m_pConfigFile(NULL) {}

Config::Config(const std::string &name) : m_pConfigFile(NULL)
{
  OpenFile(name);
}

Config::~Config() { CloseFile(); }

std::shared_ptr<nlohmann::json> Config::GetJson() { return m_pJson; }

bool Config::LoadFile() { return false; }

bool Config::IsValid()
{
  return true;
  // return nlohmann::json::accept(m_pJson.get());
}

void Config::OpenFile(const std::string &fileName)
{
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
  CloseFile();
  m_pConfigFile = fopen(fileName.c_str(), "rw");

  if (NULL == m_pConfigFile) {
    std::cout << "Config::OpenFile: could not open file: " << fileName << "."
              << std::endl;
  } else {
    return;
    // try {
    //  m_pJson = std::make_shared<nlohmann::json>(
    //    nlohmann::json::parse(m_pConfigFile, nullptr, true, true));
    //} catch (nlohmann::json::parse_error &e) {
    //  std::cout << "Config::OpenFile: " << e.what() << std::endl;
    //  CloseFile();
    // }
  }
}

void Config::CloseFile()
{
  if (m_pConfigFile != NULL) {
    if (0 != fclose(m_pConfigFile)) {
      std::cout << "unable to close config file" << std::endl;
    }
  }
}

