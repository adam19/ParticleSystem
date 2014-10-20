#pragma once

#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include "Gz.h"

class Vertex
{
public:
	Vector3			coord;
	Vector3			normal;
	Color			color;
	GzTextureIndex	uv;

	Vertex()
	{
		coord = Vector3(0.0f, 0.0f, 0.0f);
		normal = Vector3(0.0f, 0.0f, 0.0f);
		color = Color(1.0f, 1.0f, 1.0f, 1.0f);

		/*coord[0] = coord[1] = coord[2] = 0.0f;
		normal[0] = normal[1] = normal[2] = 0.0f;
		color[0] = color[1] = color[2] = 1.0f;*/
		uv[0] = uv[1] = 0.0f;
	}

	Vertex(Vertex &v)
	{
		coord = v.coord;
		normal = v.normal;
		color = v.color;

		/*memcpy((GzCoord*)coord, (GzCoord*)v.coord, sizeof(GzCoord));
		memcpy((GzCoord*)normal, (GzCoord*)v.normal, sizeof(GzCoord));
		memcpy((GzColor*)color, (GzColor*)v.color, sizeof(GzColor));*/

		this->uv[0] = v.uv[0];
		this->uv[1] = v.uv[1];
	}

	~Vertex() {}

	void operator=(Vertex &v)
	{
		this->coord.x = v.coord.x;
		this->coord.y = v.coord.y;
		this->coord.z = v.coord.z;
		
		this->normal.x = v.normal.x;
		this->normal.y = v.normal.y;
		this->normal.z = v.normal.z;
		
		this->color.r = v.color.r;
		this->color.g = v.color.g;
		this->color.b = v.color.b;
		
		this->uv[0] = v.uv[0];
		this->uv[1] = v.uv[1];
	}

	void print(FILE* outf)
	{
		fprintf(outf, "<%f %f %f> \t <%f %f %f> \t <%f %f %f> \t [%f %f]\n",
			coord.x, coord.y, coord.z,
			normal.x, normal.y, normal.z,
			color.r, color.g, color.b,
			/*coord[0], coord[1], coord[2],
			normal[0], normal[1], normal[2],
			color[0], color[1], color[2],*/
			uv[0], uv[1]);
	}
};

#endif