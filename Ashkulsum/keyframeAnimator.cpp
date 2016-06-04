#include "stdafx.h"
#include "keyframeAnimator.h"
#include "node.h"

KeyframeAnimator::~KeyframeAnimator()
{
}

KeyframeAnimator::KeyframeAnimator(int numCommonTimes, int numTranslations,
    int numRotations, int numScales, const Transformation& localTransform)
    :
    TransformAnimator(localTransform),
    m_NumCommonTimes(0),
    m_NumTranslations(0),
    m_NumRotations(0),
    m_NumScales(0),
    m_TLastIndex(0),
    m_RLastIndex(0),
    m_SLastIndex(0),
    m_CLastIndex(0)
{
    if (numCommonTimes > 0)
    {
        m_NumCommonTimes = numCommonTimes;
        m_CommonTimes.resize(m_NumCommonTimes);

        if (numTranslations > 0)
        {
            m_NumTranslations = numTranslations;
            m_TranslationTimes = m_CommonTimes;
            m_Translations.resize(m_NumTranslations);
        }

        if (numRotations > 0)
        {
            m_NumRotations = numRotations;
            m_RotationTimes = m_CommonTimes;
            m_Rotations.resize(m_NumRotations);
        }

        if (numScales > 0)
        {
            m_NumScales = numScales;
            m_ScaleTimes = m_CommonTimes;
            m_Scales.resize(m_NumScales);
        }
    }
    else
    {
        if (numTranslations > 0)
        {
            m_NumTranslations = numTranslations;
            m_TranslationTimes.resize(m_NumTranslations);
            m_Translations.resize(m_NumTranslations);
        }

        if (numRotations > 0)
        {
            m_NumRotations = numRotations;
            m_RotationTimes.resize(m_NumRotations);
            m_Rotations.resize(m_NumRotations);
        }

        if (numScales > 0)
        {
            m_NumScales = numScales;
            m_ScaleTimes.resize(m_NumScales);
            m_Scales.resize(m_NumScales);
        }
    }
}

bool KeyframeAnimator::Update(float appTime)
{
    if (!Animator::Update(appTime))
    {
        return false;
    }

    float ctrlTime = static_cast<float>(GetControlTime(appTime));
    float normTime = 0.0f;
    int i0 = 0, i1 = 0;
    glm::vec4 trn;
    glm::mat4 rot;
    float scale;

    // The logic here checks for equal-time arrays to minimize the number of
    // times GetKeyInfo is called.
    if (m_NumCommonTimes > 0)
    {
        GetKeyInfo(ctrlTime, m_NumCommonTimes, m_CommonTimes.data(), m_CLastIndex,
            normTime, i0, i1);

        if (m_NumTranslations > 0)
        {
            trn = GetTranslate(normTime, i0, i1);
			m_Transformation.SetTranslation(trn);
        }

        if (m_NumRotations > 0)
        {
            rot = GetRotate(normTime, i0, i1);
            m_Transformation.SetRotation(rot);
        }

        if (m_NumScales > 0)
        {
            scale = GetScale(normTime, i0, i1);
            m_Transformation.SetScale(glm::vec3 (scale));
        }
    }
    else
    {
        if (m_NumTranslations > 0)
        {
            GetKeyInfo(ctrlTime, m_NumTranslations, m_TranslationTimes.data(),
                m_TLastIndex, normTime, i0, i1);
            trn = GetTranslate(normTime, i0, i1);
            m_Transformation.SetTranslation(trn);
        }

        if (m_NumRotations > 0)
        {
            GetKeyInfo(ctrlTime, m_NumRotations, m_RotationTimes.data(), m_RLastIndex,
                normTime, i0, i1);
            rot = GetRotate(normTime, i0, i1);
            m_Transformation.SetRotation(rot);
        }

        if (m_NumScales > 0)
        {
            GetKeyInfo(ctrlTime, m_NumScales, m_ScaleTimes.data(), m_SLastIndex,
                normTime, i0, i1);
            scale = GetScale(normTime, i0, i1);
            m_Transformation.SetScale(glm::vec3 (scale));
        }
    }

    Node* node = static_cast<Node*>(m_Object);
    node->m_LocalT = m_Transformation;
    return true;
}

void KeyframeAnimator::GetKeyInfo(float ctrlTime, int numTimes, float* times,
    int& lastIndex, float& normTime, int& i0, int& i1)
{
    if (ctrlTime <= times[0])
    {
        normTime = 0.0f;
        lastIndex = 0;
        i0 = 0;
        i1 = 0;
        return;
    }

    if (ctrlTime >= times[numTimes - 1])
    {
        normTime = 0.0f;
        lastIndex = numTimes - 1;
        i0 = lastIndex;
        i1 = lastIndex;
        return;
    }

    int nextIndex;
    if (ctrlTime > times[lastIndex])
    {
        nextIndex = lastIndex + 1;
        while (ctrlTime >= times[nextIndex])
        {
            lastIndex = nextIndex;
            ++nextIndex;
        }

        i0 = lastIndex;
        i1 = nextIndex;
        normTime = (ctrlTime - times[i0]) / (times[i1] - times[i0]);
    }
    else if (ctrlTime < times[lastIndex])
    {
        nextIndex = lastIndex - 1;
        while (ctrlTime <= times[nextIndex])
        {
            lastIndex = nextIndex;
            --nextIndex;
        }

        i0 = nextIndex;
        i1 = lastIndex;
        normTime = (ctrlTime - times[i0]) / (times[i1] - times[i0]);
    }
    else
    {
        normTime = 0.0f;
        i0 = lastIndex;
        i1 = lastIndex;
    }
}

glm::vec4 KeyframeAnimator::GetTranslate(float normTime, int i0, int i1)
{
    glm::vec4 trn = m_Translations[i0] + normTime * (m_Translations[i1] - m_Translations[i0]);
    return trn;
}

glm::mat4 KeyframeAnimator::GetRotate(float normTime, int i0, int i1)
{
    float cosA = glm::dot(m_Rotations[i0], m_Rotations[i1]);
	
    float sign;
    if (cosA >= (float)0)
    {
        sign = (float)1;
    }
    else
    {
        cosA = -cosA;
        sign = (float)-1;
    }
	float f0, f1;
	if (cosA < (float)1)
    {
        // The angle A is in (0,pi/2].
        float A = acos(cosA);
        float invSinA = ((float)1) / sin(A);
        f0 = sin(((float)1 - normTime) * A) * invSinA;
        f1 = sin(normTime * A) * invSinA;
    }
    else
    {
        // The angle theta is 0.
        f0 = (float)1 - normTime;
        f1 = (float)normTime;
    }

	glm::quat Temp = m_Rotations[i0] * f0 + m_Rotations[i1] * (sign *f1);

	glm::mat4 rot = glm::mat4_cast (Temp);
    return rot;
}

float KeyframeAnimator::GetScale(float normTime, int i0, int i1)
{
    return m_Scales[i0] + normTime * (m_Scales[i1] - m_Scales[i0]);
}