#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <gl\glew.h>

class Mesh
{
public:
	unsigned int	*vao;
	unsigned int	*vbo;

	unsigned int	numVao;
	unsigned int	numVbo;

	unsigned int	numVerts;

	enum PrimitiveTypes
	{
		POINTS = GL_POINTS,
		TRIANGLES = GL_TRIANGLES,
		TRIANGLE_FAN = GL_TRIANGLE_FAN,
		TRIANGLE_STRIP = GL_TRIANGLE_STRIP
	};
	unsigned int	primitiveType;

	Mesh()
	{
	}

	~Mesh()
	{
		delete [] vao;
		delete [] vbo;
		vao = 0;
		vbo = 0;
	}

	void Render()
	{
		glBindVertexArray(vao[0]);
			glDrawArrays(primitiveType, 0, numVerts);
		glBindVertexArray(0);
	}
};


#endif