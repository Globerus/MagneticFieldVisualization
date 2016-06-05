// Ashkulsum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Ashkulsum.h"
//#include "oglEngine.h"
//#include "window.h"
//#include "cameraController.h"
//#include "pvwUpdater.h"
//#include "groupNode.h"
//#include "windowHandler.h"
//#include "load.h"
//#include <boost/thread.hpp>
//#include <boost/thread/scoped_thread.hpp>
//#include <iostream>
//#include "allScreen.h"
//#include "resource.h"
//#include "caseCube.h"
//#include "resourceManager.h"
//#include "primitive.h"
//#include "materialManager.h"
//#include "meshManager.h"
//#include "lightManager.h"
//ResourceTree::RsrcTreePtr resourceTree = NULL;
//ResourceManager& resourceManager = ResourceManager::GetInstance ();
//MeshManager& meshManager = MeshManager::GetInstance ();
//MaterialManager& materialManager = MaterialManager::GetInstance ();
//LightManager& lightManager = LightManager::GetInstance ();

/*std::string LOCAL_OBJECT_DIR;
std::string LOCAL_COORDINATE_DIR;
std::string LOCAL_TEXTURE_DIR;

int number_of_points = 15000;
int width, height;

float fzNear = 1.0f;
float fzFar = 1000.0f;

int loadingText_y = 100;
int loadingText_size = 16;

int isDragging = 0;
int oldX = 0, oldY = 0;

const LightingProperties lightingProperties = {
	glm::vec4(0.8f, 0.8f, 0.8f, 1.0f), //lightIntensity
	glm::vec4 (0.5f, 0.5f, 0.5f, 1.0f), //ambientIntensity
	glm::vec3 (25.866f, 18.0f, 0.0f), //lightPosition
	1.0f, //lightAttenuation
	4.0f, //shinninessFactor
	800, //shadowSizeWidth
	600, //shadowSizeHeigth
};

glm::vec3 g_sphereCamRelPos(67.5f, -46.0f, 150.0f);
glm::vec3 g_camTarget(0.0f, 0.4f, 0.0f);

ShadowMapFBO *shadowMapFBO = NULL;

ProgramData *g_LightingColour = NULL;
ProgramData *g_NoLightingColour = NULL;
ProgramData *g_ShadowMapping = NULL;
ProgramData *g_ScaleProgram = NULL;
ProgramData *g_PointProgram = NULL;
ProgramData *g_LoadingProgram = NULL;
ProgramData *g_Text2DProgram = NULL;

Loader *Scale = NULL;
Loader *ScaleCase = NULL;
Loader *PositiveScale = NULL;
Loader *NegativeScale = NULL;
Loader *Cylinder_body = NULL;
Loader *Cylinder_top = NULL;
Loader *Vector = NULL;
Loader *Cone = NULL;
Loader *LetterX = NULL;
Loader *LetterY = NULL;
Loader *LetterZ = NULL;
Loader *Spring = NULL;
//Interpolator *Point = NULL;
Loader *LoadingScreen = NULL;
Loader *LoadingText = NULL;

GLuint textTextureAtlas;

std::string ws2s(const std::wstring& wstr)
{
    int size_needed = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), 0, 0, 0, 0); 
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), &strTo[0], size_needed, 0, 0); 
    return strTo;
}
std::string GetExeDir ()
{
	TCHAR dest[MAX_PATH];
	size_t destSize = MAX_PATH;
	char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
	DWORD length = GetModuleFileName( NULL, dest, destSize );	
	std::string dest2 = ws2s (dest);
	_splitpath_s (dest2.c_str(), drive, dir, fname, ext);
	std::string path = drive;
	return path + dir;
}
GLuint LoadingTextureAtlas (const std::string pathTexture)
{
	std::string path = LOCAL_TEXTURE_DIR + pathTexture;
	GLuint text2DTexture = loadDDS(path.c_str ());
	return text2DTexture;
}

void PrintLoadingText (const std::string text, GLuint text2DTexture, int texNum)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glViewport(0, 0, width,height);
	LoadingScreen->ActivateTexture (GL_TEXTURE_2D);
	g_LoadingProgram->UseProgram();
	LoadingScreen->Render ();
	glUseProgram (0);
	glBindTexture (GL_TEXTURE_2D, 0);

	int length = text.length ();
	int cells = width/loadingText_size;
	int x = ((cells - length)/2)*loadingText_size;
	std::vector <glm::vec3> vertices = GetVerticesText2D (text.c_str (), 200, loadingText_y, loadingText_size);
	std::vector <glm::vec2> textures = GetTexturesText2D (text.c_str ());
	
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertices.size ()*sizeof (glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	GLuint textureBufferObject;
	glGenBuffers(1, &textureBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, textureBufferObject);
	glBufferData(GL_ARRAY_BUFFER, textures.size ()*sizeof (glm::vec2), &textures[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	g_Text2DProgram->UseProgram ();
	glActiveTexture(GL_TEXTURE0 + texNum);
	glBindTexture(GL_TEXTURE_2D, text2DTexture);
	glUseProgram (0);
	g_Text2DProgram->SetTexture ("loadingTextureUnif", texNum);
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, textureBufferObject);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0 );
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	g_Text2DProgram->UseProgram ();
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
	glUseProgram (0);
	glDisable(GL_BLEND);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindTexture (GL_TEXTURE_2D, 0);

	glutSwapBuffers();
}

void LoadStartScreen ()
{
	LoadingScreen = new Loader ();
	LoadingScreen->ProcessObject ("loadingScreen.obj");

	GLuint loadingTexture; 
	glGenTextures(1, &loadingTexture);
	LoadingScreen->SetTexture (loadingTexture);
	LoadingScreen->SetTextureNum (2);
	LoadingScreen->LoadTexture ("LoadingScreen.jpg", GL_TEXTURE_2D);
	g_LoadingProgram->SetTexture ("loadingTextureUnif", 2);

	// LOAD TEXTURE ATLAS
	textTextureAtlas = LoadingTextureAtlas ("TextFont.dds");
	std::string text = "Loading Resources ...";
	PrintLoadingText (text, textTextureAtlas, 3);
}
void InitializeProgram()
{	
	std::string exeDir = GetExeDir ();
	LOCAL_OBJECT_DIR = exeDir + "data\\objects\\";
	LOCAL_COORDINATE_DIR = exeDir + "data\\coordinates\\";
	LOCAL_TEXTURE_DIR = exeDir + "data\\textures\\";
	
	g_LoadingProgram = new ProgramData ();
	g_LoadingProgram->LoadProgram ("LOADING");
	g_LightingColour = new ProgramData ();
	g_LightingColour->LoadProgram ("LIGHTING");
	g_NoLightingColour = new ProgramData ();	
	g_NoLightingColour->LoadProgram ("NO_LIGHTING");
	g_PointProgram = new ProgramData ();
	g_PointProgram->LoadProgram ("POINT");
	g_ScaleProgram = new ProgramData ();
	g_ScaleProgram->LoadProgram ("SCALE");
	g_ShadowMapping = new ProgramData ();
	g_ShadowMapping->LoadProgram ("SHADOW");
	g_Text2DProgram = new ProgramData ();
	g_Text2DProgram->LoadProgram ("TEXT");
}

void LoadTextures()
{
	GLuint scaleTexture; 
	glGenTextures(1, &scaleTexture);
	Scale->SetTexture (scaleTexture);
	Scale->SetTextureNum (1);
	Scale->LoadTexture("Scale.png", GL_TEXTURE_2D);
	g_ScaleProgram->SetTexture ("scaleTextureUnif", 1);
}
void LoadResources ()
{
	LoadStartScreen ();

	Scale = new Loader ();
	Scale->SetName ("Colour Scale");
	Scale->ProcessObject ("scale.obj");
	
	ScaleCase = new Loader ();
	ScaleCase->SetName ("Coordinate Case");
	ScaleCase->ProcessObject ("case.obj");

	PositiveScale = new Loader ();
	PositiveScale->SetName ("Coordinate Case Size");
	PositiveScale->ProcessObject ("positiveScale.obj");

	NegativeScale = new Loader ();
	NegativeScale->SetName ("Coordinate Case Additional Size");
	NegativeScale->ProcessObject ("negativeScale.obj");

	Cylinder_body = new Loader ();
	Cylinder_body->SetName ("Magnet Body");
	Cylinder_body->ProcessObject ("cylinder_body.obj");

	Cylinder_top = new Loader ();
	Cylinder_top->SetName ("Magnet Top");
	Cylinder_top->ProcessObject ("cylinder_top.obj");

	Vector = new Loader();
	Vector->SetName ("Coordinate Vector");
	Vector->ProcessObject ("line.obj");

	Cone = new Loader();
	Cone->SetName ("Coordinate Vector Cone");
	Cone->ProcessObject ("cone.obj");

	LetterX = new Loader();
	LetterX->SetName ("X Coordinate");
	LetterX->ProcessObject ("letterX.obj");

	LetterY = new Loader ();
	LetterY->SetName ("Y Coordinate");
	LetterY->ProcessObject ("letterY.obj");
	
	LetterZ = new Loader ();
	LetterZ->SetName ("Z Coordinate");
	LetterZ->ProcessObject ("letterZ.obj");

	Spring = new Loader ();
	Spring->SetName ("Coil");
	Spring->ProcessObject ("spring.obj");

	//Point = new Interpolator ();
	//Point->SetName ("points in space");
	//Point->ProcessPoints ("data_set.txt");
}

void init()
{
	//resourceManager.GetResource ("data\\coordinates\\data_set.ipc");
	//resourceManager.GetResource ("data\\objects\\scale.obj");
	//resourceManager.GetResource ("data\\objects\\spotLight.lp");
	//meshManager.GetMesh ("data\\objects\\scale.obj");
	//lightManager.GetLight ("data\\objects\\spotLight.lp");
	//materialManager.GetMaterial ("data\\objects\\cylinder.mtrl");
	//ResourceManager<Material>::SharedPtr resourceManagerMtrl  (new ResourceManager<Material> ());
	//ShaderManager::SharedPtr shaderManager = ShaderManager::GetInstance ();
	//ResourceManager::SharedPtr resourceManager = ResourceManager::GetInstance ();
	//resourceManager->GetResource<Material> ("data\\objects\\cylinder.mtrl");
	//resourceManager->GetResource<Material> ("data\\objects\\cylinder.mtrl");
	//resourceManager->GetResource<Texture> ("data\\textures\\Scale.png");
	//resourceManager->GetResource<Texture> ("data\\textures\\Scale.png");
	//resourceManager->GetResource<Mesh> ("data\\objects\\scale.obj");
	//resourceManager->GetResource<Mesh> ("data\\objects\\scale.obj");
	//resourceManager->GetResource<Light> ("data\\objects\\spotLight.lp");
	//resourceManager->GetResource<Light> ("data\\objects\\spotLight.lp");
	//resourceManager->GetResource<Font> ("data\\textures\\TextFont.dds");
	//Resource <Font>::SharedPtr f = resourceManager->GetResource<Font> ("data\\textures\\TextFont.dds");
	//Resource <Point>::SharedPtr 
	//p = resourceManager->GetResource<Point> ("data\\coordinates\\data_set.ipc");
	//boost::shared_ptr<CaseCube> r = CaseCube::CreateCaseCube ();
	//Point::SharedPtr o = p->GetPtr ();
	//p->GetPtr ()->GeneratePoints ();
	//p->GetPtr ()->ProcessPoints ();
	//resourceManagerMtrl->Load ("a");
	InitializeProgram();
	shadowMapFBO = new ShadowMapFBO ();
	shadowMapFBO->Init(width, height);
	LoadResources ();	
	LoadTextures();

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void free ()
{
	g_LightingColour->~ProgramData();
	g_NoLightingColour->~ProgramData();
	g_ShadowMapping->~ProgramData();
	g_ScaleProgram->~ProgramData();

	shadowMapFBO->~ShadowMapFBO();
	Scale->~Loader ();
	PositiveScale->~Loader ();
	NegativeScale->~Loader ();
	ScaleCase->~Loader ();
	Cylinder_body->~Loader ();
	Cylinder_top->~Loader ();
	Vector->~Loader();
	Cone->~Loader();
	//Point->~Interpolator();
	LetterX->~Loader();
	LetterY->~Loader();
	LetterZ->~Loader();
	Spring->~Loader();
}
void display ()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	
	g_PointProgram->SetWorldToCameraMatrix (g_camTarget, glm::vec3 (0.0f, 1.0f, 0.0f));
	g_NoLightingColour->SetWorldToCameraMatrix (g_camTarget, glm::vec3 (0.0f, 1.0f, 0.0f));
	g_LightingColour->SetWorldToCameraMatrix (g_camTarget, glm::vec3 (0.0f, 1.0f, 0.0f));

	glutil::MatrixStack modelMatrix;
	{
		drawBigScreen (modelMatrix);
	}
	{
		glEnable(GL_SCISSOR_TEST);
		glViewport(0, 0, width - 3 * width / 4,height - 3 * height / 4);
		glScissor (0, 0, width - 3 * width / 4,height - 3 * height / 4);
		glClear(GL_DEPTH_BUFFER_BIT);
		glDisable (GL_SCISSOR_TEST);
		drawSmallScreen (modelMatrix);
	}
	{
		glEnable(GL_SCISSOR_TEST);
		glViewport(width - 3 * width / 4, 0, 3 * width / 4,height - 3 * height / 4);
		
		glScissor (width - 3 * width / 4, 0, width,height - 3 * height / 4);
		glClear(GL_DEPTH_BUFFER_BIT);
		glDisable (GL_SCISSOR_TEST);
		drawScaleScreen (modelMatrix);
	}
	
	glutSwapBuffers ();
}
void reshape (int w, int h)
{
	g_LightingColour->SetCameraToClipMatrix (fzNear, fzFar, 45.0f);
	g_NoLightingColour->SetCameraToClipMatrix (fzNear, fzFar, 45.0f);
	g_PointProgram->SetCameraToClipMatrix (fzNear, fzFar, 45.0f);
	g_ShadowMapping->SetLightCameraToClipMatrix (1, 85, 45.0f);
	g_LightingColour->SetLightCameraToClipMatrix (1, 85, 45.0f);
	width = w;
	height = h;

	glutPostRedisplay();
}*/
//OpenGLEngine* engine = NULL;
//std::shared_ptr<PVWUpdater> pvwUpdater = NULL;
//std::shared_ptr<GroupNode> scene;
//std::shared_ptr<CameraController> cameraController;



