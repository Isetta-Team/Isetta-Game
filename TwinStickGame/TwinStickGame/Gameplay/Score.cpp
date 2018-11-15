/*
 * Copyright (c) 2018 Isetta
 */
#include "Score.h"

// ENGINE
#include "Core/Color.h"
//#include "Events/EventObject.h"
//#include "Events/Events.h"
#include "Graphics/GUI.h"
#include "Graphics/RectTransform.h"
//#include "Scene/Entity.h"
#include "Util.h"

using namespace Isetta;

void Score::GuiUpdate() {
  RectTransform rect{{-20, 45, 0, 0}, GUI::Pivot::TopRight, GUI::Pivot::Right};
  GUI::Text(rect, Util::StrFormat("Score: %0*d", 3, score),
            GUI::TextStyle{50.f, "Neon"});
}
