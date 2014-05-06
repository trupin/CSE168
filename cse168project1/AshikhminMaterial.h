//
//  AshikhminMaterial.h
//  cse168project1
//
//  Created by Theophane RUPIN on 5/6/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#ifndef __cse168project1__AshikhminMaterial__
#define __cse168project1__AshikhminMaterial__

#include <iostream>

#include "Material.h"
#include "Color.h"

class AshikhminMaterial : public Material {
public:
    virtual void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) {
        
    }
    
    void SetSpecularLevel(float specularLevel) {
        _specularLevel = specularLevel;
    }
    void SetDiffuseLevel(float diffuseLevel) {
        _diffuseLevel = diffuseLevel;
    }
    void SetDiffuseColor(const Color &diffuseColor) {
        _diffuseColor = diffuseColor;
    }
    void SetSpecularColor(const Color &specularColor) {
        _specularColor = specularColor;
    }
    void SetRoughness(float nu, float nv) {
        _nu = nu;
        _nv = nv;
    }
    
private:
    float _specularLevel;
    float _diffuseLevel;
    Color _diffuseColor;
    Color _specularColor;
    float _nu, _nv;
    
};

#endif /* defined(__cse168project1__AshikhminMaterial__) */