//Window* window = NULL;
/*
void thread (Window& window)
{
	HANDLE rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console

    DWORD Events = 0;     // Event count
    DWORD EventsRead = 0; // Events read from console

    //bool Running = true;
	//while(Running) {

        // gets the systems current "event" count
        GetNumberOfConsoleInputEvents(rhnd, &Events);
		if(Events != 0)
		{
			//std::vector <INPUT_RECORD> eventBuffer;
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[Events];
			//eventBuffer.resize (Events);
			ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

			for(DWORD i = 0; i < EventsRead; ++i){
				
				if(eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown)
				{
					switch(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode){
						case VK_ESCAPE: // if escape key was pressed end program loop
                            //PostQuitMessage(0);
							//window.Destroy ();
							WindowHandler::ModifyWindow (0);
							std::cout<< "escape key pressed.\n";
                           // Running = false;
                           // break;
					}
				}
			}
			delete eventBuffer;
		}
		//std::cout << Events;

	//}
	//for (;;)
	//{
	//	std::cout << "dd";
	//}
}



void thread2 (Window& window)
{
	//bool Running = true;
	//while(Running) 
	//{
		
		WindowHandler::Update (window);
		//if (glfwWindowShouldClose(window.m_WindowContext))
			//Running = false;

	//}
}*/

//void update (Window& window)
//{
	//thread (window);
	//thread2 (window);
//}

InterpolationSimulation* InterpolationSimulation::currentInstance;

