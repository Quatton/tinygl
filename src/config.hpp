#pragma once

#include "app.hpp"

class AppBuilder {
public:
  App app;

  AppBuilder();

  AppBuilder *setOpenGLVersion(int majorVersion, int minorVersion);
  AppBuilder *setWindowSize(int width, int height);
  AppBuilder *setWindowName(const char *name);

  [[nodiscard]] App *build();
};
