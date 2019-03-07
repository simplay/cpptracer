#include <iostream>
#include <cmath>
#include "rectangle.h"

Rectangle::Rectangle(Material* material, Vector3f normal, float distance)
  : Plane(material, normal, distance)
{}

HitRecord* Rectangle::intersect(Ray* ray) {
  return new HitRecord();
}