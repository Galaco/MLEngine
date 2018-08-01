#ifndef TRANFORMCOMPONENT_H
#define TRANFORMCOMPONENT_H
#include "../Messages/BaseMessage.h"
#include "../Messages/PositionMessage.h"
#include "glm/glm.hpp"
#include <iostream>

//For transforming/positioning stuff
class TransformComponent 
{
public:
	//Constructor for the component
	TransformComponent(std::string id);
	TransformComponent(std::string id, glm::vec3 pos);
	TransformComponent(std::string id, glm::vec3 pos, glm::vec3 rot);
	TransformComponent(std::string id, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);

	//Getters/Setters
	glm::vec3 GetPosition() const { return position;};
	glm::vec3 GetRotation() const {	return rotation;};
	glm::vec3 GetScale() const { return scale; };

	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec3 rot);
	void SetScale(glm::vec3 scl);

	virtual void Init();

	//Update method
	virtual void Update(float dt);

	//Gets called to bin us
	virtual void Destroy();

	//Destructor
	virtual ~TransformComponent();

	//Stuff for listening to messages
	void msg_MoveToPosition(mauvemessage::BaseMessage* msg);

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
private:
};



#endif