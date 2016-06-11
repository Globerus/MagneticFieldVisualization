// Ashkulsum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Ashkulsum.h"

InterpolationSimulation* InterpolationSimulation::currentInstance;

InterpolationSimulation::InterpolationSimulation (std::string title, int xOrigin, int yOrigin, int xSize, int ySize)
	:	Window (title, xOrigin, yOrigin, xSize, ySize)
{

	m_AppTime = 0.0f;
	m_AppTimeDelta = 0.01f;
	m_ZAccel = 0.0f;
	m_XAccel = 0.0f;
	m_ZCorrection = false;
	m_XCorrection = false;
	m_FieldScreened = true;

	std::shared_ptr<FontArialW400H16Bold> font = std::make_shared<FontArialW400H16Bold> (m_Factory, 257);
	m_Engine->SetFont (font);

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
	ParametrizeField ();
	CreateScene ();
	ParametrizeFieldXAxisMovementAnimation ();
	ParametrizeFieldZAxisMovementAnimation ();
	InitializeInterpolation ();
	CreateLoadingScreen ();

	m_Scene->Update ();
	m_PVWUpdater.Update ();
	m_ShadowPVWUpdater.Update ();
}

void InterpolationSimulation::CreateLoadingScreen ()
{
	WICImageLoader imageLoader;

	std::shared_ptr<Texture2> loadingScreenTexture = imageLoader.Load ("data\\textures\\LoadingScreen.jpg", true);
	loadingScreenTexture->AutoGenerateMipMap ();
	m_LoadingScreen = LoadMesh ("data\\objects\\rectangle.obj");
	m_LoadingScreen->name = "m_LoadingScreen";
	m_LoadingScreenEffect = std::make_shared<Texture2Effect> (m_Factory, loadingScreenTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP);
	m_LoadingScreen->SetVisualEffect (m_LoadingScreenEffect);
}

void InterpolationSimulation::ParametrizeField ()
{
	m_FieldParam.m_WorldWidth = 14.0f;
	m_FieldParam.m_WorldHeight = 18.0f;
	m_FieldParam.m_WorldDepth = 14.0f;

	m_FieldParam.m_WidthResolution = 20;
	m_FieldParam.m_HeightResolution = 28;
	m_FieldParam.m_DepthResolution = 20;

	m_FieldParam.m_NumAnimSteps = 5;
	m_FieldParam.m_StepTime = 1;

	m_FieldParam.m_NumInterpolatedPoints = 11200;
}

void InterpolationSimulation::InitializeInterpolation ()
{
	boost::thread parallelThread (boost::bind(&InterpolationSimulation::InterpolatePoints, this));
}

void InterpolationSimulation::InterpolatePoints ()
{
	int widthResolution = m_FieldParam.m_WidthResolution;
	int heightResolution = m_FieldParam.m_HeightResolution;
	int depthResolution = m_FieldParam.m_DepthResolution;
	float widthWorld = m_FieldParam.m_WorldWidth;
	float heightWorld = m_FieldParam.m_WorldHeight;
	float depthWorld = m_FieldParam.m_WorldDepth;

	float xPixel = widthWorld/(widthResolution-1);
	float yPixel = heightWorld/(heightResolution-1);
	float zPixel = depthWorld/(depthResolution-1);

	float widthStartPoint = - widthWorld/2;
	float heightStartPoint = - heightWorld/2;
	float depthStartPoint = - depthWorld/2;

	m_CGALInterpolator->SetInterpolationDone (false);
	for (int step = 0; step < m_FieldParam.m_NumAnimSteps; step++)
	{
		m_CGALInterpolator->InitializeMagForceValues (step);
		for (int depth = 0; depth < depthResolution; depth++)
			for (int height = 0; height < heightResolution; height++)
				for (int width = 0; width < widthResolution; width++)
				{
					glm::vec3 point (widthStartPoint + xPixel*width, heightStartPoint + yPixel*height, depthStartPoint + zPixel*depth);
					m_CGALInterpolator->InterpolateMagForce (step, point);
				}
	}
	InitParticles ();
	m_CGALInterpolator->SetInterpolationDone (true);
}

void InterpolationSimulation::InitParticles ()
{
	auto instancedBuffer = m_Particles->GetInstancedBuffer ();

	struct InstancedVertex 
	{
		glm::vec2 m_TexCoord;
		glm::vec3 m_Instance;
	};

	InstancedVertex* instance = instancedBuffer->Get<InstancedVertex> ();
	auto numInterpolatedPoints = m_FieldParam.m_NumInterpolatedPoints;
	auto interpolatedPoints = m_CGALInterpolator->GetInterpolatedGLMPointMagForceVector ();
	for (int i =0; i < numInterpolatedPoints; i++)
	{
		instance[i].m_Instance = glm::vec3 (interpolatedPoints[0][i]);
		instance[i].m_TexCoord = glm::vec2 (interpolatedPoints[0][i].w, 0.0f);
	}
}