InterpolationSimulation::InterpolationSimulation (std::string title, int xOrigin, int yOrigin, int xSize, int ySize)
	:	Window (title, xOrigin, yOrigin, xSize, ySize)
{

	m_AppTime = 0.0f;
	m_AppTimeDelta = 0.01f;
	
	m_BlendState = std::make_shared<BlendState> ();
	m_BlendState->m_Target[0].enable = true;
	m_BlendState->m_Target[0].srcColor = BlendState::MODE_SRC_ALPHA;
	m_BlendState->m_Target[0].dstColor = BlendState::MODE_INV_SRC_ALPHA;
	m_BlendState->m_Target[0].srcAlpha = BlendState::MODE_SRC_ALPHA;
	m_BlendState->m_Target[0].dstAlpha = BlendState::MODE_INV_SRC_ALPHA;

	m_BlendStateLine = std::make_shared<BlendState> ();
	m_BlendStateLine->m_Target[0].enable = true;
	m_BlendStateLine->m_Target[0].srcColor = BlendState::MODE_ONE;
	m_BlendStateLine->m_Target[0].dstColor = BlendState::MODE_ONE;
	m_BlendStateLine->m_Target[0].srcAlpha = BlendState::MODE_ONE;
	m_BlendStateLine->m_Target[0].dstAlpha = BlendState::MODE_ONE;

	m_DepthStencilStateLine = std::make_shared<DepthStencilState> ();
	m_DepthStencilStateLine->m_WriteMask = DepthStencilState::MASK_ZERO;

	m_RasterizerStateLine = std::make_shared<RasterizerState> ();
	m_RasterizerStateLine->m_CullMode = RasterizerState::CULL_NONE;

	m_RasterizerStateShadow = std::make_shared<RasterizerState> ();
	m_RasterizerStateShadow->m_CullMode = RasterizerState::CULL_FRONT;

	m_CGALInterpolator = std::make_shared<CGALInterpolationSimulator> ();

	InitializeLightNode ();
	CreateScene ();
	//CreateAnimator ();

	m_Scene->Update ();
	m_PVWUpdater.Update ();
	m_ShadowPVWUpdater.Update ();
}

void InterpolationSimulation::CreateAnimator ()
{
	int mine = 1;
	if (mine)
	{	
		Transformation localTransform;
  
		/*float deg = 360.0f;
		glm::mat4 rotMatrix = glm::rotate (glm::mat4 (1.0f), deg, glm::vec3 (1.0f, 0.0f, 0.0f));

		std::vector<glm::quat> vq;
		std::vector<float> vt;
		for (int i = 0; i < deg; i ++)
		{
			glm::mat4 mat = glm::rotate (glm::mat4(1.0f), 1.0f*i, glm::vec3 (1.0f, 0.0f, 0.0f));
			vq.push_back (glm::quat_cast (mat));
			if (i % 3 == 1)
				vt.push_back ((1.0f/deg)*i);
		}
		localTransform.SetTranslation (glm::vec4(0.0f));
		localTransform.SetRotation (rotMatrix);
		localTransform.SetScale (glm::vec3 (1.0f));

		int numTranslations = 0, numRotations = (int)vt.size(), numScales = 0;

		std::shared_ptr<KeyframeAnimator> keyfctrl = std::make_shared<KeyframeAnimator>(
				0, numTranslations, numRotations, numScales, localTransform);

		if (numRotations > 0)
		{
			keyfctrl->SetRotationTimes (vt);
			keyfctrl->SetRotations (vq);
		}

			*/
		int trn = 160;
		float dest = -8.0f;
		glm::vec4 translate = m_Rec->m_LocalT.GetTranslationW0 ();
		glm::vec4 last = translate + glm::vec4 (0.0f, 0.0f, dest, 0.0f);
		glm::mat4 rotMatrix = glm::mat4(1.0f);
		std::vector<glm::vec4> vq;
		std::vector<float> vt;
		float step = dest/float(trn);

		for (int i = 0; i < trn; i ++)
		{
			glm::vec4 vec = translate + glm::vec4(0.0f, 0.0f, i * step, 1.0f);
			vq.push_back (vec);
			//if (i % 3 == 1)
				vt.push_back ((1.0f/trn)*i);
		}
		localTransform.SetTranslation (last);
		localTransform.SetRotation (rotMatrix);
		localTransform.SetScale (glm::vec3 (1.0f));

		int numTranslations = (int)vt.size(), numRotations = 0, numScales = 0;

		std::shared_ptr<KeyframeAnimator> keyfctrl = std::make_shared<KeyframeAnimator>(
				0, numTranslations, numRotations, numScales, localTransform);

		if (numTranslations > 0)
		{
			keyfctrl->SetTranslationTimes (vt);
			keyfctrl->SetTranslations (vq);
		}
		
		m_Animator = keyfctrl;
		m_Animator->m_Repeat = Animator::RT_CYCLE;
		m_Animator->m_MinTime = 0.0;
		m_Animator->m_MaxTime = 1.0;
		m_Animator->m_Phase = 0.0;
		m_Animator->m_Frequency = 0.3;
		m_Animator->m_Active = true;
	}
	else
	{
		std::string filename = "C:\\Users\\Administrator\\Desktop\\GeometricTools\\GTEngine\\Samples\\Graphics\\BlendedAnimations\\Data\\Animations\\Run\\RFoot.xfrmctrl.raw";
		std::ifstream input(filename, std::ios::binary);

		int isKeyframeController;
		input.read((char*)&isKeyframeController, sizeof(isKeyframeController));

		int repeatType, active;
		double minTime, maxTime, phase, frequency;
		input.read((char*)&repeatType, sizeof(repeatType));
		input.read((char*)&minTime, sizeof(minTime));
		input.read((char*)&maxTime, sizeof(maxTime));
		input.read((char*)&phase, sizeof(phase));
		input.read((char*)&frequency, sizeof(frequency));
		input.read((char*)&active, sizeof(active));
		
		float mat[9], trn[3], sca[3];
		char isIdentity, isRSMatrix, isUniformScale, dummy;
		input.read((char*)mat, 9 * sizeof(float));
		input.read((char*)trn, 3 * sizeof(float));
		input.read((char*)sca, 3 * sizeof(float));
		input.read((char*)&isIdentity, sizeof(isIdentity));
		input.read((char*)&isRSMatrix, sizeof(isRSMatrix));
		input.read((char*)&isUniformScale, sizeof(isUniformScale));
		input.read((char*)&dummy, sizeof(dummy));
	
		Transformation localTransform;
		localTransform.SetTranslation(glm::vec4 (trn[0], trn[1], trn[2], 0.0f));

		if (isUniformScale)
		{
		   localTransform.SetScale(glm::vec3(sca[0]));
		}
		else
		{
			localTransform.SetScale(glm::vec3 (sca[0], sca[1], sca[2]));
		}
		
		if (isRSMatrix)
		{
			localTransform.SetRotation(glm::mat4(
				mat[0], mat[1], mat[2], 0.0f,
				mat[3], mat[4], mat[5], 0.0f,
				mat[6], mat[7], mat[8], 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f ));
		}

		if (isKeyframeController)
		{
			int numTranslations, numRotations, numScales;
			input.read((char*)&numTranslations, sizeof(numTranslations));
			input.read((char*)&numRotations, sizeof(numRotations));
			input.read((char*)&numScales, sizeof(numScales));
			
			std::shared_ptr<KeyframeAnimator> keyfctrl = std::make_shared<KeyframeAnimator>(
				0, numTranslations, numRotations, numScales, localTransform);
			
			if (numTranslations > 0)
			{
				input.read((char*)keyfctrl->GetTranslationTimes(),
					sizeof(float) * numTranslations);

				input.read((char*)keyfctrl->GetTranslations(),
					sizeof(glm::vec4) * numTranslations);
			}

			if (numRotations > 0)
			{
				input.read((char*)keyfctrl->GetRotationTimes(),
					sizeof(float) * numRotations);

				input.read((char*)keyfctrl->GetRotations(),
					sizeof(glm::quat) * numRotations);
			}

			if (numScales > 0)
			{
				input.read((char*)keyfctrl->GetScaleTimes(),
					sizeof(float) * numScales);

				input.read((char*)keyfctrl->GetScales(),
					sizeof(float) * numScales);
			}
		
			m_Animator = keyfctrl;
			m_Animator->m_Repeat = Animator::RT_WRAP;
			m_Animator->m_MinTime = minTime;
			m_Animator->m_MaxTime = maxTime;
			m_Animator->m_Phase = phase;
			m_Animator->m_Frequency = frequency;
			m_Animator->m_Active = (active > 0);
			input.close ();
			}
		}
		m_Rec->AttachAnimator (m_Animator);
}

