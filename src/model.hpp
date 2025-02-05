#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

class Model {
public:
  Model(const char *path) { loadModel(path); }
  void Draw(Shader &shader);

private:
  // model data
  std::vector<Mesh> meshes;
  std::vector<Texture> textures_loaded;
  std::string directory;

  void loadModel(const std::string &path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                            const std::string &typeName);
};