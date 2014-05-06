//
//  DirectLight.cpp
//  cse168project1
//
//  Created by Theophane RUPIN on 4/10/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#include "DirectLight.h"

DirectLight::DirectLight() : Light(), _direction() {}

float DirectLight::Illuminate(const Vector3 &pos, Color &col, Vector3 &toLight, Vector3 &ltPos) {
    toLight = -_direction;
    col = BaseColor;
    ltPos = pos - (1000000.f * _direction);
    return Intensity;
}

void DirectLight::SetDirection(const Vector3 &direction) {
    _direction = direction;
    _direction.Normalize();
}

void DirectLight::GetDirection(const Vector3 &pos, Vector3 &dir) const {
    dir = -_direction;
}