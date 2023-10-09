//! @file GraphicFontData.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicFontData__
#define __MugenEngine_GraphicFontData__

#include "GraphicCharacterRenderUnit.h"

#include <unordered_map>

namespace mugen_engine
{
	class MEGraphicFontData
	{
	public:
	private:
		std::unordered_map<wchar_t, MEGraphicCharacterUnit> loadedCharacters;
	};
}

#endif//__MugenEngine_GraphicFontData__