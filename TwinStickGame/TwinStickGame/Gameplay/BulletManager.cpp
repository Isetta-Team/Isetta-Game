/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Gameplay/Bullet.h"
#include "Gameplay/BulletManager.h"
#include "Gameplay/Hitscan.h"
#include "Networking/NetworkMessages.h"

using namespace Isetta;

BulletManager* BulletManager::instance = nullptr;

void BulletManager::Awake() {
  instance = this;
  hitScan = entity->AddComponent<Hitscan>();
  InitializeBullets();

  NetworkManager::Instance().RegisterServerCallback<ShootMessage>(
      [this](int clientIndex, yojimbo::Message* message) {
        auto* shootMessage = reinterpret_cast<ShootMessage*>(message);
        shootMessage->bulletIndex = GetBulletIndex();
        if (shootMessage->bulletIndex == -1) {
          LOG_WARNING(Debug::Channel::Gameplay, "Bullet not enough");
        } else {
          // Visual bullet
          bulletPool[shootMessage->bulletIndex]->entity->SetActive(true);
          bulletPool[shootMessage->bulletIndex]->Shoot(
              shootMessage->startPos, shootMessage->dir, shootMessage->speed);

          // Hitscan bullet
          hitScan->SetRange(shootMessage->range);
          hitScan->SetSpeed(shootMessage->speed);
          hitScan->SetDamage(shootMessage->damage);
          hitScan->SetBulletIndex(shootMessage->bulletIndex);
          hitScan->SetPlayerIndex(shootMessage->playerIndex);
          hitScan->Fire(shootMessage->startPos, shootMessage->dir);

          NetworkManager::Instance().SendMessageFromServerToAll<ShootMessage>(
              message);
        }
      });

  NetworkManager::Instance().RegisterClientCallback<ShootMessage>(
      [this](yojimbo::Message* message) {
        if (!NetworkManager::Instance().IsHost()) {
          auto* shootMessage = reinterpret_cast<ShootMessage*>(message);
          auto* bullet = bulletPool[shootMessage->bulletIndex];
          bullet->entity->SetActive(true);
          bullet->Shoot(shootMessage->startPos, shootMessage->dir,
                        shootMessage->speed);
        }
      });

  NetworkManager::Instance().RegisterClientCallback<DeactivateBulletMessage>(
      [this](yojimbo::Message* inMessage) {
        auto* message = reinterpret_cast<DeactivateBulletMessage*>(inMessage);
        DeactivateBullet(message->bulletIndex);
      });
}

void BulletManager::DeactivateBullet(const int bulletIndex) {
  bulletPool[bulletIndex]->entity->SetActive(false);
}

void BulletManager::InitializeBullets() {
  bulletPool.Reserve(bulletPoolCount);

  for (int i = 0; i < bulletPoolCount; ++i) {
    auto* bulletEntity = Entity::Instantiate("Bullet");
    bulletEntity->AddComponent<MeshComponent>("models/Bullet/Bullet.scene.xml");
    auto* bullet = bulletEntity->AddComponent<Bullet>();
    bulletEntity->SetActive(false);
    bulletPool.PushBack(bullet);
  }
}

int BulletManager::GetBulletIndex() {
  for (int i = nextIndex; i < bulletPoolCount + nextIndex; ++i) {
    Bullet* bullet = bulletPool[i % bulletPoolCount];
    if (!bullet->entity->GetActive()) {
      nextIndex = i % bulletPoolCount + 1;
      return i % bulletPoolCount;
    }
  }
  return -1;
}
