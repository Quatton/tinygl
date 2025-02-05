#pragma once

#include <glad/glad.h>
#include <memory>
#include <string>

enum Wrap { REPEAT = GL_REPEAT };

enum MinFilter { LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR };

enum MagFilter { NEAREST = GL_NEAREST };

class Texture {
public:
  unsigned int ID;
  std::string type;
  std::string path;
};

class TextureLoader {
public:
  Wrap wrap_s = Wrap::REPEAT;
  Wrap wrap_t = Wrap::REPEAT;
  std::string type;

  MinFilter min_filter = MinFilter::LINEAR_MIPMAP_LINEAR;
  MagFilter mag_filter = MagFilter::NEAREST;

  bool flip_vertically = false;

  bool alpha_channel = false;

  std::string path;

  TextureLoader &set_wrap_s(Wrap wrap_s);
  TextureLoader &set_wrap_t(Wrap wrap_t);
  TextureLoader &set_min_filter(MinFilter min_filter);
  TextureLoader &set_mag_filter(MagFilter mag_filter);
  TextureLoader &set_flip_vertically(bool flip_vertically);
  TextureLoader &set_alpha_channel(bool alpha_channel);
  TextureLoader &set_type(std::string type);

  TextureLoader &from_path(const std::string &path);

  [[nodiscard]] std::unique_ptr<Texture> load() const;
};