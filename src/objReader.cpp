#include "objReader.h"
#include <algorithm>
#include <fstream>
#include <limits>

ObjReader::ObjReader(const char* filepath) : filepath(filepath) {}

MeshData ObjReader::read() {
  MeshData mesh;
  std::ifstream file(filepath);
  std::string line;

  std::vector<Vector3f> vertices;
  std::vector<Vector3f> normals;
  std::vector<Vector3f> faces;
  std::vector<Vector3f> normalFaces;

  MeshData it;
  float minX = std::numeric_limits<float>::max();
  float minY = std::numeric_limits<float>::max();
  float minZ = std::numeric_limits<float>::max();
  while (getline(file, line)) {
    float x = 0;
    float y = 0;
    float z = 0;

    std::string token = line.c_str();
    switch (line.c_str()[0]) {
      case 'v':
        if (token[1] == 'n') {
          sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
          auto n = Vector3f(x, y, z);
          n.normalize();
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

          auto v = Vector3f(x, y, z);
          vertices.push_back(v);
        }
        break;
      case 'f':

        int occurrences = 0;
        std::string::size_type pos = 0;
        std::string target = "//";
        while ((pos = line.find(target, pos)) != std::string::npos) {
          ++occurrences;
          pos += target.length();
        }
        size_t slashCount = std::count(line.begin(), line.end(), '/');

        float u, v, w;
        if (occurrences == 3) {
          sscanf(line.c_str(), "f %f//%f %f//%f %f//%f", &x, &u, &y, &v, &z,
                 &w);
          auto face = Vector3f(x, y, z);
          auto normalFace = Vector3f(u, v, w);
          faces.push_back(face);
          normalFaces.push_back(normalFace);
        } else if (slashCount == 9) {
          // also defines texture coordiantes - yet not supported
        } else {
          sscanf(line.c_str(), "f %f %f %f", &x, &y, &z);
          auto face = Vector3f(x, y, z);
          faces.push_back(face);
        }
        break;
    }
  }

  mesh.vertices = vertices;
  mesh.normals = normals;
  mesh.faces = faces;
  mesh.normalFaces = normalFaces;

  return mesh;
}
