//! @file Fps.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_Fps__
#define __MugenEngine_Fps__

#include "Core.h"
#include <math.h>
#include <chrono>

namespace mugen_engine
{
    class Fps
    {
        std::chrono::system_clock::time_point start_time_;             //����J�n����
        int count_;                 //�J�E���^
        float fps_;                 // fps_
        static const int cnt_to_sample = 60;    //���ς����T���v����
        static const int ideal_fps_ = 120;  //�ݒ肵��FPS
        mugen_engine::MEGraphicFontData defFont;

    public:
        Fps()
        {
            start_time_ = std::chrono::system_clock::now();
            count_ = 0;
            fps_ = 0;
            defFont = mugen_engine::MECore::GetIns().GetFont("__mugen_engine_default__");
        }

        bool Update()
        {
            if(count_ == 0)
            {  // 1�t���[���ڂȂ玞�����L��
                start_time_ = std::chrono::system_clock::now();
            }
            if(count_ == cnt_to_sample)
            {  // 60�t���[���ڂȂ畽�ς��v�Z����
                auto t = std::chrono::system_clock::now();
                fps_ = 1000.f / (std::chrono::duration_cast<std::chrono::milliseconds>(t - start_time_).count() / (float)cnt_to_sample);
                count_ = 0;
                start_time_ = t;
            }
            count_++;
            return true;
        }

        void Draw()
        {
            static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
            defFont.DrawFormatString(0, mugen_engine::MECore::GetIns().GetWindowHeight() - 32, color, L"fps: %.1f", fps_);
        }

        void Wait()
        {
            auto tookTime = std::chrono::system_clock::now() - start_time_;      //������������
            long long waitTime = count_ * 1000 / ideal_fps_ - std::chrono::duration_cast<std::chrono::milliseconds>(tookTime).count();  //�҂ׂ�����
            if(waitTime > 0)
            {
                Sleep(static_cast<DWORD>(waitTime));  //�ҋ@
            }
        }
    };
}

#endif//__MugenEngine_Fps__