void InterpolationSimulation::UpdateFieldVisualization ()
{
	auto posZ = m_FieldScreenZAxis->m_WorldT.GetTranslationW0 ();
	auto posX = m_FieldScreenXAxis->m_WorldT.GetTranslationW0 ();
	float startPointX = m_FieldParam.m_WorldWidth/2;
	float startPointZ = m_FieldParam.m_WorldDepth/2;

	if (posX == glm::vec4 (startPointX, 0.0f, 0.0f, 0.0f) && m_XCorrection)
	{
		m_AppTime = 0.0f;
		m_FieldScreenXAxis->DetachAnimator (m_FieldMovementXAxisAnimation);
		m_XCorrection = false;
		ParametrizeFieldXAxisMovementAnimation ();
		m_FieldScreenXAxis->AttachAnimator (m_FieldMovementXAxisAnimation);
	}

	if (posZ == glm::vec4 (0.0f, 0.0f, startPointZ, 0.0f) && m_ZCorrection)
	{
		m_FieldScreenZAxis->DetachAnimator (m_FieldMovementZAxisAnimation);
		m_ZCorrection = false;
		ParametrizeFieldZAxisMovementAnimation ();
		m_FieldScreenZAxis->AttachAnimator (m_FieldMovementZAxisAnimation);
	}

	if (!m_KeyStates[101] && m_ZAccel > 0.0f)
		m_ZAccel -= 0.25f;
	else if (!m_KeyStates[103] && m_ZAccel < 0.0f)
		m_ZAccel += 0.25;
	else if (!m_KeyStates[102] && m_XAccel > 0.0f)
		m_XAccel -= 0.25f;
	else if (!m_KeyStates[100] && m_XAccel < 0.0f)
		m_XAccel += 0.25f;
	
	posZ.z = posZ.z + 0.01f*m_ZAccel;
	posX.x = posX.x + 0.01f*m_XAccel;
	m_FieldScreenZAxis->m_LocalT.SetTranslation (posZ);
	m_FieldScreenXAxis->m_LocalT.SetTranslation (posX);

	UpdateFieldScreenXAxis ();
	UpdateFieldScreenZAxis ();
}

void InterpolationSimulation::UpdateFieldScreenXAxis ()
{
	auto interpolatedPointMagForceVector = m_CGALInterpolator->GetInterpolatedGLMPointMagForceVector ();

	int widthResolution = m_FieldParam.m_WidthResolution;
	int heightResolution = m_FieldParam.m_HeightResolution;
	int depthResolution = m_FieldParam.m_DepthResolution;
	
	float widthWorld = m_FieldParam.m_WorldWidth;

	int numSteps = m_FieldParam.m_NumAnimSteps;
	int stepTime = m_FieldParam.m_StepTime;

	float texDelta = 1.0f / numSteps;
	float x0 = 0.0f, x1 = 0.0f;

	if (!m_FieldScreenXAxisEffect)
	{
		m_ParallelThread.join ();
		
		float * data = new float [numSteps * widthResolution * heightResolution * depthResolution];
		
		for (int step = 0; step < numSteps; step += stepTime)
			for (int x = 0; x < widthResolution; x++)
				for (int y = 0; y < heightResolution; y++)
					for (int z = 0; z < depthResolution; z++)
					{
						int revIndex = x * heightResolution * depthResolution + (heightResolution - 1) * depthResolution  - y * depthResolution + z;
						int index = x * heightResolution * depthResolution * numSteps + y * depthResolution * numSteps + step * depthResolution + z;
						data[index] = interpolatedPointMagForceVector[step][revIndex].w;
					}
			
		std::shared_ptr<Texture2Array> magneticFieldTextureArray = std::make_shared<Texture2Array> (widthResolution, DP_R32_FLOAT, numSteps * depthResolution, heightResolution);
		magneticFieldTextureArray->SetUsage (Resource::DYNAMIC_UPDATE);
		magneticFieldTextureArray->AutoGenerateMipMap ();
		memcpy (magneticFieldTextureArray->GetData(), data, magneticFieldTextureArray->GetNumBytes ());
		delete [] data;

		m_FieldScreenXAxisEffect = std::make_shared<MagneticFieldEffect> (m_Factory, magneticFieldTextureArray, m_ColorScaleTexture, glm::vec3 (widthWorld, float(widthResolution), 0.0f), SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP);
		m_FieldScreenXAxis->SetVisualEffect (m_FieldScreenXAxisEffect);
		m_PVWUpdater.Subscribe (m_FieldScreenXAxisEffect->GetPVWMatrixUniformBuffer (), m_FieldScreenXAxis->m_WorldT);	

		x0 = 0.0f;
		x1 = texDelta;

		m_Timer.Reset ();
	}
	else 
	{
		float time = (float)m_Timer.GetSeconds ();

		int intTime = (int)glm::floor (time);
		numSteps -= 1;
		intTime = numSteps - abs(intTime - numSteps);
	
		x0 = intTime * texDelta;
		x1 = (intTime + 1) * texDelta;

		if (time >= 2*numSteps) 
			m_Timer.Reset ();		
	}

	struct Vertex
	{
		glm::vec3 pos;
		glm::vec2 tex;
		glm::vec3 norm;
	};

	Vertex* vertexData = m_FieldScreenXAxis->GetVertexBuffer ()->Get<Vertex> ();

	vertexData[0].tex.x = x1;
	vertexData[1].tex.x = x1;
	vertexData[2].tex.x = x0;
	vertexData[3].tex.x = x0;
	vertexData[4].tex.x = x0;
	vertexData[5].tex.x = x0;
	vertexData[6].tex.x = x1;
	vertexData[7].tex.x = x1;
			
	m_Engine->Update (m_FieldScreenXAxis->GetVertexBuffer ());
}

