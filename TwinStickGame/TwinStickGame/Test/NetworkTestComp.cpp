/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>
#include "NetworkTestComp.h"

namespace Isetta {
void NetworkTestComp::Start() {
  NetworkManager::Instance().RegisterClientConnectedCallback([](ClientInfo info) {
    LOG_INFO(Debug::Channel::Networking,
             "Client [%s] with IP [%s] is connected", info.machineName.c_str(),
             info.ip.c_str());
  });

  NetworkManager::Instance().RegisterClientDisconnectedCallback([](ClientInfo info) {
    LOG_INFO(Debug::Channel::Networking,
             "Client [%s] with IP [%s] is disconnected",
             info.machineName.c_str(), info.ip.c_str());
  });

  NetworkManager::Instance().RegisterConnectedToServerCallback([]() {
    LOG_INFO(Debug::Channel::Networking, "Successfully connected to server");
  });

  NetworkManager::Instance().RegisterDisconnectedFromServerCallback([]() {
    LOG_INFO(Debug::Channel::Networking,
             "Successfully disconnected from server");
  });

  Input::RegisterKeyPressCallback(KeyCode::F1, []() {
    NetworkManager::Instance().StartHost(
        CONFIG_VAL(networkConfig.defaultServerIP));
    LOG_INFO(Debug::Channel::Networking, "Started as host on %s",
             CONFIG_VAL(networkConfig.defaultServerIP).c_str());
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
          CONFIG_VAL(networkConfig.defaultServerIP),
          [](const NetworkManager::ClientState state) {
            if (state == NetworkManager::ClientState::Connected) {
              LOG_INFO(Debug::Channel::Networking, "Connected to %s",
                       CONFIG_VAL(networkConfig.defaultServerIP).c_str());
            }
          });
    }
  });

  Input::RegisterKeyPressCallback(KeyCode::KP_8, []() {
    NetworkManager::Instance().NetworkLoadLevel("Level1");
  });
}
}  // namespace Isetta