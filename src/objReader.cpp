#include <fstream>
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
  while (getline(file, line)) {
    float x, y, z;
    float u, v, w;
    std::string token = line.c_str();
    switch(line.c_str()[0]) {
      case 'v':
        if (token[1] == 'n') {
          sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
          auto n = new Point3f(x, y, z);
          n->log();
          normals.push_back(n);
        } else {
          sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
          auto v = new Point3f(x, y, z);
          vertices.push_back(v);
        }
        break;
      case 'f':
        sscanf(line.c_str(), "f %f//%f %f//%f %f//%f", &x, &u, &y, &v, &z, &w);
        auto face = new Point3f(x, y, z);
        auto normalFace = new Point3f(u, v, w);

        faces.push_back(face);
        normalFaces.push_back(normalFace);
        break;
    }
  }

  mesh.vertices = vertices;
  mesh.normals = normals;
  mesh.faces = faces;
  mesh.normalFaces = normalFaces;

  return mesh;
}
