//#include "ResultKey.h"
//#include "Keyboard.h"
//#include "DxLib.h"
//#include "Sound.h"
//
//ResultKey::ResultKey()
//{
//    //サウンドハンドルをロードする
//    m_sound_select = Sound::getIns()->myLoadSound("data/sound/selecting.mp3");
//}
//
//void ResultKey::init(const bool _mod, const bool _self)
//{
//    m_mod_rule = _mod;
//    m_self_harm = _self;
//}
//
//bool ResultKey::update(const std::vector<MatchField>& _field, int& _select, bool& _replay, bool& _replay_fail)
//{
//    //上下きーを押したときの処理
//    if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1)
//    {
//        _select--;
//        if (_select < 0) { _select = 0; }
//        else { PlaySoundMem(m_sound_select, DX_PLAYTYPE_BACK); }
//    }
//    else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1)
//    {
//        _select++;
//        if (_select >= _field.size()) { _select = (int)_field.size() - 1; }
//        else { PlaySoundMem(m_sound_select, DX_PLAYTYPE_BACK); }
//    }
//
//    //ESCキーで戻る処理
//    if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1)
//    {
//        return false;
//    }
//
//    //Zきーで保存する処理
//    if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1 && _replay == false)
//    {
//        PlaySoundMem(m_sound_select, DX_PLAYTYPE_BACK);
//
//        if (VariousFunctionsForMatchGame::outputFieldList(_field, m_mod_rule, m_self_harm) == false)
//        {
//            _replay_fail = true;
//        }
//
//        //保存済みフラグを立てる
//        _replay = true;
//    }
//
//    return true;
//}