void InterpolationSimulation::InitializeLightNode ()
{
	
	m_LightWorldDirection = glm::vec4 (-1.0f, -1.0f, -1.0f, 0.0f);

	std::shared_ptr<LightCamera> lightCamera = std::make_shared<LightCamera> (false);
		
	m_ShadowPVWUpdater.Set (lightCamera, m_Updater);

	m_LightNode = std::make_shared<CameraNode> (lightCamera);
	m_LightNode->SetShadowMapTransformation (m_LightWorldDirection, m_Camera);
	
	m_LightNode->SetAddtnlUpdate ([this](CameraNode*)
	{
		std::vector<std::pair <std::shared_ptr<Node>, std::shared_ptr<DirectionalLightingTextureWithShadowEffect>>> m_NodesEffects;
		m_NodesEffects.push_back (std::make_pair (m_Cylinder, m_CylinderEffect));
		m_NodesEffects.push_back (std::make_pair (m_Spring, m_SpringEffect));

		auto const lightPVMatrix = m_LightNode->GetCamera ()->GetProjectionViewMatrix ();
		auto const cameraWorldPosition = m_Camera->GetPosition ();
		
		for (unsigned int i = 0; i < m_NodesEffects.size (); i++)
		{
			m_NodesEffects.at(i).second->GetLightInfo ()->m_CameraPosition =   cameraWorldPosition;		
			m_NodesEffects.at(i).second->UpdateEffectLightCameraInfo ();

			auto worldMatrix = m_NodesEffects.at(i).first->m_WorldT.GetTransformationMatrix ();
			m_NodesEffects.at(i).second->GetWorldMatrixUniformBuffer ()->SetMember ("worldMatrix", worldMatrix);
			m_NodesEffects.at(i).second->GetNormalWorldMatrixUniformBuffer ()->SetMember ("normalWorldMatrix", glm::transpose(glm::inverse (worldMatrix)));
			
			m_Updater (m_NodesEffects.at(i).second->GetWorldMatrixUniformBuffer ());
			m_Updater (m_NodesEffects.at(i).second->GetNormalWorldMatrixUniformBuffer ());
		}		

		auto const cameraViewMatrix = m_Camera ->GetViewMatrix ();
		for (unsigned int i = 0; i < m_GVector.size (); i++)
		{
			auto const volumetricLineWorldMatrix = m_GVector[i]->m_WorldT.GetTransformationMatrix ();
			m_GEffectVector[i]->GetVWMatrixUniformBuffer () ->SetMember ("vwMatrix", cameraViewMatrix * volumetricLineWorldMatrix);
			m_Updater (m_GEffectVector[i]->GetVWMatrixUniformBuffer ());
		}

		auto const cameraProjectionMatrix = m_Camera->GetProjectionMatrix ();
		auto const particlesWorldMatrix = m_Particles->m_WorldT.GetTransformationMatrix ();
		m_ParticlesEffect->GetProjectionMatrixUniformBuffer () ->SetMember ("projectionMatrix", cameraProjectionMatrix);
		m_ParticlesEffect->GetViewMatrixUniformBuffer () ->SetMember ("viewMatrix", cameraViewMatrix);
		m_ParticlesEffect->GetWorldMatrixUniformBuffer () ->SetMember ("worldMatrix", particlesWorldMatrix);
		m_Updater (m_ParticlesEffect->GetProjectionMatrixUniformBuffer ());
		m_Updater (m_ParticlesEffect->GetViewMatrixUniformBuffer ());
		m_Updater (m_ParticlesEffect->GetWorldMatrixUniformBuffer ());
	});
}

void InterpolationSimulation::MouseMove(int x, int y) 
{ 	
	if (m_TrackBall.GetActive ())
	{
		m_TrackBall.SetFinalCoordinates (x, y);
		m_TrackBall.SetInitialCoordinates (x,y);
	}
}

void InterpolationSimulation::MouseButton(int button, int state, int x, int y) 
{
	m_TrackBall.SetZoomActive (false);
	if (button == GLUT_LEFT_BUTTON) 
	{
		if (state == GLUT_DOWN) 
		{ 
			m_TrackBall.SetActive (true);
			m_TrackBall.SetInitialCoordinates (x, y);
		}	
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			m_TrackBall.SetActive (true);
			m_TrackBall.SetZoomActive (true);
			m_TrackBall.SetInitialCoordinates (x, y);
		}
	}
	else
	{
		m_TrackBall.SetActive (false);
		m_TrackBall.SetZoomActive (false);
	}
}

void InterpolationSimulation::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		return;
	}
}

void InterpolationSimulation::Reshape (int w, int h)
{
	SetWindowSize (w, h);
}

void InterpolationSimulation::MouseMoveCallback (int x, int y)
{
	currentInstance->MouseMove (x, y);
}

void InterpolationSimulation::MouseButtonCallback (int button, int state, int x, int y)
{
	currentInstance->MouseButton (button, state, x, y);
}

void InterpolationSimulation::KeyboardCallback (unsigned char key, int x, int y)
{
	currentInstance->Keyboard (key, x, y);
}

void InterpolationSimulation::ReshapeCallback (int w, int h)
{
	currentInstance->Reshape (w, h);
}

void InterpolationSimulation::SetCurrentInstance ()
{
	currentInstance = this;

}

