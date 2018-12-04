/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>
#include "Score.h"

#include "Consts.h"

using namespace Isetta;

void Score::GuiUpdate() {
  RectTransform rect{{-20, 45, 0, 0}, GUI::Pivot::TopRight, GUI::Pivot::Right};
  GUI::Text(rect, Util::StrFormat("Score: %0*d", 3, score),
            GUI::TextStyle{Consts::MID_SIZE, "Neon"});
}
