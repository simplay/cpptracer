#include "mesh.h"
#include "objReader.h"
#include "meshTriangle.h"
#include "triangle.h"

Mesh::Mesh(Material* material)
  : material(material) {

    MeshData mesh = ObjReader("../meshes/teapot.obj").read();
    mesh.log();

    int faceIdx = 0;
    for (auto face : mesh.faces) {
      int idX = face->x;
      int idY = face->y;
      int idZ = face->z;

      auto vx = mesh.vertices.at(idX - 1);
      auto vy = mesh.vertices.at(idY - 1);
      auto vz = mesh.vertices.at(idZ - 1);

      // auto nx = mesh.normals.at(face->x - 1);
      // auto ny = mesh.normals.at(face->y - 1);
      // auto nz = mesh.normals.at(face->z - 1);

      auto nf = mesh.normalFaces.at(faceIdx);
      int idNx = nf->x;
      int idNy = nf->y;
      int idNz = nf->z;

      auto nx = mesh.normals.at(idNx - 1);
      auto ny = mesh.normals.at(idNy - 1);
      auto nz = mesh.normals.at(idNz - 1);

      auto triangle = new MeshTriangle(
        faceIdx,
        material,
        vx, vy, vz,
        nx, ny, nz
      );
      // auto triangle = new Triangle(
      //     faceIdx,
      //     material,
      //     vx, vy, vz
      //     );
      this->put(triangle);
      faceIdx++;
    }
}


