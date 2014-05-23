//
//  RayTrace.h
//  cse168project1
//
//  Created by Theophane RUPIN on 5/6/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#ifndef __cse168project1__RayTrace__
#define __cse168project1__RayTrace__

#include <iostream>

#include "Scene.h"
#include "Ray.h"
#include "Intersection.h"

class RayTrace {
public:
    RayTrace(Scene &s, int MaxDepth = 5);
    
    bool TraceRay(const Ray &ray, Intersection &hit, int depth = 0);
    
private:
    Scene &Scn;
    
    int MaxDepth;
    
    int PrimaryRays;
    int SecondaryRays;
    int ShadowRays;
};

#endif /* defined(__cse168project1__RayTrace__) */
