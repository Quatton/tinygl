#include "config.hpp"

AppBuilder::AppBuilder() {
  this->app.majorVersion = 3;
  this->app.minorVersion = 3;
  this->app.windowWidth = 800;
  this->app.windowHeight = 600;
  this->app.windowName = "LearnOpenGL";
}

AppBuilder *AppBuilder::setOpenGLVersion(int majorVersion, int minorVersion) {
  this->app.majorVersion = majorVersion;
  this->app.minorVersion = minorVersion;

  return this;
}

AppBuilder *AppBuilder::setWindowSize(int width, int height) {
  this->app.windowWidth = width;
  this->app.windowHeight = height;

  return this;
}

AppBuilder *AppBuilder::setWindowName(const char *name) {
  this->app.windowName = name;

  return this;
}

App *AppBuilder::build() {
  app.init();
  return &app;
}