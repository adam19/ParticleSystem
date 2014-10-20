#ifndef __PARTICLESYSTEM_HPP__
#define __PARTICLESYSTEM_HPP__

#include <gl\glew.h>

#include <glm\glm.hpp>

#include "Mesh.hpp"

struct Particle
{
	glm::vec3	pos;
	glm::vec3	vel;
	glm::vec3	acc;
	float		mass;
	bool		alive;

	Mesh		m;
};

class ParticleSystem
{
public:
	ParticleSystem();
	ParticleSystem(const ParticleSystem&);
	~ParticleSystem();

	void Resize(unsigned int numParticles);

	void Init();
	void Update(double dt);
	void Render(double dt);

	glm::vec3		pos;
	glm::vec3		dir;
	float			spread;

	float			startSpeed;
	float			size;

	void operator=(ParticleSystem &rhs);

private:
	Particle		*particles;
	unsigned int	numParticles;
};

#endif