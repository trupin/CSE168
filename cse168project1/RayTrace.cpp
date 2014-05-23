//
//  RayTrace.cpp
//  cse168project1
//
//  Created by Theophane RUPIN on 5/6/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#include "RayTrace.h"
#include "Material.h"

#include "LambertMaterial.h"
#include "AshikhminMaterial.h"

RayTrace::RayTrace(Scene &s, int MaxDepth): Scn(s), MaxDepth(MaxDepth), PrimaryRays(0), SecondaryRays(0), ShadowRays(0) {}

bool RayTrace::TraceRay(const Ray &ray, Intersection &hit, int depth) {

    // Find ray intersection
    if(!Scn.Intersect(ray, hit)) {
        hit.Shade = Scn.GetSkyColor();
        return false;
    }
    
    switch (ray.type) {
        case Ray::SHADOW:
            ShadowRays += 1;
            return true;

        case Ray::PRIMARY:
            PrimaryRays += 1;
            break;
            
        default:
            SecondaryRays += 1;
            break;
    }
    
    hit.Shade = Color::BLACK;
    Material *mtl = hit.Mtl;
    hit.Mtl = ray.Mtl;
    
    for (Light *light : Scn.Lights) {
        // Compute shade due to lighting
        Ray lRay;
        lRay.Origin = hit.Position + 0.00001 * hit.Normal;
        lRay.type = Ray::SHADOW;
        
        Color illuminance;
        Vector3 pos, toLight;
        float intensity = light->Illuminate(hit.Position, illuminance, toLight, pos);

        lRay.Direction = toLight;
        
        float cosTheta = hit.Normal.Dot(toLight);
        if (cosTheta < 0.f)
            continue;
        
        Intersection lHit;
        if (TraceRay(lRay, lHit))
            continue;

        Color reflectance;
        mtl->ComputeReflectance(reflectance, lRay.Direction, -ray.Direction, hit);
   
        illuminance.Scale(intensity * cosTheta);
        illuminance.Multiply(reflectance);

        hit.Shade.Add(illuminance);
    }
    
    if (depth == MaxDepth)
        return true;

    // Compute shade due to reflection
    Ray rRay;
    rRay.Origin = hit.Position + 0.00001 * hit.Normal;
    rRay.type = Ray::SECONDARY;
    rRay.Mtl = mtl;
    
    for (int i = 0, j = mtl->NSamples(); i < j; ++i) {
        Color intensity;
        
        mtl->GenerateSample(i, intensity, ray.Direction, rRay.Direction, hit);
        
        if (intensity.Red < 0.0001f && intensity.Blue < 0.0001f && intensity.Green < 0.0001f)
            continue;
        
        Intersection rHit;
        TraceRay(rRay, rHit, depth + 1);
        
        rHit.Shade.Multiply(intensity);
        
        hit.Shade.Add(rHit.Shade);
    }

    return true;
}
