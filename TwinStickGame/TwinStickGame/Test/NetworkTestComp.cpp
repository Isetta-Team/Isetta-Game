/*
 * Copyright (c) 2018 Isetta
 */
#include "NetworkTestComp.h"

#include "Core/Config/Config.h"
#include "Core/IsettaCore.h"
#include "Core/SystemInfo.h"
#include "Networking/NetworkDiscovery.h"
#include "Networking/NetworkManager.h"

namespace Isetta {
void NetworkTestComp::Start() {
  NetworkManager::Instance().AddClientConnectedListener([](ClientInfo info) {
    LOG_INFO(Debug::Channel::Networking,
             "Client [%s] with IP [%s] is connected", info.machineName.c_str(),
             info.ip.c_str());
  });

  NetworkManager::Instance().AddClientDisconnectedListener([](ClientInfo info) {
    LOG_INFO(Debug::Channel::Networking,
             "Client [%s] with IP [%s] is disconnected",
             info.machineName.c_str(), info.ip.c_str());
  });

  NetworkManager::Instance().AddConnectedToServerListener([]() {
    LOG_INFO(Debug::Channel::Networking, "Successfully connected to server");
  });

  NetworkManager::Instance().AddDisconnectedFromServerListener([]() {
    LOG_INFO(Debug::Channel::Networking,
             "Successfully disconnected from server");
  });

  Input::RegisterKeyPressCallback(KeyCode::F1, []() {
    NetworkManager::Instance().StartHost(
        CONFIG_VAL(networkConfig.defaultServerIP));
  });

  Input::RegisterKeyPressCallback(KeyCode::F2, []() {
    NetworkManager::Instance().StartServer(
        CONFIG_VAL(networkConfig.defaultServerIP));
  });

  Input::RegisterKeyPressCallback(KeyCode::F3, []() {
    if (NetworkManager::Instance().IsClientRunning()) {
      NetworkManager::Instance().StopClient();
    } else {
      NetworkManager::Instance().StartClient(
          CONFIG_VAL(networkConfig.defaultServerIP));
    }
  });

  Input::RegisterKeyPressCallback(KeyCode::KP_7, []() {
    NetworkManager::Instance().NetworkLoadLevel("Level1");
  });
}
}  // namespace Isetta