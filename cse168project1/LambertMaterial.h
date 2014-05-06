////////////////////////////////////////
// LambertMaterial.h
////////////////////////////////////////

#ifndef CSE168_LAMBERTMATERIAL_H
#define CSE168_LAMBERTMATERIAL_H

#include "Material.h"
#include "Color.h"

////////////////////////////////////////////////////////////////////////////////

class LambertMaterial: public Material {
public:
	void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) {
		col.Scale(_diffuseColor, 1.0f / PI);
	}

    void SetDiffuseColor(const Color &diffuseColor) {
        _diffuseColor = diffuseColor;
    }
    
private:
	Color _diffuseColor;
};

////////////////////////////////////////////////////////////////////////////////

#endif
