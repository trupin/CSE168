//
//  PointLight.cpp
//  cse168project1
//
//  Created by Theophane RUPIN on 4/10/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#include "PointLight.h"

PointLight::PointLight() : Light(), _position() {}

float PointLight::Illuminate(const Vector3 &pos, Color &col, Vector3 &toLight, Vector3 &ltPos) {
    toLight = _position - pos;
    float b = Intensity / toLight.Magnitude2();
    toLight.Normalize();
    col = BaseColor;
    ltPos = _position;
    return b;
}

void PointLight::SetPosition(const Vector3 &position) {
    _position = position;
}

void PointLight::GetDirection(const Vector3 &pos, Vector3 &dir) const  {
    dir = _position - pos;
    dir.Normalize();
}
