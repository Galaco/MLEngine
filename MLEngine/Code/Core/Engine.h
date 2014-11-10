#ifndef ENGINE_H
#define ENGINE_H
#include "../Assert/Assert.h"
#include "../States/TestState.h"
#include "..\Graphics\GraphicsManager.h"
#include "..\Entities\GeneralEntity.h"

struct EngineConfig
{
	int resX;
	int resY;
};

class Engine
{
public:
	//Constructor/destructor
	Engine(const EngineConfig conf);
	virtual ~Engine();

	//Init the engine with config
	void Init();

	//Update the engine
	bool Update();
	void Draw();

private:
	//State stuff
	//States will be a collection of systems that all have their own Init/Update/Finish
	std::unique_ptr<IState> currentState;
	std::unique_ptr<GraphicsManager> graphicsManager;
	GeneralEntity* testEntity;

	EngineConfig currentConfig;

	//Load the next state into current state from the current state 
	//(ie - put the next state into the current state and release the pointer for the old state)
	bool LoadNextState();
	int loops;
};

#endif
