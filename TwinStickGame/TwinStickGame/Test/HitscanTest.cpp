#include "HitscanTest.h"
#include "Core/IsettaCore.h"
#include "Gameplay/Hitscan.h"

void HitscanTest::Start() {
  hitscan = entity->GetComponent<Hitscan>();
  if (!hitscan) {
    throw std::exception(
        "HitscanTest::Start => No Hitscan component found on entity with "
        "HitscanTest!");
  }

  Input::RegisterKeyPressCallback(
      KeyCode::I, [&]() { hitscan->SetDamage(hitscan->GetDamage() + 1); });
  Input::RegisterKeyPressCallback(
      KeyCode::K, [&]() { hitscan->SetDamage(hitscan->GetDamage() - 1); });
  Input::RegisterKeyPressCallback(
      KeyCode::O, [&]() { hitscan->SetPiercing(!hitscan->GetPiercing()); });
}

void HitscanTest::Update() {
  if (Input::IsMouseButtonPressed(MouseButtonCode::MOUSE_LEFT)) {
    hitscan->Fire(Math::Vector3::zero,
                  Math::Vector3((Input::GetMousePosition().x - 960) / 960, 0,
                                (Input::GetMousePosition().y - 540) / 540));
  }

  if (Input::IsKeyPressed(KeyCode::T)) {
    hitscan->cooldown += Time::GetDeltaTime() * .5;
  }
  if (Input::IsKeyPressed(KeyCode::G)) {
    hitscan->cooldown -= Time::GetDeltaTime() * .5;
  }
  if (Input::IsKeyPressed(KeyCode::Y)) {
    hitscan->SetRange(hitscan->GetRange() + Time::GetDeltaTime() * 5);
  }
  if (Input::IsKeyPressed(KeyCode::H)) {
    hitscan->SetRange(hitscan->GetRange() - Time::GetDeltaTime() * 5);
  }
  if (Input::IsKeyPressed(KeyCode::U)) {
    hitscan->SetSpeed(hitscan->GetSpeed() + Time::GetDeltaTime() * 5);
  }
  if (Input::IsKeyPressed(KeyCode::J)) {
    hitscan->SetSpeed(hitscan->GetSpeed() - Time::GetDeltaTime() * 5);
  }
}

void HitscanTest::GuiUpdate() {
  GUI::Window(RectTransform{Math::Rect{180, 10, 150, 200}}, "Hitscan", [&]() {
    GUI::TextStyle style{Color::white};

    GUI::Text(RectTransform{Math::Rect{5, 5, 50, 5}},
              Util::StrFormat("Number of Shots: %d", hitscan->GetNumFired()),
              style);
    GUI::Text(RectTransform{Math::Rect{5, 25, 50, 5}},
              Util::StrFormat("Number of Props: %d", hitscan->GetNumProps()),
              style);
    GUI::Text(RectTransform{Math::Rect{5, 45, 50, 5}},
              Util::StrFormat("Cooldown: %f", hitscan->cooldown), style);
    GUI::Text(RectTransform{Math::Rect{5, 65, 50, 5}},
              Util::StrFormat("Range: %.3f", hitscan->GetRange()), style);
    GUI::Text(RectTransform{Math::Rect{5, 85, 50, 5}},
              Util::StrFormat("Speed: %.3f", hitscan->GetSpeed()), style);
    GUI::Text(RectTransform{Math::Rect{5, 105, 50, 5}},
              Util::StrFormat("Damage: %d", hitscan->GetDamage()), style);
    GUI::Text(RectTransform{Math::Rect{5, 125, 50, 5}},
              Util::StrFormat("Piercing: %d", hitscan->GetPiercing()), style);
  });
}