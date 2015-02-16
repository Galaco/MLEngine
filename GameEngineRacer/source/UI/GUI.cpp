#include "UI\GUI.h"


GUI::GUI() :width(0),height(0),j(0),objects(new Object[200]), modelType()
{
	rManager = ResourceManager::getInstance();

}

GUI::~GUI()
{
	delete objects;
	objects = NULL;
	TwTerminate();
}

void TW_CALL GUI::Save(void *clientData)
{ 
	GUI *ui = static_cast<GUI *>(clientData);
	ui->saveData();
}

void TW_CALL GUI::OpenFile(void *clientData)
{
	GUI *ui = static_cast<GUI *>(clientData);
	ui->openFile();
}

void GUI::openFile()
{

	OPENFILENAME ofn={0};
	char szFileName[MAX_PATH]={0};
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.Flags=OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
	ofn.lpstrFilter = "Obj Files\0*.OBJ\0Scene Files\0*.scn\0";
	ofn.lpstrFile=szFileName;
	ofn.nMaxFile=MAX_PATH;
	if(GetOpenFileName(&ofn))
	{
		std::string filename = ofn.lpstrFile;

		std::string newstring = filename.substr(filename.find_last_of("."));


		if(newstring == ".obj")
		{
			ModelLoader mLoader(filename);
			GameObject* g = new GameObject();
			Model* m = new Model();
			filename = filename.substr(filename.find_last_of("\\")+1);

			m->normals = mLoader.getNormals();
			m->verts = mLoader.getVerts();
			m->textureCoords = mLoader.getTextureCoords();
			g->setEntityType("generalEntity");
			g->addToComponentModelFiles(filename);
			g->addToComponentTextureFiles("data\\images\\default.png");
			g->getTransformComp()->Translate(0.0,0.0,0.0);
			g->getTransformComp()->Scale(1.0, 1.0, 1.0);
			g->getTransformComp()->Rotate(0.0, 0.0, 0.0);
			g->getRenderComp()->init(m,rManager->getTexture().at("data\\images\\default.png"),m_scene->getSceneData().sceneShader);
			g->setName(filename);
			m_scene->addGameObject(g);
			TwRemoveAllVars(bar);
			updateLayout();
		}
		else if(newstring == ".scn")
		{
			Scene* newScene = new Scene();
			newScene->LoadScene(filename);
		}
		

	}

}

void GUI::saveData()
{ 

	OPENFILENAME ofn={0};
	char szFileName[MAX_PATH]={0};
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.Flags=OFN_EXPLORER;
	ofn.lpstrFilter="Scene Files (*.scn)\0";
	ofn.lpstrFile=szFileName;
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrDefExt = "scn";

	if(GetSaveFileName(&ofn))
	{
		std::ofstream myfile;
		myfile.open (ofn.lpstrFile);
		myfile << writer.write( m_scene->createJson() );
		myfile.close();
	}


	
}

