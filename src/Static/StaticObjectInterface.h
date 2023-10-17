//! @file StaticObjectInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_StaticObjectInterface__
#define __MagicaRogue_StaticObjectInterface__

#include "../Util/Camera.h"
#include "../Util/Transform.h"

namespace magica_rogue
{
	class MRStaticObjectInterface
	{
	public:
		//! ˆÊ’uî•ñ‚ğæ“¾
		virtual MRTransform& GetTransform() = 0;
		//! •`‰æ
		virtual void Render(const MRCamera& camera) const = 0;
	};
}

#endif//__MagicaRogue_StaticObjectInterface__