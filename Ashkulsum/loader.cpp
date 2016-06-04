#include "stdafx.h"
#include "loader.h"

Loader::Loader (){}
Loader::~Loader (){}

//coordinates
void Loader::SetVertices (std::vector <glm::vec3> vertices)
{
	this->vertices = vertices;
}

void Loader::SetTexCoords (std::vector <glm::vec2> texCoords)
{
	this->texCoords = texCoords;
}

void Loader::SetColours (std::vector <glm::vec4> colours)
{
	this->colours = colours;
}

void Loader::SetIndicesVertices (std::vector <GLshort> indicesVertices)
{
	this->indicesVertices = indicesVertices;
}

void Loader::SetIndicesTexCoords (std::vector <GLshort> indicesTexCoords)
{
	this->indicesTexCoords = indicesTexCoords;
}

void Loader::SetIndicesColours (std::vector <GLshort> indicesColours)
{
	this->indicesColours = indicesColours;
}

void Loader::SetProcessedVertices (std::vector <glm::vec3> processedVertices)
{
	this->processedVertices = processedVertices;
}

void Loader::SetProcessedTexCoords (std::vector <glm::vec2> processedTexCoords)
{
	this->processedTexCoords = processedTexCoords;
}

void Loader::SetProcessedColours (std::vector <glm::vec4> processedColours)
{
	this->processedColours = processedColours;
}

void Loader::SetFaceNormals (std::vector <glm::vec3> faceNormals)
{
	this->faceNormals = faceNormals;
}

void Loader::SetVertexNormals (std::vector <glm::vec3> vertexNormals)
{
	this->vertexNormals = vertexNormals;
}

//array
void Loader::SetVao (GLuint vao)
{
	this->vao = vao;
}

//buffers
void Loader::SetVertexBufferObject (GLuint vertexBufferObject)
{
	this->vertexBufferObject = vertexBufferObject;
}

void Loader::SetColourBufferObject (GLuint colourBufferObject)
{
	this->colourBufferObject = colourBufferObject;
}

void Loader::SetNormalBufferObject (GLuint normalBufferObject)
{
	this->normalBufferObject = normalBufferObject;
}

void Loader::SetShadowTextureObject (GLuint shadowTextureObject)
{
	this->shadowTextureObject = shadowTextureObject;
}

void Loader::SetTextureBufferObject (GLuint textureBufferObject)
{
	this->textureBufferObject = textureBufferObject;
}

void Loader::SetDrawPrimitive (Primitives drawPrimitive)
{
	this->drawPrimitive = drawPrimitive;
}

// Texture

void Loader::SetTextureNum (int textureNum)
{
	this->textureNum = textureNum;
}

void Loader::SetTexture (GLuint texture)
{
	this->texture = texture;
}

void Loader::SetName (std::string name)
{
	this->name = name;
}

//coordinates
std::vector <glm::vec3> Loader::GetVertices ()
{
	return this->vertices;
}

std::vector <glm::vec2> Loader::GetTexCoords ()
{
	return this->texCoords;
}

std::vector <glm::vec4> Loader::GetColours ()
{
	return this->colours;
}

std::vector <GLshort> Loader::GetIndicesVertices ()
{
	return this->indicesVertices;
}

std::vector <GLshort> Loader::GetIndicesTexCoords ()
{
	return this->indicesTexCoords;
}

std::vector <GLshort> Loader::GetIndicesColours ()
{
	return this->indicesColours;
}

std::vector <glm::vec3> Loader::GetProcessedVertices ()
{
	return this->processedVertices;
}

std::vector <glm::vec2> Loader::GetProcessedTexCoords()
{
	return this->processedTexCoords;
}

std::vector <glm::vec4> Loader::GetProcessedColours()
{
	return this->processedColours;
}

std::vector <glm::vec3> Loader::GetFaceNormals()
{
	return this->faceNormals;
}

std::vector <glm::vec3> Loader::GetVertexNormals ()
{
	return this->vertexNormals;
}

//array
GLuint Loader::GetVao ()
{
	return this->vao;
}

