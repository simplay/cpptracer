#include <string>
#include <vector>
#include "point3f.h"
#include <iostream>

#ifndef OBJ_READER_H
#define OBJ_READER_H

struct MeshData {
  std::vector<Point3f> vertices;
  std::vector<Point3f> normals;
  std::vector<Point3f> faces;
  void log() {
    std::cout << "Nr. of vertices extracted: " << vertices.size() << std::endl;
    std::cout << "Nr. of normals extracted: " << normals.size() << std::endl;
    std::cout << "Nr. of faces extracted: " << faces.size() << std::endl;
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
