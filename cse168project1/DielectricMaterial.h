//
//  DielectricMaterial.h
//  cse168project1
//
//  Created by Theophane RUPIN on 5/9/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#ifndef __cse168project1__DielectricMaterial__
#define __cse168project1__DielectricMaterial__

#include <iostream>
#include "Material.h"

class RayTrace;

class DielectricMaterial : public Material {
public:
    int NSamples() const {
        return 2;
    };
    
    void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) {
        col = _color;
    }
    
    void GenerateSample(int i, Color &col, const Vector3 &in, Vector3 &out, const Intersection &hit) {
        col = Color::BLACK;

        DielectricMaterial *mi = dynamic_cast<DielectricMaterial *>(hit.Mtl);
        if (!mi) {
            std::cerr << "Cannot compute transmittance from a non dielectric material" << std::endl;
            return ;
        }

        float ni = mi->_refractiveIndice, nt = _refractiveIndice;
        
        if (i == 0) { // reflectance
            out = in - 2 * in.Dot(hit.Normal) * hit.Normal;
        }
        else if (i == 1) { // transmittance
            Vector3 z = (ni / nt) * (in - in.Dot(hit.Normal) * hit.Normal);
            out = z - sqrtf(1.0f - z.Magnitude2()) * hit.Normal;
        }
        
        float nDotD = hit.Normal.Dot(in);
        float nDotT = hit.Normal.Dot(out);
        float rPar = (nt * nDotD - ni * nDotT) / (nt * nDotD + ni * nDotT);
        float rPerp = (ni * nDotD - nt * nDotT) / (ni * nDotD + nt * nDotT);
        float fR = (rPar * rPar + rPerp * rPerp) / 2.0f;
        col.AddScaled(_color, i == 0 ? fR : 1.0f - fR);
    }
    
    void SetRefractiveIndice(float refractiveIndice) {
        _refractiveIndice = refractiveIndice;
    }
    
    void SetColor(const Color &color) {
        _color = color;
    }

private:
    float _refractiveIndice;
    Color _color;
};


#endif /* defined(__cse168project1__DielectricMaterial__) */
