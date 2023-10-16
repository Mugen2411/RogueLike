//! @file Camera.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Camera__
#define __MagicaRogue_Camera__

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRCamera
		@brief		スクロール機能とカメラを扱うクラス
	*//***********************************************************************/
	class MRCamera
	{
	public:
		//! コンストラクタ
		MRCamera(const int x, const int y);
		//! カメラの左上座標を設定
		void SetAnchor(const int x, const int y);
		//! スクリーン座標のX要素を取得
		int GetAnchoredX(const int x) const;
		//! スクリーン座標のY要素を取得
		int GetAnchoredY(const int y) const;
	private:
		int m_anchorX;						//!< カメラ左上のX座標
		int m_anchorY;						//!< カメラ左上のY座標
	};
}

#endif//__MagicaRogue_Camera__