void GUI::updateLayout()
{

	
	for(unsigned int i=0; i<m_scene->GetGameObjects().size(); ++i)  // Add 'maxLights' variables of type lightType; 
	{                               // unused lights variables (over NumLights) will hidden by Scene::Update( )
		objects[i].x = m_scene->GetGameObjects().at(i)->getTransformComp()->getTranslate().x;
		objects[i].y = m_scene->GetGameObjects().at(i)->getTransformComp()->getTranslate().y;
		objects[i].z = m_scene->GetGameObjects().at(i)->getTransformComp()->getTranslate().z;
		objects[i].xR = m_scene->GetGameObjects().at(i)->getTransformComp()->getRotate().x;
		objects[i].yR = m_scene->GetGameObjects().at(i)->getTransformComp()->getRotate().y;
		objects[i].zR = m_scene->GetGameObjects().at(i)->getTransformComp()->getRotate().z;


		_snprintf(objects[i].type, sizeof(objects[i].type), "%s", m_scene->GetGameObjects().at(i)->getEntityType().c_str());//Copy data into objects.

		_snprintf(objects[i].Name, sizeof(objects[i].Name), "%d", i+1); //Create a unique name;

		std::string grouping = "group="+m_scene->GetGameObjects().at(i)->getEntityType();//Creates the string for grouping.
		TwAddVarRW(bar, objects[i].Name, modelType, &objects[i], grouping.c_str());//Creates Type Grouping.

		char paramValue[64];
		_snprintf(paramValue, sizeof(paramValue), "%s", m_scene->GetGameObjects().at(i)->getName().c_str());
		TwSetParam(bar, objects[i].Name, "label", TW_PARAM_CSTRING, 1, paramValue); // Set label
		std::string fold = "GameEngine/"+m_scene->GetGameObjects().at(i)->getEntityType()+" opened='false'";
		TwDefine(fold.c_str());

	}



	TwDefine("GameEngine help='Press N to change camera'");
	TwAddButton(bar, "Saving", Save, this , " label='Save Scene' ");
	TwAddButton(bar, "OpenFiles", OpenFile, this , " label='Open File BROKEN!!' ");
}
bool GUI::setup(int w, int h, Scene* nScene ) {
	width = w;
	height = h;
	m_scene = nScene;

	TwInit(TW_OPENGL_CORE, NULL);
	bar = TwNewBar("GameEngine");
	TwStructMember objectMembers[] = // array used to describe tweakable variables of the Light structure
	{
		{ "Translate X",    TW_TYPE_FLOAT, offsetof(Object, x),    " help='Translates the object in X.' " },   // Light::Active is a C++ boolean value
		{ "Translate Y",     TW_TYPE_FLOAT, offsetof(Object, y),     " help='Translates the object in Y.' " },        // Light::Color is represented by 4 floats, but alpha channel should be ignored
		{ "Translate Z",    TW_TYPE_FLOAT,   offsetof(Object, z),    " help='Translates the object in Z.' " },
		{ "Rotate X", TW_TYPE_FLOAT,        offsetof(Object, xR), " help='Rotate in the X.' " },  // use the enum 'modeType' created before to tweak the Light::Animation variable
		{ "Rotate Y",     TW_TYPE_FLOAT,   offsetof(Object, yR),    "  help='Rotate in the Y.' " }, // Light::Speed is made read-only
		{ "Rotate Z",     TW_TYPE_FLOAT,   offsetof(Object, zR),    "  help='Rotate in the Z.' " } // Light::Speed is made read-only
	};

	modelType = TwDefineStruct("Object", objectMembers, 6, sizeof(Object), NULL, NULL);  // create a new TwType associated to the struct defined by the lightMembers array
	updateLayout();


	TwWindowSize(width, height);
	return true;
}

void GUI::onResize(int w, int h) {
	width = w;
	height = h;
	TwWindowSize(w, h);
}

void GUI::onMouseMoved(double x, double y) {
	TwMouseMotion((int)x, (int)y);
}

void GUI::onMouseClicked(int bt, int action) {
	TwMouseButtonID btn = (bt == 0) ? TW_MOUSE_LEFT : TW_MOUSE_RIGHT;
	TwMouseAction ma = (action == GLFW_PRESS) ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED;
	TwMouseButton(ma, btn);
}

void GUI::onKeyPressed(int key, int mod) {

	switch(key) {
	case GLFW_KEY_LEFT: key = TW_KEY_LEFT; break;
	case GLFW_KEY_RIGHT: key = TW_KEY_RIGHT; break;
	case GLFW_KEY_UP: key = TW_KEY_UP; break;
	case GLFW_KEY_DOWN: key = TW_KEY_DOWN; break;
	default: break;
	}

	int tw_mod = TW_KMOD_NONE;

	if(mod & GLFW_MOD_SHIFT) {
		tw_mod |= TW_KMOD_SHIFT;
	}

	if(mod & GLFW_MOD_CONTROL) {
		tw_mod |= TW_KMOD_CTRL;
	}

	if(mod & GLFW_MOD_ALT) {
		tw_mod |= TW_KMOD_ALT;
	}

	TwKeyPressed(key, TW_KMOD_NONE);
}
void GUI::update(Scene* nscene)
{
	m_scene=nscene;
	if(m_scene)
	{
		int j =0;
		for(unsigned int i = 0; i < m_scene->GetGameObjects().size(); ++i)
		{   
			m_scene->GetGameObjects().at(i)->getTransformComp()->setTranslate(glm::vec3(objects[i].x,objects[i].y,objects[i].z));
			m_scene->GetGameObjects().at(i)->getTransformComp()->setRotate(glm::vec3(objects[i].xR,objects[i].yR,objects[i].zR)) ;
			if(m_scene->GetGameObjects().at(i)->getEntityType() == "light")
			{
				m_scene->getLights().at(j++).position = glm::vec3(objects[i].x,objects[i].y,objects[i].z);
			}

		}

	}
}
void GUI::draw() {



	TwDraw();
}