void InterpolationSimulation::CreateScene ()
{
	std::shared_ptr<FontArialW400H16Bold> font = std::make_shared<FontArialW400H16Bold> (m_Factory, 257);
	m_Engine->SetFont (font);

	WICImageLoader imageLoader;

	m_CylinderDrawTarget = std::make_shared<DrawTarget> (1, DP_R8G8B8A8_UNSIGNED_NORM, 8*m_WindowSize.m_XSize, 8*m_WindowSize.m_YSize, false, false, DP_D16_UNSIGNED_NORM, true);
	m_ShadowTexture = m_CylinderDrawTarget->GetDSTexture ();

	m_Scene = std::make_shared<GroupNode> ();
	m_Scene->name = "m_Scene";

	
	std::shared_ptr<GroupNode> animatedNode = std::make_shared<GroupNode> ();
	animatedNode->name = "animatedNode";

	std::shared_ptr<GroupNode> nodeX = std::make_shared<GroupNode> ();
	nodeX->name = "nodeX";
	nodeX->m_LocalT.SetRotation (glm::vec3 (0.0f, 0.0f, 1.0f), -90.0f);
	std::shared_ptr<GroupNode> nodeY = std::make_shared<GroupNode> ();
	nodeY->name = "nodeY";
	std::shared_ptr<GroupNode> nodeZ = std::make_shared<GroupNode> ();
	nodeZ->name = "nodeZ";
	nodeZ->m_LocalT.SetRotation (glm::vec3 (1.0f, 0.0f, 0.0f), 90.0f);

	std::shared_ptr<BillBoardNode> billBoardParticles = std::make_shared<BillBoardNode> (m_Camera);
	billBoardParticles->name = "billBoardParticles";

	std::shared_ptr<BillBoardNode> billBoardX = std::make_shared<BillBoardNode> (m_Camera);
	billBoardX->name = "billBoardX";
	billBoardX->m_LocalT.SetTranslation (glm::vec3 (5.6f, -0.2f, 0.0f));
	std::shared_ptr<BillBoardNode> billBoardY = std::make_shared<BillBoardNode> (m_Camera);
	billBoardY->name = "billBoardY";
	billBoardY->m_LocalT.SetTranslation (glm::vec3 (-0.2f, 5.6f, 0.0f));
	std::shared_ptr<BillBoardNode> billBoardZ = std::make_shared<BillBoardNode> (m_Camera);
	billBoardZ->name = "billBoardZ";
	billBoardZ->m_LocalT.SetTranslation (glm::vec3 (0.0f, -0.2f, 5.6f));
	
	m_Scene->AttachChild (nodeX);
	m_Scene->AttachChild (nodeY);
	m_Scene->AttachChild (nodeZ);
	m_Scene->AttachChild (billBoardX);
	m_Scene->AttachChild (billBoardY);
	m_Scene->AttachChild (billBoardZ);
	m_Scene->AttachChild (billBoardParticles);
	m_Scene->AttachChild (animatedNode);
	m_Scene->AttachChild (m_LightNode);

	std::shared_ptr<Material> material = std::make_shared<Material> ();
	std::shared_ptr<Lighting> lighting = std::make_shared<Lighting> ();
	std::shared_ptr<LightCameraInfo> lightCameraInfo = std::make_shared<LightCameraInfo> ();

	auto cameraLighting = std::static_pointer_cast<LightCamera> (m_LightNode->GetCamera ());
	cameraLighting->m_Lighting = lighting;
	
	material->m_Diffuse = glm::vec4 (1.0f, 1.0f, 1.0f, 1.0f);
	material->m_Ambient = glm::vec4 (0.25f, 0.25f, 0.25f, 1.0f);
	material->m_Emissive = glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f);
	material->m_Specular = glm::vec4 (1.0f, 1.0f, 1.0f, 9.0f);

	lighting->m_Diffuse = glm::vec4 (1.0f, 1.0f, 1.0f, 1.0f);
	lighting->m_Ambient = glm::vec4 (1.0f, 1.0f, 1.0f, 1.0f);
	lighting->m_Specular = glm::vec4 (1.0f, 1.0f, 1.0f, 1.0f);
	lighting->m_Attenuation = glm::vec4 (1.0f, 1.0f, 1.0f, 1.0f);
	
	m_Scale = LoadMesh ("data\\objects\\scale.obj");
	m_Scale->name = "m_Scale";
	std::shared_ptr<Texture2> scaleTexture = imageLoader.Load ("data\\textures\\Scale.png", true);
	scaleTexture->AutoGenerateMipMap ();
	m_ScaleEffect = std::make_shared<Texture2Effect> (m_Factory, scaleTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP); 
	m_Scale->SetVisualEffect (m_ScaleEffect);

	m_CylinderShadowMapEffect = std::make_shared<ShadowMapEffect> (m_Factory);
	m_SpringShadowMapEffect = std::make_shared<ShadowMapEffect> (m_Factory);
	
	std::shared_ptr<Texture2> cylinderTexture = imageLoader.Load ("data\\textures\\stainless-steel.png", true);
	cylinderTexture->AutoGenerateMipMap ();
	m_Cylinder = LoadMesh ("data\\objects\\cylinder.obj");
	m_Cylinder->name = "m_Cylinder";

	m_CylinderEffect = std::make_shared<DirectionalLightingTextureWithShadowEffect> (m_Factory, m_Updater, material, lighting, lightCameraInfo, cylinderTexture, m_ShadowTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP);
	m_CylinderEffect->GetLightInfo ()->m_LightDirection = m_LightWorldDirection;
	m_Cylinder->SetVisualEffect (m_CylinderEffect);
	m_PVWUpdater.Subscribe (m_CylinderEffect->GetPVWMatrixUniformBuffer (), m_Cylinder->m_WorldT);
	m_ShadowPVWUpdater.Subscribe (m_CylinderEffect->GetLightPVWMatrixUniformBuffer (), m_Cylinder->m_WorldT, "lightPVWMatrix");
	m_ShadowPVWUpdater.Subscribe (m_CylinderShadowMapEffect->GetPVWMatrixUniformBuffer (), m_Cylinder->m_WorldT);
	m_Scene->AttachChild (m_Cylinder);

	std::shared_ptr<Texture2> springTexture = imageLoader.Load ("data\\textures\\copper.png", true);
	springTexture->AutoGenerateMipMap ();
	m_Spring = LoadMesh ("data\\objects\\spring.obj");
	m_Spring->name = "m_Spring";

	m_SpringEffect = std::make_shared<DirectionalLightingTextureWithShadowEffect> (m_Factory, m_Updater, material, lighting, lightCameraInfo, springTexture, m_ShadowTexture, SamplerState::MIN_N_MAG_N_MIP_N, SamplerState::CLAMP);
	m_SpringEffect->GetLightInfo ()->m_LightDirection = m_LightWorldDirection;
	m_Spring->SetVisualEffect (m_SpringEffect);
	m_PVWUpdater.Subscribe (m_SpringEffect->GetPVWMatrixUniformBuffer (), m_Spring->m_WorldT);
	m_ShadowPVWUpdater.Subscribe (m_SpringEffect->GetLightPVWMatrixUniformBuffer (), m_Spring->m_WorldT, "lightPVWMatrix");
	m_ShadowPVWUpdater.Subscribe (m_SpringShadowMapEffect->GetPVWMatrixUniformBuffer (), m_Spring->m_WorldT);
	animatedNode->AttachChild (m_Spring);
	//animatedNode->AttachAnimator (m_Animator);
	
	m_LineX = LoadLine ("data\\objects\\line.obj");
	m_LineX->m_LocalT.SetScale (glm::vec3 (1.0f, 4.0f, 1.0f));
	

	m_LineXEffect = std::make_shared<NormalEffect> (m_Factory);
	m_LineXEffect->SetColour (glm::vec4 (1.0f, 0.0f, 0.0f, 1.0f));
	m_LineX->SetVisualEffect (m_LineXEffect);
	m_PVWUpdater.Subscribe (m_LineXEffect->GetPVWMatrixUniformBuffer (), m_LineX->m_WorldT);
	nodeX->AttachChild (m_LineX);

	m_ConeX = LoadMesh ("data\\objects\\cone.obj");
	m_ConeX->m_LocalT.SetTranslation (glm::vec3 (0.0f, 4.0f, 0.0f));
	m_ConeX->m_LocalT.SetUniformScale (0.4f);
	m_ConeXEffect = std::make_shared<NormalEffect> (m_Factory);
	m_ConeXEffect->SetColour (glm::vec4 (1.0f, 0.0f, 0.0f, 1.0f));
	m_ConeX->SetVisualEffect (m_ConeXEffect);
	m_PVWUpdater.Subscribe (m_ConeXEffect->GetPVWMatrixUniformBuffer (), m_ConeX->m_WorldT);
	nodeX->AttachChild (m_ConeX);

	m_LetterX = LoadMesh ("data\\objects\\LetterX.obj");
	m_LetterX->m_LocalT.SetUniformScale (2.0f);
	m_LetterXEffect = std::make_shared<NormalEffect> (m_Factory);
	m_LetterXEffect->SetColour (glm::vec4 (1.0f, 0.0f, 0.0f, 1.0f));
	m_LetterX->SetVisualEffect (m_LetterXEffect);
	m_PVWUpdater.Subscribe (m_LetterXEffect->GetPVWMatrixUniformBuffer (), m_LetterX->m_WorldT);
	billBoardX->AttachChild (m_LetterX);
	
	m_LineY = LoadLine ("data\\objects\\line.obj");
	m_LineY->m_LocalT.SetScale (glm::vec3 (1.0f, 4.0f, 1.0f));
	m_LineYEffect = std::make_shared<NormalEffect> (m_Factory);
	m_LineYEffect->SetColour (glm::vec4 (0.0f, 1.0f, 0.0f, 1.0f));
	m_LineY->SetVisualEffect (m_LineYEffect);
	m_PVWUpdater.Subscribe (m_LineYEffect->GetPVWMatrixUniformBuffer (), m_LineY->m_WorldT);
	nodeY->AttachChild (m_LineY);
	
	m_ConeY = LoadMesh ("data\\objects\\cone.obj");
	m_ConeY->m_LocalT.SetTranslation (glm::vec3 (0.0f, 4.0f, 0.0f));
	m_ConeY->m_LocalT.SetUniformScale (0.4f);	
	m_ConeYEffect = std::make_shared<NormalEffect> (m_Factory);
	m_ConeYEffect->SetColour (glm::vec4 (0.0f, 1.0f, 0.0f, 1.0f));
	m_ConeY->SetVisualEffect (m_ConeYEffect);
	m_PVWUpdater.Subscribe (m_ConeYEffect->GetPVWMatrixUniformBuffer (), m_ConeY->m_WorldT);
	nodeY->AttachChild (m_ConeY);

	m_LetterY = LoadMesh ("data\\objects\\LetterY.obj");
	m_LetterY->m_LocalT.SetUniformScale (2.0f);

	m_LetterYEffect = std::make_shared<NormalEffect> (m_Factory);
	m_LetterYEffect->SetColour (glm::vec4 (0.0f, 1.0f, 0.0f, 1.0f));
	m_LetterY->SetVisualEffect (m_LetterYEffect);
	m_PVWUpdater.Subscribe (m_LetterYEffect->GetPVWMatrixUniformBuffer (), m_LetterY->m_WorldT);
	billBoardY->AttachChild (m_LetterY);


	m_LineZ = LoadLine ("data\\objects\\line.obj");
	m_LineZ->m_LocalT.SetScale (glm::vec3 (1.0f, 4.0f, 1.0f));
	
	m_LineZEffect = std::make_shared<NormalEffect> (m_Factory);
	m_LineZEffect->SetColour (glm::vec4 (0.0f, 0.0f, 1.0f, 1.0f));
	m_LineZ->SetVisualEffect (m_LineZEffect);
	m_PVWUpdater.Subscribe (m_LineZEffect->GetPVWMatrixUniformBuffer (), m_LineZ->m_WorldT);
	nodeZ->AttachChild (m_LineZ);
		
	m_ConeZ = LoadMesh ("data\\objects\\cone.obj");
	m_ConeZ->m_LocalT.SetTranslation (glm::vec3 (0.0f, 4.0f, 0.0f));
	m_ConeZ->m_LocalT.SetUniformScale (0.4f);
	m_ConeZEffect = std::make_shared<NormalEffect> (m_Factory);
	m_ConeZEffect->SetColour (glm::vec4 (0.0f, 0.0f, 1.0f, 1.0f));
	m_ConeZ->SetVisualEffect (m_ConeZEffect);
	m_PVWUpdater.Subscribe (m_ConeZEffect->GetPVWMatrixUniformBuffer (), m_ConeZ->m_WorldT);
	nodeZ->AttachChild (m_ConeZ);

	m_LetterZ = LoadMesh ("data\\objects\\LetterZ.obj");
	m_LetterZ->m_LocalT.SetUniformScale (2.0f);
	
	m_LetterZEffect = std::make_shared<NormalEffect> (m_Factory);
	m_LetterZEffect->SetColour (glm::vec4 (0.0f, 0.0f, 1.0f, 1.0f));
	m_LetterZ->SetVisualEffect (m_LetterZEffect);
	m_PVWUpdater.Subscribe (m_LetterZEffect->GetPVWMatrixUniformBuffer (), m_LetterZ->m_WorldT);
	billBoardZ->AttachChild (m_LetterZ);
	
	std::vector<glm::vec4> generatedPoints = m_CGALInterpolator->GeneratePoints ();

	std::shared_ptr<Texture2> particleTexture = imageLoader.Load ("data\\textures\\particle.png", true);
	cylinderTexture->AutoGenerateMipMap ();
	m_Particles = LoadParticles (generatedPoints);
	m_Particles->m_LocalT.SetUniformScale (0.05f);
	m_ParticlesEffect = std::make_shared<ParticlesEffect> (m_Factory, scaleTexture, particleTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP);
	m_Particles->SetVisualEffect (m_ParticlesEffect);
	billBoardParticles->AttachChild (m_Particles);
	

	////////////////////////////////
	/*int xRes = 10, yRes = 10, zRes = 10;
	
	float* r = new float [xRes * yRes * zRes];

	int xMax = 4,yMax = 4, xMin = -4, yMin = -4, zMax =4, zMin = -4;
	
	int xDelta = xMax - xMin;
	int yDelta = yMax - yMin;
	int zDelta = zMax - zMin;

	float xPixel = float(xDelta)/float(xRes);
	float yPixel = float(yDelta)/float(yRes);
	float zPixel = float(zDelta)/float(zRes);

	for (int z = 0; z < zRes; z++)
		for (int y = 0; y < yRes; y++)
			for(int x = 0; x < xRes; x++)
			{
				glm::vec3 point (xMin + xPixel*x, yMin + yPixel*y, zMin + zPixel*z);
				m_CGALInterpolator->InterpolateMagForce (point);
			}

	std::vector <float> m,q;
	for (int z = 0; z < zRes; z++)
		for (int y = 0; y < yRes; y++)
			for (int x = 0; x < xRes; x++)
			{
				int id = y*yRes + x;

				glm::vec4 val = m_CGALInterpolator->m_Interpolated3DPointMagForceVector[id];
				r[z*zRes + y*yRes + x] = val.w;
				m.push_back ( val.w);
			}

	for (int z = 0; z < zRes; z++)
		for (int y = 0; y < yRes; y++)
			for (int x = 0; x < xRes; x++)
			{
				q.push_back ( r[z*zRes + y*yRes + x]);
			}
		
	std::shared_ptr<Texture2Array> m_Texture = std::make_shared<Texture2Array> (zRes, DP_R32_FLOAT, xRes, yRes);
	//m_Texture->AutoGenerateMipMap ();
	memcpy (m_Texture->GetData(), r, m_Texture->GetNumBytes ());


	m_Rec = LoadMesh ("data\\objects\\rectangle.obj");
	m_Rec->m_LocalT.SetTranslation (glm::vec4 (0.0f, 0.0f, 4.0f, 0.0f));
	m_RecEffect = std::make_shared<FieldEffect> (m_Factory, m_Texture, scaleTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP);
	m_Rec->SetVisualEffect (m_RecEffect);
	m_PVWUpdater.Subscribe (m_RecEffect->GetPVWMatrixUniformBuffer (), m_Rec->m_WorldT);
	m_Scene->AttachChild (m_Rec);
	//m_Rec->AttachAnimator (m_Animator);
	/*std::shared_ptr<Texture2> volumetricLineTexture = imageLoader.Load ("data\\textures\\1d_debug2.png", true);
	volumetricLineTexture->AutoGenerateMipMap ();

	auto points = m_CGALInterpolator->GenerateStreamLine (10, 0.5f, glm::vec3 (1.2f, 0.0f, 0.0f));
	std::shared_ptr<GeometryNode> volumetricLine = LoadVolumetricLine (points, 20);
	std::shared_ptr<VolumetricLineEffect> volumetricLineEffect = std::make_shared<VolumetricLineEffect> (m_Factory, volumetricLineTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP);
	volumetricLine->SetVisualEffect (volumetricLineEffect);
	m_PVWUpdater.Subscribe (volumetricLineEffect->GetPVWMatrixUniformBuffer (), volumetricLine->m_WorldT);
	m_Scene->AttachChild (volumetricLine);
	m_GVector.push_back (volumetricLine);
	m_GEffectVector.push_back (volumetricLineEffect);

	points = m_CGALInterpolator->GenerateStreamLine (10, 0.5f, glm::vec3 (1.1f, 0.0f, 0.0f));
	std::shared_ptr<GeometryNode> volumetricLine2 = LoadVolumetricLine (points, 20);
	std::shared_ptr<VolumetricLineEffect> volumetricLineEffect2 = std::make_shared<VolumetricLineEffect> (m_Factory, volumetricLineTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP);
	volumetricLine2->SetVisualEffect (volumetricLineEffect2);
	m_PVWUpdater.Subscribe (volumetricLineEffect2->GetPVWMatrixUniformBuffer (), volumetricLine2->m_WorldT);
	m_Scene->AttachChild (volumetricLine2);
	m_GVector.push_back (volumetricLine2);
	m_GEffectVector.push_back (volumetricLineEffect2);

	points = m_CGALInterpolator->GenerateStreamLine (10, 0.5f, glm::vec3 (1.0f, 0.0f, 0.0f));
	std::shared_ptr<GeometryNode> volumetricLine3 = LoadVolumetricLine (points, 20);
	std::shared_ptr<VolumetricLineEffect> volumetricLineEffect3 = std::make_shared<VolumetricLineEffect> (m_Factory, volumetricLineTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP);
	volumetricLine3->SetVisualEffect (volumetricLineEffect3);
	m_PVWUpdater.Subscribe (volumetricLineEffect3->GetPVWMatrixUniformBuffer (), volumetricLine3->m_WorldT);
	m_Scene->AttachChild (volumetricLine3);
	m_GVector.push_back (volumetricLine3);
	m_GEffectVector.push_back (volumetricLineEffect3);

	points = m_CGALInterpolator->GenerateStreamLine (10, 0.5f, glm::vec3 (0.9f, 0.0f, 0.0f));
	std::shared_ptr<GeometryNode> volumetricLine4 = LoadVolumetricLine (points, 20);
	std::shared_ptr<VolumetricLineEffect> volumetricLineEffect4 = std::make_shared<VolumetricLineEffect> (m_Factory, volumetricLineTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP);
	volumetricLine4->SetVisualEffect (volumetricLineEffect4);
	m_PVWUpdater.Subscribe (volumetricLineEffect4->GetPVWMatrixUniformBuffer (), volumetricLine4->m_WorldT);
	m_Scene->AttachChild (volumetricLine4);
	m_GVector.push_back (volumetricLine4);
	m_GEffectVector.push_back (volumetricLineEffect4);
	//InitializeForceLines (imageLoader);*/
}

