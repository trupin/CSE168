
//
//  Camera.cpp
//  cse168project1
//
//  Created by Theophane RUPIN on 4/10/14.
//  Copyright (c) 2014 com. All rights reserved.
//


#include "Camera.h"
#include "Ray.h"
#include <iostream>

Camera::Camera(): _img(800, 600), _verticalFOV(0.f), _aspect(0.f)  {}

void Camera::LookAt(const Vector3 &pos, const Vector3 &target, const Vector3 &up) {
    _worldMatrix.d = pos;
    _worldMatrix.c = -(_worldMatrix.d - target);
    _worldMatrix.c.Normalize();
    _worldMatrix.a.Cross(up,  _worldMatrix.c);
    _worldMatrix.a.Normalize();
    _worldMatrix.b.Cross(_worldMatrix.c, _worldMatrix.a);
}

void Camera::SetResolution(int width, int height) {
    _img.XRes = width;
    _img.YRes = height;
}

void Camera::SetFOV(float fov) {
    _verticalFOV =  fov * M_PI / 180;
}

void Camera::SetAspect(float aspect) {
    _aspect = aspect;
}

void Camera::Render(Scene &scn) {
    Color color;
    
    for (int y = 0; y < _img.YRes; y++) {
        for (int x = 0; x < _img.XRes; x++) {
            Vector3 cy;
            cy.Cross(_worldMatrix.c, _worldMatrix.b);
            Vector3 cx = cy / pow(cy.Magnitude(), 2);
            cy.Cross(cx, _worldMatrix.c);
            
            float hfov = 2.f * atanf(_aspect * tanf(_verticalFOV / 2.f));
            float cw = 2.f * tanf(hfov/2.f);
            float ch = cw / _aspect;
            
            Ray r;
            r.Origin = _worldMatrix.d;
            
            r.Direction =
            _worldMatrix.c + ((float)(x + 0.5f)/(float)_img.XRes - 0.5f) * cw * cx +
            ((float)(y + 0.5f)/(float)_img.YRes - 0.5f) * ch * cy;
            
            r.isShadow = false;
            
            Intersection hit;
            if (scn.Intersect(r, hit))
                _computeLights(scn, color, hit);
            else
                color = scn.GetSkyColor();
            _img.SetPixel(x, y, color.ToInt());
        }
    }
}

void Camera::_computeLights(Scene &scn, Color &color, Intersection &hit) {
    int i = 0;
    
    float intensity;
    Color tcolor = Color::BLACK;
    for (i = 0; i < scn.GetNumLights(); ++i)
    {
        Light &l = scn.GetLight(i);

        Ray lray;
        lray.Origin = hit.Position;
        l.GetDirection(hit.Position, lray.Direction);
        lray.isShadow = true;
        
        if (scn.Intersect(lray, hit))
            continue;

        Vector3 pos;
        Vector3 toLight;
        intensity = l.Illuminate(hit.Position, color, toLight, pos);

        float diffuse = hit.Normal.Dot(toLight);
        if (diffuse < 0.f)
            diffuse = 0.f;
        
        color.Scale(color, intensity * diffuse);
        tcolor.Add(color);
    }
    color = tcolor;
}


void Camera::SaveBitmap(const std::string &name) {
    _img.SaveBMP(name.c_str());
}

void Camera::SetSuperSample(int superSample) {
    _superSample = superSample;
}