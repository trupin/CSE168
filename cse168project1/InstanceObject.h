//
//  Header.h
//  cse168project1
//
//  Created by Theophane RUPIN on 4/10/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#ifndef cse168project1_InstanceObject_h
#define cse168project1_InstanceObject_h

#include "Object.h"
#include "MeshObject.h"
#include "Matrix34.h"

class InstanceObject : public Object {
public:
    virtual ~InstanceObject() {}
    InstanceObject(Object &child);
    
    bool Intersect(const Ray &ray, Intersection &hit);
    
    void SetMatrix(const Matrix34 &matrix);
    void SetMaterial(Material *material);
    
private:
    Object &_child;
    Matrix34 _matrix;
    Matrix34 _inverse;
    Material *_material;
};

#endif
