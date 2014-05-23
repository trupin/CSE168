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
    int NSamples() const {
        return 1;
    }
    
    void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) {
        Vector3 h = in + out;
        h.Normalize();

        float kh = in.Dot(h);
        
        // specular
        float specular = sqrtf((_nu + 1.0f) * (_nv + 1.0f)) / (8.0f * PI);
        float hu = h.Dot(hit.TangentU), hv = h.Dot(hit.TangentV), nh = hit.Normal.Dot(h);
        specular *= powf(nh, (_nu * hu * hu + _nv * hv * hv) / (1.0f - nh * nh)) / (kh * Max(hit.Normal.Dot(in), hit.Normal.Dot(out)));
        specular *= _specularLevel + (1.0f - _specularLevel) * powf(1.0f - kh, 5);
        
        // diffuse
        float diffuse = 28.0f * _diffuseLevel * (1.0f - _specularLevel) / (23.0f * PI);
        diffuse *= 1.0f - powf(1.0f - (hit.Normal.Dot(in)) / 2.0f, 5);
        diffuse *= 1.0f - powf(1.0f - (hit.Normal.Dot(out)) / 2.0f, 5);
        
        // intensity
        col = Color::BLACK;
        col.AddScaled(_diffuseColor, diffuse);
        col.AddScaled(_specularColor, specular);
    }
    
    void GenerateSample(int i, Color &col, const Vector3 &in, Vector3 &out, const Intersection &hit) {
        if (((float) rand()) / (float) RAND_MAX < _specularLevel) {
            float E1 = ((float) rand()) / (float) RAND_MAX;
            float E2 = ((float) rand()) / (float) RAND_MAX;
            
            float phi = atanf(sqrtf((_nu + 1) / (_nv + 1)) * tanf(PI * E1 / 2.0f));

            float q = ((float) rand()) / (float) RAND_MAX;

            if (q >= 0.25f && q < 0.5f)
                phi = PI - phi;
            else if (q >= 0.5f && q < 0.75f)
                phi += PI;
            else if (q >= 0.75f && q < 1.0f)
                phi = 2.0f * PI - phi;
        
            float cosPhi = cosf(phi), sinPhi = sinf(phi);
            
            float cosTheta = powf(1.0f - E2, 1.0f / (_nu * cosPhi * cosPhi + _nv * sinPhi * sinPhi + 1.0f));
            float sinTheta = sinf(acosf(cosTheta));

            Vector3 h;
            h.x = sinTheta * cosPhi;
            h.y = cosTheta;
            h.z = sinTheta * sinPhi;

            h = hit.Normal * h.y + hit.TangentU * h.x + hit.TangentV * h.z;
            h.Normalize();

            out =  in + 2.0f * (-in).Dot(h) * h;
            out.Normalize();
            
            if (hit.Normal.Dot(out) < 0.0f)
                col = Color::BLACK;
            else
                col = _specularColor;
         }
        else {
            float r[2];
            r[0] = ((float) rand()) / (float) RAND_MAX;
            r[1] = ((float) rand()) / (float) RAND_MAX;
            
            float u = 2 * PI * r[0];
            float v = sqrtf(1.0f - r[1]);
            
            Vector3 p;
            p.x = v * cosf(u);
            p.y = sqrtf(r[1]);
            p.z = v * sinf(u);
            
            out = hit.Normal * p.y + hit.TangentU * p.x + hit.TangentV * p.z;
            out.Normalize();
            
            col = _diffuseColor;
        }

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
