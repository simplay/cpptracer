#include "intersectables/containers/mesh.h"
#include "intersectables/geometries/meshTriangle.h"
#include "intersectables/geometries/triangle.h"
#include "logger.h"
#include "objReader.h"

Mesh::Mesh(Material* material, std::string filepath) : material(material) {
  MeshData mesh = ObjReader(filepath.c_str()).read();
  Logger().log(mesh);
  Logger().log("\n");

  int faceIdx = 0;
  for (auto face : mesh.faces) {
    int idX = face.x;
    int idY = face.y;
    int idZ = face.z;

    auto vx = mesh.vertices.at(idX - 1);
    auto vy = mesh.vertices.at(idY - 1);
    auto vz = mesh.vertices.at(idZ - 1);

    if (mesh.normals.size() > 0) {
      auto nf = mesh.normalFaces.at(faceIdx);
      int idNx = nf.x;
      int idNy = nf.y;
      int idNz = nf.z;

      auto nx = mesh.normals.at(idNx - 1);
      auto ny = mesh.normals.at(idNy - 1);
      auto nz = mesh.normals.at(idNz - 1);

      auto triangle = new MeshTriangle(faceIdx, material, vx, vy, vz, nx, ny, nz);
      this->put(triangle);
    } else {
      auto triangle = new Triangle(faceIdx, material, vx, vy, vz);
      this->put(triangle);
    }

    faceIdx++;
  }
}
