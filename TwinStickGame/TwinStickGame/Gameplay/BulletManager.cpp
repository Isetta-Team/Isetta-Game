/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "BulletManager.h"
#include "Gameplay/Hitscan.h"
#include "Networking/PlayerMessages.h"
#include "Player/Bullet.h"

using namespace Isetta;

void BulletManager::Awake() {
  hitScan = entity->AddComponent<Hitscan>();
  NetworkManager::Instance().RegisterServerCallback<ShootMessage>(
      [](int clientIndex, yojimbo::Message* message) {
        NetworkManager::Instance().SendMessageFromServerToAll<ShootMessage>(
            message);
      });
  NetworkManager::Instance().RegisterClientCallback<ShootMessage>(
      [this](yojimbo::Message* message) {
        if (NetworkManager::Instance().IsHost()) {
          auto* shootMessage = reinterpret_cast<ShootMessage*>(message);
          hitScan->SetRange(shootMessage->range);
          hitScan->SetSpeed(shootMessage->speed);
          hitScan->Fire(shootMessage->startPos, shootMessage->dir);
        }
        auto* shootMessage = reinterpret_cast<ShootMessage*>(message);
        auto* bullet = Entity::Instantiate("Bullet");
        bullet->AddComponent<MeshComponent>("models/Bullet/Bullet.scene.xml");
        bullet->AddComponent<Bullet>()->Initialize(
            shootMessage->startPos, shootMessage->dir, shootMessage->speed,
            shootMessage->range);
      });
}
