#include "config.hpp"

AppBuilder::AppBuilder() {
  this->app.majorVersion = 3;
  this->app.minorVersion = 3;
  this->app.windowWidth = 800;
  this->app.windowHeight = 600;
  this->app.windowName = "LearnOpenGL";
}

void AppBuilder::setOpenGLVersion(int majorVersion, int minorVersion) {
  this->app.majorVersion = majorVersion;
  this->app.minorVersion = minorVersion;
}

void AppBuilder::setWindowSize(int width, int height) {
  this->app.windowWidth = width;
  this->app.windowHeight = height;
}

void AppBuilder::setWindowName(const char *name) {
  this->app.windowName = name;
}

App *AppBuilder::build() {
  app.init();
  return &app;
}