void InterpolationSimulation::UpdateFieldScreenZAxis ()
{
	auto interpolatedPointMagForceVector = m_CGALInterpolator->GetInterpolatedGLMPointMagForceVector ();

	int widthResolution = m_FieldParam.m_WidthResolution;
	int heightResolution = m_FieldParam.m_HeightResolution;
	int depthResolution = m_FieldParam.m_DepthResolution;
	
	float depthWorld = m_FieldParam.m_WorldDepth;

	int numSteps = m_FieldParam.m_NumAnimSteps;
	int stepTime = m_FieldParam.m_StepTime;

	float texDelta = 1.0f / numSteps;
	float x0 = 0.0f, x1 = 0.0f;

	if (!m_FieldScreenZAxisEffect)
	{
		m_ParallelThread.join ();
		
		float * data = new float [numSteps * widthResolution * heightResolution * depthResolution];
		
		for (int step = 0; step < numSteps; step += stepTime)
			for (int z = 0; z < depthResolution; z++)
				for (int y = 0; y < heightResolution; y++)
					for (int x = 0; x < widthResolution; x++)
					{
						int revIndex = z * heightResolution * widthResolution + (heightResolution - 1) * widthResolution  - y * widthResolution + x;
						int index = z * heightResolution * widthResolution * numSteps + y * widthResolution * numSteps + step * widthResolution + x;
						data[index] = interpolatedPointMagForceVector[step][revIndex].w;
					}
		
		
		std::shared_ptr<Texture2Array> magneticFieldTextureArray = std::make_shared<Texture2Array> (depthResolution, DP_R32_FLOAT, numSteps * widthResolution, heightResolution);
		magneticFieldTextureArray->SetUsage (Resource::DYNAMIC_UPDATE);
		magneticFieldTextureArray->AutoGenerateMipMap ();
		memcpy (magneticFieldTextureArray->GetData(), data, magneticFieldTextureArray->GetNumBytes ());
		delete [] data;

		m_FieldScreenZAxisEffect = std::make_shared<MagneticFieldEffect> (m_Factory, magneticFieldTextureArray, m_ColorScaleTexture, glm::vec3 (depthWorld, float(depthResolution), 2.0f), SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP);
		m_FieldScreenZAxis->SetVisualEffect (m_FieldScreenZAxisEffect);
		m_PVWUpdater.Subscribe (m_FieldScreenZAxisEffect->GetPVWMatrixUniformBuffer (), m_FieldScreenZAxis->m_WorldT);	

		x0 = 0.0f;
		x1 = texDelta;

		m_Timer.Reset ();
	}
	else 
	{
		float time = (float)m_Timer.GetSeconds ();

		int intTime = (int)glm::floor (time);
		numSteps -= 1;
		intTime = numSteps - abs(intTime - numSteps);
	
		x0 = intTime * texDelta;
		x1 = (intTime + 1) * texDelta;

		if (time >= 2*numSteps) 
			m_Timer.Reset ();		
	}

	struct Vertex
	{
		glm::vec3 pos;
		glm::vec2 tex;
		glm::vec3 norm;
	};

	Vertex* vertexData = m_FieldScreenZAxis->GetVertexBuffer ()->Get<Vertex> ();

	vertexData[0].tex.x = x1;
	vertexData[1].tex.x = x1;
	vertexData[2].tex.x = x0;
	vertexData[3].tex.x = x0;
	vertexData[4].tex.x = x0;
	vertexData[5].tex.x = x0;
	vertexData[6].tex.x = x1;
	vertexData[7].tex.x = x1;
			
	m_Engine->Update (m_FieldScreenZAxis->GetVertexBuffer ());
}

