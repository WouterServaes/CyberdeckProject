
#include "CyberdeckApp.h"

#include <csignal>
#include <iostream>

#include "Config.h"

#define START_MESSAGE "==Cyberdeck App==\n \
                         "\t<ctrl+c> or <signal sigusr_1> to end cyberdeck app and all processes" \
                         "\t./CyberdeckApp <-h or --help> for help"  
#define CONFIG_FILE "Cyberdeck_Config_01.json"

CyberdeckApp::CyberdeckApp()
    : m_ProcessHanders{}, m_pConfig{nullptr}, m_IsRunning{true} {}

void CyberdeckApp::Start() {
  std::cout << START_MESSAGE << std::endl;
  std::signal(SIGINT, SignalHandler);
  std::signal(SIGUSR1, SignalHandler);

  m_pConfig = std::make_shared<Config>(Config(CONFIG_FILE));
  if(m_pConfig->IsValid())
  {
    CreateProcesses();
  } 
}

void CyberdeckApp::Run() {
  Start();
  while (m_IsRunning) {
  }
  End();
}

void CyberdeckApp::End() {}

void CyberdeckApp::SignalProcess(const std::string& name, int sig) {}

void CyberdeckApp::SignalHandler(int sig) {
  switch
    sig {
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
  //
  
  //
}





