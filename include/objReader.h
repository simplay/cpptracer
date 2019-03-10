#include <iostream>
#include <string>
#include <vector>
#include "math/vector3f.h"

#ifndef OBJ_READER_H
#define OBJ_READER_H

struct MeshData {
  std::vector<Vector3f> vertices;
  std::vector<Vector3f> normals;
  std::vector<Vector3f> faces;
  std::vector<Vector3f> normalFaces;
  void log() {
    std::cout << "Vertices extracted: " << vertices.size() << std::endl;
    std::cout << "Normals extracted: " << normals.size() << std::endl;
    std::cout << "Faces extracted: " << faces.size() << std::endl;
    std::cout << "Normal Faces extracted: " << normalFaces.size() << std::endl;
  }
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
