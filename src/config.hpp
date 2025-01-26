#pragma once
#include "app.hpp"

class AppBuilder {
public:
  App app;

  AppBuilder();

  void setOpenGLVersion(int majorVersion, int minorVersion);
  void setWindowSize(int width, int height);
  void setWindowName(const char *name);

  [[nodiscard]] App build() const;
};
