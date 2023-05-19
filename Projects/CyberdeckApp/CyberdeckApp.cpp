
#include "CyberdeckApp.h"

#include <csignal>
#include <iostream>

#include "Config.h"

#define START_MESSAGE                                                          \
  "==Cyberdeck App==\n"                                                        \
  "\t<ctrl+c> or <signal sigusr_1> to end cyberdeck app and all processes"     \
  "\t./CyberdeckApp <-h or --help> for help"
#define CONFIG_FOLDER "ConfigFiles"
#define CONFIG_FILE "Cyberdeck_Config_01.json"

std::atomic<bool> CyberdeckApp::m_IsRunning = true;

CyberdeckApp::CyberdeckApp() : m_PythonHandlers{}, m_pConfig{nullptr} {}

void CyberdeckApp::Start()
{
  std::cout << START_MESSAGE << std::endl;
  std::signal(SIGINT, SignalHandler);
  std::signal(SIGUSR1, SignalHandler);

  m_pConfig = std::make_shared<Config>(
    std::string(CONFIG_FOLDER) + std::string("/") + std::string(CONFIG_FILE));
  // if (m_pConfig->IsValid()) {
  CreateProcesses();
  //}
}

void CyberdeckApp::Run()
{
  Start();
  while (m_IsRunning) {
  }
  End();
}

void CyberdeckApp::End()
{
  for (auto &process : m_PythonHandlers) {
    process.second->End();
  }
}

void CyberdeckApp::SignalProcess(const std::string &name, int sig) {}

void CyberdeckApp::SignalHandler(int sig)
{
  switch (sig) {
  case SIGINT:
  case SIGUSR1:
    m_IsRunning = false;
    break;
  default:
    break;
  }
}

void CyberdeckApp::CreateProcesses()
{
  // From the json, get the python script names
  // for each json python process item
  // get the name
  std::string processName{"testLedMatrix"};
  // Create the process and add it
  m_PythonHandlers.insert(
    {processName, std::make_unique<PythonHandler>(processName, m_pConfig)});

  // Start all processes
  for (auto &process : m_PythonHandlers) {
    process.second->Start();
  }
}