void InterpolationSimulation::ParametrizeFieldXAxisMovementAnimation ()
{
	Transformation localTransform;
  
	glm::vec4 startTranslation = m_FieldScreenXAxis->m_WorldT.GetTranslationW0 ();
	float startScale = m_FieldScreenXAxis->m_WorldT.GetUniformScale ();
	glm::mat4 startRotation = m_FieldScreenXAxis->m_WorldT.GetRotation ();
	float width = m_FieldParam.m_WorldWidth;
	
	int numTranslations = 160;
	int numRotations = 0;
	int numScales = 0;

	glm::vec4 endTranslation = startTranslation + glm::vec4 (-width, 0.0f, 0.0f, 0.0f);
	glm::mat4 endRotation = startRotation;
	float endScale = startScale;

	std::vector<glm::vec4> translationsVector;
	std::vector<float> translationTimesVector;
	
	float step = width/numTranslations;

	for (int i = 0; i < numTranslations; i ++)
	{
		glm::vec4 midTranslation = startTranslation + glm::vec4(-(i * step), 0.0f, 0.0f, 0.0f);
		translationsVector.push_back (midTranslation);
		translationTimesVector.push_back ((1.0f/numTranslations) * i);
	}

	localTransform.SetTranslation (endTranslation);
	localTransform.SetRotation (endRotation);
	localTransform.SetUniformScale (endScale);

	std::shared_ptr<KeyframeAnimator> keyfctrl = 
		std::make_shared<KeyframeAnimator>(0, numTranslations, numRotations, numScales, localTransform);

	if (numTranslations > 0)
	{
		keyfctrl->SetTranslationTimes (translationTimesVector);
		keyfctrl->SetTranslations (translationsVector);
	}
		
	m_FieldMovementXAxisAnimation = keyfctrl;
	m_FieldMovementXAxisAnimation->m_Repeat = Animator::RT_CYCLE;
	m_FieldMovementXAxisAnimation->m_MinTime = 0.0;
	m_FieldMovementXAxisAnimation->m_MaxTime = 1.0;
	m_FieldMovementXAxisAnimation->m_Phase = 0.0;
	m_FieldMovementXAxisAnimation->m_Frequency = 0.3;
	m_FieldMovementXAxisAnimation->m_Active = true;
}

void InterpolationSimulation::ParametrizeFieldXAxisCorrectionMovementAnimation ()
{
	Transformation localTransform;
  
	glm::vec4 startTranslation = m_FieldScreenXAxis->m_WorldT.GetTranslationW0 ();
	float startScale = m_FieldScreenXAxis->m_WorldT.GetUniformScale ();
	glm::mat4 startRotation = m_FieldScreenXAxis->m_WorldT.GetRotation ();
	float width = m_FieldParam.m_WorldWidth;

	float halfWidth = width/2;

	float distance = halfWidth - startTranslation.x;

	int numTranslations = 160;
	int numRotations = 0;
	int numScales = 0;

	numTranslations = int(distance*numTranslations/width);

	glm::vec4 endTranslation = glm::vec4 (halfWidth, startTranslation.y, startTranslation.z, startTranslation.w);
	glm::mat4 endRotation = startRotation;
	float endScale = startScale;

	std::vector<glm::vec4> translationsVector;
	std::vector<float> translationTimesVector;
	
	float step = distance/numTranslations;

	for (int i = 0; i < numTranslations; i ++)
	{
		glm::vec4 midTranslation = startTranslation + glm::vec4((i * step), 0.0f, 0.0f, 0.0f);
		translationsVector.push_back (midTranslation);
		translationTimesVector.push_back ((1.0f/numTranslations) * i);
	}

	translationsVector.push_back (endTranslation);
	translationTimesVector.push_back (1.0f);

	numTranslations ++;

	localTransform.SetTranslation (endTranslation);
	localTransform.SetRotation (endRotation);
	localTransform.SetUniformScale (endScale);

	std::shared_ptr<KeyframeAnimator> keyfctrl = 
		std::make_shared<KeyframeAnimator>(0, numTranslations, numRotations, numScales, localTransform);

	if (numTranslations > 0)
	{
		keyfctrl->SetTranslationTimes (translationTimesVector);
		keyfctrl->SetTranslations (translationsVector);
	}
		
	m_FieldMovementXAxisAnimation = keyfctrl;
	m_FieldMovementXAxisAnimation->m_Repeat = Animator::RT_CLAMP;
	m_FieldMovementXAxisAnimation->m_MinTime = 0.0;
	m_FieldMovementXAxisAnimation->m_MaxTime = 1.0;
	m_FieldMovementXAxisAnimation->m_Phase = 0.0;
	m_FieldMovementXAxisAnimation->m_Frequency = 1.0;
	m_FieldMovementXAxisAnimation->m_Active = true;
}

