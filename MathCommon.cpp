#include "MathCommon.h"

void OutputMatrix(glm::mat4 mat, const char* indent)
{
	if (indent == NULL)
		indent = "";

	for (int i=0; i<4; i++)
	{
		printf("%s[ %f %f %f %f ]\n", indent, mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
	}
}