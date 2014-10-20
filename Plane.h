#ifndef __PLANE_H__
#define __PLANE_H__

#include <glm\glm.hpp>
#include <glm\gtx\projection.hpp>
#include <glm\gtc\matrix_transform.hpp>


class Plane
{
public:
	glm::vec3	normal;
	float		dist;

	Plane()
	{
		this->Plane::Plane(glm::vec3(0,1,0), 0);
	}

	Plane(glm::vec3 n, float d)
	{
		normal = n;
		dist = d;
	}

	bool inline PointInFront(glm::vec3 p)
	{
		if (glm::dot(normal, p) + dist > 0)
			return true;
		return false;
	}
};

#endif