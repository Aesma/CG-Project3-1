#ifndef CAMERA_H
#define CAMERA_H

#include "vectors.h"
#include "ray.h"
#include "hit.h"

class Camera
{
public:
	virtual Ray generateRay(Vec2f point) = 0;
	virtual float getTMin() const = 0;
};

#endif