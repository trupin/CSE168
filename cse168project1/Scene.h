////////////////////////////////////////
// Scene.h
////////////////////////////////////////

#ifndef CSE168_SCENE_H
#define CSE168_SCENE_H

#include "Object.h"
#include "Light.h"

#include <vector>
#include <string>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

////////////////////////////////////////////////////////////////////////////////

class RayTrace;

class Scene {
    friend RayTrace;
    
public:
	Scene()										{SkyColor.Set(0.2f,0.2f,0.5f);}

	void AddObject(Object &obj)					{Objects.push_back(&obj);}
	void AddLight(Light &lgt)					{Lights.push_back(&lgt);}
	void SetSkyColor(const Color sky)			{SkyColor=sky;}

	int GetNumLights()							{return Lights.size();}
	Light &GetLight(int i)						{return *Lights[i];}
	Color GetSkyColor()							{return SkyColor;}

	bool Intersect(const Ray &ray, Intersection &hit) {
        
        bool hashit = false;
        for (Object *obj : Objects) {
            Intersection tHit;
            if (obj->Intersect(ray, tHit) && tHit.HitDistance < hit.HitDistance) {
                hashit = true;
                hit = tHit;
            }
        }
        return hashit;
	}

    bool Load(const std::string &path) {
        Assimp::Importer importer;

        const aiScene *scene = importer.ReadFile(path, aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                                                 aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
        
        if (!scene) {
            std::cerr << importer.GetErrorString() << std::endl;
            return false;
        }

        // process the scene here
//        std::cout << scene->mNumLights << std::endl;
//        
//        std::cout << scene->mNumMeshes << std::endl;
//
//        std::cout << scene->mMeshes[scene->mRootNode->mMeshes[0]]->mTangents << std::endl;
        
        return true;
    }
    
private:
	std::vector<Object*> Objects;
	std::vector<Light*> Lights;
	Color SkyColor;
};

////////////////////////////////////////////////////////////////////////////////

#endif
