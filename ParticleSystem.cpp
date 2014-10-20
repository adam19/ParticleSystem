#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem()
{
	particles = NULL;
	numParticles = 0;
}

ParticleSystem::ParticleSystem(const ParticleSystem &p)
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Resize(unsigned int numParticles)
{
	if (particles)
		delete [] particles;

	this->numParticles = numParticles;
	particles = new Particle[numParticles];

	Init();
}

void ParticleSystem::Init()
{
	for (unsigned int i=0; i<numParticles; i++)
	{
		particles[i].alive = false;
		particles[i].mass = 1.0f;
		particles[i].pos = pos;
		particles[i].vel = glm::vec3(0,0,0);
		particles[i].acc = glm::vec3(0,0,0);
	}
}

void ParticleSystem::Update(double dt)
{
	for (unsigned int i=0; i<numParticles; i++)
	{
		if (!particles[i].alive)
			continue;

		particles[i].vel += particles[i].acc;
		particles[i].pos += particles[i].vel;
	}
}

void ParticleSystem::Render(double dt)
{
	for (unsigned int i=0; i<numParticles; i++)
	{
		if (!particles[i].alive)
			continue;

		float s2 = size * 0.5f;

		glVertex3f(particles[i].pos.x - s2, particles[i].pos.y - s2, particles[i].pos.z);
		glVertex3f(particles[i].pos.x + s2, particles[i].pos.y - s2, particles[i].pos.z);
		glVertex3f(particles[i].pos.x + s2, particles[i].pos.y + s2, particles[i].pos.z);
		glVertex3f(particles[i].pos.x - s2, particles[i].pos.y + s2, particles[i].pos.z);
	}
}

void ParticleSystem::operator=(ParticleSystem &rhs)
{
	this->dir = rhs.dir;
	this->pos = rhs.pos;
	this->size = rhs.size;
	this->spread = rhs.spread;
	this->startSpeed = rhs.startSpeed;
}