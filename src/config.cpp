#include "config.hpp"

AppBuilder::AppBuilder() {
  this->majorVersion = 3;
  this->minorVersion = 3;
  this->windowWidth = 800;
  this->windowHeight = 600;
  this->windowName = "LearnOpenGL";
}

void AppBuilder::setOpenGLVersion(int majorVersion, int minorVersion) {
  this->majorVersion = majorVersion;
  this->minorVersion = minorVersion;
}

void AppBuilder::setWindowSize(int width, int height) {
  this->windowWidth = width;
  this->windowHeight = height;
}

void AppBuilder::setWindowName(const char *name) { this->windowName = name; }

App AppBuilder::build() const {
  App app;

  app.majorVersion = this->majorVersion;
  app.minorVersion = this->minorVersion;
  app.windowWidth = this->windowWidth;
  app.windowHeight = this->windowHeight;
  app.windowName = this->windowName;

  return app;
}