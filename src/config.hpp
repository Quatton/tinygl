#pragma once
#include "app.hpp"

class AppBuilder {
public:
  int majorVersion;
  int minorVersion;

  int windowWidth;
  int windowHeight;

  const char *windowName;

  AppBuilder();

  void setOpenGLVersion(int majorVersion, int minorVersion);
  void setWindowSize(int width, int height);
  void setWindowName(const char *name);

  [[nodiscard]] App build() const;
};
