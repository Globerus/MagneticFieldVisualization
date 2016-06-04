#ifndef FONT_ARIAL_W400_H16_BOLD_H
#define FONT_ARIAL_W400_H16_BOLD_H

#include "fontO.h"

class FontArialW400H16Bold : public Font
{
public:
	FontArialW400H16Bold (std::shared_ptr<ProgramFactory> const& programFactory, int maxMessageLength);

private:
	static int m_Width;
	static int m_Height;
	static unsigned char m_Texels[];
	static float m_CharacterData[];
	static float m_CharacterWidth[];
};
#endif