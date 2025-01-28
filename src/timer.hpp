#pragma once

class Timer {
public:
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  void tick();
};