//
//  AABBNode.cpp
//  cse168project1
//
//  Created by Theophane RUPIN on 4/20/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#include "AABBNode.h"
#include <vector>
#include <map>
#include <algorithm>

#define NCHILDREN 2

AABBNode::AABBNode(): _triangles(nullptr), _numTriangles(0), _children(nullptr), _toDelete(false) {}

AABBNode::AABBNode(const MeshObject &obj): _triangles(nullptr), _numTriangles(0), _children(nullptr), _toDelete(true) {
    _triangles = new Triangle *[obj.NumTriangles];
    for (int i = 0; i < obj.NumTriangles; ++i)
        _triangles[i] = obj.Triangles + i;
    
    _construct(_triangles, obj.NumTriangles, 0);
}

void AABBNode::_construct(Triangle **triangles, int num, int deep) {

    Vector3 dist;
    Vector3 min, max;
    
    // find the longest axis
    triangles[0]->ComputeMinMax(_min, _max);
    for (int i = 1; i < num; ++i) {
        triangles[i]->ComputeMinMax(min, max);
        
        if (min.x < _min.x) _min.x = min.x;
        if (min.y < _min.y) _min.y = min.y;
        if (min.z < _min.z) _min.z = min.z;
        
        if (max.x > _max.x) _max.x = max.x;
        if (max.y > _max.y) _max.y = max.y;
        if (max.z > _max.z) _max.z = max.z;
    }
    
    dist = _max - _min;

    if (num > 40 && deep < 18) {
        int mid = num / 2;

        std::vector<Triangle *> t(num);
        for (int i = 0; i < num; ++i)
            t[i] = triangles[i];

        // compute the median on the longest axis
        if (dist.x > dist.y && dist.x > dist.z)
            std::nth_element(t.begin(), t.begin() + mid, t.end(), Triangle::compareX);
        else if (dist.y > dist.x && dist.y > dist.z)
            std::nth_element(t.begin(), t.begin() + mid, t.end(), Triangle::compareY);
        else
            std::nth_element(t.begin(), t.begin() + mid, t.end(), Triangle::compareZ);

        for (int i = 0; i < num; ++i)
            triangles[i] = t[i];
        
        _children = new AABBNode[NCHILDREN];
        _children[0]._construct(triangles, mid, deep + 1);
        _children[1]._construct(triangles + mid, num - mid, deep + 1);
    }
    else {
        _triangles = triangles;
        _numTriangles = num;
    }

}

AABBNode::~AABBNode() {
    if (_children) delete []_children;
    if (_toDelete) delete []_triangles;
}

bool AABBNode::isLeaf(void) const {
    return !_children;
}

bool AABBNode::Intersect(const Ray &ray, Intersection &hit) {
    if (isLeaf()) {
        if (!_numTriangles)
            return false;

        bool hashit = false;
        for (int i = 0; i < _numTriangles; ++i) {
            if (_triangles[i]->Intersect(ray, hit))
                hashit = true;
        }
        
        return hashit;
    }

    Intersection hits[2];
    bool res[2];
    res[0] = _children[0]._intersectBB(ray, hits[0]);
    res[1] = _children[1]._intersectBB(ray, hits[1]);

    bool result = false;
    if (res[0] && _children[0].Intersect(ray, hit))
        result = true;
    if (res[1] && _children[1].Intersect(ray, hit))
        result = true;
    
    return result;
}

bool AABBNode::_intersectBB(const Ray &ray, Intersection &hit) const {
    Vector3 t1, t2;

    Vector3 invDir = Vector3(1.f, 1.f, 1.f) / ray.Direction;
    
    t1 = (_min - ray.Origin) * invDir;
    t2 = (_max - ray.Origin) * invDir;
    
    Vector3 tmin, tmax;
    
    tmin.x = Min(t1.x, t2.x);
    tmin.y = Min(t1.y, t2.y);
    tmin.z = Min(t1.z, t2.z);

    tmax.x = Max(t1.x, t2.x);
    tmax.y = Max(t1.y, t2.y);
    tmax.z = Max(t1.z, t2.z);
    
    float min = Max(Max(tmin.x, tmin.y), tmin.z);
    float max = Min(Min(tmax.x, tmax.y), tmax.z);
    
    if (min <= max) {
        if ((min <= 0.f && max <= 0.f) || min >= MAXFLOAT)
            return false;
        hit.HitDistance = min < 0.f ? 0.f : min;
        return true;
    }
    return false;
}

void AABBNode::dump(int deep) const {

    std::cout << std::string(deep, '-') << "> ";
    _min.Print();
    _max.Print();
    std::cout << std::endl;
    
    if (_children) {
        _children[0].dump(deep + 1);
        _children[1].dump(deep + 1);
    }
}


