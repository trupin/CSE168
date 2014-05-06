//
//  PointLight.h
//  cse168project1
//
//  Created by Theophane RUPIN on 4/10/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#ifndef cse168project1_PointLight_h
#define cse168project1_PointLight_h

#include "Light.h"

class PointLight : public Light {
public:
    virtual ~PointLight() {}
    PointLight();
    
    float Illuminate(const Vector3 &pos, Color &col, Vector3 &toLight, Vector3 &ltPos);
    
    void SetPosition(const Vector3 &position);

    void GetDirection(const Vector3 &pos, Vector3 &dir) const;
    
private:
    Vector3 _position;
};

#endif
