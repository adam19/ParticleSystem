#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <vector>

#include <glm\glm.hpp>
#include <glm\gtx\projection.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "MathCommon.h"
#include "Frustum.h"

using namespace std;


class Camera
{
private:
	/*glm::vec3	pos;
	glm::vec3	target;
	glm::vec3	up;
	double		pitchDegrees;
	double		yawDegrees;

	int			width, height;
	float		fovx, fovy;
	float		nearDist, farDist;
	float		ratio;*/

public:
	glm::vec3	pos;
	glm::vec3	target;
	glm::vec3	up;
	double		pitchDegrees;
	double		yawDegrees;

	int			width, height;
	float		fovx, fovy;
	float		nearDist, farDist;
	float		ratio;



	glm::mat4	projMatrix;
	glm::mat4	viewMatrix;

	bool		isActive;
	string		name;

	Camera();
	~Camera();

	void resize(unsigned int width, unsigned int height, float fovy=0);
	void resizeDepth(float nearDist, float farDist);

	void lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
	void getProjMatrix(glm::mat4 &proj);
	void getViewMatrix(glm::mat4 &view);
	void getViewProjMatrix(glm::mat4 &viewProg);

	void StrafeCamera(float d);	// left and right
	void DollyCamera(float d); // forward and backward
	void BoomCamera(float d);
	void AdjustPitch(float deg);
	void AdjustYaw(float deg);
	void RotY(float deg);
	void GetFrustum(Frustum &f);	
	void BuildProjMatrix();

private:
	inline void BuildViewMatrix();
};

class CameraManager
{
private:
	static CameraManager	*instance;

	static vector<Camera*>	cameras;	
	static unsigned int		currentCameraIndex;

	CameraManager()
	{
		currentCameraIndex = -1;
		instance = NULL;
	}

	~CameraManager();

public:
	static CameraManager* GetInstance();
	static Camera* GetCurrentCamera();

	void AddCamera(Camera *camera);
	void SetActiveCamera(unsigned int cameraIndex);
};

#endif