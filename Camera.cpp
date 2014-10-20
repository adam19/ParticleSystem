#include "Camera.h"


Camera::Camera()
{
	pitchDegrees = 0.0;
	yawDegrees = 90.0;

	width = height = 256;
	fovx = fovy = 1.0f;
	nearDist = 0.1f;
	farDist = 1000.0f;
	ratio = 1.0f;

	pos = glm::vec3(0,0,1);
	target = glm::vec3();

	projMatrix = glm::mat4();
	viewMatrix = glm::mat4();

	isActive = true;

	name = "";
}

Camera::~Camera()
{
}

void Camera::resize(unsigned int width, unsigned int height, float fovy)
{
	this->width = width;
	this->height = height;

	if (height == 0)
		height = 1;

	ratio = (float)width / (float)height;
	
	if (fovy > 0)
	{
		this->fovy = fovy;
		fovx = fovy * ratio;
	}

	projMatrix = glm::perspective<float>(fovy, ratio, nearDist, farDist);

	// extract frustum planes
	glm::vec3 pos = glm::vec3(viewMatrix[3][0], viewMatrix[3][1], viewMatrix[3][2]);
	glm::vec3 view = glm::vec3(viewMatrix[2][0]*farDist-pos[0],
								viewMatrix[2][1]*farDist-pos[1],
								viewMatrix[2][2]*farDist-pos[2]);
	glm::vec3 up = glm::vec3(viewMatrix[1][0], viewMatrix[1][1], viewMatrix[1][2]);
	glm::vec3 right = glm::vec3(viewMatrix[0][0], viewMatrix[0][1], viewMatrix[0][2]);
	float hFar = view.length() * (float)atan(fovy * 0.5);
	float wFar = view.length() * (float)atan(fovx * 0.5);
	glm::vec3 ftl = view + (up * hFar) - (right * wFar);
	glm::vec3 ftr = view + (up * hFar) + (right * wFar);
	glm::vec3 fbl = view - (up * hFar) - (right * wFar);
	glm::vec3 fbr = view - (up * hFar) + (right * wFar);
	
	printf("wFar = %f  hFar = %f\n", wFar, hFar);
	printf("pos: [%f %f %f]\n", pos[0], pos[1], pos[2]);
	printf("view: [%f %f %f]\n", view[0], view[1], view[2]);
	printf("up: [%f %f %f]\n", up[0], up[1], up[2]);
	printf("right: [%f %f %f]\n", right[0], right[1], right[2]);

	printf("ftl: [%f %f %f]\n", ftl[0], ftl[1], ftl[2]);
	printf("ftr: [%f %f %f]\n", ftr[0], ftr[1], ftr[2]);
	printf("fbl: [%f %f %f]\n", fbl[0], fbl[1], fbl[2]);
	printf("fbr: [%f %f %f]\n", fbr[0], fbr[1], fbr[2]);
}

void Camera::resizeDepth(float nearDist, float farDist)
{
	this->nearDist = nearDist;
	this->farDist = farDist;

	resize(width, height, fovy);
}

void Camera::lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up)
{
	viewMatrix = glm::lookAt(pos, target, up);
}

void Camera::getProjMatrix(glm::mat4 &proj)
{
	proj = projMatrix;
}

void Camera::getViewMatrix(glm::mat4 &view)
{
	view = viewMatrix;
}

void Camera::getViewProjMatrix(glm::mat4 &viewProg)
{
	viewProg = this->projMatrix * this->viewMatrix;
}

void Camera::StrafeCamera(float d) // left and right
{
	glm::vec3 right = glm::normalize(glm::cross(target - pos, up));

	pos += right * d;
	target += right * d;

	BuildViewMatrix();
	printf("pos:[%f %f %f]  target:[%f %f %f]\n",
		pos.x, pos.y, pos.z, target.x, target.y, target.z);
}

void Camera::DollyCamera(float d) // forward and backward
{
	glm::vec3 view = glm::normalize(target - pos);

	pos += view * d;
	target += view * d;

	BuildViewMatrix();
	printf("pos:[%f %f %f]  target:[%f %f %f]\n",
		pos.x, pos.y, pos.z, target.x, target.y, target.z);
}

void Camera::BoomCamera(float d)
{
	pos.y += d;
	target.y += d;

	BuildViewMatrix();
}

