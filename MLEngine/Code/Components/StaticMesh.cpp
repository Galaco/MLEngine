#include "StaticMesh.h"

StaticMesh::StaticMesh(std::string id) : IComponent(id)
{
	//Invalidate our IDs
	verticesID = 0;
	normalsID = 0;
	uvID = 0;
	indicesID = 0;
	vaoID = 0;
	currentVAOIndex = 0;
	VAOGenerated = false;
}

StaticMesh::~StaticMesh()
{
	IComponent::~IComponent();
}

void StaticMesh::Init()
{
}

void StaticMesh::Update(float dt)
{
}

void StaticMesh::Destroy()
{
}

bool StaticMesh::UploadVertices(std::vector<GLfloat> verts)
{
	bool result = BufferDataToGPU(verts, verticesID);
	if (result)
	{
		vertices = verts;
	}

	return result;
}


bool StaticMesh::UploadNormals(std::vector<GLfloat> norm)
{
	bool result = BufferDataToGPU(norm, normalsID);
	if (result) normals = norm;
	return result;
}

bool StaticMesh::UploadUVs(std::vector<GLfloat> uvs)
{
	bool result = BufferDataToGPU(uvs, verticesID);
	if (result)
	{
		UVs = uvs;
	}
	return result;
}

bool StaticMesh::UploadIndices(std::vector<GLuint> ind)
{
	bool result = BufferDataToGPU(ind, verticesID);
	if (result)
	{
		indices = ind;
	}
	return result;
}

bool StaticMesh::BufferDataToGPU(std::vector<GLfloat> data, GLuint &bufferAddr)
{


	GenVertexArrays(bufferAddr, vaoID, currentVAOIndex);
	//Generate, bind and upload data
	glGenBuffers(1, &bufferAddr);
	glBindBuffer(GL_ARRAY_BUFFER, bufferAddr);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GL_FLOAT), &(data)[0], GL_STATIC_DRAW);
	glVertexAttribPointer(currentVAOIndex, 3, GL_FLOAT, GL_FALSE, 0, NULL);



	++currentVAOIndex;

	GLenum error = glGetError();
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	return true;
}

bool StaticMesh::BufferDataToGPU(std::vector<GLuint> data, GLuint &bufferAddr)
{

	GenVertexArrays(bufferAddr, vaoID, currentVAOIndex);
	//Generate, bind and upload data
	glGenBuffers(1, &bufferAddr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferAddr);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), &(data)[0], GL_STATIC_DRAW);
	++currentVAOIndex;

	GLenum error = glGetError();
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	return true;
}

bool StaticMesh::GenVertexArrays(GLuint bufferAddr, GLuint &arrayAddr, int &currentIndex)
{
	if (!VAOGenerated)
	{
		glGenVertexArrays(1, &arrayAddr);
		VAOGenerated = true;
	}
	glBindVertexArray(arrayAddr);



	return true;
}


const GLuint StaticMesh::GetVerticesID()
{
	return verticesID;
}


const GLuint StaticMesh::GetNormalsID()
{
	return normalsID;
}

const GLuint StaticMesh::GetVAO()
{
	return vaoID;
}


const std::vector<GLfloat> StaticMesh::GetVertices()
{
	return vertices;
}


const std::vector<GLfloat> StaticMesh::GetNormals()
{
	return normals;
}

const std::vector<GLfloat> StaticMesh::GetUVs()
{
	return UVs;
}

const std::vector<GLuint> StaticMesh::GetIndices()
{
	return indices;
}