void InterpolationSimulation::ParametrizeFieldZAxisMovementAnimation ()
{
	Transformation localTransform;
  
	glm::vec4 startTranslation = m_FieldScreenZAxis->m_WorldT.GetTranslationW0 ();
	float startScale = m_FieldScreenZAxis->m_WorldT.GetUniformScale ();
	glm::mat4 startRotation = m_FieldScreenZAxis->m_WorldT.GetRotation ();
	float depth = m_FieldParam.m_WorldDepth;
	
	int numTranslations = 160;
	int numRotations = 0;
	int numScales = 0;

	glm::vec4 endTranslation = startTranslation + glm::vec4 (0.0f, 0.0f, -depth, 0.0f);
	glm::mat4 endRotation = startRotation;
	float endScale = startScale;

	std::vector<glm::vec4> translationsVector;
	std::vector<float> translationTimesVector;
	
	float step = depth/numTranslations;

	for (int i = 0; i < numTranslations; i ++)
	{
		glm::vec4 midTranslation = startTranslation + glm::vec4(0.0f, 0.0f, -(i * step), 0.0f);
		translationsVector.push_back (midTranslation);
		translationTimesVector.push_back ((1.0f/numTranslations) * i);
	}

	localTransform.SetTranslation (endTranslation);
	localTransform.SetRotation (endRotation);
	localTransform.SetUniformScale (endScale);

	std::shared_ptr<KeyframeAnimator> keyfctrl = 
		std::make_shared<KeyframeAnimator>(0, numTranslations, numRotations, numScales, localTransform);

	if (numTranslations > 0)
	{
		keyfctrl->SetTranslationTimes (translationTimesVector);
		keyfctrl->SetTranslations (translationsVector);
	}
		
	m_FieldMovementZAxisAnimation = keyfctrl;
	m_FieldMovementZAxisAnimation->m_Repeat = Animator::RT_CYCLE;
	m_FieldMovementZAxisAnimation->m_MinTime = 0.0;
	m_FieldMovementZAxisAnimation->m_MaxTime = 1.0;
	m_FieldMovementZAxisAnimation->m_Phase = 0.0;
	m_FieldMovementZAxisAnimation->m_Frequency = 0.3;
	m_FieldMovementZAxisAnimation->m_Active = true;
}

