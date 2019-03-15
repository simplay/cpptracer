#ifndef OBJ_READER_H
#define OBJ_READER_H

#include <string>
#include <vector>
#include "math/vector3f.h"

struct MeshData {
  std::vector<Vector3f> vertices;
  std::vector<Vector3f> normals;
  std::vector<Vector3f> faces;
  std::vector<Vector3f> normalFaces;
};

class ObjReader {
 private:
  const char* filepath;
  MeshData mesh;

 public:
  ObjReader(const char* filepath);
  MeshData read();
};
#endif
