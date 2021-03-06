#include "Components\RenderComponent.h"

RenderComponent::RenderComponent()
{
	rManager = ResourceManager::getInstance();
};

void RenderComponent::loadTexture(GameObject* g)
{
	OPENFILENAME ofn={0};
	char szFileName[MAX_PATH]={0};
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.Flags=OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR;
	ofn.lpstrFilter = "Images (*.jpg;*.png;*.bmp;*.tga;*.tif)\0*.jpg;*.png;*.bmp;*.tga;*.tif;\0";
	ofn.lpstrFile=szFileName;
	ofn.nMaxFile=MAX_PATH;
	
	if(GetOpenFileName(&ofn))
	{
		std::string filename = ofn.lpstrFile;
		std::string newfilename = filename.substr(filename.find("data"));
		TextureLoader* tLoader = new TextureLoader();
		if (rManager->getTextures_const().find(filename) == rManager->getTextures_const().end() ) 
		{
			
			tLoader->LoadTexture(filename);
			tLoader->FlipImage();
			tLoader->setName(newfilename);
			rManager->addToTexture(std::pair<std::string, Texture*>(newfilename,tLoader->getTexture()));
		}
		
		setTexture(rManager->getTexture().at(newfilename));
		glBindTexture(GL_TEXTURE_2D,texture->object());
		if(g->getComponentTextureFiles().size() != 0)
		{
			g->replaceComponentTextureFile(newfilename);
		}else
		{
			g->addToComponentTextureFiles(newfilename);
		}
		
	}
}
void RenderComponent::init(Model* model, Texture* nTexture)
{
	texture = nTexture;
	m_model = *model;
	indicesCount  = m_model.verts.size()/3;
	// Create and populate the buffer objects using separate buffers

	GLuint vboHandles[3];
	glGenBuffers(3, vboHandles);
	positionBufferHandle = vboHandles[0];
	normalBufferHandle = vboHandles[1];
	uvBufferHandle = vboHandles[2];

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, m_model.verts.size() * sizeof(GLfloat), &m_model.verts[0], GL_STATIC_DRAW);
				
	glBindBuffer(GL_ARRAY_BUFFER, normalBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, m_model.normals.size() * sizeof(GLfloat),&m_model.normals[0] ,GL_STATIC_DRAW);
				 
	glBindBuffer(GL_ARRAY_BUFFER, uvBufferHandle);
	glBufferData(GL_ARRAY_BUFFER,  m_model.textureCoords.size() * sizeof(GLfloat),&m_model.textureCoords[0], GL_STATIC_DRAW);
	
	// Create and set-up the vertex array object
	glGenVertexArrays( 1, &vaoHandle );
	glBindVertexArray(vaoHandle);

	glEnableVertexAttribArray(0);  // Vertex position
	glEnableVertexAttribArray(1);  // Vertex normal
	glEnableVertexAttribArray(2); //uv

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );

	glBindBuffer(GL_ARRAY_BUFFER, normalBufferHandle);
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );

	glBindBuffer(GL_ARRAY_BUFFER, uvBufferHandle);
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );




	
	
	//glDepthGL_nc(glLESS);



	
	
}
void RenderComponent::update()
{
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texture->object());
	
	glBindVertexArray(vaoHandle);
	glEnableVertexAttribArray(0);  // Vertex position
	glEnableVertexAttribArray(1);  // Vertex normal
	glEnableVertexAttribArray(2); //uv
	
	glDrawArrays(GL_TRIANGLES, 0,indicesCount );

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
