#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

#define BOUNDING_TYPE_AABBOX 1
#define BOUNDING_TYPE_OBBOX 2
#define BOUNDING_TYPE_SPHERE 3
#define BOUNDING_TYPE_CAPSULE 4

#include "..\Assert\Assert.h"
#include "..\Interfaces\IComponent.h"
#include "..\..\glm\GLM\glm.hpp"
#include "..\Components\Transform.h"

class BoundingVolume: public IComponent
{
public:
	BoundingVolume(std::string id);
	virtual ~BoundingVolume();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Destroy();
	
	int GetType();

	void SetStatic(bool isStatic);
	bool IsStatic();

	void SetCollided(bool hasCollided);
	bool IsCollided();

	std::string GetOwnerId();

	glm::vec3 Rigid_vel;	//temp rigid body values
	glm::vec3 Rigid_ang;
	float Rigid_mass;
	float Rigid_inverse;
	float Rigid_density;
	float Rigid_friction;
	float Rigid_push;

protected:
	int type;
	bool isStatic;
	bool collided;
	std::string owner;
};
#endif