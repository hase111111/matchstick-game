//#include"MatchGameCommon.h"
//#include <algorithm>
//#include "DxLib.h"
//
//namespace MG = VariousFunctionsForMatchGame;
//
//bool VariousFunctionsForMatchGame::matchGameCOM(const int _level, const MatchField& _field, MatchField& _result, const bool _self_harm, const bool _mod_rule)
//{
//    //定義する
//    const int RAND_KAKURITU = 35;   //HARD - ここに代入した数値%でランダムに行動する
//
//    switch (_level) 
//    {
//    case 0://EASY
//
//        //MODルールありの時
//        if (_mod_rule == true)
//        {
//            //盤面を生成する
//            if (matchGameCOM_EasyForMod(_field, _result, _self_harm) == true) {
//                return true;
//            }
//        }
//        //MODルールなしの時
//        else
//        {
//            //盤面を生成する
//            if (matchGameCOM_Easy(_field, _result, _self_harm) == true) {
//                return true;
//            }
//        }
//        break;
//
//    case 1://NORMAL
//
//        //ランダムな盤面を出力する
//        if (matchGameCOM_Rand(_field, _result, _self_harm, _mod_rule) == true) {
//            return true;
//        }
//        break;
//
//    case 2://HARD
//
//        //ランダムな盤面出力
//        if (GetRand((100 / RAND_KAKURITU) + 1) == 0) {
//            if (matchGameCOM_Rand(_field, _result, _self_harm, _mod_rule) == true) {
//                return true;
//            }
//        }
//        //ガチ盤面出力
//        else {
//            //MODルールありの時
//            if (_mod_rule == true)
//            {
//                //盤面を生成する
//                if (matchGameCOM_HardForMod(_field, _result, _self_harm) == true) {
//                    return true;
//                }
//            }
//            //MODルールなしの時
//            else
//            {
//                //盤面を生成する
//                if (matchGameCOM_Hard(_field, _result, _self_harm) == true) {
//                    return true;
//                }
//            }
//        }
//
//        break;
//
//    default://Impossible
//
//        //MODルールありの時
//        if (_mod_rule == true)
//        {
//            //盤面を生成する
//            if (matchGameCOM_HardForMod(_field, _result, _self_harm) == true) {
//                return true;
//            }
//        }
//        //MODルールなしの時
//        else
//        {
//            //盤面を生成する
//            if (matchGameCOM_Hard(_field, _result, _self_harm) == true) {
//                return true;
//            }
//        }
//
//        break;
//    }
//
//    return false;
//}
//
//bool VariousFunctionsForMatchGame::matchGameCOM_Easy(const MatchField& _field, MatchField& _result, bool _self_harm)
//{
//    //次盤面を生成する
//    std::vector<MatchField> _list;
//    makeNextFieldList(_list, _field, false, _self_harm);
//
//    //生成可能な盤面がないのならばFalseを返して終了
//    if (_list.size() == 0) { return false; }
//
//    //生成した盤面を採点し、マイナスしたものをリストに追加
//    std::vector<int> _point;
//    for (int i = 0; i < _list.size(); i++)
//    {
//        _point.push_back(evaluationFunction(_list.at(i), !_field.turn, _self_harm, 0));
//    }
//
//    //一番良い盤面を選択
//    int MAX = -10000;
//    int which = 0;
//    for (size_t c = 0; c < _point.size(); c++)
//    {
//        if (_point.at(c) > MAX)
//        {
//            MAX = _point.at(c);
//            which = (int)c;
//        }
//    }
//
//    //盤面を記録
//    _result = _list.at(which);
//
//    return true;
//}
//
//bool VariousFunctionsForMatchGame::matchGameCOM_EasyForMod(const MatchField& _field, MatchField& _result, bool _self_harm)
//{
//    //次盤面を生成する
//    std::vector<MatchField> _list;
//    makeNextFieldList(_list, _field, true, _self_harm);
//
//    //生成可能な盤面がないのならばFalseを返して終了
//    if (_list.size() == 0) { return false; }
//
//    //生成した盤面を採点する
//    std::vector<int> _point;
//    for (int i = 0; i < _list.size(); i++)
//    {
//        _point.push_back(evaluationFunctionForMod(_list.at(i), !_field.turn, _self_harm, 0));
//    }
//
//    //一番良い盤面を選択
//    int MAX = -10000;
//    for (size_t c = 0; c < _point.size(); c++)
//    {
//        if (_point.at(c) > MAX)
//        {
//            MAX = _point.at(c);
//        }
//    }
//
//    //良い盤面からランダムに選択
//    std::vector<MatchField> _rand;
//
//    for (size_t c = 0; c < _point.size(); c++)
//    {
//        if (_point.at(c) == MAX) {
//            _rand.push_back(_list.at(c));
//        }
//    }
//
//    //ランダム
//    int ans = GetRand((int)_rand.size() - 1);
//
//    //盤面を記録
//    _result = _rand.at(ans);
//
//    return true;
//}
//
//bool VariousFunctionsForMatchGame::matchGameCOM_Rand(const MatchField& _field, MatchField& _result, bool _self_harm, const bool _mod_rule)
//{
//    //次盤面を生成する
//    std::vector<MatchField> _list;
//    makeNextFieldList(_list, _field, _mod_rule, _self_harm);
//
//    //生成可能な盤面がないのならばFalseを返して終了
//    if (_list.size() == 0) { return false; }
//
//    //適当に一つを選択
//    int ans = GetRand((int)_list.size() - 1);
//
//    //出力
//    _result = _list.at(ans);
//    return true;
//}
//
//bool VariousFunctionsForMatchGame::matchGameCOM_Hard(const MatchField& _field, MatchField& _result, bool _self_harm)
//{
//    //次盤面を生成する
//    std::vector<MatchField> _list;
//    makeNextFieldList(_list, _field, false, _self_harm);
//
//    //生成可能な盤面がないのならばFalseを返して終了
//    if (_list.size() == 0) { return false; }
//
//    //生成した盤面を採点する
//    std::vector<int> _point;
//    for (int i = 0; i < _list.size(); i++)
//    {
//        _point.push_back(evaluationFunction(_list.at(i), _field.turn, _self_harm, 0));
//    }
//
//    //一番良い盤面を選択
//    int MAX = -10000;
//    int which = 0;
//    for (size_t c = 0; c < _point.size(); c++)
//    {
//        if (_point.at(c) > MAX)
//        {
//            MAX = _point.at(c);
//            which = (int)c;
//        }
//    }
//
//    //盤面を記録
//    _result = _list.at(which);
//
//    return true;
//}
//
//bool VariousFunctionsForMatchGame::matchGameCOM_HardForMod(const MatchField& _field, MatchField& _result, bool _self_harm)
//{
//    //次盤面を生成する
//    std::vector<MatchField> _list;
//    makeNextFieldList(_list, _field, true, _self_harm);
//
//    //生成可能な盤面がないのならばFalseを返して終了
//    if (_list.size() == 0) { return false; }
//
//    //生成した盤面を採点する
//    std::vector<int> _point;
//    for (int i = 0; i < _list.size(); i++)
//    {
//        _point.push_back(evaluationFunctionForMod(_list.at(i), _field.turn, _self_harm, 0));
//    }
//
//    //一番良い盤面を選択
//    int MAX = -10000;
//    for (size_t c = 0; c < _point.size(); c++)
//    {
//        if (_point.at(c) > MAX)
//        {
//            MAX = _point.at(c);
//        }
//    }
//
//    //良い盤面からランダムに選択
//    std::vector<MatchField> _rand;
//
//    for (size_t c = 0; c < _point.size(); c++)
//    {
//        if (_point.at(c) == MAX) {
//            _rand.push_back(_list.at(c));
//        }
//    }
//
//    //ランダム
//    int ans = GetRand((int)_rand.size() - 1);
//
//    //盤面を記録
//    _result = _rand.at(ans);
//
//    return true;
//}
//
//int VariousFunctionsForMatchGame::evaluationFunction(const MatchField _field, const  bool _player, const  bool _self_harm, int _loop_num)
//{
//    int res = 0;
//    if (MatchGameList::getIns()->evaluationFunctionList(_field, _player, _self_harm, res) == true) { return res; }
//
//    if (_loop_num >= ERROR_LOOP) { return ERROR_EVALUATION; }
//
//    //既に勝負がついているか調べる
//    if (_player == true) {
//        if (_field.doesWinFirstPlayer() == true) {
//            return WIN;
//        }
//        else if (_field.doesWinSecondPlayer() == true) {
//            return LOSE;
//        }
//    }
//    else {
//        if (_field.doesWinSecondPlayer() == true) {
//            return WIN;
//        }
//        else if (_field.doesWinFirstPlayer() == true) {
//            return LOSE;
//        }
//    }
//
//    //勝負がついていないならば，次盤面を生成する
//    std::vector<MatchField> f_vec;
//    MG::makeNextFieldList(f_vec, _field, false, _self_harm);
//
//    std::vector<int> _point;
//    int temp = 0;
//    for (auto& i : f_vec)
//    {
//        temp = evaluationFunction(i, _player, _self_harm, _loop_num + 1);
//        if (temp < 0) { temp += 1; }
//        else if (temp > 0) { temp -= 1; }
//        _point.push_back(temp);
//    }
//
//    if (_point.empty() == true) { return ERROR_EVALUATION; }
//
//    //生成した全盤面の最高得点を出力する
//    std::sort(_point.begin(), _point.end());
//    if (_field.turn == _player) {
//        //最大
//        return _point.back();
//    }
//    else {
//        //最小
//        return _point.front();
//    }
//
//    return ERROR_EVALUATION;
//}
//
////CPUを作成するのが面倒になったため適当に条件分けする
//int VariousFunctionsForMatchGame::evaluationFunctionForMod(const MatchField _field, const  bool _player, const  bool _self_harm, int _loop_num)
//{
//    int res = 0;
//    if (MatchGameList::getIns()->evaluationFunctionListForMod(_field, _player, _self_harm, res) == true) { return res; }
//
//    //既に勝負がついているか調べる
//    if (_player == true) {
//        if (_field.doesWinFirstPlayer() == true) {
//            return WIN;
//        }
//        else if (_field.doesWinSecondPlayer() == true) {
//            return LOSE;
//        }
//    }
//    else {
//        if (_field.doesWinSecondPlayer() == true) {
//            return WIN;
//        }
//        else if (_field.doesWinFirstPlayer() == true) {
//            return LOSE;
//        }
//    }
//
//    //勝負がついていないかつ深さがある程度に達したならば終了する
//    if (_loop_num > 3) { 
//        return evaluationFunctionForModSaiten(_field, _player);
//    }
//
//    //勝負がついていないならば，次盤面を生成する
//    std::vector<MatchField> f_vec;
//    MG::makeNextFieldList(f_vec, _field, true, _self_harm);
//
//    std::vector<int> _point;
//    int temp = 0;
//    for (auto& i : f_vec)
//    {
//        temp = evaluationFunctionForMod(i, _player, _self_harm, _loop_num + 1);
//        if (temp < 0) { temp += 1; }
//        else if (temp > 0) { temp -= 1; }
//        _point.push_back(temp);
//    }
//
//    if (_point.empty() == true) { return ERROR_EVALUATION; }
//
//    //生成した全盤面の最高得点を出力する
//    std::sort(_point.begin(), _point.end());
//    if (_field.turn == _player) {
//        //最大
//        return _point.back();
//    }
//    else {
//        //最小
//        return _point.front();
//    }
//
//    return ERROR_EVALUATION;
//}
//
//int VariousFunctionsForMatchGame::evaluationFunctionForModSaiten(const MatchField _field, const  bool _player)
//{
//    const int PINCH = LOSE / 2;
//    const int PINCH_HIGH = LOSE * 3 / 4;
//    const int CHANCE = WIN / 2;
//    const int CHANCE_LOW = WIN / 4;
//    const int CHANCE_HIGH = WIN * 3 / 4;
//    const int HUMEI = 0;
//    int point = 0;
//
//    const int my1 = (_player) ? _field.player1.first : _field.player2.first;
//    const int my2 = (_player) ? _field.player1.second : _field.player2.second;
//    const int myS = (_player) ? _field.player1_avatar_num : _field.player2_avatar_num;
//    const int ene1 = (_player) ? _field.player2.first : _field.player1.first;
//    const int ene2 = (_player) ? _field.player2.second : _field.player1.second;
//    const int eneS = (_player) ? _field.player2_avatar_num : _field.player1_avatar_num;
//    const bool myTurn = !(_player ^ _field.turn);
//
//    if (ene1 == 0 && ene2 == 1) { return WIN; }
//
//    //両者片手の盤面
//    if (my1 == 0 && ene1 == 0) 
//    {
//        //両者采配なし
//        if (myS == 0 && eneS == 0) {
//            if (myTurn) {
//                if (ene2 + my2 == 5) { return WIN; }
//                else { return HUMEI; }
//            }
//            else {
//                if (ene2 + my2 == 5) { return LOSE; }
//                else { return HUMEI; }
//            }
//        }
//
//        //敵だけ采配あり
//        else if (myS == 0 && eneS != 0) {
//            if (ene2 == 1) { return CHANCE_LOW; }
//
//            if (myTurn) {
//                if (ene2 + my2 == 5) { return WIN; }
//                else { return PINCH; }
//            }
//            else {
//                return PINCH;
//            }
//        }
//
//        //自分だけ采配あり
//        else if (myS != 0 && eneS == 0) {
//            if (my2 == 1) { return PINCH; }
//
//            if (myTurn) {
//                return CHANCE_LOW;
//            }
//            else {
//                if (ene2 + my2 == 5) { return LOSE; }
//                else { return CHANCE_LOW; }
//            }
//        }
//
//        //両社采配あり
//        else {
//            if (my2 == 1 && ene2 == 1) { return HUMEI; }
//            else if (my2 == 1) { return PINCH; }
//            else if (ene2 == 1) { return CHANCE_LOW; }
//            else { return HUMEI; }
//        }
//    }
//    //どちらかが片手の盤面
//    else if (my1 == 0 || ene1 == 0) {
//        if (my1 == 0) { return PINCH_HIGH; }
//        else { return CHANCE_HIGH; }
//    }
//    //両者健在の場合
//    else {
//        if (myTurn == true) {
//            if (my1 + ene1 == 5 || my1 + ene2 == 5 || my2 + ene1 == 5 || my2 + ene2 == 5) {
//                return CHANCE_HIGH;
//            }
//            else { return CHANCE; }
//        }
//        else {
//            if (my1 + ene1 == 5 || my1 + ene2 == 5 || my2 + ene1 == 5 || my2 + ene2 == 5) {
//                return PINCH;
//            }
//            else { return CHANCE; }
//        }
//    }
//
//    return HUMEI;
//}
