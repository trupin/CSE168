//
//  BoxTreeObject.h
//  cse168project1
//
//  Created by Theophane RUPIN on 4/20/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#ifndef __cse168project1__BoxTreeObject__
#define __cse168project1__BoxTreeObject__

#include <iostream>

#include "MeshObject.h"
#include "AABBNode.h"

class BoxTreeObject : public Object {
public:
    BoxTreeObject(): _root(nullptr) {}
    virtual ~BoxTreeObject() {
        if (_root) delete _root;
    }

    void Construct(const MeshObject &obj);
    
    virtual bool Intersect(const Ray &ray, Intersection &hit);
    
private:
    AABBNode *_root;
};

#endif /* defined(__cse168project1__BoxTreeObject__) */
