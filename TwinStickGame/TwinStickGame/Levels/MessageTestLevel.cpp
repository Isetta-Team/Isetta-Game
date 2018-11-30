/*
 * Copyright (c) 2018 Isetta
 */

#include "MessageTestLevel.h"

#include "Components/Editor/EditorComponent.h"
#include "Networking/NetworkManager.h"
#include "Test/MessageTestComponent.h"
#include "Test/NetworkTestComp.h"

void MessageTestLevel::Load() {
  Input::RegisterKeyPressCallback(KeyCode::ESCAPE,
                                  []() { Application::Exit(); });

  Entity* entity = Entity::Instantiate("Network Test");
  entity->AddComponent<EditorComponent>();
  entity->AddComponent<NetworkTestComp>();
  MessageTestComponent* mtc = entity->AddComponent<MessageTestComponent>();

  // Register network callbacks
  static int jump = 1;

  NetworkManager::Instance().RegisterClientCallback<TestingMessage>(
      [&](yojimbo::Message* message) {
        mtc->counter = Math::Util::Max(0, mtc->counter + jump);
      });

  NetworkManager::Instance().RegisterServerCallback<TestingMessage>(
      [&](int clientIdx, yojimbo::Message* message) {
        TestingMessage* testingMessage = static_cast<TestingMessage*>(message);
        NetworkManager::Instance().SendMessageFromServerToAll<TestingMessage>(
            message);
      });

  // Register a bunch of input functions to send messages
  Input::RegisterKeyPressCallback(KeyCode::MINUS, [&] {
    NetworkManager::Instance().SendMessageFromClient<TestingMessage>(
        [&](TestingMessage* message) {
          message->number = -jump;
        });
  });
  Input::RegisterKeyPressCallback(KeyCode::EQUAL, [&] {
    NetworkManager::Instance().SendMessageFromClient<TestingMessage>(
        [&](TestingMessage* message) { message->number = jump; });
  });
}
