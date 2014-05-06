//
//  AABBNode.h
//  cse168project1
//
//  Created by Theophane RUPIN on 4/20/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#ifndef __cse168project1__AABBNode__
#define __cse168project1__AABBNode__

#include <iostream>
#include <vector>
#include "Vector3.h"
#include "Triangle.h"
#include "MeshObject.h"

class BoxTreeObject;

class AABBNode {
public:
    AABBNode();
    AABBNode(const MeshObject &obj);
    
    virtual ~AABBNode();

    bool Intersect(const Ray &ray, Intersection &hit);
    
    bool isLeaf(void) const;
    
    void dump(int deep) const;
    
private:
    void _construct(Triangle **triangles, int num, int deep);
    bool _intersectBB(const Ray &ray, Intersection &hit) const;
    
private:
    Vector3 _min, _max;
    
    AABBNode *_children;

    Triangle **_triangles;
    int _numTriangles;
    int _toDelete;
    
};

#endif /* defined(__cse168project1__AABBNode__) */
