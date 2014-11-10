#include "Transform.h"

TransformComponent::TransformComponent(std::string id) : IComponent(id)
{
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
}

TransformComponent::TransformComponent(std::string id, glm::vec3 pos) : IComponent(id)
{
	position = pos;
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
}

TransformComponent::TransformComponent(std::string id, glm::vec3 pos, glm::vec3 rot) : IComponent(id)
{
	position = pos;
	rotation = rot;
	scale = glm::vec3(1.0f);
}

TransformComponent::TransformComponent(std::string id, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl) : IComponent(id)
{
	position = pos;
	rotation = rot;
	scale = scl;
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetPosition(glm::vec3 pos)
{
	position = pos;
}

void TransformComponent::SetRotation(glm::vec3 rot)
{
	rotation = rot;
}

void TransformComponent::SetScale(glm::vec3 scl)
{
	scale = scl;
}

glm::vec3 TransformComponent::GetPosition()
{
	return position;
}

glm::vec3 TransformComponent::GetRotation()
{
	return rotation;
}

glm::vec3 TransformComponent::GetScale()
{
	return scale;
}

void TransformComponent::Init()
{
}

void TransformComponent::Update(float dt)
{
}

void TransformComponent::Destroy()
{
}