void InterpolationSimulation::ParametrizeFieldZAxisCorrectionMovementAnimation ()
{
	Transformation localTransform;
  
	glm::vec4 startTranslation = m_FieldScreenZAxis->m_WorldT.GetTranslationW0 ();
	float startScale = m_FieldScreenZAxis->m_WorldT.GetUniformScale ();
	glm::mat4 startRotation = m_FieldScreenZAxis->m_WorldT.GetRotation ();
	float depth = m_FieldParam.m_WorldDepth;

	float halfDepth = depth/2;

	float distance = halfDepth - startTranslation.z;

	int numTranslations = 160;
	int numRotations = 0;
	int numScales = 0;

	numTranslations = int(distance*numTranslations/depth);
	glm::vec4 endTranslation = glm::vec4 (startTranslation.x, startTranslation.y, halfDepth, startTranslation.w);
	glm::mat4 endRotation = startRotation;
	float endScale = startScale;

	std::vector<glm::vec4> translationsVector;
	std::vector<float> translationTimesVector;
	
	float step = distance/numTranslations;

	for (int i = 0; i < numTranslations; i ++)
	{
		glm::vec4 midTranslation = startTranslation + glm::vec4(0.0f, 0.0f, (i * step), 0.0f);
		translationsVector.push_back (midTranslation);
		translationTimesVector.push_back ((1.0f/numTranslations) * i);
	}

	translationsVector.push_back (endTranslation);
	translationTimesVector.push_back (1.0f);

	numTranslations ++;

	localTransform.SetTranslation (endTranslation);
	localTransform.SetRotation (endRotation);
	localTransform.SetUniformScale (endScale);

	std::shared_ptr<KeyframeAnimator> keyfctrl = 
		std::make_shared<KeyframeAnimator>(0, numTranslations, numRotations, numScales, localTransform);

	if (numTranslations > 0)
	{
		keyfctrl->SetTranslationTimes (translationTimesVector);
		keyfctrl->SetTranslations (translationsVector);
	}

	m_FieldMovementZAxisAnimation = keyfctrl;
	m_FieldMovementZAxisAnimation->m_Repeat = Animator::RT_CLAMP;
	m_FieldMovementZAxisAnimation->m_MinTime = 0.0;
	m_FieldMovementZAxisAnimation->m_MaxTime = 1.0;
	m_FieldMovementZAxisAnimation->m_Phase = 0.0;
	m_FieldMovementZAxisAnimation->m_Frequency = 1.0;
	m_FieldMovementZAxisAnimation->m_Active = true;
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
		m_NodesEffects.push_back (std::make_pair (m_Plane, m_PlaneEffect));

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
		auto const cameraProjectionMatrix = m_Camera->GetProjectionMatrix ();
		auto const particlesWorldMatrix = m_Particles->m_WorldT.GetTransformationMatrix ();
		m_ParticlesEffect->GetProjectionMatrixUniformBuffer () ->SetMember ("projectionMatrix", cameraProjectionMatrix);
		m_ParticlesEffect->GetViewMatrixUniformBuffer () ->SetMember ("viewMatrix", cameraViewMatrix);
		m_ParticlesEffect->GetWorldMatrixUniformBuffer () ->SetMember ("worldMatrix", particlesWorldMatrix);
		m_Updater (m_ParticlesEffect->GetProjectionMatrixUniformBuffer ());
		m_Updater (m_ParticlesEffect->GetViewMatrixUniformBuffer ());
		m_Updater (m_ParticlesEffect->GetWorldMatrixUniformBuffer ());

		auto const fieldScreenXAxisWorldMatrix = m_FieldScreenXAxis->m_WorldT.GetTransformationMatrix ();
		auto const fieldScreenZAxisWorldMatrix = m_FieldScreenZAxis->m_WorldT.GetTransformationMatrix ();

		if (m_FieldScreenXAxisEffect && m_FieldScreenZAxisEffect)
		{
			m_FieldScreenXAxisEffect->GetWMatrixUniformBuffer () ->SetMember ("wMatrix", fieldScreenXAxisWorldMatrix);
			m_Updater (m_FieldScreenXAxisEffect->GetWMatrixUniformBuffer ());

			m_FieldScreenZAxisEffect->GetWMatrixUniformBuffer () ->SetMember ("wMatrix", fieldScreenZAxisWorldMatrix);
			m_Updater (m_FieldScreenZAxisEffect->GetWMatrixUniformBuffer ());
		}
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
	glm::vec4 posX, posZ; 
	float startPointX, startPointZ;
	switch (key)
	{
	case 'x':
		m_AppTime = 0.0f;
		posX = m_FieldScreenXAxis->m_WorldT.GetTranslationW0 ();
		startPointX = m_FieldParam.m_WorldWidth/2;

		if (!m_XCorrection && posX != glm::vec4 (startPointX, 0.0f, 0.0f, 0.0f))
		{
			m_XCorrection = true;
			ParametrizeFieldXAxisCorrectionMovementAnimation ();
		}

		posZ = m_FieldScreenZAxis->m_WorldT.GetTranslationW0 ();
		startPointZ = m_FieldParam.m_WorldDepth/2;

		if (!m_ZCorrection && posZ != glm::vec4 (0.0f, 0.0f, startPointZ, 0.0f))
		{
			m_ZCorrection = true;
			ParametrizeFieldZAxisCorrectionMovementAnimation ();
		}

		m_FieldScreenZAxis->AttachAnimator (m_FieldMovementZAxisAnimation);
		m_FieldScreenXAxis->AttachAnimator (m_FieldMovementXAxisAnimation);
		return;
	case 's':
		if(m_FieldScreened)
			m_FieldScreened = false;
		else
			m_FieldScreened = true;
		return;
	case 27:
		glutLeaveMainLoop();
		return;
	}
}

void InterpolationSimulation::KeyboardUp(unsigned char key, int x, int y)
{
	m_KeyStates[key] = 0;
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		return;
	}
}

