#ifndef GUI_H
#define GUI_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <AntTweakBar.h>
#include "Scene\Scene.h"
#include <vector>
#include <assert.h>
#include "3rdParty\gl_core_4_3.hpp"
#include "glfw3.h"
#include <commdlg.h>
#include "ResourceManager.h"
#include <fstream>

enum LoadState {OPEN, DONTOPEN};

class GUI {
private:
	struct Object{
		///char type[32];
		glm::vec3 pos;
		bool useRotBall;
		glm::quat rot;
		glm::vec3 eulers;
		glm::vec3 scale;
		char    name[4];
	};

	struct GUILight{
		glm::vec3 position;
		glm::vec3 diffuse;
	};
	static LoadState loadfile;
	GUILight* lights;
	Light light;
	TwType modelType, lightType;
	Object* objects;
	TwBar* bar, *lightbar;

	ResourceManager* rManager;
	int width;
	int height;
	Scene* m_scene;
	Json::StyledWriter writer;
	int j;
	void saveData();
	void deleteLightBar();
	void addToLights();
	void createLight();
	void updateObjects();
	void updateLights();
	void openFile(std::vector<Scene*>& scene, int& activeScene);
public:
	GUI();
	~GUI();
	bool setup(int w, int h, Scene* nScene );
	void onMouseMoved(double x, double y);
	void onMouseClicked(int bt, int action);
	void onKeyPressed(int key, int mod);
	void onResize(int w, int h);
	void draw();


	void checkOpenFile(std::vector<Scene*>& scene, int& activeScene);
	void update(Scene* scene);

	Scene* getScene(){return m_scene;};
	static void TW_CALL DeleteLightBar(void *clientData);
	static void TW_CALL AddtoLights(void *clientData);
	static void TW_CALL Save(void *clientData);
	static void TW_CALL OpenFile(void *clientData);
	static void TW_CALL CreateLight(void *clientData);
	static void TW_CALL CopyStdStringToClient(std::string& destinationClientString, const std::string& sourceLibraryString);
	
};


#endif

