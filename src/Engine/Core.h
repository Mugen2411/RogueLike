//! @file Core.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_Core__
#define __MugenEngine_Core__

#include "Graphic/GraphicDevice.h"
#include "Graphic/GraphicCommandList.h"
#include "Graphic/GraphicRenderTarget.h"
#include "Graphic/GraphicPipeline.h"
#include "Graphic/GraphicGpuResourceManager.h"
#include "Graphic/GraphicLoadedImage.h"
#include "Graphic/GraphicFontData.h"

#include <DirectXMath.h>
#include <unordered_map>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MECore
		@brief		メディアサポートエンジンの中核となるクラス
	*//***********************************************************************/
	class MECore
	{
	public:
		//! インスタンスの取得
		static MECore& GetIns();
		//! 最初に必ず呼び出す初期化処理
		void Initialize(const std::wstring window_title, int window_width, int window_height);
		//! 最後に必ず呼び出す終了処理
		void Finalize();
		//! システムのメッセージを処理する
		int ProcessMessage();
		//! 描画結果を画面に反映させる
		void ScreenFlip();
		//! 画面を指定した色で初期化する
		void ClearScreen(const int R, const int G, const int B);
		//! 描画可能な範囲を設定する
		void SetRenderArea(const int topX, const int topY, const int bottomX, const int bottomY);
		//! 描画可能な範囲を画面全体に設定する
		void ResetRenderArea();
		//! 画像をファイルから読み込む
		void LoadGraph(std::string gid, std::wstring filepath);
		//! 画像をファイルから分割して読み込む
		void LoadDivGraph(std::string gid, std::wstring filepath, size_t xDivideNum, size_t yDivideNum);
		//! 読み込み済み画像を取得する
		MEGraphicLoadedImage& GetGraph(std::string gid);
		//! フォントを読み込む
		void LoadFont(std::string gid, std::wstring fontName, int fontSize);
		//! 読み込み済みフォントを取得する
		MEGraphicFontData& GetFont(std::string gid);
		//! 画面の横幅を取得
		int GetWindowWidth() const
		{
			return m_windowWidth;
		}
		//! 画面の高さを取得
		int GetWindowHeight() const
		{
			return m_windowHeight;
		}

	private:
		//! デフォルトコンストラクタ
		MECore();
		//! コピーコンストラクタ(削除)
		MECore(const MECore&) = delete;

		//! ウィンドウの作成
		void _CreateWindow();
		
		HWND m_windowHandle;											//!< ウィンドウハンドル
		std::wstring m_windowTitle;										//!< ウィンドウの名前(ウィンドウクラスの名前)
		WNDCLASSEX m_windowClass;										//!< ウィンドウクラス
		int m_windowWidth;												//!< ウィンドウの横幅
		int m_windowHeight;												//!< ウィンドウの高さ

		D3D12_INPUT_ELEMENT_DESC m_inputLayout[2];						//!< 入力レイアウト

		MEGraphicDevice m_device;										//!< グラフィックデバイス
		MEGraphicCommandList m_commandList;								//!< グラフィックコマンドリスト
		MEGraphicRenderTarget m_renderTarget;							//!< レンダーターゲット
		MEGraphicPipeline m_pipeline;									//!< パイプライン
		MEGraphicGpuResourceManager m_resourceManager;					//!< GPUリソースマネージャー

		std::unordered_map<std::string, MEGraphicLoadedImage> m_loadedImages;	//!< 読み込み済み画像を辞書で管理する
		std::unordered_map<std::string, MEGraphicFontData> m_loadedFonts;		//!< 読み込み済みのフォントを辞書で管理する
	};
}

#endif//__MugenEngine_Core__