#include "mesh.h"
#include "objReader.h"
#include "meshTriangle.h"

Mesh::Mesh(Material* material)
  : material(material) {

    MeshData mesh = ObjReader("../meshes/teapot.obj").read();
    mesh.log();

    int faceIdx = 0;
    for (auto face : mesh.faces) {
      auto vx = mesh.vertices.at(face->x - 1);
      auto vy = mesh.vertices.at(face->y - 1);
      auto vz = mesh.vertices.at(face->z - 1);

      auto nx = mesh.normals.at(face->x - 1);
      auto ny = mesh.normals.at(face->y - 1);
      auto nz = mesh.normals.at(face->z - 1);

      auto mesh = new MeshTriangle(
        material,
        faceIdx,
        vx, vy, vz,
        nx, ny, nz
      );
      mesh->log();
      this->put(mesh);
      faceIdx++;
    }
}


