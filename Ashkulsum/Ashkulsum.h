#include "window.h"
#include "pvwUpdater.h"
#include "load.h"
#include <boost/thread.hpp>
#include <boost/thread/scoped_thread.hpp>
#include "wicImageLoader.h"
#include "keyframeAnimator.h"
#include "lightCamera.h"
#include "cameraNode.h"
#include "normalEffect.h"
#include "texture2Effect.h"
#include "particlesEffect.h"
#include "directionalLightingEffect.h"
#include "directionalLightingTextureEffect.h"
#include "directionalLightingTextureWithShadowEffect.h"
#include "volumetricLineEffect.h"
#include "shadowMapEffect.h"
#include "textEffect.h"
#include "fontArialW400H16.h"
#include "fontArialW400H16Bold.h"
#include "field.h"

class InterpolationSimulation : public Window
{
public:
	InterpolationSimulation (std::string title, int xOrigin, int yOrigin, int xSize, int ySize);
	~InterpolationSimulation ();

	void InitializeCameraNode ();
	void InitializeLightNode ();
	void InitializeForceLines (WICImageLoader imageLoader);

	void MouseMove(int x, int y);
	void MouseButton(int button, int state, int x, int y);
	void Keyboard(unsigned char key, int x, int y);
	void Reshape (int w, int h);
	
	void CreateAnimator ();
	void CreateScene ();
	void DrawShadowPass ();
	void OnIdle ();
	void Update ();
	void Render ();

	static void OnIdleCallback ();
	static void RenderCallback ();
	static void MouseMoveCallback (int x, int y);
	static void MouseButtonCallback (int button, int state, int x, int y);
	static void KeyboardCallback (unsigned char key, int x, int y);
	static void ReshapeCallback (int w, int h);

	void SetCurrentInstance ();

private:
	static InterpolationSimulation* currentInstance;
	
	std::shared_ptr<CGALInterpolationSimulator> m_CGALInterpolator;
	PVWUpdater m_ShadowPVWUpdater;

	std::shared_ptr<BlendState> m_BlendState;
	std::shared_ptr<BlendState> m_BlendStateLine;

	std::shared_ptr<DepthStencilState> m_DepthStencilStateLine;

	std::shared_ptr<RasterizerState> m_RasterizerStateShadow;
	std::shared_ptr<RasterizerState> m_RasterizerStateLine;

	std::shared_ptr<KeyframeAnimator> m_Animator;
	float m_AppTime, m_AppTimeDelta;
	glm::vec4 m_CameraModelPosition;
	glm::vec4 m_LightWorldDirection;
	glm::vec4 m_LightModelDirection;

	std::shared_ptr<GroupNode> m_Scene;

	std::shared_ptr<CameraNode> m_LightNode;
	
	std::shared_ptr<GeometryNode> m_Rec;
	std::shared_ptr<FieldEffect> m_RecEffect;
	std::shared_ptr<GeometryNode> m_LineX;
	std::shared_ptr<NormalEffect> m_LineXEffect;
	std::shared_ptr<GeometryNode> m_LineY;
	std::shared_ptr<NormalEffect> m_LineYEffect;
	std::shared_ptr<GeometryNode> m_LineZ;
	std::shared_ptr<NormalEffect> m_LineZEffect;
	std::shared_ptr<GeometryNode> m_ConeX;
	std::shared_ptr<NormalEffect> m_ConeXEffect;
	std::shared_ptr<GeometryNode> m_ConeY;
	std::shared_ptr<NormalEffect> m_ConeYEffect;
	std::shared_ptr<GeometryNode> m_ConeZ;
	std::shared_ptr<NormalEffect> m_ConeZEffect;
	std::shared_ptr<GeometryNode> m_LetterX;
	std::shared_ptr<NormalEffect> m_LetterXEffect;
	std::shared_ptr<GeometryNode> m_LetterY;
	std::shared_ptr<NormalEffect> m_LetterYEffect;
	std::shared_ptr<GeometryNode> m_LetterZ;
	std::shared_ptr<NormalEffect> m_LetterZEffect;

	std::shared_ptr<GeometryNode> m_Cylinder;
	std::shared_ptr<DirectionalLightingTextureWithShadowEffect> m_CylinderEffect;
	std::shared_ptr<ShadowMapEffect> m_CylinderShadowMapEffect;
	
	std::shared_ptr<GeometryNode> m_Spring;
	std::shared_ptr<DirectionalLightingTextureWithShadowEffect> m_SpringEffect;
	std::shared_ptr<ShadowMapEffect> m_SpringShadowMapEffect;

	std::shared_ptr<GeometryNode> m_VolumetricLine;
	std::shared_ptr<VolumetricLineEffect> m_VolumetricLineEffect;

	std::shared_ptr<GeometryNode> m_Particles;
	std::shared_ptr<ParticlesEffect> m_ParticlesEffect;

	std::shared_ptr<GeometryNode> m_Scale;
	std::shared_ptr<Texture2Effect> m_ScaleEffect;

	std::shared_ptr<DrawTarget> m_CylinderDrawTarget;
	std::shared_ptr<TextureDS> m_ShadowTexture;


	std::vector <std::shared_ptr<GeometryNode>> m_GVector;
	std::vector <std::shared_ptr<VolumetricLineEffect>> m_GEffectVector;
};