void InterpolationSimulation::InitializeForceLines (WICImageLoader imageLoader)
{
	std::shared_ptr<Texture2> volumetricLineTexture = imageLoader.Load ("data\\textures\\1d_glow1.png", true);
	volumetricLineTexture->AutoGenerateMipMap ();

	int numSegments = 40;
	std::vector<glm::vec4> points;

	float angle = 0.0f;
	float x = std::cos (Maths::DegToRad(angle));
	float z = std::sin (Maths::DegToRad(angle));
	
	points.push_back (glm::vec4(0.0f, 0.0f, 0.0f, angle));	
	
	points.push_back (glm::vec4(0.1*x, 0.0f, 0.1*z, angle));
	points.push_back (glm::vec4(0.2*x, 0.0f, 0.2*z, angle));
	points.push_back (glm::vec4(0.3*x, 0.0f, 0.3*z, angle));
	points.push_back (glm::vec4(0.4*x, 0.0f, 0.4*z, angle));
	points.push_back (glm::vec4(0.5*x, 0.0f, 0.5*z, angle));
	points.push_back (glm::vec4(0.6*x, 0.0f, 0.6*z, angle));
	points.push_back (glm::vec4(0.7*x, 0.0f, 0.7*z, angle));
	points.push_back (glm::vec4(0.8*x, 0.0f, 0.8*z, angle));
	points.push_back (glm::vec4(0.9*x, 0.0f, 0.9*z, angle));
	
	angle = 45.0f;
	x = std::cos (Maths::DegToRad(angle));
	z = std::sin (Maths::DegToRad(angle));

	points.push_back (glm::vec4(0.1*x, 0.0f, 0.1*z, angle));
	points.push_back (glm::vec4(0.2*x, 0.0f, 0.2*z, angle));
	points.push_back (glm::vec4(0.3*x, 0.0f, 0.3*z, angle));
	points.push_back (glm::vec4(0.4*x, 0.0f, 0.4*z, angle));
	points.push_back (glm::vec4(0.5*x, 0.0f, 0.5*z, angle));
	points.push_back (glm::vec4(0.6*x, 0.0f, 0.6*z, angle));
	points.push_back (glm::vec4(0.7*x, 0.0f, 0.7*z, angle));
	points.push_back (glm::vec4(0.8*x, 0.0f, 0.8*z, angle));
	points.push_back (glm::vec4(0.9*x, 0.0f, 0.9*z, angle));
	
	angle = 90.0f;
	x = std::cos (Maths::DegToRad(angle));
	z = std::sin (Maths::DegToRad(angle));

	points.push_back (glm::vec4(0.1*x, 0.0f, 0.1*z, angle));
	points.push_back (glm::vec4(0.2*x, 0.0f, 0.2*z, angle));
	points.push_back (glm::vec4(0.3*x, 0.0f, 0.3*z, angle));
	points.push_back (glm::vec4(0.4*x, 0.0f, 0.4*z, angle));
	points.push_back (glm::vec4(0.5*x, 0.0f, 0.5*z, angle));
	points.push_back (glm::vec4(0.6*x, 0.0f, 0.6*z, angle));
	points.push_back (glm::vec4(0.7*x, 0.0f, 0.7*z, angle));
	points.push_back (glm::vec4(0.8*x, 0.0f, 0.8*z, angle));
	points.push_back (glm::vec4(0.9*x, 0.0f, 0.9*z, angle));
	
	angle = 135.0f;
	x = std::cos (Maths::DegToRad(angle));
	z = std::sin (Maths::DegToRad(angle));

	points.push_back (glm::vec4(0.1*x, 0.0f, 0.1*z, angle));
	points.push_back (glm::vec4(0.2*x, 0.0f, 0.2*z, angle));
	points.push_back (glm::vec4(0.3*x, 0.0f, 0.3*z, angle));
	points.push_back (glm::vec4(0.4*x, 0.0f, 0.4*z, angle));
	points.push_back (glm::vec4(0.5*x, 0.0f, 0.5*z, angle));
	points.push_back (glm::vec4(0.6*x, 0.0f, 0.6*z, angle));
	points.push_back (glm::vec4(0.7*x, 0.0f, 0.7*z, angle));
	points.push_back (glm::vec4(0.8*x, 0.0f, 0.8*z, angle));
	points.push_back (glm::vec4(0.9*x, 0.0f, 0.9*z, angle));
	
	angle = 180.0f;
	x = std::cos (Maths::DegToRad(angle));
	z = std::sin (Maths::DegToRad(angle));

	points.push_back (glm::vec4(0.1*x, 0.0f, 0.1*z, angle));
	points.push_back (glm::vec4(0.2*x, 0.0f, 0.2*z, angle));
	points.push_back (glm::vec4(0.3*x, 0.0f, 0.3*z, angle));
	points.push_back (glm::vec4(0.4*x, 0.0f, 0.4*z, angle));
	points.push_back (glm::vec4(0.5*x, 0.0f, 0.5*z, angle));
	points.push_back (glm::vec4(0.6*x, 0.0f, 0.6*z, angle));
	points.push_back (glm::vec4(0.7*x, 0.0f, 0.7*z, angle));
	points.push_back (glm::vec4(0.8*x, 0.0f, 0.8*z, angle));
	points.push_back (glm::vec4(0.9*x, 0.0f, 0.9*z, angle));

	angle = 225.0f;
	x = std::cos (Maths::DegToRad(angle));
	z = std::sin (Maths::DegToRad(angle));

	points.push_back (glm::vec4(0.1*x, 0.0f, 0.1*z, angle));
	points.push_back (glm::vec4(0.2*x, 0.0f, 0.2*z, angle));
	points.push_back (glm::vec4(0.3*x, 0.0f, 0.3*z, angle));
	points.push_back (glm::vec4(0.4*x, 0.0f, 0.4*z, angle));
	points.push_back (glm::vec4(0.5*x, 0.0f, 0.5*z, angle));
	points.push_back (glm::vec4(0.6*x, 0.0f, 0.6*z, angle));
	points.push_back (glm::vec4(0.7*x, 0.0f, 0.7*z, angle));
	points.push_back (glm::vec4(0.8*x, 0.0f, 0.8*z, angle));
	points.push_back (glm::vec4(0.9*x, 0.0f, 0.9*z, angle));

	angle = 270.0f;
	x = std::cos (Maths::DegToRad(angle));
	z = std::sin (Maths::DegToRad(angle));

	points.push_back (glm::vec4(0.1*x, 0.0f, 0.1*z, angle));
	points.push_back (glm::vec4(0.2*x, 0.0f, 0.2*z, angle));
	points.push_back (glm::vec4(0.3*x, 0.0f, 0.3*z, angle));
	points.push_back (glm::vec4(0.4*x, 0.0f, 0.4*z, angle));
	points.push_back (glm::vec4(0.5*x, 0.0f, 0.5*z, angle));
	points.push_back (glm::vec4(0.6*x, 0.0f, 0.6*z, angle));
	points.push_back (glm::vec4(0.7*x, 0.0f, 0.7*z, angle));
	points.push_back (glm::vec4(0.8*x, 0.0f, 0.8*z, angle));
	points.push_back (glm::vec4(0.9*x, 0.0f, 0.9*z, angle));

	angle = 315.0f;
	x = std::cos (Maths::DegToRad(angle));
	z = std::sin (Maths::DegToRad(angle));

	points.push_back (glm::vec4(0.1*x, 0.0f, 0.1*z, angle));
	points.push_back (glm::vec4(0.2*x, 0.0f, 0.2*z, angle));
	points.push_back (glm::vec4(0.3*x, 0.0f, 0.3*z, angle));
	points.push_back (glm::vec4(0.4*x, 0.0f, 0.4*z, angle));
	points.push_back (glm::vec4(0.5*x, 0.0f, 0.5*z, angle));
	points.push_back (glm::vec4(0.6*x, 0.0f, 0.6*z, angle));
	points.push_back (glm::vec4(0.7*x, 0.0f, 0.7*z, angle));
	points.push_back (glm::vec4(0.8*x, 0.0f, 0.8*z, angle));
	points.push_back (glm::vec4(0.9*x, 0.0f, 0.9*z, angle));
	
	for (unsigned int i = 0; i < points.size (); i++)
	{
		glm::vec3 point = glm::vec3(points[i]);

		glm::vec3 controlPoint1 = point;
		glm::vec3 controlPoint2 = point;
		glm::vec3 controlPoint3 = point;
		
		float angle = points[i].w;
		float cos = std::cos (Maths::DegToRad (angle));
		float sin = std::sin (Maths::DegToRad (angle));
		float hip = controlPoint3.x / cos;

		controlPoint1.y += (30.0f *(1.0f - hip)) + 5.0f;
		controlPoint2.y += -(30.0f *(1.0f - hip)) - 5.0f;

		controlPoint3.x = controlPoint3.x == 0.0f ? 0.0f : (40.0f*cos * (1.0f - hip)) + cos*3.0f;
		controlPoint3.z = controlPoint3.z == 0.0f ? 0.0f : (40.0f*sin * (1.0f - hip)) + sin*3.0f;
		
		std::vector<glm::vec3> points;
		points.push_back (point);
		points.push_back (controlPoint1);
		points.push_back (controlPoint3);
		points.push_back (controlPoint2);
		points.push_back (point);
	
		std::shared_ptr<GeometryNode> volumetricLine = LoadVolumetricLine (points, numSegments);
		std::shared_ptr<VolumetricLineEffect> volumetricLineEffect = std::make_shared<VolumetricLineEffect> (m_Factory, volumetricLineTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP);
		volumetricLine->SetVisualEffect (volumetricLineEffect);
		m_PVWUpdater.Subscribe (volumetricLineEffect->GetPVWMatrixUniformBuffer (), volumetricLine->m_WorldT);
		m_Scene->AttachChild (volumetricLine);
		m_GVector.push_back (volumetricLine);
		m_GEffectVector.push_back (volumetricLineEffect);
	}	
}

