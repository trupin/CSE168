////////////////////////////////////////
// Material.h
////////////////////////////////////////

#ifndef CSE168_MATERIAL_H
#define CSE168_MATERIAL_H

#include "Intersection.h"

////////////////////////////////////////////////////////////////////////////////

class Material {
public:
    virtual ~Material() {}
    
public:
    virtual int NSamples() const = 0;
	virtual void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit)=0;
    virtual void GenerateSample(int i, Color &col, const Vector3 &in, Vector3 &out, const Intersection &hit) = 0;
};

////////////////////////////////////////////////////////////////////////////////

#endif
