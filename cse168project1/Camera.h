//
//  Camera.h
//  cse168project1
//
//  Created by Theophane RUPIN on 4/10/14.
//  Copyright (c) 2014 com. All rights reserved.
//

#ifndef cse168project1_Camera_h
#define cse168project1_Camera_h

#include <string>

#include "Vector3.h"
#include "Scene.h"
#include "Bitmap.h"
#include "Matrix34.h"

class Camera {
public:
    virtual ~Camera() {}
    Camera();
    
    void LookAt(const Vector3 &pos, const Vector3 &target, const Vector3 &up = Vector3::YAXIS);
    void SetResolution(int width, int height);
    void SetFOV(float fov);
    void SetAspect(float aspect);
    void Render(Scene &scn);
    void RenderPath(Scene &scn, int n = -1);
    void SaveBitmap(const std::string &name);
    void SetSuperSample(int superSample);

private:
    Matrix34 _worldMatrix;
    float _verticalFOV, _aspect;
    Bitmap _img;
    int _superSample;
};

#endif
