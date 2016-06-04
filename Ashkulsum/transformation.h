#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "boost\shared_ptr.hpp"
#include "boost\make_shared.hpp"
#include "glm\gtx\transform.hpp"
#include "glm\gtc\quaternion.hpp"

class Transformation
{
public:

	Transformation ();


	~Transformation () {};

	inline operator glm::mat4 const&() const;

	void SetIdentity ();

	template <typename M, typename V>
	M MultiplyMatByVec (M const& mat, V const& vec);

	static glm::mat4 CalcRotationMatrix (const glm::vec3 axis, const float angle);
	glm::mat4 QuatToMat4x4 (glm::fquat quaternion);

	void SetRotation (const glm::mat4 rotation);
	void SetRotation (const glm::vec3 axis, const float rotation);
	void SetMatrix(glm::mat4 const& matrix);

	inline const glm::mat4 GetRotation () const;

	void SetTranslation (const glm::vec3 translation);
	void SetTranslation (const glm::vec4 translation);
	inline const glm::vec3 GetTranslation () const;
	inline const glm::vec4 GetTranslationW0 () const;
	inline const glm::vec4 GetTranslationW1 () const;

	void SetUniformScale (float scale);
	void SetScale (const glm::vec3 scale);
	inline const glm::vec3 GetScale () const;
	inline const glm::vec4 GetScaleW1 () const;
	inline const float GetUniformScale () const;

	void SetTransformationMatrix (glm::mat4 tMatrix);
	inline glm::mat4 const& GetTransformationMatrix () const;
	inline glm::mat4 const& GetInverseTMatrix () const;

	bool IsUniformScale () const;
	
	Transformation operator= (Transformation const& transformation);

private:
	void UpdateMatrix();
	void UpdateInverseMatrix ();

	bool m_IsUniformScale;
	glm::mat4 m_TransformationMatrix, m_InverseTMatrix;
	glm::mat4 m_Rotation;
	glm::vec4 m_Translation;
	glm::vec4 m_Scale;
};

inline Transformation::operator glm::mat4 const&() const
{
    return GetTransformationMatrix ();
}


template <typename M, typename  V>
M MultiplyMatByVec (M const& mat, V const& vec)
{
	M result;
	for (unsigned int i = 0; i < mat.row_size(); i++)
		for (unsigned int j =0; j < mat.col_size(); j++)
		{
			result[i][j] = mat[i][j] * vec [j];
		}

	return result;
}


inline const glm::mat4 Transformation::GetRotation () const
{
	return m_Rotation;
}

inline const glm::vec3 Transformation::GetTranslation () const
{
	return glm::vec3 (m_Translation);
}

inline const glm::vec4 Transformation::GetTranslationW0 () const
{
	return glm::vec4(m_Translation.x, m_Translation.y, m_Translation.z, 0.0f);
}

inline const glm::vec4 Transformation::GetTranslationW1 () const
{
	return glm::vec4(m_Translation.x, m_Translation.y, m_Translation.z, 1.0f);
}

inline const glm::vec3 Transformation::GetScale () const
{
	return glm::vec3 (m_Scale.x, m_Scale.y, m_Scale.z);
}

inline const glm::vec4 Transformation::GetScaleW1 () const
{
	return m_Scale;
}

inline const float Transformation::GetUniformScale () const
{
	return m_Scale.x;
}

inline glm::mat4 const& Transformation::GetTransformationMatrix () const
{
	return m_TransformationMatrix;
}

inline glm::mat4 const& Transformation::GetInverseTMatrix () const
{
	return m_InverseTMatrix;
}

Transformation operator* (Transformation const& A, Transformation const& B);
#endif