////////////
// Base SerialDevice class
// Holds the device information, python script handles, and signal handler
// -----------------------------

#include <Python.h>

#include <string>
#include <unordered_map>

class SerialDevice {
 public:
  // Relevant settings for the Serial Device, can be expanded with device
  // specific settings
  struct SerialDeviceSettings {
    std::string name{};
    unsigned portId{};
    unsigned deviceId{};
  };
  SerialDevice(const SerialDeviceSettings& settings);
  ~SerialDevice();
  SerialDevice(const SerialDevice& dev) = delete;
  SerialDevice(SerialDevice&& dev) = delete;
  SerialDevice& operator=(const SerialDevice&) = delete;
  SerialDevice& operator=(SerialDevice&&) = delete;
  // Runs the active script
  void RunScript();
  // Ends the active script
  void EndScript();
  // Sends script specific settings to script
  // virtual void SetScriptSettings() = 0;
  // Adds a python script, path starts in PythonScripts folder
  void AddPythonScript(const std::string& scriptName);
  // Sets the active python script, starts it if runScript is true
  void SetActivePythonScript(const std::string& scriptName,
                             bool runScript = true);

  // template<typename T>
  // bool SetPythonVariable(const std::string& varName, T val);
 protected:
  // Relevant settings to the device
  SerialDeviceSettings m_Settings{};

 private:
  // Sends a signal to the active python script
  void SendSignal();
  // Name of file with FILE ptr
  typedef std::pair<std::string, FILE*> pythonFile;
  // Map of Hash of file name with pythonFile
  std::unordered_map<unsigned, pythonFile> m_PythonFiles{};
  // Hash of file name of active script
  unsigned m_ActiveScriptHash;
  // PyObject* m_MainPythonObject{nullptr};
};
