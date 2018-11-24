#include "HitscanTest.h"
#include "Core/IsettaCore.h"
#include "Gameplay/Hitscan.h"

void HitscanTest::Start() {
  hitscan = entity->GetComponent<Hitscan>();
  if (!hitscan) {
    throw std::exception("HitscanTest::Start => No Hitscan component found on entity with HitscanTest!");
  }
}

void HitscanTest::Update() {
  if (Input::IsMouseButtonPressed(MouseButtonCode::MOUSE_LEFT)) {
    hitscan->Fire(Math::Vector3::zero,
                  Math::Vector3((Input::GetMousePosition().x - 960)/960, 0,
                                (Input::GetMousePosition().y - 540)/540));
  }
}