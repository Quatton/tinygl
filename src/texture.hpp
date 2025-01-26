#pragma once

#include <glad/glad.h>
#include <memory>

enum Wrap { REPEAT = GL_REPEAT };

enum MinFilter { LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR };

enum MagFilter { NEAREST = GL_NEAREST };

class Texture {
public:
  unsigned int ID;
};

class TextureLoader {
public:
  Wrap wrap_s = Wrap::REPEAT;
  Wrap wrap_t = Wrap::REPEAT;

  MinFilter min_filter = MinFilter::LINEAR_MIPMAP_LINEAR;
  MagFilter mag_filter = MagFilter::NEAREST;

  bool flip_vertically = false;

  bool alpha_channel = false;

  const char *path;

  TextureLoader &set_wrap_s(Wrap wrap_s);
  TextureLoader &set_wrap_t(Wrap wrap_t);
  TextureLoader &set_min_filter(MinFilter min_filter);
  TextureLoader &set_mag_filter(MagFilter mag_filter);
  TextureLoader &set_flip_vertically(bool flip_vertically);
  TextureLoader &set_alpha_channel(bool alpha_channel);

  TextureLoader &from_path(const char *path);

  [[nodiscard]] std::unique_ptr<Texture> load() const;
};