
#include "ProcessHandler.h"

#include <filesystem>
#include <iostream>
#include <signal>

#include "Config.h"

ProcessHandler::ProcessHandler(const std::string &processName,
                               std::shared_ptr<Config> &pConfig)
  : m_Name(processName), m_pConfig(pConfig), m_Thread()
{
  ApplyConfigItems();
}

const std::string &ProcessHandler::GetName() { return m_Name; }

bool ProcessHandler::IsProcessActive()
{
  std::filesystem::path f{GetActiveFileName()};
  return IsProcessActive(f);
}

void ProcesHandler::RemoveActiveFile()
{
  std::filesystem::path f{GetActiveFileName()};
  if (IsProcessActive(f) && std::filesystem::remove(f)) {
    std::cout << "Stopped " << m_Name << std::endl;
  }
}

void ProcessHandler::CreateActiveFile()
{
  std::filesystem::path f{GetActiveFileName()};
  if (!IsProcessActive(f)) {
    f /= GetActiveFileName();
  }
}

std::string GetActiveFileName() { return std::string("." + m_Name); }

bool ProcessHandler::IsProcessActive(const std::filesystem::path &pathToFile)
{
  return std::filesystem::exists(pathToFile);
}

