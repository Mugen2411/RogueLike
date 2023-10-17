//! @file StaticObjectManager.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_StaticObjectManager__
#define __MagicaRogue_StaticObjectManager__

#include "StaticObjectInterface.h"
#include "../Util/Camera.h"
#include <list>
#include <vector>
#include <memory>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRStaticObjectManager
		@brief		�Î~�I�u�W�F�N�g���Ǘ�����N���X
	*//***********************************************************************/
	class MRStaticObjectManager
	{
	public:
		//! �R���X�g���N�^
		MRStaticObjectManager();
		//! �Ǘ��Ώۂɒǉ�����
		void Register(std::unique_ptr<MRStaticObjectInterface>&& obj);
		//! ���̂̈ʒu����vector�Ŏ擾
		void GetTransforms(std::vector<MRTransform>& list);
		//! �`��
		void Render(const MRCamera& camera) const;
	private:
		std::list<std::unique_ptr<MRStaticObjectInterface>> m_objectList;			//!< �I�u�W�F�N�g�̃��X�g
	};
}

#endif//__MagicaRogue_StaticObjectManager__