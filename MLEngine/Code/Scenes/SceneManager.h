#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "..\Assert\Assert.h"
#include "..\Graphics\GraphicsManager.h"
#include "..\Interfaces\IEntity.h"
#include "..\resources\Shader.h"
#include "..\Resources\OBJModel.h"
#include "..\Resources\JSONFile.h"
#include "..\entities\Camera.h"
#include "..\entities\GeneralEntity.h"
#include "..\entities\Robot.h"
#include "..\Components\BasicKeyMovement.h"
#include "..\Components\MousePoller.h"
#include "..\Components\StaticMeshNoIndices.h"
#include "..\Components\StaticMesh.h"
#include "..\Messages\BaseMessage.h"
#include "SceneTypes.h"
#include <vector>
#include <map>
#include <sstream>





class SceneManager
{
public:

	SceneManager(std::unique_ptr<GraphicsManager> graph);

	//Load scene into engine
	bool LoadScene(std::unique_ptr<SceneConfig> scene);

	//Generate scene from file
	std::unique_ptr<SceneConfig> LoadSceneFromFile(const char* fileName);

	//Do manager Init stuff
	bool InitSceneManager();

	//Init current stored scene and it's entities
	bool InitCurrentScene();

	//Update all entities
	bool UpdateCurrentSceneEntities(float dt);

	//Draw all scene entities
	bool DrawCurrentSceneEntities(float dt);

	//Destroy all scene entities and their components
	bool DestroyCurrentSceneEntities();

	SceneConfig CreateTestScene();

	void msg_SetCamera(mauvemessage::BaseMessage* msg);

	void msg_ReloadScene(mauvemessage::BaseMessage* msg);

	void msg_ShowDebug(mauvemessage::BaseMessage* msg);

	void msg_LoadGame(mauvemessage::BaseMessage* msg);

	void ReloadScene();

	bool ShouldLoadLevel();


private:
	void AddMessageListner(const char* typeToListen, void* entToBindTo, std::function<void(mauvemessage::BaseMessage*)> functionToBind);
	std::unique_ptr<GraphicsManager> graphicsManager;
	std::unique_ptr<SceneConfig> currentScene;
	bool isLoading;
	bool showDebug;
	bool shouldLoadLevel;
	
};

#endif