#include "texture.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

TextureLoader &TextureLoader::set_wrap_s(Wrap wrap_s) {
  this->wrap_s = wrap_s;
  return *this;
}

TextureLoader &TextureLoader::set_wrap_t(Wrap wrap_t) {
  this->wrap_t = wrap_t;
  return *this;
}
TextureLoader &TextureLoader::set_min_filter(MinFilter min_filter) {
  this->min_filter = min_filter;
  return *this;
}

TextureLoader &TextureLoader::set_mag_filter(MagFilter mag_filter) {
  this->mag_filter = mag_filter;
  return *this;
}

TextureLoader &TextureLoader::set_flip_vertically(bool flip_vertically) {
  this->flip_vertically = flip_vertically;
  return *this;
}

TextureLoader &TextureLoader::set_alpha_channel(bool alpha_channel) {
  this->alpha_channel = alpha_channel;
  return *this;
}

TextureLoader &TextureLoader::set_type(std::string type) {
  this->type = std::move(type);
  return *this;
}

TextureLoader &TextureLoader::from_path(const std::string &path) {
  this->path = path;
  return *this;
}

Texture TextureLoader::load() const {
  stbi_set_flip_vertically_on_load(flip_vertically);

  Texture tx;

  glGenTextures(1, &tx.ID);

  int width, height, nrComponents;
  unsigned char *data =
      stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1) {
      format = GL_RED;
    } else if (nrComponents == 3) {
      format = GL_RGB;
    } else if (nrComponents == 4) {
      format = GL_RGBA;
    } else {
      throw std::runtime_error("Unknown number of components");
    }
    glBindTexture(GL_TEXTURE_2D, tx.ID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  tx.type = type;

  return tx;
}