//
//  BoxTreeObject.cpp
//  cse168project1
//
//  Created by Theophane RUPIN on 4/20/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#include "BoxTreeObject.h"

void BoxTreeObject::Construct(const MeshObject &obj) {
    _root = new AABBNode(obj);
}

bool BoxTreeObject::Intersect(const Ray &ray, Intersection &hit) {
    return _root->Intersect(ray, hit);
}