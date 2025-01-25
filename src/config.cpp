#include "config.hpp"

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

AppConfig::AppConfig() {
  this->setOpenGLVersion(3, 3);
  this->setWindowSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
}

void AppConfig::setOpenGLVersion(int majorVersion, int minorVersion) {
  this->majorVersion = majorVersion;
  this->minorVersion = minorVersion;
}

void AppConfig::setWindowSize(int width, int height) {
  this->windowWidth = width;
  this->windowHeight = height;
}