//buffers
GLuint Loader::GetVertexBufferObject ()
{
	return this->vertexBufferObject;
}

GLuint Loader::GetColourBufferObject ()
{
	return this->colourBufferObject;
}

GLuint Loader::GetNormalBufferObject ()
{
	return this->normalBufferObject;
}

GLuint Loader::GetShadowTextureObject ()
{
	return this->shadowTextureObject;
}

GLuint Loader::GetTextureBufferObject ()
{
	return this->textureBufferObject;
}

Primitives Loader::GetDrawPrimitive ()
{
	return this->drawPrimitive;
}

//Texture

int Loader::GetTextureNum ()
{
	return this->textureNum;
}

GLuint Loader::GetTexture ()
{
	return this->texture;
}
std::string Loader::GetName ()
{
	return this->name;
}
/////////////////////////////////////////////////////////// DRAW PRIMITIVES ////////////////////////////////////////////////
void Loader::ProcessDrawPrimitive (const std::string shaderPath)
{	
	std::string line;
	const char * strShaderPath = shaderPath.c_str();
	std::ifstream fileStream (strShaderPath, std::ios::in);
	getline (fileStream, line);
	if	(line == "line")
		SetDrawPrimitive (Line);
	else
		SetDrawPrimitive (Triangle);
}
////////////////////////////////////////////////////////       LOAD OBJECTS FROM FILE          //////////////////////////////
void Loader::LoadObjectVertices (const std::string Path)
{
	std::string line;
	const char * strPath = Path.c_str();
	std::ifstream fileStream (strPath, std::ios::in);
	std::vector <glm::vec3> vertices = GetVertices ();

	while (!fileStream.eof())
	{
		getline (fileStream, line);
		if	(!line.empty () && (line.substr (0, 2) == "v "))
		{
				std::istringstream s(line.substr(2));
				glm::vec3 v; s >> v.x >> v.y >> v.z;
				vertices.push_back (v);
		}
	}
	fileStream.close ();
	SetVertices (vertices);
	std::vector <glm::vec3>().swap (vertices);
}

void Loader::LoadObjectTexCoords (const std::string Path)
{
	std::string line;
	const char * strPath = Path.c_str();
	std::ifstream fileStream (strPath, std::ios::in);
	std::vector <glm::vec2> texCoords = GetTexCoords ();
	while (!fileStream.eof())
	{
		getline (fileStream, line);
		if	(!line.empty () && (line.substr (0, 2) == "vt"))
		{
				std::istringstream s(line.substr(2));
				glm::vec2 t; s >> t.x >> t.y;
				t.y = 1.0f - t.y;
				texCoords.push_back (t);
		}
	}
	fileStream.close ();
	SetTexCoords (texCoords);
	std::vector <glm::vec2>().swap (texCoords);
}
void Loader::LoadObjectColours (const std::string Path)
{
	// OBJ does not support colours
}

void Loader::LoadObjectIndices (const std::string Path)
{	
	if (Triangle == GetDrawPrimitive ())
	{
	std::vector <GLshort> indicesVertices = GetIndicesVertices ();
	std::vector <GLshort> indicesTexCoords = GetIndicesTexCoords ();
	std::string ident = "f ";
	std::string line;
	const char * strPath = Path.c_str();
	std::ifstream fileStream (strPath, std::ios::in);
	while (!fileStream.eof())
	{
		getline (fileStream, line);
		if	(!line.empty () && (line.substr (0, 2) == ident))
			{
				std::istringstream s(line.substr(2));
				char tmp; // For the slashes between elements
                unsigned short a,b,c, d,e,f;
                s >> a >> tmp >> d;
                s >> b >> tmp >> e;
                s >> c >> tmp >> f;
                a--; b--; c--; d--; e--; f--;
				indicesVertices.push_back (a); indicesVertices.push_back (b); indicesVertices.push_back (c);
				indicesTexCoords.push_back (d); indicesTexCoords.push_back (e); indicesTexCoords.push_back (f);
			}
	}
	fileStream.close ();
	SetIndicesVertices(indicesVertices);
	SetIndicesTexCoords(indicesTexCoords);
	std::vector <GLshort>().swap (indicesVertices);
	std::vector <GLshort>().swap (indicesTexCoords);
	}
	else
	{
		std::vector <GLshort> indicesVertices = GetIndicesVertices();
		std::string ident = "l ";
		std::string line;
		const char * strPath = Path.c_str();
		std::ifstream fileStream (strPath, std::ios::in);
		while (!fileStream.eof())
		{
			getline (fileStream, line);
			if	(!line.empty () && (line.substr (0, 2) == ident))
			{
				std::istringstream s(line.substr(2));
				GLushort a,b;
				s >> a >> b;
				a--; b--;
				indicesVertices.push_back (a); indicesVertices.push_back (b);
			}
		}	
		fileStream.close ();
		SetIndicesVertices(indicesVertices);
		std::vector <GLshort>().swap (indicesVertices);
	}
}