void InterpolationSimulation::DrawShadowPass ()
{
	m_Cylinder->SetVisualEffect (m_CylinderShadowMapEffect);
	m_Spring->SetVisualEffect (m_SpringShadowMapEffect);

	m_Engine->Enable (m_CylinderDrawTarget);
	m_Engine->ClearDepthBuffer ();
	m_Engine->SetRasterizerState (m_RasterizerStateShadow);

	m_Engine->Draw (m_Cylinder);
	m_Engine->Draw(m_Spring);

	m_Engine->Disable (m_CylinderDrawTarget);
	m_Engine->SetDefaultRasterizerState ();
	m_Cylinder->SetVisualEffect (m_CylinderEffect);
	m_Spring->SetVisualEffect (m_SpringEffect);
}

void InterpolationSimulation::Update ()
{
	m_Scene->Update (m_AppTime);
	m_AppTime += m_AppTimeDelta;
	m_PVWUpdater.Update ();
	m_ShadowPVWUpdater.Update ();
}

void InterpolationSimulation::OnIdle ()
{
	Update ();	
	glutPostRedisplay ();	
}

void InterpolationSimulation::Render ()
{
	
	m_Timer.Measure ();	

	int width = m_WindowSize.m_XSize;
	int height = m_WindowSize.m_YSize;

	glm::vec4 bigScreenViewport (width - (width * 3)/4, height - (height * 3)/4, (width * 3)/4, (height * 3)/4);
	glm::vec4 smallScreenViewport (0, 0, width - (width * 3)/4, height - (height * 3)/4);
	glm::vec4 menuScreenViewport (width - 3 * width / 4, 0, 3 * width / 4,height - 3 * height / 4);

	m_Engine->SetViewport (bigScreenViewport);
	
	DrawShadowPass ();

	m_Engine->ClearBuffers ();
	//m_Engine->Draw (m_Rec);
	m_Engine->Draw(m_Cylinder);
	m_Engine->Draw(m_Spring);

	m_Engine->SetBlendState (m_BlendState);
	m_Engine->Draw(m_Particles);
	m_Engine->SetDefaultBlendState ();

	m_Engine->SetBlendState (m_BlendStateLine);
	m_Engine->SetRasterizerState (m_RasterizerStateLine);
	m_Engine->SetDepthStencilState (m_DepthStencilStateLine);
	/*for (unsigned int i = 0; i < m_GVector.size (); i++)
	{
		m_Engine->Draw (m_GVector[i]);
	}*/
	m_Engine->SetDefaultDepthStencilState ();
	m_Engine->SetDefaultRasterizerState ();
	m_Engine->SetDefaultBlendState ();

	m_Engine->SetViewport (smallScreenViewport);

	m_Engine->Draw (m_LineX);
	m_Engine->Draw (m_ConeX);
	m_Engine->Draw (m_LetterX);

	m_Engine->Draw (m_LineY);
	m_Engine->Draw (m_ConeY);
	m_Engine->Draw (m_LetterY);

	m_Engine->Draw (m_LineZ);
	m_Engine->Draw (m_ConeZ);
	m_Engine->Draw (m_LetterZ);
	
	m_Engine->SetViewport (menuScreenViewport);
	m_Engine->Draw (m_Scale);
	m_Engine->Draw (70, 40, glm::vec4 (1.0f), " 0 T");
	m_Engine->Draw (210, 40, glm::vec4 (1.0f), "  10 T");
	m_Engine->Draw (335, 40, glm::vec4 (1.0f), "  20 T");

	SwapBuffers ();
	m_Timer.UpdateFrameCount ();
}

