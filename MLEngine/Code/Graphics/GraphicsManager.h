#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H
#include "../Assert/Assert.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "..\Interfaces\IEntity.h"
#include "GLM\glm.hpp"
#include "GLM\gtx\transform.hpp"
#include "..\Components\StaticMeshNoIndices.h"
#include "..\Components\StaticMesh.h"
#include "..\Resources\ResourceManager.h"
#include "..\Entities\Camera.h"
#include "..\Scenes\SceneTypes.h"
#include <map>

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();
	//TODO - Add another constructor here

	//Init OpenGL Windowing engine
	bool Init(int GLVersionMajor, int GLVersionMinor);

	//Create window to render stuff in and make it current
	bool CreateGraphicsWindow(const int xSize, const int ySize, const char* windowTitle);

	//Draw window, poll events and swap buffers. Returns false if window should be closing
	bool DrawAndUpdateWindow(std::vector<IEntity*> entities, float dt);

	//Handles the window close event
	static void WindowCloseCallback(GLFWwindow* window);

	void DrawEntity(IEntity* ent);

	template <class IComponent>
	void RenderComponents(IComponent* componentToRender, TransformComponent* modelTransform);

	//Getters
	GLFWwindow* GetCurrentWindow();
	const int GetXSize();
	const int GetYSize();
	CameraEntity* GetCurrentCamera();
	SceneLight* GetCurrentSceneLight();
	Shader* GetCurrentShader();

	//Setters
	void SetCurrentCamera(CameraEntity* camera);
	void SetCurrentSceneLight(SceneLight* light);
	void SetCurrentShader(Shader* shader);

private:

	bool UploadShaderDataForDraw(TransformComponent* modelTransform);

	//This class will store the current window
	GLFWwindow* currentWindow;

	//Width and height of window in pixels
	int xSize;
	int ySize;

	Shader* currentShader;
	CameraEntity* currentCamera;
	SceneLight* currentSceneLight;

	static bool windowShouldBeClosed;	
};


#endif