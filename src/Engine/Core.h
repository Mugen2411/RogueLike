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

#include "Audio/AudioDevice.h"

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
		/**********************************************************************//**
			@brief			インスタンスの取得
			@param			なし
			@return			インスタンス
		*//***********************************************************************/
		static MECore& GetIns()
		{
			static MECore instance;
			return instance;
		}

		/**********************************************************************//**
			@brief			初期化
			@param[in]		window_title		ウィンドウのタイトル
			@param[in]		window_width		ウィンドウ(描画範囲)の横幅
			@param[in]		window_height		ウィンドウ(描画範囲)の縦幅
			@return			インスタンス
		*//***********************************************************************/
		void Initialize(const std::wstring window_title, int window_width, int window_height);

		/**********************************************************************//**
			@brief			終了処理
			@param			なし
			@return			なし
		*//***********************************************************************/
		void Finalize();

		/**********************************************************************//**
			@brief			システムのメッセージを処理する
			@param			なし
			@return			何もなければ0、アプリケーションが終了するなら-1
		*//***********************************************************************/
		int ProcessMessage();

		/**********************************************************************//**
			@brief			描画結果を画面に反映する
			@param			なし
			@return			なし
		*//***********************************************************************/
		void ScreenFlip();

		/**********************************************************************//**
			@brief			画面を指定した色でクリアする
			@param[in]		R			赤の輝度
			@param[in]		G			緑の輝度
			@param[in]		B			青の輝度
			@return			なし
		*//***********************************************************************/
		void ClearScreen(const int R, const int G, const int B);

		/**********************************************************************//**
			@brief			描画可能な範囲を設定する
			@param[in]		topX		左上のX座標
			@param[in]		topY		左上のY座標
			@param[in]		bottomX		右下のX座標
			@param[in]		bottomY		右下のY座標
			@return			なし
		*//***********************************************************************/
		void SetRenderArea(const int topX, const int topY, const int bottomX, const int bottomY);

		/**********************************************************************//**
			@brief			描画可能な範囲を画面全体に設定する
			@param			なし
			@return			なし
		*//***********************************************************************/
		void ResetRenderArea();

		/**********************************************************************//**
			@brief			ファイルから画像を読み込む
			@param[in]		gid				取り出すキー
			@param[in]		filepath		画像ファイルへのパス
			@return			なし
		*//***********************************************************************/
		void LoadGraph(const std::string gid, const std::wstring filepath);

		/**********************************************************************//**
			@brief			ファイルから分割して画像を読み込む
			@param[in]		gid				取り出すキー
			@param[in]		filepath		画像ファイルへのパス
			@param[in]		xDivideNum		横方向の分割数
			@param[in]		yDivideNum		縦方向の分割数
			@return			なし
		*//***********************************************************************/
		void LoadDivGraph(const std::string gid, const std::wstring filepath, const size_t xDivideNum, const size_t yDivideNum);

		/**********************************************************************//**
			@brief			キーを指定して読み込み済み画像を取り出す
			@param[in]		gid				取り出すキー
			@return			読み込み済み画像
		*//***********************************************************************/
		MEImage& GetGraph(const std::string gid);

		/**********************************************************************//**
			@brief			フォントを読み込む
			@param[in]		gid				取り出すキー
			@param[in]		fontName		フォントの名前
			@param[in]		fontSize		フォントサイズ
			@return			なし
		*//***********************************************************************/
		void LoadFont(const std::string gid, const std::wstring fontName, const int fontSize);

		/**********************************************************************//**
			@brief			キーを指定して読み込みフォントを取り出す
			@param[in]		gid				取り出すキー
			@return			読み込み済みフォント
		*//***********************************************************************/
		MEFontData& GetFont(const std::string gid);

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
		/**********************************************************************//**
			@brief			コンストラクタ
			@param			なし
			@return			なし
		*//***********************************************************************/
		MECore();

		//! コピーコンストラクタ(削除)
		MECore(const MECore&) = delete;

		/**********************************************************************//**
			@brief			ウィンドウの作成
			@param			なし
			@return			なし
		*//***********************************************************************/
		void _CreateWindow();
		
		HWND m_windowHandle;											//!< ウィンドウハンドル
		std::wstring m_windowTitle;										//!< ウィンドウの名前(ウィンドウクラスの名前)
		WNDCLASSEX m_windowClass;										//!< ウィンドウクラス
		int m_windowWidth;												//!< ウィンドウの横幅
		int m_windowHeight;												//!< ウィンドウの高さ

		D3D12_INPUT_ELEMENT_DESC m_inputLayout[2];						//!< 入力レイアウト

		MEGraphicDevice m_graphicDevice;										//!< グラフィックデバイス
		MEGraphicCommandList m_commandList;								//!< グラフィックコマンドリスト
		MEGraphicRenderTarget m_renderTarget;							//!< レンダーターゲット
		MEGraphicPipeline m_pipeline;									//!< パイプライン

		MEAudioDevice m_audioDevice;									//!< オーディオデバイス

		std::unordered_map<std::string, MEImage> m_loadedImages;	//!< 読み込み済み画像を辞書で管理する
		std::unordered_map<std::string, MEFontData> m_loadedFonts;		//!< 読み込み済みのフォントを辞書で管理する
	};
}

#endif//__MugenEngine_Core__