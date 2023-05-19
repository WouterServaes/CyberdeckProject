
#include "ProcessHandler.h"

#include "Config.h"
#include <csignal>
#include <filesystem>
#include <fstream>
#include <iostream>

ProcessHandler::ProcessHandler(const std::string &processName,
                               std::shared_ptr<Config> pConfig)
  : m_Name(processName), m_pConfig(pConfig), m_Thread()
{
}

ProcessHandler::~ProcessHandler()
{
  // make sure the process is stopped and thread is joined
  End();
}

void ProcessHandler::Start()
{
  if (!IsProcessActive()) {
    ApplyConfigItems();
    CreateActiveFile();
    StartProcess();
  }
}

void ProcessHandler::End()
{
  if (IsProcessActive()) {
    RemoveActiveFile();
    EndProcess();
    m_Thread.join();
  }
}

const std::string &ProcessHandler::GetName() { return m_Name; }

bool ProcessHandler::IsProcessActive()
{
  std::filesystem::path f = std::filesystem::path(GetActiveFileName());
  return IsProcessActive(f);
}

void ProcessHandler::RemoveActiveFile()
{
  std::filesystem::path f = std::filesystem::path(GetActiveFileName());
  if (IsProcessActive(f) && std::filesystem::remove(f)) {
    std::cout << "Stopped " << m_Name << std::endl;
  }
}

void ProcessHandler::CreateActiveFile()
{
  std::filesystem::path f = std::filesystem::path(GetActiveFileName());
  if (!IsProcessActive(f)) {
    std::ofstream(f.c_str()) << m_Name;
  }
}

std::string ProcessHandler::GetActiveFileName()
{
  return std::string("." + m_Name);
}

bool ProcessHandler::IsProcessActive(const std::filesystem::path &pathToFile)
{
  return std::filesystem::exists(pathToFile);
}

void ProcessHandler::EndProcess() {}

