#include <gtest/gtest.h>
#include "camera.h"
#include "point3f.h"
#include <iostream>

TEST(Camera, camera_matrix) {
  int width = 1000;
  int height = 1000;

  Point3f eye(0.0, 0.0, 3.0);
  Point3f lookAt(0.0, 0.0, 0.0);
  Point3f up(0.0, 1.0, 0.0);
  float fov = 60.0;
  float aspectRatio = (float)width / height;

  Camera camera(
    &eye, &lookAt, &up, fov, aspectRatio, width, height
  );

  ASSERT_EQ(1, camera.transformation()->m00);
  ASSERT_EQ(0, camera.transformation()->m01);
  ASSERT_EQ(0, camera.transformation()->m02);
  ASSERT_EQ(0, camera.transformation()->m03);

  ASSERT_EQ(0, camera.transformation()->m10);
  ASSERT_EQ(1, camera.transformation()->m11);
  ASSERT_EQ(0, camera.transformation()->m12);
  ASSERT_EQ(0, camera.transformation()->m13);

  ASSERT_EQ(0, camera.transformation()->m20);
  ASSERT_EQ(0, camera.transformation()->m21);
  ASSERT_EQ(1, camera.transformation()->m22);
  ASSERT_EQ(0, camera.transformation()->m23);

  ASSERT_EQ(0, camera.transformation()->m30);
  ASSERT_EQ(0, camera.transformation()->m31);
  ASSERT_EQ(3, camera.transformation()->m32);
  ASSERT_EQ(1, camera.transformation()->m33);
}
