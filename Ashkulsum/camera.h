#ifndef CAMERA_H
#define CAMERA_H

#include "include.h"
#include "maths.h"
//#include <glload\gl_3_3.h>
//#include <glload\gl_load.hpp>
//#include <glutil\glutil.h>
//#include <glm\gtc\matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <assert.h>

class Camera
{
public:
	~Camera ();
	Camera (bool isPerspective);

	//static float DegToRad(float fAngDeg);

	enum {
		DMIN = 0,  // near
        DMAX = 1,  // far
        UMIN = 2,  // bottom
        UMAX = 3,  // top
        RMIN = 4,  // left
        RMAX = 5  // right
	};

	void SetFrame (glm::vec4 const& position, glm::vec4 const& lookVector, glm::vec4 const& upVector);
	void SetFrame (glm::vec4 const& position, glm::vec4 const& lookVector, glm::vec4 const& upVector, glm::vec4 const& rightVector);
	void SetFrustum (float angle, float ratio, float zNear, float zFar);
	void SetFrustum (float dMin, float dMax, float uMin, float uMax, float rMin, float rMax);

	void SetPosition (glm::vec4 const& position);
	void SetLookVector (glm::vec4 const& lookVector);
	void SetUpVector (glm::vec4 const& upVector);
	void SetRightVector (glm::vec4 const& rightVector);

	void SetProjectionMatrix ();
	void SetViewMatrix ();

	glm::vec4 const& GetPosition () const;
	glm::vec4 const& GetLookVector () const;
	glm::vec4 const& GetUpVector () const;
	glm::vec4 const& GetRightVector () const;

	glm::mat4 const& GetProjectionMatrix () const;
	glm::mat4 const& GetViewMatrix () const;
	glm::mat4 const& GetProjectionViewMatrix () const;

	float GetDMax () const;
	float GetDMin () const;
	float GetUMax () const;
	float GetUMin () const;
	float GetRMax () const;
	float GetRMin () const;

	bool GetFrustum (float & fov, float & aspectRatio, float & dMin, float & dMax);

	void OnFrameChange ();
	void OnFrustumChange ();

	void UpdatePVMatrix ();

protected:
	bool m_IsPerspective;;

	glm::vec4 m_Position;
	glm::vec4 m_LookVector;
	glm::vec4 m_UpVector;
	glm::vec4 m_RightVector;

	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionViewMatrix;

	float m_Frustum[6];

};


/*
class Camera 
{
public:
	Camera () {};
	Camera (glm::vec3 cameraPosition, glm::vec3 lookDirection, glm::vec3 UpDirection);
	
	~Camera () {};

	float DegToRad(float fAngDeg);
	float CalcFrustumScale(float fFovDeg);

	glm::vec3 ResolveCamPosition();
	glm::mat4 CalcLookAtMatrix (const glm::vec3 &cameraPosition, const glm::vec3 &lookDirection, const glm::vec3 &uPDirection);
	glm::mat4 CalcProjectionMatrix(float fzNear, float fzFar, float angle);

	void SetCameraPosition (glm::vec3 cameraPosition);
	void SetLookDirection (glm::vec3 lookDirection);
	void SetUpDirection (glm::vec3 upDirection);
	void SetNearPlane (float nearPlane);
	void SetFarPlane (float farPlane);
	void SetAngle (float angle);

	glm::vec3 GetCameraPosition ();
	glm::vec3 GetLookDirection ();
	glm::vec3 GetUpDirection ();
	float GetNearPlane ();
	float GetFarPlane ();
	float GetAngle ();

private:
	glm::vec3 m_CameraPosition;
	glm::vec3 m_LookDirection;
	glm::vec3 m_UpDirection;

	float m_Near, m_Far, m_Angle;

};*/
#endif