////////////////////////////////////////
// Intersection.h
////////////////////////////////////////

#ifndef CSE168_INTERSECTION_H
#define CSE168_INTERSECTION_H

#include "Vector3.h"
#include "Color.h"

class Material;
class Object;

////////////////////////////////////////////////////////////////////////////////

class Intersection {
public:
	Intersection(): Obj(nullptr)			{HitDistance=1e10; Mtl=0;}

public:
	// Ray intersection data
	float HitDistance;
	Vector3 Position;
	Vector3 Normal;
	Material *Mtl;

	// Shaded color
	Color Shade;
    
    Object *Obj;
};

////////////////////////////////////////////////////////////////////////////////

#endif
