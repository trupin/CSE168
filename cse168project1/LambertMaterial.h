////////////////////////////////////////
// LambertMaterial.h
////////////////////////////////////////

#ifndef CSE168_LAMBERTMATERIAL_H
#define CSE168_LAMBERTMATERIAL_H

#include "Material.h"
#include "Color.h"


#include <iostream>

////////////////////////////////////////////////////////////////////////////////

class LambertMaterial: public Material {
public:
    int NSamples() const {
        return 1;
    }
    
	void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) {
        col = _diffuseColor;
	}

    void GenerateSample(int i, Color &col, const Vector3 &in, Vector3 &out, const Intersection &hit) {
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
    
    void SetDiffuseColor(const Color &diffuseColor) {
        _diffuseColor = diffuseColor;
    }
        
private:
	Color _diffuseColor;
};

////////////////////////////////////////////////////////////////////////////////

#endif
