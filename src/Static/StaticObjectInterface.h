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
		//! �ʒu�����擾
		virtual MRTransform& GetTransform() = 0;
		//! �`��
		virtual void Render(const MRCamera& camera) const = 0;
	};
}

#endif//__MagicaRogue_StaticObjectInterface__