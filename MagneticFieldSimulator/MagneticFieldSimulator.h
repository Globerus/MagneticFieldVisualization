#include "window.h"
#include "pvwUpdater.h"
#include "load.h"
#include <boost/thread.hpp>
//#include <boost/thread/scoped_thread.hpp>
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
#include "magneticFieldEffect.h"
#include "shadowMapEffect.h"
#include "textEffect.h"
#include "fontArialW400H16.h"
#include "fontArialW400H16Bold.h"
#include "interpolationSimulator.h"


class InterpolationSimulation : public Window
{
public:
	InterpolationSimulation (std::string title, int xOrigin, int yOrigin, int xSize, int ySize);
	~InterpolationSimulation ();

	struct FieldParametrization
	{
		float m_WorldWidth;
		float m_WorldHeight;
		float m_WorldDepth;

		int m_WidthResolution;
		int m_HeightResolution;
		int m_DepthResolution;
	};

	
	void InitializeInterpolation ();
	void InterpolatePoints ();
	void InitializeCameraNode ();
	void InitializeLightNode ();

	void MouseMove(int x, int y);
	void MouseButton(int button, int state, int x, int y);
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void SpecialKeyboard(int key, int x, int y);
	void SpecialKeyboardUp(int key, int x, int y);
	void Reshape (int w, int h);
	
	void CreateLoadingScreen ();

	void ParametrizeField ();
	void ParametrizeFieldXAxisMovementAnimation ();
	void ParametrizeFieldZAxisMovementAnimation ();
	void ParametrizeFieldXAxisCorrectionMovementAnimation ();
	void ParametrizeFieldZAxisCorrectionMovementAnimation ();

	void UpdateFieldVisualization ();
	void UpdateFieldScreenXAxis ();
	void UpdateFieldScreenZAxis ();
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
	static void KeyboardUpCallback (unsigned char key, int x, int y);
	static void SpecialKeyboardCallback (int key, int x, int y);
	static void SpecialKeyboardUpCallback (int key, int x, int y);
	static void ReshapeCallback (int w, int h);

	void SetCurrentInstance ();

private:
	static InterpolationSimulation* currentInstance;
	
	unsigned char m_KeyStates[255];
	float m_XAccel, m_ZAccel;
	bool m_XCorrection, m_ZCorrection, m_SolenoidVisible;

	std::shared_ptr<InterpolationSimulator> m_Interpolator;

	float m_AppTime, m_AppTimeDelta;

	FieldParametrization m_FieldParam;

	boost::thread m_ParallelThread;

	PVWUpdater m_ShadowPVWUpdater;

	std::shared_ptr<BlendState> m_BlendState;
	std::shared_ptr<BlendState> m_BlendStateLine;

	std::shared_ptr<DepthStencilState> m_DepthStencilStateLine;

	std::shared_ptr<RasterizerState> m_RasterizerStateShadow;
	std::shared_ptr<RasterizerState> m_RasterizerStateLine;

	glm::vec4 m_CameraModelPosition;
	glm::vec4 m_LightWorldDirection;
	glm::vec4 m_LightModelDirection;

	std::shared_ptr<GroupNode> m_Scene;

	std::shared_ptr<CameraNode> m_LightNode;
	
	std::shared_ptr<Texture2> m_ColorScaleTexture;

	std::shared_ptr<GeometryNode> m_LoadingScreen;
	std::shared_ptr<Texture2Effect> m_LoadingScreenEffect;

	std::shared_ptr<GeometryNode> m_FieldScreenXAxis;
	std::shared_ptr<MagneticFieldEffect> m_FieldScreenXAxisEffect;
	std::shared_ptr<KeyframeAnimator> m_FieldMovementXAxisAnimation;

	std::shared_ptr<GeometryNode> m_FieldScreenZAxis;
	std::shared_ptr<MagneticFieldEffect> m_FieldScreenZAxisEffect;
	std::shared_ptr<KeyframeAnimator> m_FieldMovementZAxisAnimation;

	std::shared_ptr<GeometryNode> m_Cube;
	std::shared_ptr<DirectionalLightingTextureWithShadowEffect> m_CubeEffect;
	std::shared_ptr<ShadowMapEffect> m_CubeShadowMapEffect;

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


	std::shared_ptr<GeometryNode> m_Scale;
	std::shared_ptr<Texture2Effect> m_ScaleEffect;

	std::shared_ptr<DrawTarget> m_CylinderDrawTarget;
	std::shared_ptr<TextureDS> m_ShadowTexture;


	std::vector <std::shared_ptr<GeometryNode>> m_GVector;
	std::vector <std::shared_ptr<VolumetricLineEffect>> m_GEffectVector;
};