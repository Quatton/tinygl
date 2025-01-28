#pragma once

#include "timer.hpp"
#include "window.hpp"
#include <vector>

class PipelineContext {
public:
  std::unique_ptr<Window> window;
  std::unique_ptr<Timer> timer;

  PipelineContext(std::unique_ptr<Window> window) : window(std::move(window)) {
    timer = std::make_unique<Timer>();
  }

  ~PipelineContext() = default;
};