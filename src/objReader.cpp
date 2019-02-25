#include <algorithm>
#include <fstream>
#include <limits>
#include "objReader.h"

ObjReader::ObjReader(const char* filepath)
  : filepath(filepath) {}

MeshData ObjReader::read() {
  MeshData mesh;
  std::ifstream file(filepath);
  std::string line;

  std::vector<Point3f*> vertices;
  std::vector<Point3f*> normals;
  std::vector<Point3f*> faces;
  std::vector<Point3f*> normalFaces;

  MeshData it;
  float minX = std::numeric_limits<float>::max();
  float minY = std::numeric_limits<float>::max();
  float minZ = std::numeric_limits<float>::max();
  while (getline(file, line)) {
    float x = 0;
    float y = 0;
    float z = 0;

    std::string token = line.c_str();
    switch(line.c_str()[0]) {
      case 'v':
        if (token[1] == 'n') {
          sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
          auto n = new Point3f(x, y, z);
          n->normalize();
          normals.push_back(n);
        } else {
          sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
          if (x <= minX) {
            minX = x;
          }

          if (y <= minY) {
            minY = y;
          }

          if (z <= minZ) {
            minZ = z;
          }

          auto v = new Point3f(x, y, z);
          vertices.push_back(v);
        }
        break;
      case 'f':

        int occurrences = 0;
        std::string::size_type pos = 0;
        std::string target = "//";
        while ((pos = line.find(target, pos )) != std::string::npos) {
          ++ occurrences;
          pos += target.length();
        }
        size_t slashCount = std::count(line.begin(), line.end(), '/');

        float u, v, w;
        if (occurrences == 3) {
          // std::cout << "1" << std::endl;
          sscanf(line.c_str(), "f %f//%f %f//%f %f//%f", &x, &u, &y, &v, &z, &w);
          auto face = new Point3f(x, y, z);
          auto normalFace = new Point3f(u, v, w);
          faces.push_back(face);
          normalFaces.push_back(normalFace);
        } else if (slashCount == 9) {
          // std::cout << "2" << std::endl;
          // also defines texture coordiantes - yet not supported
        } else {
          // std::cout << "3" << std::endl;
          sscanf(line.c_str(), "f %f %f %f", &x, &y, &z);
          auto face = new Point3f(x, y, z);
          faces.push_back(face);
        }
        break;
    }
  }

  // move to origin
  Point3f p(minX, minY, minZ);
  p.log();
  for (auto v : vertices) {
    v->sub(&p);
  }

  mesh.vertices = vertices;
  mesh.normals = normals;
  mesh.faces = faces;
  mesh.normalFaces = normalFaces;

  return mesh;
}
