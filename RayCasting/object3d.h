#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "hit.h"
#include "material.h"
#include "ray.h"

class Object3D
{
public:
	Object3D(){ material = NULL; };
	virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;
	~Object3D(){};
public:
	Material *material;
};

#endif