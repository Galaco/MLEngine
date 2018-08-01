#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H
#include <vector>
#include "glm/gtx/transform.hpp"
#include "../Components/BoundingVolume.h"
#include "../Components/BoundingBox.h"
#include "../Components/BoundingBoxO.h"
#include "../Components/BoundingSphere.h"
#include "../Components/BoundingCapsule.h"
#include "../Messages/CollisionMessage.h"
#include "../Messages/MessageManager.h"
#include "../Interfaces/IEntity.h"

struct CollisionEvent
{
	CollisionEvent(BoundingVolume* voli, BoundingVolume* volj, CollisionManifold colM)
	{
		volumei = voli;
		volumej = volj;
		collision = colM;
	}
	CollisionEvent()
	{

	}
	BoundingVolume* volumei;
	BoundingVolume* volumej;
	CollisionManifold collision;
};

class CollisionSystem 
{
public:
	virtual ~CollisionSystem();
	void Init();

	bool Update(float dt);

	static void Destroy();

	static void AddStaticVolume(BoundingVolume* volume);
	static void AddDynamicVolume(BoundingVolume* volume);

	static void RemoveObject(IEntity* volume);

	static void CheckCollisions();
	static CollisionManifold CheckVolumes(BoundingVolume* volumea, BoundingVolume* volumeb);
	
	static std::vector<BoundingVolume*> statics;
	static std::vector<BoundingVolume*> dynamics;

	static void ClearVolumes();

private:
	static CollisionManifold HasCollided(BoundingBox* boxa, BoundingBox* boxb);
	static CollisionManifold HasCollided(BoundingBoxO* boxa, BoundingBoxO* boxb);
	static CollisionManifold HasCollided(BoundingBoxO* box, BoundingCapsule* capsule);
};

#endif