void InterpolationSimulation::OnIdleCallback ()
{
	currentInstance->OnIdle ();
}

void InterpolationSimulation::RenderCallback ()
{
	currentInstance->Render ();
}


int _tmain(int argc, char* argv[])
{
	//engine = new OpenGLEngine ();
	//Window* window = new Window ("Ashkulsum", 100, 100, 600, 600);
	InterpolationSimulation* interp = new InterpolationSimulation ("Ashkulsum", 100, 100, 600, 600);
	interp->SetCurrentInstance ();
	//createScene ();
	glutIdleFunc (InterpolationSimulation::OnIdleCallback);
	glutDisplayFunc (InterpolationSimulation::RenderCallback);
	glutReshapeFunc(InterpolationSimulation::ReshapeCallback);
	glutMouseFunc(InterpolationSimulation::MouseButtonCallback);
	glutMotionFunc(InterpolationSimulation::MouseMoveCallback);
	glutKeyboardFunc (InterpolationSimulation::KeyboardCallback);
	glutMainLoop();
	//glload::LoadFunctions();
	
	/*if(!glload::IsVersionGEQ(3, 3))
	{
		printf("Your OpenGL version is %i, %i. You must have at least OpenGL 3.3.\n",
			glload::GetMajorVersion(), glload::GetMinorVersion());
		window->Destroy ();
		return 0;
	}*/
	//boost::thread t, t1;
	//t = boost::thread (thread, *window);
	//t1 = boost::thread (thread2, *window);

	/*while (!window->IsDestroyed ())
	{
		glfwPollEvents();
		update (*window);
		render ();
		/*MSG msg;
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                {
                    break;
                }

                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
		window->SwapBuffers ();
	}
	/*glutInit(&argc, argv);
	width = 1200;
	height = 800;
	unsigned int displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL;

	glutInitDisplayMode (displayMode);
	glutInitContextVersion (3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
#ifdef DEBUG
	glutInitContextFlags(GLUT_DEBUG);
#endif
	glutInitWindowSize (width, height); 
	glutInitWindowPosition (0, 0);
	int window = glutCreateWindow (argv[0]);
	glload::LoadFunctions();
	
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	if(!glload::IsVersionGEQ(3, 3))
	{
		printf("Your OpenGL version is %i, %i. You must have at least OpenGL 3.3.\n",
			glload::GetMajorVersion(), glload::GetMinorVersion());
		glutDestroyWindow(window);
		return 0;
	}
	init ();

	glutDisplayFunc(display);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutKeyboardFunc (keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	free();
	*/
}


