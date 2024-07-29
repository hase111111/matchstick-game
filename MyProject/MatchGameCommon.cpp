//#include "MatchGameCommon.h"
//#include "DxLib.h"
//#include <algorithm>
//
//namespace MG = VariousFunctionsForMatchGame;
//
//MatchField::MatchField()
//{
//    player1.first = 1;
//    player1.second = 1;
//    player2.first = 1;
//    player2.second = 1;
//    turn = true;
//    player1_avatar_num = 0;
//    player2_avatar_num = 0;
//}
//
//MatchField::MatchField(int p1l, int p1r, int p2l, int p2r, bool _turn)
//{
//    player1.first = p1l;
//    player1.second = p1r;
//    player2.first = p2l;
//    player2.second = p2r;
//    turn = _turn;
//    player1_avatar_num = 0;
//    player2_avatar_num = 0;
//}
//
//MatchField::MatchField(int p1l, int p1r, int p2l, int p2r, bool _turn, int _pl1_avatar_num, int _pl2_avatar_num)
//{
//    player1.first = p1l;
//    player1.second = p1r;
//    player2.first = p2l;
//    player2.second = p2r;
//    turn = _turn;
//    player1_avatar_num = _pl1_avatar_num;
//    player2_avatar_num = _pl2_avatar_num;
//}
//
//void MatchField::Optimisation(bool _mod_rule)
//{
//    MG::changeMoreFiveToZero(player1.first, _mod_rule);
//    MG::changeMoreFiveToZero(player1.second, _mod_rule);
//    MG::changeMoreFiveToZero(player2.first, _mod_rule);
//    MG::changeMoreFiveToZero(player2.second, _mod_rule);
//
//    if (player1.first > player1.second) {
//        int temp = player1.second;
//        player1.second = player1.first;
//        player1.first = temp;
//    }
//
//    if (player2.first > player2.second) {
//        int temp = player2.second;
//        player2.second = player2.first;
//        player2.first = temp;
//    }
//}
//
//void MatchField::WriteDown()
//{
//    //std::cout << "(" << player1.first << "," << player1.second << ")(" << player2.first << "," << player2.second << ")" ;
//    printfDx("(%d,%d) (%d,%d)", player1.first, player1.second, player2.first, player2.second);
//    if (player1_avatar_num != 0) { printfDx(" 先手分身%d回,", player1_avatar_num); }
//    if (player2_avatar_num != 0) { printfDx(" 後手分身%d回,", player2_avatar_num); }
//    if (turn == true) { printfDx(" 先手\n"); }
//    else { printfDx(" 後手\n"); }
//}
//
//bool MatchField::doesWinFirstPlayer() const
//{
//    if (player2.first == 0 || player2.first >= MG::DEAD_LINE) {
//        if (player2.second == 0 || player2.second >= MG::DEAD_LINE) {
//            return true;
//        }
//    }
//
//    return false;
//}
//
//bool MatchField::doesWinSecondPlayer() const
//{
//    if (player1.first == 0 || player1.first >= MG::DEAD_LINE) {
//        if (player1.second == 0 || player1.second >= MG::DEAD_LINE) {
//            return true;
//        }
//    }
//
//    return false;
//}
//
//bool MatchField::isEndOfGame() const
//{
//    if (doesWinFirstPlayer() || doesWinSecondPlayer())return true;
//    return false;
//}
//
//bool MatchField::operator==(const MatchField& rhs) const
//{
//    //両要素が等しい,かつターンの偶奇が等しいなら=
//    return (MG::comparePairUnit(player1, rhs.player1) == true && MG::comparePairUnit(player2, rhs.player2) == true && turn == rhs.turn && player1_avatar_num == rhs.player1_avatar_num && player2_avatar_num == rhs.player2_avatar_num);
//}
//
//bool MatchField::operator!=(const MatchField& rhs) const
//{
//    //両要素が等しくない,またはターンの偶奇が等しくないなら!=
//    return (MG::comparePairUnit(player1, rhs.player1) == false || MG::comparePairUnit(player2, rhs.player2) == false || turn != rhs.turn || player1_avatar_num != rhs.player1_avatar_num || player2_avatar_num != rhs.player2_avatar_num);
//}
//
//bool MatchField::operator<(const MatchField& rhs) const
//{
//    if (player1.first < rhs.player1.first) { return true; }
//    else if(player1.first == rhs.player1.first){
//        if (player1.second < rhs.player1.second) { return true; }
//        else if (player1.second == rhs.player1.second) {
//            if (player2.first < rhs.player2.first) { return true; }
//            else if (player2.first == rhs.player2.first) {
//                if (player2.second < rhs.player2.second) { return true; }
//                else if (player2.second == rhs.player2.second) {
//                    if (player1_avatar_num < rhs.player1_avatar_num) { return true; }
//                    else if (player1_avatar_num == rhs.player1_avatar_num) {
//                        if (player2_avatar_num < rhs.player2_avatar_num) { return true; }
//                        else if (player2_avatar_num == rhs.player2_avatar_num) {
//                            if (turn == false && rhs.turn == true) { return true; }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return false;
//}
//
//
//void VariousFunctionsForMatchGame::changeMoreFiveToZero(int& _num, bool _mod_rule)
//{
//    //0以下なら0にする
//    if (_num < 0)_num = 0;
//
//    //5を上回っていたら,その手は0になる
//    if (_num >= DEAD_LINE && _mod_rule == false) {
//        _num = 0;
//    }
//
//    //MODルールが適用されているなら,5のmodの値にする
//    if (_mod_rule == true && _num >= DEAD_LINE) {
//        _num = _num % DEAD_LINE;
//    }
//}
//
//bool VariousFunctionsForMatchGame::comparePairUnit(std::pair<int, int> _p1, std::pair<int, int> _p2)
//{
//    if (_p1.first == _p2.first && _p1.second == _p2.second) { return true; }
//    if (_p1.first == _p2.second && _p1.second == _p2.first) { return true; }
//    return false;
//}
//
//void VariousFunctionsForMatchGame::makeNextFieldList(std::vector<MatchField>& _list, MatchField _now, bool _mod_rule, bool _self_harm)
//{
//    _now.Optimisation(_mod_rule);//最適化する
//    _list.clear();//リストをクリア
//
//    //まずに自傷可能なら自傷する
//    if (_self_harm == true)
//    {
//        if ((_now.turn == true && _now.player1.first != 0 && _now.player1.second != 0) || (_now.turn == false && _now.player2.first != 0 && _now.player2.second != 0)) {
//            MatchField _new_self1 = _now;
//            _new_self1.turn = !_now.turn;
//
//            MatchField _new_self2 = _now;
//            _new_self2.turn = !_now.turn;
//
//            if (_now.turn == true) {
//                _new_self1.player1.first += _new_self1.player1.second;
//                _new_self2.player1.second += _new_self2.player1.first;
//            }
//            else {
//                _new_self1.player2.first += _new_self1.player2.second;
//                _new_self2.player2.second += _new_self2.player2.first;
//            }
//
//            _new_self1.Optimisation(_mod_rule);
//            _new_self2.Optimisation(_mod_rule);
//
//            _list.push_back(_new_self1);
//            if (_new_self1 != _new_self2) { _list.push_back(_new_self2); }
//        }
//    }
//
//    //次に、考えられる次の盤面は4通り。これを生成する
//    MatchField _new;
//
//    for (int i = 0; i < 4; i++)
//    {
//        _new = _now;
//        _new.turn = !_now.turn;//ターンを反転
//
//        if (_now.turn == true)
//        {
//            if (i == 0 && _now.player2.first * _now.player1.first == 0) { continue; }
//            else if (i == 1 && _now.player2.first * _now.player1.second == 0) { continue; }
//            else if (i == 2 && _now.player2.second * _now.player1.first == 0) { continue; }
//            else if (i == 3 && _now.player2.second * _now.player1.second == 0) { continue; }
//
//            if (i == 0) { _new.player2.first = _now.player2.first + _now.player1.first; }
//            else if (i == 1) { _new.player2.first = _now.player2.first + _now.player1.second; }
//            else if (i == 2) { _new.player2.second = _now.player2.second + _now.player1.first; }
//            else if (i == 3) { _new.player2.second = _now.player2.second + _now.player1.second; }
//        }
//        else {
//            if (i == 0 && _now.player1.first * _now.player2.first == 0) { continue; }
//            else if (i == 1 && _now.player1.first * _now.player2.second == 0) { continue; }
//            else if (i == 2 && _now.player1.second * _now.player2.first == 0) { continue; }
//            else if (i == 3 && _now.player1.second * _now.player2.second == 0) { continue; }
//
//            if (i == 0) { _new.player1.first = _now.player1.first + _now.player2.first; }
//            else if (i == 1) { _new.player1.first = _now.player1.first + _now.player2.second; }
//            else if (i == 2) { _new.player1.second = _now.player1.second + _now.player2.first; }
//            else if (i == 3) { _new.player1.second = _now.player1.second + _now.player2.second; }
//        }
//
//        _new.Optimisation(_mod_rule);//生成終了したら最適化
//
//        //盤面の生成に成功したなら,かぶりがないか検索し,なければ挿入する
//        if (_list.empty() == true) {
//            _list.push_back(_new);
//        }
//        else {
//            bool kaburi_nashi = true;
//
//            for (auto i = _list.begin(); i != _list.end(); i++)
//            {
//                if ((*i) == _new)kaburi_nashi = false;
//            }
//
//            if (kaburi_nashi == true) { _list.push_back(_new); }
//        }
//    }
//
//    //分身可能ならば分身する
//    if ((_now.player1_avatar_num > 0 && _now.turn == true) || (_now.player2_avatar_num > 0 && _now.turn == false)) {
//        
//        int sum = 0;
//
//        if (_now.turn == true) {
//            sum = _now.player1.first + _now.player1.second;
//            int loop_num = sum + 1;
//            if (loop_num % 2 == 0) { loop_num /= 2; }
//            else { loop_num = (loop_num / 2) + 1; }
//
//            for (int i = 0; i < loop_num; i++)
//            {
//                _new = _now;
//                _new.turn = !_now.turn;
//                _new.player1_avatar_num -= 1;
//                _new.player1.first = i;
//                _new.player1.second = sum - i;
//                _new.Optimisation(_mod_rule);
//
//                if (_new.player1.first + _new.player1.second == sum) {
//                    if (_now.player1.first != _new.player1.first || _now.player1.second != _new.player1.second) {
//                        _list.push_back(_new);
//                    }
//                }
//            }
//        }
//        else {
//            sum = _now.player2.first + _now.player2.second;
//            int loop_num = sum + 1;
//            if (loop_num % 2 == 0) { loop_num /= 2; }
//            else { loop_num = (loop_num / 2) + 1; }
//
//            for (int i = 0; i < loop_num; i++)
//            {
//                _new = _now;
//                _new.turn = !_now.turn;
//                _new.player2_avatar_num -= 1;
//                _new.player2.first = i;
//                _new.player2.second = sum - i;
//                _new.Optimisation(_mod_rule);
//
//                if (_new.player2.first + _new.player2.second == sum) {
//                    if (_now.player2.first != _new.player2.first || _now.player2.second != _new.player2.second) {
//                        _list.push_back(_new);
//                    }
//                }
//            }
//        }
//    }    
//}
//
//int VariousFunctionsForMatchGame::getCommand(const MatchField& _old, const MatchField& _new, bool _mod_rule, bool _self_harm)
//{
//    MatchField _temp;
//
//    for (int i = 0; i < 8; i++)
//    {
//        if (executeCommand(i, _old, _temp, _mod_rule, _self_harm) == true) 
//        {
//            if (_temp == _new) {
//                return i;
//            }
//        }
//    }
//
//    return COMMAND_ERROR;
//}
//
//bool VariousFunctionsForMatchGame::executeCommand(const int _command, const MatchField& _old, MatchField& _new, bool _mod_rule, bool _self_harm)
//{
//    _new = _old;
//    _new.turn = !_new.turn;
//    _new.Optimisation();
//
//    switch (_command)
//    {
//    case COMMAND_ERROR:
//        return false;
//        break;
//
//    case COMMAND_1_TO_1:
//        if (_old.turn == true) { _new.player2.first += _new.player1.first; }
//        else { _new.player1.first += _new.player2.first; }
//        _new.Optimisation(_mod_rule);
//        break;
//
//    case COMMAND_1_TO_2:
//        if (_old.turn == true) { _new.player2.second += _new.player1.first; }
//        else { _new.player1.second += _new.player2.first; }
//        _new.Optimisation(_mod_rule);
//        break;
//
//    case COMMAND_2_TO_1:
//        if (_old.turn == true) { _new.player2.first += _new.player1.second; }
//        else { _new.player1.first += _new.player2.second; }
//        _new.Optimisation(_mod_rule);
//        break;
//
//    case COMMAND_2_TO_2:
//        if (_old.turn == true) { _new.player2.second += _new.player1.second; }
//        else { _new.player1.second += _new.player2.second; }
//        _new.Optimisation(_mod_rule);
//        break;
//
//    case COMMAND_1_SELF:
//        if (_self_harm == true) {
//            if (_old.turn == true) { _new.player1.second += _new.player1.first; }
//            else { _new.player2.second += _new.player2.first; }
//            _new.Optimisation(_mod_rule);
//        }
//        else { return false; }
//        break;
//
//    case COMMAND_2_SELF:
//        if (_self_harm == true) {
//            if (_old.turn == true) { _new.player1.first += _new.player1.second; }
//            else { _new.player2.first += _new.player2.second; }
//            _new.Optimisation(_mod_rule);
//        }
//        else { return false; }
//        break;
//
//    case COMMAND_SAIHAI_LOW:
//        if ((_old.turn == true && _old.player1_avatar_num > 0) || (_old.turn == false && _old.player2_avatar_num > 0)) //采配可能か確認する
//        {
//            int sum = 0, res = 0;
//
//            if (_old.turn == true) //自ターンの場合
//            {
//                sum = _old.player1.first + _old.player1.second;
//
//                if (2 <= sum && sum <= 6) 
//                {
//                    for (int i = 0; i < sum; i++)
//                    {
//                        if (sum - i < 5 && i != _old.player1.first) {
//                            _new.player1.first = i;
//                            _new.player1.second = sum - i;
//                            _new.player1_avatar_num -= 1;
//                            _new.Optimisation(_mod_rule);
//                            break;
//                        }
//                    }
//                }
//                else {
//                    //采配可能な合計値は２～６
//                    return false;
//                }
//            }
//            else { //敵ターンの場合
//                sum = _old.player2.first + _old.player2.second;
//
//                if (2 <= sum && sum <= 6) 
//                {
//                    for (int i = 0; i < sum; i++)
//                    {
//                        if (sum - i < 5 && i != _old.player2.first) {
//                            _new.player2.first = i;
//                            _new.player2.second = sum - i;
//                            _new.Optimisation(_mod_rule);
//                            _new.player2_avatar_num -= 1;
//                            break;
//                        }
//                    }
//                }
//                else {
//                    //采配可能な合計値は２～６
//                    return false;
//                }
//            }
//        }
//        else {
//            //采配できない場合はfalse 
//            return false; 
//        }
//        break;
//
//    case COMMAND_SAIHAI_HIGH:
//        if ((_old.turn == true && _old.player1_avatar_num > 0) || (_old.turn == false && _old.player2_avatar_num > 0)) //采配可能か確認する
//        {
//            int sum = 0, res = 0;
//
//            if (_old.turn == true) //自ターンの場合
//            {
//                sum = _old.player1.first + _old.player1.second;
//
//                if (2 <= sum && sum <= 6)
//                {
//                    for (int i = (sum / 2); i >= 0; i--)
//                    {
//                        if (sum - i < 5 && i != _old.player1.first) {
//                            _new.player1.first = i;
//                            _new.player1.second = sum - i;
//                            _new.player1_avatar_num -= 1;
//                            _new.Optimisation(_mod_rule);
//                            break;
//                        }
//                    }
//                }
//                else {
//                    //采配可能な合計値は２～６
//                    return false;
//                }
//            }
//            else { //敵ターンの場合
//                sum = _old.player2.first + _old.player2.second;
//
//                if (2 <= sum && sum <= 6)
//                {
//                    for (int i = (sum / 2); i >= 0; i--)
//                    {
//                        if (sum - i < 5 && i != _old.player2.first) {
//                            _new.player2.first = i;
//                            _new.player2.second = sum - i;
//                            _new.Optimisation(_mod_rule);
//                            _new.player2_avatar_num -= 1;
//                            break;
//                        }
//                    }
//                }
//                else {
//                    //采配可能な合計値は２～６
//                    return false;
//                }
//            }
//        }
//        else {
//            //采配できない場合はfalse 
//            return false;
//        }
//        break;
//
//    default:
//        return false;
//        break;
//    }
//
//    return true;
//}
