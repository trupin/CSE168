////////////////////////////////////////
// Vertex.h
////////////////////////////////////////

#ifndef CSE168_VERTEX_H
#define CSE168_VERTEX_H

#include "Vector3.h"

////////////////////////////////////////////////////////////////////////////////

class Vertex {
public:
	void Set(const Vector3 &p, const Vector3 &n, const Vector3 &t)		{Position=p; Normal=n; TexCoord=t;}

public:
	Vector3 Position;
	Vector3 Normal;
	Vector3 TexCoord;
};

////////////////////////////////////////////////////////////////////////////////

#endif