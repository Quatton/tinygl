#define CONFIG_HPP

class AppConfig {
 public:
  int majorVersion;
  int minorVersion;

  int windowWidth;
  int windowHeight;

  AppConfig();
  void setOpenGLVersion(int majorVersion, int minorVersion);
  void setWindowSize(int width, int height);
};