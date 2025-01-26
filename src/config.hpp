#pragma once

#include "app.hpp"
#include "const.hpp"

class AppBuilder {
public:
  AppBuilder() = default;
  virtual ~AppBuilder() = default;

  AppBuilder &setOpenGLVersion(int majorVersion, int minorVersion);
  AppBuilder &setWindowSize(int width, int height);
  AppBuilder &setWindowName(const char *name);

  std::unique_ptr<App> build();

private:
  int major_version{3};
  int minor_version{3};
  int window_width{SCR_WIDTH};
  int window_height{SCR_HEIGHT};
  const char *window_name{"LearnOpenGL"};
};
