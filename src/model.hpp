#pragma once

#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

class Model {
public:
  unsigned int ID;

  std::vector<Mesh> meshes;
  std::vector<Texture> textures_loaded;
  std::string directory;
  bool gammaCorrection;

  Model(const char *path, bool gamma = false) : gammaCorrection(gamma) {
    loadModel(path);
  }

  void Draw(Shader &shader);

private:
  void loadModel(const std::string &path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                            const std::string &typeName);
};