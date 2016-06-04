#ifndef KEYFRAME_ANIMATOR_H
#define KEYFRAME_ANIMATOR_H

#include "transformAnimator.h"

class KeyframeAnimator : public TransformAnimator
{
public:
	virtual ~KeyframeAnimator ();

	KeyframeAnimator (int numCommonTimes, int numTranslations,
        int numRotations, int numScales, Transformation const& localTransform);

	inline int GetNumCommonTimes() const;
    inline float* GetCommonTimes();

	inline void SetNumTranslations(int numTranslations);
	inline void SetTranslationTimes (std::vector<float> translationTimes);
	inline void SetTranslations (std::vector<glm::vec4> translations);

	inline void SetNumRotations(int numRotations);
	inline void SetRotationTimes (std::vector<float> rotationTimes);
	inline void SetRotations (std::vector<glm::quat> rotations);

	inline void SetNumScales(int numScales);
	inline void SetScaleTimes (std::vector<float> scaleTimes);
	inline void SetScales (std::vector<float> scales);

    inline int GetNumTranslations() const;
    inline float* GetTranslationTimes();
    inline glm::vec4* GetTranslations();

    inline int GetNumRotations() const;
    inline float* GetRotationTimes();
	inline glm::quat* GetRotations();

    inline int GetNumScales() const;
    inline float* GetScaleTimes();
    inline float* GetScales();

	virtual bool Update(float applicationTime);

protected:
	static void GetKeyInfo(float ctrlTime, int numTimes, float* times,
        int& lastIndex, float& normTime, int& i0, int& i1);

    glm::vec4 GetTranslate(float normTime, int i0, int i1);
    glm::mat4 GetRotate(float normTime, int i0, int i1);
    float GetScale(float normTime, int i0, int i1);

    int m_NumCommonTimes;
    std::vector<float> m_CommonTimes;

    int m_NumTranslations;
    std::vector<float> m_TranslationTimes;
    std::vector<glm::vec4> m_Translations;

    int m_NumRotations;
    std::vector<float> m_RotationTimes;
    std::vector<glm::quat> m_Rotations;

    int m_NumScales;
    std::vector<float> m_ScaleTimes;
    std::vector<float> m_Scales;

    int m_TLastIndex, m_RLastIndex, m_SLastIndex, m_CLastIndex;
};

inline int KeyframeAnimator::GetNumCommonTimes() const
{
    return m_NumCommonTimes;
}

inline float* KeyframeAnimator::GetCommonTimes()
{
    return m_CommonTimes.data();
}

inline int KeyframeAnimator::GetNumTranslations() const
{
    return m_NumTranslations;
}

inline float* KeyframeAnimator::GetTranslationTimes()
{
    return m_TranslationTimes.data();
}

inline glm::vec4* KeyframeAnimator::GetTranslations()
{
    return m_Translations.data();
}

inline int KeyframeAnimator::GetNumRotations() const
{
    return m_NumRotations;
}

inline float* KeyframeAnimator::GetRotationTimes()
{
    return m_RotationTimes.data();
}

inline glm::quat* KeyframeAnimator::GetRotations()
{
    return m_Rotations.data();
}

inline int KeyframeAnimator::GetNumScales() const
{
    return m_NumScales;
}

inline float* KeyframeAnimator::GetScaleTimes()
{
    return m_ScaleTimes.data();
}

inline float* KeyframeAnimator::GetScales()
{
    return m_Scales.data();
}

inline void KeyframeAnimator::SetNumTranslations(int numTranslations) 
{
    m_NumTranslations = numTranslations;
}

inline void KeyframeAnimator::SetTranslationTimes(std::vector<float> translationTimes)
{
    m_TranslationTimes = translationTimes;
}

inline void KeyframeAnimator::SetTranslations(std::vector<glm::vec4> translations)
{
    m_Translations = translations;
}

inline void KeyframeAnimator::SetNumRotations(int numRotations) 
{
    m_NumRotations = numRotations;
}

inline void KeyframeAnimator::SetRotationTimes(std::vector<float> rotationTimes)
{
    m_RotationTimes = rotationTimes;
}

inline void KeyframeAnimator::SetRotations(std::vector<glm::quat> rotations)
{
    m_Rotations = rotations;
}


inline void KeyframeAnimator::SetNumScales(int numScales) 
{
    m_NumScales = numScales;
}

inline void KeyframeAnimator::SetScaleTimes(std::vector<float> scaleTimes)
{
    m_ScaleTimes = scaleTimes;
}

inline void KeyframeAnimator::SetScales(std::vector<float> scales)
{
    m_Scales = scales;
}

#endif