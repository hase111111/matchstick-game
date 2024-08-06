//#include "SceneChangeEffect.h"
//#include "define.h"
//#include "DxLib.h"
//#include "Sound.h"
//
//SceneChangeEffect::SceneChangeEffect() : m_COLOR(GetColor(0x55, 0x55, 0x55))
//{
//    m_sound_fade_in = Sound::getIns()->myLoadSound("data/sound/fade_in.mp3");
//    m_sound_fade_out = Sound::getIns()->myLoadSound("data/sound/fade_out.mp3");
//}
//
//void SceneChangeEffect::init(const int _mode)
//{
//    m_counter = 0;	//カウンタの初期化
//    m_mode = _mode;	//モードを設定
//}
//
//bool SceneChangeEffect::update()
//{
//    ++m_counter;
//
//    //既にアニメーションが終了していたならfalseを返す
//    if (m_END_TIME < m_counter)return false;
//
//    //マイナスモードの時はfalseを返す
//    if (m_mode < 0) return false;
//
//    return true;
//}
//
//void SceneChangeEffect::draw() const
//{
//    int temp_y = 0;
//
//    switch (m_mode)
//    {
//        //フェードアウトのエフェクト
//        case 0:
//            //サウンドを鳴らす
//            if (m_counter == 1)PlaySoundMem(m_sound_fade_out, DX_PLAYTYPE_BACK);
//
//            //帯の描画
//            for (int i = 0; i < m_WIN_DIV; i++)
//            {
//                temp_y = Define::kWindowSizeY * (m_counter - m_END_TIME * i / m_WIN_DIV) / (m_END_TIME / m_WIN_DIV);
//                DrawBox(Define::kWindowSizeX / m_WIN_DIV * i, 0, Define::kWindowSizeX * (i + 1) / m_WIN_DIV, temp_y, m_COLOR, TRUE);
//            }
//
//            break;
//
//            //フェードインのエフェクト
//        case 1:
//            //サウンドを鳴らす
//            if (m_counter == 1)PlaySoundMem(m_sound_fade_in, DX_PLAYTYPE_BACK);
//
//            //帯の描画
//            for (int i = 0; i < m_WIN_DIV; i++)
//            {
//                temp_y = Define::kWindowSizeY * (m_counter - m_END_TIME * (m_WIN_DIV - 1 - i) / m_WIN_DIV) / (m_END_TIME / m_WIN_DIV);
//                DrawBox(Define::kWindowSizeX / m_WIN_DIV * (m_WIN_DIV - 1 - i), temp_y, Define::kWindowSizeX * (m_WIN_DIV - i) / m_WIN_DIV, Define::kWindowSizeY, m_COLOR, TRUE);
//            }
//
//            break;
//
//            //フェードアウト
//        case 2:
//            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * m_counter / m_END_TIME);
//            DrawBox(0, 0, Define::kWindowSizeX, Define::kWindowSizeY, GetColor(0, 0, 0), TRUE);
//            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//            break;
//
//            //フェードアウト
//        case 3:
//            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (m_END_TIME - m_counter) / m_END_TIME);
//            DrawBox(0, 0, Define::kWindowSizeX, Define::kWindowSizeY, GetColor(0, 0, 0), TRUE);
//            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//            break;
//
//        default:
//
//            break;
//    }
//
//}
