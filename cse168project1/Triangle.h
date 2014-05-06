////////////////////////////////////////
// Triangle.h
////////////////////////////////////////

#ifndef CSE168_TRIANGLE_H
#define CSE168_TRIANGLE_H

#include "Vertex.h"
#include "Material.h"
#include "Ray.h"
#include "Object.h"

////////////////////////////////////////////////////////////////////////////////

class Triangle : public Object {
public:
	Triangle();
	void Init(Vertex *v0,Vertex *v1,Vertex *v2,Material *m);

	bool Intersect(const Ray &ray, Intersection &hit);
    
    Vertex &GetVtx(int i) const;

    void ComputeMinMax(Vector3 &min, Vector3 &max) const;

    static bool compareX(Triangle *t1, Triangle *t2) {
        float x1 = t1->Vtx[0]->Position.x + t1->Vtx[1]->Position.x + t1->Vtx[2]->Position.x;
        float x2 = t2->Vtx[0]->Position.x + t2->Vtx[1]->Position.x + t2->Vtx[2]->Position.x;
        return x1 < x2;
    }
    
    static bool compareY(Triangle *t1, Triangle *t2) {
        float y1 = t1->Vtx[0]->Position.y + t1->Vtx[1]->Position.y + t1->Vtx[2]->Position.y;
        float y2 = t2->Vtx[0]->Position.y + t2->Vtx[1]->Position.y + t2->Vtx[2]->Position.y;
        return y1 < y2;
    }

    static bool compareZ(Triangle *t1, Triangle *t2) {
        float z1 = t1->Vtx[0]->Position.z + t1->Vtx[1]->Position.z + t1->Vtx[2]->Position.z;
        float z2 = t2->Vtx[0]->Position.z + t2->Vtx[1]->Position.z + t2->Vtx[2]->Position.z;
        return z1 < z2;
    }

    
private:
	Vertex *Vtx[3];
	Material *Mtl;
};

////////////////////////////////////////////////////////////////////////////////

#endif
