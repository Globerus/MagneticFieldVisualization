#include "stdafx.h"
#include "transformation.h"

Transformation::Transformation ()
{
	SetIdentity ();
}

void Transformation::SetIdentity ()
{
	m_InverseTMatrix = glm::mat4 (1.0f);
	m_TransformationMatrix = glm::mat4 (1.0f);
	m_Rotation = glm::mat4 (1.0f);
	m_Translation = glm::vec4 (0);
	m_Scale = glm::vec4 (1.0f);
	m_IsUniformScale = true;
}

glm::mat4 Transformation::QuatToMat4x4 (glm::fquat quaternion)
{
	float xx = quaternion.x * quaternion.x;
	float xy = quaternion.x * quaternion.y;
	float xz = quaternion.x * quaternion.z;
	float xw = quaternion.x * quaternion.w;

	float yy = quaternion.y * quaternion.y;
	float yz = quaternion.y * quaternion.z;
	float yw = quaternion.y * quaternion.w;

	float zz = quaternion.z * quaternion.z;
	float zw = quaternion.z * quaternion.w;

	glm::mat4 mat (1.0f);

	mat[0].x = 1 - 2 * (yy + zz);
	mat[0].y = 2 * (xy - zw);
	mat[0].z = 2 * (xz + yw);

	mat[1].x = 2 * (xy + zw);
	mat[1].y = 1 - 2* (xx + zz);
	mat[1].z = 2 * (yz - xw);

	mat[2].x = 2 * (xz - yw);
	mat[2].y = 2 * (yz + xw);
	mat[2].z = 1 - 2 * (xx + yy);
	
	return mat;
}

glm::mat4 Transformation::CalcRotationMatrix (const glm::vec3 axis, const float angle)
{
	glm::mat4 mat (1.0f);

	float sinTheta = -sin (angle * (3.14159f * 2.0f / 360.0f));
	float cosTheta = cos (angle * (3.14159f * 2.0f / 360.0f));

	float t = 1 - cosTheta;

	glm::vec3 norm = glm::normalize (axis);
	mat[0].x = t * norm.x * norm.x + cosTheta;
	mat[0].y = t * norm.x * norm.y - sinTheta * norm.z;
	mat[0].z = t * norm.x * norm.z + sinTheta * norm.y;

	mat[1].x = t * norm.x * norm.y + sinTheta * norm.z;
	mat[1].y = t * norm.y * norm.y + cosTheta;
	mat[1].z = t * norm.y * norm.z - sinTheta * norm.x;

	mat[2].x = t * norm.x * norm.z - sinTheta * norm.y;
	mat[2].y = t * norm.y * norm.z + sinTheta * norm.x;
	mat[2].z = t * norm.z * norm.z + cosTheta;
	
	return mat;
}

void Transformation::SetRotation (const glm::vec3 axis, const float rotation)
{
	m_Rotation =  CalcRotationMatrix (axis, rotation);
	UpdateMatrix ();
	UpdateInverseMatrix ();
}

void Transformation::SetRotation (const glm::mat4 rotation)
{
	m_Rotation = rotation;
	UpdateMatrix ();
	UpdateInverseMatrix ();
}

void Transformation::SetMatrix(glm::mat4 const& matrix)
{
    m_Rotation = matrix;
	m_IsUniformScale = false;
    UpdateMatrix();
}

void Transformation::SetTranslation (const glm::vec3 translation)
{
	m_Translation = glm::vec4 (translation, 1.0f);
	UpdateMatrix ();
	UpdateInverseMatrix ();
}

void Transformation::SetTranslation (const glm::vec4 translation)
{
	SetTranslation (glm::vec3(translation));
}

void Transformation::SetUniformScale (float scale)
{
	m_Scale = glm::vec4(scale);
	m_IsUniformScale = true;
	UpdateMatrix ();
	UpdateInverseMatrix ();
}

void Transformation::SetScale (const glm::vec3 scale)
{
	m_Scale = glm::vec4 (scale, 1.0f);
	m_IsUniformScale = false;
	UpdateMatrix ();
	UpdateInverseMatrix ();
}

void Transformation::SetTransformationMatrix (glm::mat4 tMatrix)
{
	m_TransformationMatrix = tMatrix;
}

bool Transformation::IsUniformScale () const
{
	return m_IsUniformScale;
}

void Transformation::UpdateMatrix ()
{
	m_TransformationMatrix[0] = m_Rotation[0] * m_Scale.x;
	m_TransformationMatrix[1] = m_Rotation[1] * m_Scale.y;
	m_TransformationMatrix[2] = m_Rotation[2] * m_Scale.z;
	
	m_TransformationMatrix[3].x = m_Translation.x;
	m_TransformationMatrix[3].y = m_Translation.y;
	m_TransformationMatrix[3].z = m_Translation.z;
}

void Transformation::UpdateInverseMatrix ()
{
	m_InverseTMatrix = glm::inverse (m_TransformationMatrix);
}


Transformation operator* (Transformation const& A, Transformation const& B) 
{
	Transformation newTransformation;
	if (A.IsUniformScale ())
	{
		newTransformation.SetRotation (A.GetRotation () * B.GetRotation ());
		newTransformation.SetTranslation (A.GetUniformScale () * (A.GetRotation () * B.GetTranslationW0 ()) + A.GetTranslationW1 ());
		
		if (B.IsUniformScale ())
		{
			newTransformation.SetUniformScale (A.GetUniformScale () * B.GetUniformScale ());
		}
		else
		{
			newTransformation.SetScale (A.GetUniformScale () * B.GetScale ());
		}

		return newTransformation;
	}

	glm::mat4 matA;

	matA = MultiplyMatByVec (A.GetRotation (), A.GetScaleW1 ());

	glm::mat4 matB;

	matB = MultiplyMatByVec (B.GetRotation (), B.GetScaleW1 ());

	newTransformation.SetMatrix (matA * matB);

	newTransformation.SetTranslation (matA * B.GetTranslationW0 () + A.GetTranslationW1 ());
	
	return newTransformation;
}
/*
Transformation Transformation::operator* (Transformation const& transformation) 
{
	Transformation newTransformation;
	//newTransformation.m_Rotation = m_Rotation * transformation.m_Rotation;
	//newTransformation.SetRotation (GetRotation () * transformation.GetRotation ());
	//newTransformation.SetTranslation (glm::vec4 (GetScale (), 1.0f) * ( GetRotation () * glm::vec4(transformation.GetTranslation (), 0.0f)) + glm::vec4(GetTranslation (), 1.0f));

	//mat = glm::vec4 (transformation.GetScale (),1.0f) *transformation.GetRotation ();
	newTransformation.m_Scale = m_Scale *  transformation.m_Scale;
	//newTransformation.m_Translation = m_Translation + transformation.m_Translation;
	newTransformation.UpdateMatrix ();
	newTransformation.UpdateInverseMatrix ();
	return newTransformation;
}*/
Transformation Transformation::operator= (Transformation const& transformation)
{
	m_Rotation = transformation.m_Rotation;
	m_Translation = transformation.m_Translation;
	m_Scale = transformation.m_Scale;
	m_TransformationMatrix = transformation.m_TransformationMatrix;
	m_InverseTMatrix = transformation.m_InverseTMatrix;

	return *this;
}