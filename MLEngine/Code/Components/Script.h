#ifndef ScriptComponent_H
#define ScriptComponent_H
#include "../Interfaces/IComponent.h"
#include "../Assert/Assert.h"

#include <iostream>
#include <memory>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include <LuaBridge/LuaBridge.h>

class IEntity;

//For transforming/positioning stuff
class ScriptComponent : public IComponent
{
public:
	//Constructor for the component
	ScriptComponent(std::string id = "defaultScript");

	//Getters/Setters
	virtual void Init();
	void Load(std::string filename = "", std::string expectedNamespace = "");

	//Update method
	virtual void Update(float dt);

	//Gets called to bin us
	virtual void Destroy();

	//Destructor
	virtual ~ScriptComponent();

	static void setVM(lua_State*);

	IEntity* owner;

private:
	static lua_State* luaVM;
	static int uid;
	std::string uuid;

	std::shared_ptr<luabridge::LuaRef> luaDataTable;
	std::shared_ptr<luabridge::LuaRef> updateFunc;
	std::shared_ptr<luabridge::LuaRef> startFunc;

	int error;
};



#endif