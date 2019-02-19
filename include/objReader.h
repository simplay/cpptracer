#include <string>
#include <vector>
#include "point3f.h"
#include <iostream>

#ifndef OBJ_READER_H
#define OBJ_READER_H

struct MeshData {
  std::vector<Point3f*> vertices;
  std::vector<Point3f*> normals;
  std::vector<Point3f*> faces;
  void log() {
    std::cout << "Vertices extracted: " << vertices.size() << std::endl;
    std::cout << "Normals extracted: " << normals.size() << std::endl;
    std::cout << "Faces extracted: " << faces.size() << std::endl;
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
