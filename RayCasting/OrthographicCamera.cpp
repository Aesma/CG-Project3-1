#include "OrthographicCamera.h";

OrthographicCamera::OrthographicCamera(Vec3f center, Vec3f direction, Vec3f up, float size)
{
	this->center = center;
	this->direction = direction;
	this->up = up;
	this->size = size;
	this->direction.Normalize();
	this->up.Normalize();
	Vec3f::Cross3(this->horizontal, this->direction, this->up);
	Vec3f::Cross3(this->up, this->horizontal, this->direction);
	this->horizontal.Normalize();
}

Ray OrthographicCamera::generateRay(Vec2f point)
{
	Vec3f origin = center + horizontal * point.x() * size * 0.5 + up * point.y() * size * 0.5;
	return Ray(origin, direction);
}

float OrthographicCamera::getTMin() const
{
	return -1.0f * INT_MAX;
}