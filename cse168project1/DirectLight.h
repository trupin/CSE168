//
//  DirectionLight.h
//  cse168project1
//
//  Created by Theophane RUPIN on 4/10/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#ifndef cse168project1_DirectLight_h
#define cse168project1_DirectLight_h

#include "Light.h"

class DirectLight : public Light {
public:
    virtual ~DirectLight() {}
    DirectLight();
    
    float Illuminate(const Vector3 &pos, Color &col, Vector3 &toLight, Vector3 &ltPos);
    void SetDirection(const Vector3 &direction);
    void GetDirection(const Vector3 &pos, Vector3 &dir) const;

protected:
    Vector3 _direction;
};

#endif
