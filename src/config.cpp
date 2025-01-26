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
  app->majorVersion = major_version;
  app->minorVersion = minor_version;
  app->windowWidth = window_width;
  app->windowHeight = window_height;
  app->windowName = window_name;

  app->init();

  return app;
}