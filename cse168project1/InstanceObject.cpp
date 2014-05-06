//
//  InstanceObject.cpp
//  cse168project1
//
//  Created by Theophane RUPIN on 4/10/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#include "InstanceObject.h"

InstanceObject::InstanceObject(Object &child): _child(child), _matrix(), _material(nullptr) {}

bool InstanceObject::Intersect(const Ray &ray, Intersection &hit) {
    Ray ray2;
    _inverse.Transform(ray.Origin, ray2.Origin);
    _inverse.Transform3x3(ray.Direction, ray2.Direction);
    if (!_child.Intersect(ray2, hit))
        return false;
    _matrix.Transform(hit.Position, hit.Position);
    _matrix.Transform3x3(hit.Normal, hit.Normal);
    hit.HitDistance = ray.Origin.Distance(hit.Position);
    return true;
}

void InstanceObject::SetMatrix(const Matrix34 &matrix) {
    _inverse = _matrix = matrix;
    _inverse.Inverse();
}

void InstanceObject::SetMaterial(Material *material) {
    _material = material;
}