void InterpolationSimulation::SpecialKeyboard(int key, int x, int y)
{
	m_KeyStates[key] = 1;
	switch (key)
	{
	case GLUT_KEY_UP:
		m_FieldScreenZAxis->DetachAnimator (m_FieldMovementZAxisAnimation);
		m_ZAccel =  m_ZAccel + 0.25f;
		m_ZAccel = m_ZAccel > 40.0f ? 40.0f : m_ZAccel;
		return;
	case GLUT_KEY_DOWN:
		m_FieldScreenZAxis->DetachAnimator (m_FieldMovementZAxisAnimation);
		m_ZAccel -= 0.25f;
		m_ZAccel = m_ZAccel < -40.0f ? -40.0f : m_ZAccel;
		return;
	case GLUT_KEY_RIGHT:
		m_FieldScreenXAxis->DetachAnimator (m_FieldMovementXAxisAnimation);
		m_XAccel += 0.25f;
		m_XAccel = m_XAccel > 40.0f ? 40.0f : m_XAccel;
		return;
	case GLUT_KEY_LEFT:
		m_FieldScreenXAxis->DetachAnimator (m_FieldMovementXAxisAnimation);
		m_XAccel -= 0.25f;
		m_XAccel = m_XAccel < -40.0f ? -40.0f : m_XAccel;
		return;
	case 27:
		glutLeaveMainLoop();
		return;
	}
}

void InterpolationSimulation::SpecialKeyboardUp(int key, int x, int y)
{
	m_KeyStates[key] = 0;	
}


