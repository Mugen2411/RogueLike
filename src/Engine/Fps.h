//! @file MEFps.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_Fps__
#define __MugenEngine_Fps__

#include "Core.h"
#include <math.h>
#include <chrono>

namespace mugen_engine
{
    /**********************************************************************//**
        @class		MEFps
        @brief		読み込んだフォントで画面上に文字列描画を行うクラス
    *//***********************************************************************/
    class MEFps
    {
        std::chrono::system_clock::time_point start_time_;              //!< 測定開始時刻
        int count_;                                                     //!< カウンタ
        float fps_;                                                     //!< FPS
        static const int cnt_to_sample = 60;                            //!< 平均を取るサンプル数
        static const int ideal_fps_ = 60;                               //!< 設定したFPS
        mugen_engine::MEFontData defFont;                               //!< FPSを表示するフォント

    public:
        /**********************************************************************//**
            @brief			コンストラクタ
            @param			なし
            @return			なし
        *//***********************************************************************/
        MEFps()
        {
            start_time_ = std::chrono::system_clock::now();
            count_ = 0;
            fps_ = 0;
            defFont = mugen_engine::MECore::GetIns().GetFont("__mugen_engine_default__");
        }

        /**********************************************************************//**
            @brief			更新
            @param			なし
            @return			なし
        *//***********************************************************************/
        bool Update()
        {
            if(count_ == 0)
            {  // 1フレーム目なら時刻を記憶
                start_time_ = std::chrono::system_clock::now();
            }
            if(count_ == cnt_to_sample)
            {  // 60フレーム目なら平均を計算する
                auto t = std::chrono::system_clock::now();
                fps_ = 1000.f / (std::chrono::duration_cast<std::chrono::milliseconds>(t - start_time_).count() / (float)cnt_to_sample);
                count_ = 0;
                start_time_ = t;
            }
            count_++;
            return true;
        }

        /**********************************************************************//**
            @brief			描画
            @param			なし
            @return			なし
        *//***********************************************************************/
        void Draw()
        {
            static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
            defFont.DrawFormatString(0, mugen_engine::MECore::GetIns().GetWindowHeight() - 32, color, -9999.9f, L"fps: %.1f", fps_);
        }

        /**********************************************************************//**
            @brief			待機
            @param			なし
            @return			なし
        *//***********************************************************************/
        void Wait()
        {
            auto tookTime = std::chrono::system_clock::now() - start_time_;      //かかった時間
            long long waitTime = count_ * 1000 / ideal_fps_ - std::chrono::duration_cast<std::chrono::milliseconds>(tookTime).count();  //待つべき時間
            if(waitTime > 0)
            {
                Sleep(static_cast<DWORD>(waitTime));  //待機
            }
        }
    };
}

#endif//__MugenEngine_Fps__