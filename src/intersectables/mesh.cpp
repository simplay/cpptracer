#include "mesh.h"
#include "objReader.h"
#include "meshTriangle.h"

Mesh::Mesh(Material* material)
  : material(material) {

    MeshData mesh = ObjReader("../meshes/teapot.obj").read();
    mesh.log();

    for (auto face : mesh.faces) {
      auto vx = mesh.vertices.at(face->x);
      auto vy = mesh.vertices.at(face->y);
      auto vz = mesh.vertices.at(face->z);

      auto nx = mesh.normals.at(face->x);
      auto ny = mesh.normals.at(face->y);
      auto nz = mesh.normals.at(face->z);

      this->put(
        new MeshTriangle(
          material,
          vx, vy, vz,
          nx, ny, nz
        )
      );
    }
}