void InterpolationSimulation::Reshape (int w, int h)
{
	//Window::SetWindowSize (w, h);
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

void InterpolationSimulation::KeyboardUpCallback (unsigned char key, int x, int y)
{
	currentInstance->KeyboardUp (key, x, y);
}

void InterpolationSimulation::SpecialKeyboardCallback (int key, int x, int y)
{
	currentInstance->SpecialKeyboard (key, x, y);
}

void InterpolationSimulation::SpecialKeyboardUpCallback (int key, int x, int y)
{
	currentInstance->SpecialKeyboardUp (key, x, y);
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
	m_ColorScaleTexture = imageLoader.Load ("data\\textures\\Scale.png", true);
	m_ColorScaleTexture->AutoGenerateMipMap ();
	m_ScaleEffect = std::make_shared<Texture2Effect> (m_Factory, m_ColorScaleTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP); 
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
	
	auto interpolatedPoints = m_CGALInterpolator->GetInterpolatedGLMPointMagForceVector ();
	std::shared_ptr<Texture2> particleTexture = imageLoader.Load ("data\\textures\\particle.png", true);
	particleTexture->AutoGenerateMipMap ();
	m_Particles = LoadParticles (m_FieldParam.m_NumInterpolatedPoints);
	m_Particles->m_LocalT.SetUniformScale (0.05f);
	m_ParticlesEffect = std::make_shared<ParticlesEffect> (m_Factory, m_ColorScaleTexture, particleTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP, SamplerState::CLAMP);
	m_Particles->SetVisualEffect (m_ParticlesEffect);
	billBoardParticles->AttachChild (m_Particles);
	
	m_FieldScreenZAxis = LoadMesh ("data\\objects\\fieldScreen.obj");
	m_FieldScreenZAxis->m_LocalT.SetUniformScale (8.0f);
	m_FieldScreenZAxis->m_LocalT.SetTranslation (glm::vec4 (0.0f, 0.0f, 4.0f, 0.0f));
	m_Scene->AttachChild (m_FieldScreenZAxis);

	m_FieldScreenXAxis = LoadMesh ("data\\objects\\fieldScreen.obj");
	m_FieldScreenXAxis->m_LocalT.SetRotation (glm::vec3 (0.0f, 1.0f, 0.0f), -90.0f);
	m_FieldScreenXAxis->m_LocalT.SetUniformScale (8.0f);
	m_FieldScreenXAxis->m_LocalT.SetTranslation (glm::vec4 (4.0f, 0.0f, 0.0f, 0.0f));
	m_Scene->AttachChild (m_FieldScreenXAxis);

	m_Plane = LoadMesh ("data\\objects\\plane.obj");
	m_Plane->m_LocalT.SetUniformScale (24.0f);
	m_Plane->m_LocalT.SetTranslation (glm::vec4 (0.0f, -10.0f, 0.0f, 0.0f));

	m_PlaneEffect = std::make_shared<DirectionalLightingTextureWithShadowEffect> (m_Factory, m_Updater, material, lighting, lightCameraInfo, cylinderTexture, m_ShadowTexture, SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP);
	m_PlaneEffect->GetLightInfo ()->m_LightDirection = m_LightWorldDirection;
	m_Plane->SetVisualEffect (m_PlaneEffect);

	m_PlaneShadowMapEffect = std::make_shared<ShadowMapEffect> (m_Factory);

	m_PVWUpdater.Subscribe (m_PlaneEffect->GetPVWMatrixUniformBuffer (), m_Plane->m_WorldT);
	m_ShadowPVWUpdater.Subscribe (m_PlaneEffect->GetLightPVWMatrixUniformBuffer (), m_Plane->m_WorldT, "lightPVWMatrix");
	m_ShadowPVWUpdater.Subscribe (m_PlaneShadowMapEffect->GetPVWMatrixUniformBuffer (), m_Plane->m_WorldT);
	m_Scene->AttachChild (m_Plane);
	
}

void InterpolationSimulation::DrawShadowPass ()
{
	m_Cylinder->SetVisualEffect (m_CylinderShadowMapEffect);
	m_Spring->SetVisualEffect (m_SpringShadowMapEffect);
	m_Plane->SetVisualEffect (m_PlaneShadowMapEffect);

	m_Engine->Enable (m_CylinderDrawTarget);
	m_Engine->ClearDepthBuffer ();
	m_Engine->SetRasterizerState (m_RasterizerStateShadow);

	m_Engine->Draw (m_Plane);
	m_Engine->Draw (m_Cylinder);
	m_Engine->Draw (m_Spring);

	m_Engine->Disable (m_CylinderDrawTarget);
	m_Engine->SetDefaultRasterizerState ();
	m_Cylinder->SetVisualEffect (m_CylinderEffect);
	m_Spring->SetVisualEffect (m_SpringEffect);
	m_Plane->SetVisualEffect (m_PlaneEffect);
}

void InterpolationSimulation::Update ()
{
	if(m_CGALInterpolator->GetInterpolationDone ())
	{
		UpdateFieldVisualization ();
	}

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
	
	m_MainLoopTimer.Measure ();

	int width = Window::m_WindowSize.m_XSize;
	int height = Window::m_WindowSize.m_YSize;

	glm::vec4 bigScreenViewport (0, height - (height * 3)/4, width, (height * 3)/4);
	glm::vec4 smallScreenViewport (0, 0, width - (width * 3)/4, height - (height * 3)/4);
	glm::vec4 menuScreenViewport (width - 3 * width / 4, 0, 3 * width / 4,height - 3 * height / 4);

	m_Engine->ClearBuffers ();

	if (!m_CGALInterpolator->GetInterpolationDone ())
	{
		m_Engine->SetViewport (glm::vec4 (0.0f, 0.0f, width, height));
		m_Engine->Draw (m_LoadingScreen);
		m_Engine->Draw (360, 150, glm::vec4 (1.0f), "L O A D I N G");
	}
	else
	{
		m_Engine->SetViewport (bigScreenViewport);
	
		DrawShadowPass ();

		m_Engine->SetBlendState (m_BlendState);
		if (m_FieldScreened)
		{
			m_Engine->Draw (m_FieldScreenZAxis);
			m_Engine->Draw (m_FieldScreenXAxis);
		}
		else
		{
			m_Engine->Draw(m_Particles);
		}

		m_Engine->SetDefaultBlendState ();

		m_Engine->Draw(m_Plane);
		m_Engine->Draw(m_Cylinder);
		m_Engine->Draw(m_Spring);

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
		m_Engine->Draw (120, 40, glm::vec4 (1.0f), " 0 mT");
		m_Engine->Draw (285, 40, glm::vec4 (1.0f), "  5 mT");
		m_Engine->Draw (440, 40, glm::vec4 (1.0f), "  10 mT");
	}

	SwapBuffers ();

	m_MainLoopTimer.UpdateNumFrames ();
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
	InterpolationSimulation* interp = new InterpolationSimulation ("Ashkulsum", 0, 0, 800, 600);
	interp->SetCurrentInstance ();
	
	glutIdleFunc (InterpolationSimulation::OnIdleCallback);
	glutDisplayFunc (InterpolationSimulation::RenderCallback);
	glutReshapeFunc(InterpolationSimulation::ReshapeCallback);
	glutMouseFunc(InterpolationSimulation::MouseButtonCallback);
	glutMotionFunc(InterpolationSimulation::MouseMoveCallback);
	glutKeyboardFunc (InterpolationSimulation::KeyboardCallback);
	glutKeyboardUpFunc (InterpolationSimulation::KeyboardUpCallback);
	glutSpecialFunc(InterpolationSimulation::SpecialKeyboardCallback);
	glutSpecialUpFunc(InterpolationSimulation::SpecialKeyboardUpCallback);
	glutMainLoop();
}


