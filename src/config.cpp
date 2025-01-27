#include "config.hpp"

AppBuilder &AppBuilder::setOpenGLVersion(int majorVersion, int minorVersion) {
  major_version = majorVersion;
  minor_version = minorVersion;
  return *this;
}

AppBuilder &AppBuilder::setWindowSize(int width, int height) {
  window_width = width;
  window_height = height;
  return *this;
}

AppBuilder &AppBuilder::setWindowName(const char *name) {
  window_name = name;
  return *this;
}

std::unique_ptr<App> AppBuilder::build() {
  auto app = std::make_unique<App>();
  app->windowWidth = window_width;
  app->windowHeight = window_height;

  app->init(major_version, minor_version, window_name);

  return app;
}