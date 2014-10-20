#ifndef __MATHCOMMON_H__
#define __MATHCOMMON_H__

#include <math.h>

#include <glm\glm.hpp>
#include <glm\gtx\projection.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#define PI 3.14159265359
#define PIOVER180 (PI/180.0)

void OutputMatrix(glm::mat4 mat, const char* indent = NULL);

#endif