void Loader::LoadObjectFile (const std::string Path)
{
	std::string strFilename = LOCAL_OBJECT_DIR + Path;
	ProcessDrawPrimitive (strFilename);
	LoadObjectVertices (strFilename);
	LoadObjectTexCoords (strFilename);
	LoadObjectIndices (strFilename);
}
//////////////////////////////////////////////////////// LOAD TEXTURE //////////////////////////////////////////////
void Loader::LoadTexture( std::string strPath, GLenum enumerator)
{
	Loader* self = this;

	GLuint texture = self->GetTexture ();
	int textureNum = self->GetTextureNum ();
	int img_width, img_height;
	std::string strImagePath = LOCAL_TEXTURE_DIR + strPath;
	unsigned char* image = SOIL_load_image(strImagePath.c_str (), &img_width, &img_height, 0, SOIL_LOAD_RGB);

	glBindTexture (enumerator, texture);
	if (enumerator == GL_TEXTURE_2D)
	{glTexImage2D( enumerator, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);}	

	SOIL_free_image_data(image);
	glTexParameteri(enumerator, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(enumerator, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(enumerator, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(enumerator, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture (enumerator, 0);
}

void Loader::ActivateTexture (GLenum enumerator)
{
	Loader* self = this;
	GLuint texture = self->GetTexture ();
	int textureNum = self->GetTextureNum ();
	glActiveTexture(GL_TEXTURE0 + textureNum);
	glBindTexture(enumerator, texture);
}

////////////////////////////////////////////////////    INITIALIZE COORDINATES     ///////////////////////////////////
void Loader::ProcessFaceNormals ()
{
	if (Triangle == GetDrawPrimitive ())
	{
		std::vector <glm::vec3> faceNormals = GetFaceNormals();
		std::vector <glm::vec3> vertices = GetVertices ();
		std::vector <GLshort> indicesVertices = GetIndicesVertices ();
		if (!vertices.empty () && !indicesVertices.empty ())
		{
			faceNormals.resize(vertices.size(), glm::vec3(0.0f));
			std::vector<GLshort> nb_seen;
			nb_seen.resize(vertices.size(), 0);
			for (unsigned int i = 0; i < indicesVertices.size(); i+=3) 
			{
				GLushort ia = indicesVertices[i];
				GLushort ib = indicesVertices[i+1];
				GLushort ic = indicesVertices[i+2];
				glm::vec3 cross = glm::cross(glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
									 glm::vec3(vertices[ic]) - glm::vec3(vertices[ia]));
				glm::vec3 normal = glm::normalize(cross);
				int v[3]; v[0] = ia; v[1] = ib; v[2] = ic;
				for (int j = 0; j < 3; j++) 
				{
					GLushort cur_v = v[j];
					nb_seen[cur_v]++;
					if (nb_seen[cur_v] == 1) 
					{
						faceNormals[cur_v] = normal;
					} else 
					{
					// average
						faceNormals[cur_v].x = faceNormals[cur_v].x * (1.0f - 1.0f/nb_seen[cur_v]) + normal.x * 1.0f/nb_seen[cur_v];
						faceNormals[cur_v].y = faceNormals[cur_v].y * (1.0f - 1.0f/nb_seen[cur_v]) + normal.y * 1.0f/nb_seen[cur_v];
						faceNormals[cur_v].z = faceNormals[cur_v].z * (1.0f - 1.0f/nb_seen[cur_v]) + normal.z * 1.0f/nb_seen[cur_v];		
						faceNormals[cur_v] = glm::normalize(faceNormals[cur_v]);
					}
				}
			}
			SetFaceNormals (faceNormals);
			std::vector <glm::vec3>().swap (faceNormals);
			std::vector <glm::vec3>().swap (vertices);
			std::vector <GLshort>().swap (indicesVertices);
		} 
	}
}
void Loader::ProcessVertexNormals ()
{
	std::vector <glm::vec3> faceNormals = GetFaceNormals();
	std::vector <glm::vec3> vertexNormals = GetVertexNormals();
	std::vector <GLshort> indicesVertices = GetIndicesVertices ();
	if (!faceNormals.empty())
	{
		for( unsigned int v=0; v<indicesVertices.size(); v+=3 )
		{
			// For each vertex of the triangle
			for ( unsigned int i=0; i<3; i+=1 )
			{
				unsigned int vertexIndex = indicesVertices[v+i];
				glm::vec3 normal = faceNormals[ vertexIndex ];
				vertexNormals.push_back(normal);
			}
		}
		SetVertexNormals (vertexNormals);
		std::vector <glm::vec3>().swap (faceNormals);
		std::vector <glm::vec3>().swap (vertexNormals);
		std::vector <GLshort>().swap (indicesVertices);
	}
}

void Loader::ProcessVertices ()
{
	unsigned int indices;
	if (Triangle == GetDrawPrimitive ())
		indices = 3;
	else
		indices = 2;

	std::vector <glm::vec3> vertices = GetVertices();
	std::vector <glm::vec3> processedVertices = GetProcessedVertices();
	std::vector <GLshort> indicesVertices = GetIndicesVertices();
	if (!vertices.empty () && !indicesVertices.empty ())
	{
		for( unsigned int v=0; v<indicesVertices.size(); v+=indices )
		{
			// For each vertex of the triangle
			for ( unsigned int i=0; i<indices; i+=1 )
			{
				unsigned int vertexIndex = indicesVertices[v+i];
				glm::vec3 vertex = vertices[ vertexIndex ];
				processedVertices.push_back(vertex);
			}
		}
		SetProcessedVertices (processedVertices);
		std::vector <glm::vec3>().swap (vertices);
		std::vector <glm::vec3>().swap (processedVertices);
		std::vector <GLshort>().swap (indicesVertices);
	}
}

void Loader::ProcessTexCoords ()
{
	unsigned int indices;
	if (Triangle == GetDrawPrimitive ())
		indices = 3;
	else
		indices = 2;

	std::vector <glm::vec2> texCoords = GetTexCoords ();
	std::vector <glm::vec2> processedTexCoords = GetProcessedTexCoords();
	std::vector <GLshort> indicesTexCoords = GetIndicesTexCoords ();
	
	if (!texCoords.empty() && !indicesTexCoords.empty())
	{
		for( unsigned int t=0; t<indicesTexCoords.size(); t+=indices )
		{
			// For each vertex of the triangle
			for ( unsigned int i=0; i<indices; i+=1 )
			{
				unsigned int texCoordIndex = indicesTexCoords[t+i];
				glm::vec2 texCoord = texCoords[ texCoordIndex ];
				processedTexCoords.push_back(texCoord);
			}
		}
		SetProcessedTexCoords (processedTexCoords);
		std::vector <glm::vec2>().swap (texCoords);
		std::vector <glm::vec2>().swap (processedTexCoords);
		std::vector <GLshort>().swap (indicesTexCoords);
	}
}
void Loader::ProcessColours ()
{
	unsigned int indices;
	if (Triangle == GetDrawPrimitive ())
		indices = 3;
	else
		indices = 2;

	std::vector <glm::vec4> colours = GetColours ();
	std::vector <glm::vec4> processedColours = GetProcessedColours();
	std::vector <GLshort> indicesColours = GetIndicesColours ();
	
	if (!colours.empty() && !indicesColours.empty())
	{
		for( unsigned int c=0; c<indicesColours.size(); c+=indices )
		{
			// For each colour of the triangle
			for ( unsigned int i=0; i<indices; i+=1 )
			{
				unsigned int colourIndex = indicesColours[c+i];
				glm::vec4 colour = colours[ colourIndex ];
				processedColours.push_back(colour);
			}
		}
		SetProcessedColours (processedColours);
		std::vector <glm::vec4>().swap (colours);
		std::vector <glm::vec4>().swap (processedColours);
		std::vector <GLshort>().swap (indicesColours);
	}
}
void Loader::InitializeVertexBuffer ()
{
	const std::vector <glm::vec3> processedVertices = GetProcessedVertices ();
	if (!processedVertices.empty())
	{
		GLuint vertexBufferObject = GetVertexBufferObject();
		glGenBuffers(1, &vertexBufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, processedVertices.size ()*sizeof (glm::vec3), &processedVertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		SetVertexBufferObject (vertexBufferObject);
	}
	const std::vector <glm::vec3> vertexNormals = GetVertexNormals();
	if (!vertexNormals.empty())
	{
		GLuint normalBufferObject = GetNormalBufferObject();
		glGenBuffers(1, &normalBufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, normalBufferObject);
		glBufferData(GL_ARRAY_BUFFER, vertexNormals.size ()*sizeof (glm::vec3), &vertexNormals[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		SetNormalBufferObject (normalBufferObject);
	}
	const std::vector <glm::vec2> processedTexCoords = GetProcessedTexCoords();
	if (!processedTexCoords.empty())
	{
		GLuint textureBufferObject = GetTextureBufferObject();
		glGenBuffers(1, &textureBufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, textureBufferObject);
		glBufferData(GL_ARRAY_BUFFER, processedTexCoords.size ()*sizeof (glm::vec2), &processedTexCoords[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		SetTextureBufferObject (textureBufferObject);
	}
	const std::vector <glm::vec4> processedColours = GetProcessedColours();
	if (!processedColours.empty ())
	{
		GLuint colourBufferObject = GetColourBufferObject();
		glGenBuffers(1, &colourBufferObject);
	
		glBindBuffer (GL_ARRAY_BUFFER, colourBufferObject);	
		glBufferData(GL_ARRAY_BUFFER, processedColours.size ()*sizeof (glm::vec4), &processedColours[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		SetColourBufferObject (colourBufferObject);	
	}
}

void Loader::GenerateBuffers ()
{
	ProcessFaceNormals ();
	ProcessVertexNormals ();
	ProcessVertices ();
	ProcessTexCoords ();
	InitializeVertexBuffer ();

	GLuint vao = GetVao();
	GLuint vertexBufferObject = GetVertexBufferObject();
	GLuint normalBufferObject = GetNormalBufferObject();
	GLuint textureBufferObject = GetTextureBufferObject();
	GLuint colourBufferObject = GetColourBufferObject();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer (GL_ARRAY_BUFFER, vertexBufferObject);	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer (GL_ARRAY_BUFFER, normalBufferObject);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, textureBufferObject);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, colourBufferObject);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	SetVao (vao);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}
void Loader::ProcessObject (const std::string path)
{
	Loader* self = this;
	self->LoadObjectFile (path);
	self->GenerateBuffers ();
}

void Loader::Render ()
{
	const std::vector <glm::vec3> processedVertices = GetProcessedVertices();
	Primitives drawPrimitive = GetDrawPrimitive ();
	GLuint vao = GetVao();
	glBindVertexArray(vao);
	if (drawPrimitive == Points)
		glDrawArrays (GL_POINTS, 0, processedVertices.size());
	else if (drawPrimitive == Line)
		glDrawArrays (GL_LINES, 0, processedVertices.size());
	else
		glDrawArrays (GL_TRIANGLES, 0, processedVertices.size());
	glBindVertexArray(0);
}