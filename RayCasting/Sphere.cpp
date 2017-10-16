#include "sphere.h"

Sphere::Sphere(Vec3f center, float radius, Material* material)
{
	this->center = center;
	this->radius = radius;
	this->material = material;
}

bool Sphere::intersect(const Ray &r, Hit &h, float tmin)
{
	Vec3f direction = r.getDirection();
	Vec3f origin = r.getOrigin();

	float a = direction.Dot3(direction);
	float b = 2 * direction.Dot3(origin - (center));
	float c = (origin - (center)).Length() * (origin - (center)).Length() - radius * radius;
	float delta = b * b - 4 * a * c;
	float t = INT_MAX * 1.0f;
	bool result = false;
	if (delta > 0){
		float d = sqrt(delta);
		float t1 = (-b - d) * 0.5f;
		float t2 = (-b + d) * 0.5f;
		if (t1 >= tmin){
			t = t1;
		}else if (t2 >= tmin){
			t = t2;
		}
		if (t < h.getT()){
			h.set(t, material, r);
		}
		result = true;
	}
	else if (delta == 0){
		float t2 = -b * 0.5f;
		if (t >= tmin){
			t = t2;
		}
		if (t < h.getT()){
			h.set(t, material, r);
		}
		result = true;
	}
	return result;
}

Sphere::~Sphere()
{
	
}