/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

int main() {
  try {
  Isetta::Application::Start();
  } catch (std::exception e) {
    LOG_INFO(Isetta::Debug::Channel::General, e.what());
  }
  return 0;
}