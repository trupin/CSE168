
//
//  Camera.cpp
//  cse168project1
//
//  Created by Theophane RUPIN on 4/10/14.
//  Copyright (c) 2014 com. All rights reserved.
//


#include "Camera.h"
#include "Ray.h"
#include "Material.h"
#include "RayTrace.h"
#include "DielectricMaterial.h"

#include <iostream>

Camera::Camera(): _img(800, 600), _verticalFOV(0.f), _aspect(0.f), _superSample(10) {}

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
    _verticalFOV =  fov * PI / 180;
}

void Camera::SetAspect(float aspect) {
    _aspect = aspect;
}

void Camera::Render(Scene &scn) {
    RenderPath(scn);
    SaveBitmap("tmp-rendering.bmp");
    std::cout << "Rendered initial pass" << std::endl;
    for (int i = 0; i < _superSample; ++i) {
        RenderPath(scn, i + 1);
        SaveBitmap("tmp-rendering.bmp");
        std::cout << "Rendered " << i << " pass" << std::endl;
    }
}

void Camera::RenderPath(Scene &scn, int n) {
    RayTrace rayTrace(scn);
    
    for (int y = 0; y < _img.YRes; y++) {
        for (int x = 0; x < _img.XRes; x++) {
            
            // compute the primary ray
            Vector3 cy;
            cy.Cross(_worldMatrix.c, _worldMatrix.b);
            Vector3 cx = cy / pow(cy.Magnitude(), 2);
            cy.Cross(cx, _worldMatrix.c);
            
            float hfov = 2.f * atanf(_aspect * tanf(_verticalFOV / 2.f));
            float cw = 2.f * tanf(hfov/2.f);
            float ch = cw / _aspect;
            
            Ray ray;
            ray.Origin = _worldMatrix.d;
            
            ray.Direction =
            _worldMatrix.c + ((float)(x + 0.5f) / (float)_img.XRes - 0.5f) * cw * cx +
            ((float)(y + 0.5f)/(float)_img.YRes - 0.5f) * ch * cy;
            
            ray.type = Ray::PRIMARY;
            
            // shoot the primary ray
            Intersection hit;
            if (x > 124 && x <= 140 && y == _img.YRes - 495 ) {
//                Color white = Color::WHITE;
//                std::cout << "debug pixel" << std::endl;
//                _img.SetPixel(x, y, white.ToInt());
//                continue;
            }
            
            rayTrace.TraceRay(ray, hit);
            
            if (n != -1) {
                Color c;
                c.FromInt(_img.GetPixel(x, y));
                
                Color avg = Color::BLACK;
                avg.AddScaled(c, n - 1);
                avg.Add(hit.Shade);
                avg.Scale(1.0f / n);
                _img.SetPixel(x, y, avg.ToInt());
            }
            else _img.SetPixel(x, y, hit.Shade.ToInt());
        }
    }
    
}

void Camera::SaveBitmap(const std::string &name) {
    _img.SaveBMP(name.c_str());
}

void Camera::SetSuperSample(int superSample) {
    _superSample = superSample;
}