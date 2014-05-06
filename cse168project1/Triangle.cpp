//
//  Triangle.cpp
//  cse168project1
//
//  Created by Theophane RUPIN on 4/10/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#include "Triangle.h"
#include <iostream>

Triangle::Triangle() {}
void Triangle::Init(Vertex *v0, Vertex *v1, Vertex *v2, Material *m) {
    Vtx[0]=v0; Vtx[1]=v1; Vtx[2]=v2; Mtl=m;
}

bool Triangle::Intersect(const Ray &ray, Intersection &hit) {

    Vector3 d = ray.Direction;
    Vector3 p = ray.Origin;
    Vector3 aa = Vtx[0]->Position;
    Vector3 ab = Vtx[1]->Position - Vtx[0]->Position;
    Vector3 ac = Vtx[2]->Position - Vtx[0]->Position;
    
    Vector3 cross;

    cross.Cross(ab, ac);
    float det = (-d).Dot(cross);
    
    if (det <= 0.f)
        return false;
    
    float t = (p - aa).Dot(cross) / det;
    cross.Cross(p - aa, ac);
    float a = (-d).Dot(cross) / det;
    
    cross.Cross(ab, p - aa);
    float b = (-d).Dot(cross) / det;
    
    if (a >= 0.f && b >= 0.f && (a + b) <= 1.f && t > 0.f && t < hit.HitDistance) {
        hit.HitDistance = t;
        hit.Position = p + t * d;
        hit.Mtl = Mtl;
        hit.Normal.Cross(ab, ac);
        hit.Normal.Normalize();
        hit.Obj = this;
        return true;
    }
    return false;
}

Vertex &Triangle::GetVtx(int i) const {
    return *Vtx[i];
}

void Triangle::ComputeMinMax(Vector3 &min, Vector3 &max) const {
    min.x = Min(Vtx[0]->Position.x, Min(Vtx[1]->Position.x, Vtx[2]->Position.x));
    min.y = Min(Vtx[0]->Position.y, Min(Vtx[1]->Position.y, Vtx[2]->Position.y));
    min.z = Min(Vtx[0]->Position.z, Min(Vtx[1]->Position.z, Vtx[2]->Position.z));
 
    max.x = Max(Vtx[0]->Position.x, Max(Vtx[1]->Position.x, Vtx[2]->Position.x));
    max.y = Max(Vtx[0]->Position.y, Max(Vtx[1]->Position.y, Vtx[2]->Position.y));
    max.z = Max(Vtx[0]->Position.z, Max(Vtx[1]->Position.z, Vtx[2]->Position.z));
}
