#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include <glm\glm.hpp>
#include <glm\gtx\projection.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Plane.h"


class Frustum
{
public:
	Plane	*planes;

	enum
	{
		LEFT_PLANE,
		RIGHT_PLANE,
		TOP_PLANE,
		BOTTOM_PLANE,
		NEAR_PLANE,
		FAR_PLANE,
		NUM_PLANES
	};

	Frustum()
	{
		planes = new Plane[6];

		planes[LEFT_PLANE] = Plane(glm::vec3(1,0,0), 1);
		planes[RIGHT_PLANE] = Plane(glm::vec3(-1,0,0), 1);
		planes[TOP_PLANE] = Plane(glm::vec3(0,-1,0), 1);
		planes[BOTTOM_PLANE] = Plane(glm::vec3(0,1,0), 1);
		planes[NEAR_PLANE] = Plane(glm::vec3(0,0,1), 1);
		planes[FAR_PLANE] = Plane(glm::vec3(0,0,-1), 1);
	}

	~Frustum() {}

	bool PointInside(glm::vec3 p)
	{
		for (int i=0; i<6; i++)
		{
			if (!planes[i].PointInFront(p))
				return false;
		}
		return true;
	}
};

#endif