void Camera::AdjustPitch(float deg)
{
	pitchDegrees += deg;

	if (pitchDegrees > 90)
		pitchDegrees = 89.5;
	if (pitchDegrees < -90)
		pitchDegrees = -89.5;
		
	target.x = (float)cos(yawDegrees*PIOVER180) * (float)cos(pitchDegrees * PIOVER180);
	target.y = (float)sin(pitchDegrees*PIOVER180);
	target.z = (float)sin(yawDegrees*PIOVER180) * (float)cos(pitchDegrees * PIOVER180);
		
	target = glm::normalize(target) + pos;
		
	BuildViewMatrix();
	printf("pos:[%f %f %f]  target:[%f %f %f]\n",
		pos.x, pos.y, pos.z, target.x, target.y, target.z);
}

void Camera::AdjustYaw(float deg)
{
	yawDegrees += deg;

	target.x = (float)cos(yawDegrees*PIOVER180) * (float)cos(pitchDegrees * PIOVER180);
	target.y = (float)sin(pitchDegrees*PIOVER180);
	target.z = (float)sin(yawDegrees*PIOVER180) * (float)cos(pitchDegrees * PIOVER180);

	target = glm::normalize(target) + pos;

	BuildViewMatrix();
	printf("pos:[%f %f %f]  target:[%f %f %f]\n",
		pos.x, pos.y, pos.z, target.x, target.y, target.z);
}

void Camera::RotY(float deg)
{
	yawDegrees += deg;

	glm::vec3 l = glm::normalize(pos - target);

	float mag = (float)l.length();
	pos.x = target.x + (float)cos(yawDegrees*PIOVER180)*mag;
	pos.z = target.z + (float)sin(yawDegrees*PIOVER180)*mag;
		
	BuildViewMatrix();
}

void Camera::GetFrustum(Frustum &f)
{
	// update matrices
	BuildProjMatrix();
	BuildViewMatrix();
		
	// calculate verts on frustum
	glm::vec3 view = glm::vec3(viewMatrix[2][0]*farDist-pos.x,
								viewMatrix[2][1]*farDist-pos.y,
								viewMatrix[2][2]*farDist-pos.z);
	glm::vec3 up = glm::vec3(viewMatrix[1][0], viewMatrix[1][1], viewMatrix[1][2]);
	glm::vec3 right = glm::vec3(viewMatrix[0][0], viewMatrix[0][1], viewMatrix[0][2]);
	float hFar = view.length() * (float)atan(fovy * 0.5);
	float wFar = view.length() * (float)atan(fovx * 0.5);
	float hNear = (view.length() - nearDist) * (float)atan(fovy * 0.5);
	float wNear = (view.length() - nearDist) * (float)atan(fovx * 0.5);

	// far points
	glm::vec3 ftl = view + (up * hFar) - (right * wFar);
	glm::vec3 ftr = view + (up * hFar) + (right * wFar);
	glm::vec3 fbl = view - (up * hFar) - (right * wFar);
	glm::vec3 fbr = view - (up * hFar) + (right * wFar);

	// near points		
	glm::vec3 ntl = view + (up * hNear) - (right * wNear);
	glm::vec3 ntr = view + (up * hNear) + (right * wNear);
	glm::vec3 nbl = view - (up * hNear) - (right * wNear);
	glm::vec3 nbr = view - (up * hNear) + (right * wNear);
}

void Camera::BuildProjMatrix()
{
	ratio = (float)width / (float)height;
	fovx = ratio * fovy;
	projMatrix = glm::perspective<float>(fovy, ratio, nearDist, farDist);
}

inline void Camera::BuildViewMatrix()
{
	viewMatrix = glm::lookAt(pos, target, up);
}

// CameraManager

CameraManager* CameraManager::instance = NULL;
unsigned int CameraManager::currentCameraIndex = 0;
vector<Camera*> CameraManager::cameras;

CameraManager::~CameraManager()
{
}

CameraManager* CameraManager::GetInstance()
{
	if (!instance)
	{
		instance = new CameraManager;
	}
	return instance;
}

Camera* CameraManager::GetCurrentCamera()
{
	return cameras[currentCameraIndex];
}

void CameraManager::AddCamera(Camera *camera)
{
	cameras.push_back(camera);
}

void CameraManager::SetActiveCamera(unsigned int cameraIndex)
{
	for (unsigned int i=0; i<cameras.size(); i++)
		cameras[i]->isActive = false;

	cameras[cameraIndex]->isActive = true;
	currentCameraIndex = cameraIndex;
}
