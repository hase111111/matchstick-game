#include"MatchGameCommon.h"
#include <algorithm>
#include "DxLib.h"

namespace MG = VariousFunctionsForMatchGame;

bool VariousFunctionsForMatchGame::matchGameCOM(const int _level, const MatchField& _field, MatchField& _result, const bool _self_harm, const bool _mod_rule)
{
    //��`����
    const int RAND_KAKURITU = 35;   //HARD - �����ɑ���������l%�Ń����_���ɍs������

    switch (_level) 
    {
    case 0://EASY

        //MOD���[������̎�
        if (_mod_rule == true)
        {
            //�Ֆʂ𐶐�����
            if (matchGameCOM_EasyForMod(_field, _result, _self_harm) == true) {
                return true;
            }
        }
        //MOD���[���Ȃ��̎�
        else
        {
            //�Ֆʂ𐶐�����
            if (matchGameCOM_Easy(_field, _result, _self_harm) == true) {
                return true;
            }
        }
        break;

    case 1://NORMAL

        //�����_���ȔՖʂ��o�͂���
        if (matchGameCOM_Rand(_field, _result, _self_harm, _mod_rule) == true) {
            return true;
        }
        break;

    case 2://HARD

        //�����_���ȔՖʏo��
        if (GetRand((100 / RAND_KAKURITU) + 1) == 0) {
            if (matchGameCOM_Rand(_field, _result, _self_harm, _mod_rule) == true) {
                return true;
            }
        }
        //�K�`�Ֆʏo��
        else {
            //MOD���[������̎�
            if (_mod_rule == true)
            {
                //�Ֆʂ𐶐�����
                if (matchGameCOM_HardForMod(_field, _result, _self_harm) == true) {
                    return true;
                }
            }
            //MOD���[���Ȃ��̎�
            else
            {
                //�Ֆʂ𐶐�����
                if (matchGameCOM_Hard(_field, _result, _self_harm) == true) {
                    return true;
                }
            }
        }

        break;

    default://Impossible

        //MOD���[������̎�
        if (_mod_rule == true)
        {
            //�Ֆʂ𐶐�����
            if (matchGameCOM_HardForMod(_field, _result, _self_harm) == true) {
                return true;
            }
        }
        //MOD���[���Ȃ��̎�
        else
        {
            //�Ֆʂ𐶐�����
            if (matchGameCOM_Hard(_field, _result, _self_harm) == true) {
                return true;
            }
        }

        break;
    }

    return false;
}

bool VariousFunctionsForMatchGame::matchGameCOM_Easy(const MatchField& _field, MatchField& _result, bool _self_harm)
{
    //���Ֆʂ𐶐�����
    std::vector<MatchField> _list;
    makeNextFieldList(_list, _field, false, _self_harm);

    //�����\�ȔՖʂ��Ȃ��̂Ȃ��False��Ԃ��ďI��
    if (_list.size() == 0) { return false; }

    //���������Ֆʂ��̓_���A�}�C�i�X�������̂����X�g�ɒǉ�
    std::vector<int> _point;
    for (int i = 0; i < _list.size(); i++)
    {
        _point.push_back(evaluationFunction(_list.at(i), !_field.turn, _self_harm, 0));
    }

    //��ԗǂ��Ֆʂ�I��
    int MAX = -10000;
    int which = 0;
    for (size_t c = 0; c < _point.size(); c++)
    {
        if (_point.at(c) > MAX)
        {
            MAX = _point.at(c);
            which = (int)c;
        }
    }

    //�Ֆʂ��L�^
    _result = _list.at(which);

    return true;
}

bool VariousFunctionsForMatchGame::matchGameCOM_EasyForMod(const MatchField& _field, MatchField& _result, bool _self_harm)
{
    //���Ֆʂ𐶐�����
    std::vector<MatchField> _list;
    makeNextFieldList(_list, _field, true, _self_harm);

    //�����\�ȔՖʂ��Ȃ��̂Ȃ��False��Ԃ��ďI��
    if (_list.size() == 0) { return false; }

    //���������Ֆʂ��̓_����
    std::vector<int> _point;
    for (int i = 0; i < _list.size(); i++)
    {
        _point.push_back(evaluationFunctionForMod(_list.at(i), !_field.turn, _self_harm, 0));
    }

    //��ԗǂ��Ֆʂ�I��
    int MAX = -10000;
    for (size_t c = 0; c < _point.size(); c++)
    {
        if (_point.at(c) > MAX)
        {
            MAX = _point.at(c);
        }
    }

    //�ǂ��Ֆʂ��烉���_���ɑI��
    std::vector<MatchField> _rand;

    for (size_t c = 0; c < _point.size(); c++)
    {
        if (_point.at(c) == MAX) {
            _rand.push_back(_list.at(c));
        }
    }

    //�����_��
    int ans = GetRand((int)_rand.size() - 1);

    //�Ֆʂ��L�^
    _result = _rand.at(ans);

    return true;
}

bool VariousFunctionsForMatchGame::matchGameCOM_Rand(const MatchField& _field, MatchField& _result, bool _self_harm, const bool _mod_rule)
{
    //���Ֆʂ𐶐�����
    std::vector<MatchField> _list;
    makeNextFieldList(_list, _field, _mod_rule, _self_harm);

    //�����\�ȔՖʂ��Ȃ��̂Ȃ��False��Ԃ��ďI��
    if (_list.size() == 0) { return false; }

    //�K���Ɉ��I��
    int ans = GetRand((int)_list.size() - 1);

    //�o��
    _result = _list.at(ans);
    return true;
}

bool VariousFunctionsForMatchGame::matchGameCOM_Hard(const MatchField& _field, MatchField& _result, bool _self_harm)
{
    //���Ֆʂ𐶐�����
    std::vector<MatchField> _list;
    makeNextFieldList(_list, _field, false, _self_harm);

    //�����\�ȔՖʂ��Ȃ��̂Ȃ��False��Ԃ��ďI��
    if (_list.size() == 0) { return false; }

    //���������Ֆʂ��̓_����
    std::vector<int> _point;
    for (int i = 0; i < _list.size(); i++)
    {
        _point.push_back(evaluationFunction(_list.at(i), _field.turn, _self_harm, 0));
    }

    //��ԗǂ��Ֆʂ�I��
    int MAX = -10000;
    int which = 0;
    for (size_t c = 0; c < _point.size(); c++)
    {
        if (_point.at(c) > MAX)
        {
            MAX = _point.at(c);
            which = (int)c;
        }
    }

    //�Ֆʂ��L�^
    _result = _list.at(which);

    return true;
}

bool VariousFunctionsForMatchGame::matchGameCOM_HardForMod(const MatchField& _field, MatchField& _result, bool _self_harm)
{
    //���Ֆʂ𐶐�����
    std::vector<MatchField> _list;
    makeNextFieldList(_list, _field, true, _self_harm);

    //�����\�ȔՖʂ��Ȃ��̂Ȃ��False��Ԃ��ďI��
    if (_list.size() == 0) { return false; }

    //���������Ֆʂ��̓_����
    std::vector<int> _point;
    for (int i = 0; i < _list.size(); i++)
    {
        _point.push_back(evaluationFunctionForMod(_list.at(i), _field.turn, _self_harm, 0));
    }

    //��ԗǂ��Ֆʂ�I��
    int MAX = -10000;
    for (size_t c = 0; c < _point.size(); c++)
    {
        if (_point.at(c) > MAX)
        {
            MAX = _point.at(c);
        }
    }

    //�ǂ��Ֆʂ��烉���_���ɑI��
    std::vector<MatchField> _rand;

    for (size_t c = 0; c < _point.size(); c++)
    {
        if (_point.at(c) == MAX) {
            _rand.push_back(_list.at(c));
        }
    }

    //�����_��
    int ans = GetRand((int)_rand.size() - 1);

    //�Ֆʂ��L�^
    _result = _rand.at(ans);

    return true;
}

int VariousFunctionsForMatchGame::evaluationFunction(const MatchField _field, const  bool _player, const  bool _self_harm, int _loop_num)
{
    int res = 0;
    if (MatchGameList::getIns()->evaluationFunctionList(_field, _player, _self_harm, res) == true) { return res; }

    if (_loop_num >= ERROR_LOOP) { return ERROR_EVALUATION; }

    //���ɏ��������Ă��邩���ׂ�
    if (_player == true) {
        if (_field.doesWinFirstPlayer() == true) {
            return WIN;
        }
        else if (_field.doesWinSecondPlayer() == true) {
            return LOSE;
        }
    }
    else {
        if (_field.doesWinSecondPlayer() == true) {
            return WIN;
        }
        else if (_field.doesWinFirstPlayer() == true) {
            return LOSE;
        }
    }

    //���������Ă��Ȃ��Ȃ�΁C���Ֆʂ𐶐�����
    std::vector<MatchField> f_vec;
    MG::makeNextFieldList(f_vec, _field, false, _self_harm);

    std::vector<int> _point;
    int temp = 0;
    for (auto& i : f_vec)
    {
        temp = evaluationFunction(i, _player, _self_harm, _loop_num + 1);
        if (temp < 0) { temp += 1; }
        else if (temp > 0) { temp -= 1; }
        _point.push_back(temp);
    }

    if (_point.empty() == true) { return ERROR_EVALUATION; }

    //���������S�Ֆʂ̍ō����_���o�͂���
    std::sort(_point.begin(), _point.end());
    if (_field.turn == _player) {
        //�ő�
        return _point.back();
    }
    else {
        //�ŏ�
        return _point.front();
    }

    return ERROR_EVALUATION;
}

//CPU���쐬����̂��ʓ|�ɂȂ������ߓK���ɏ�����������
int VariousFunctionsForMatchGame::evaluationFunctionForMod(const MatchField _field, const  bool _player, const  bool _self_harm, int _loop_num)
{
    int res = 0;
    if (MatchGameList::getIns()->evaluationFunctionListForMod(_field, _player, _self_harm, res) == true) { return res; }

    //���ɏ��������Ă��邩���ׂ�
    if (_player == true) {
        if (_field.doesWinFirstPlayer() == true) {
            return WIN;
        }
        else if (_field.doesWinSecondPlayer() == true) {
            return LOSE;
        }
    }
    else {
        if (_field.doesWinSecondPlayer() == true) {
            return WIN;
        }
        else if (_field.doesWinFirstPlayer() == true) {
            return LOSE;
        }
    }

    //���������Ă��Ȃ����[����������x�ɒB�����Ȃ�ΏI������
    if (_loop_num > 3) { 
        return evaluationFunctionForModSaiten(_field, _player);
    }

    //���������Ă��Ȃ��Ȃ�΁C���Ֆʂ𐶐�����
    std::vector<MatchField> f_vec;
    MG::makeNextFieldList(f_vec, _field, true, _self_harm);

    std::vector<int> _point;
    int temp = 0;
    for (auto& i : f_vec)
    {
        temp = evaluationFunctionForMod(i, _player, _self_harm, _loop_num + 1);
        if (temp < 0) { temp += 1; }
        else if (temp > 0) { temp -= 1; }
        _point.push_back(temp);
    }

    if (_point.empty() == true) { return ERROR_EVALUATION; }

    //���������S�Ֆʂ̍ō����_���o�͂���
    std::sort(_point.begin(), _point.end());
    if (_field.turn == _player) {
        //�ő�
        return _point.back();
    }
    else {
        //�ŏ�
        return _point.front();
    }

    return ERROR_EVALUATION;
}

int VariousFunctionsForMatchGame::evaluationFunctionForModSaiten(const MatchField _field, const  bool _player)
{
    const int PINCH = LOSE / 2;
    const int PINCH_HIGH = LOSE * 3 / 4;
    const int CHANCE = WIN / 2;
    const int CHANCE_LOW = WIN / 4;
    const int CHANCE_HIGH = WIN * 3 / 4;
    const int HUMEI = 0;
    int point = 0;

    const int my1 = (_player) ? _field.player1.first : _field.player2.first;
    const int my2 = (_player) ? _field.player1.second : _field.player2.second;
    const int myS = (_player) ? _field.player1_avatar_num : _field.player2_avatar_num;
    const int ene1 = (_player) ? _field.player2.first : _field.player1.first;
    const int ene2 = (_player) ? _field.player2.second : _field.player1.second;
    const int eneS = (_player) ? _field.player2_avatar_num : _field.player1_avatar_num;
    const bool myTurn = !(_player ^ _field.turn);

    if (ene1 == 0 && ene2 == 1) { return WIN; }

    //���ҕЎ�̔Ֆ�
    if (my1 == 0 && ene1 == 0) 
    {
        //���ҍєz�Ȃ�
        if (myS == 0 && eneS == 0) {
            if (myTurn) {
                if (ene2 + my2 == 5) { return WIN; }
                else { return HUMEI; }
            }
            else {
                if (ene2 + my2 == 5) { return LOSE; }
                else { return HUMEI; }
            }
        }

        //�G�����єz����
        else if (myS == 0 && eneS != 0) {
            if (ene2 == 1) { return CHANCE_LOW; }

            if (myTurn) {
                if (ene2 + my2 == 5) { return WIN; }
                else { return PINCH; }
            }
            else {
                return PINCH;
            }
        }

        //���������єz����
        else if (myS != 0 && eneS == 0) {
            if (my2 == 1) { return PINCH; }

            if (myTurn) {
                return CHANCE_LOW;
            }
            else {
                if (ene2 + my2 == 5) { return LOSE; }
                else { return CHANCE_LOW; }
            }
        }

        //���Ѝєz����
        else {
            if (my2 == 1 && ene2 == 1) { return HUMEI; }
            else if (my2 == 1) { return PINCH; }
            else if (ene2 == 1) { return CHANCE_LOW; }
            else { return HUMEI; }
        }
    }
    //�ǂ��炩���Ў�̔Ֆ�
    else if (my1 == 0 || ene1 == 0) {
        if (my1 == 0) { return PINCH_HIGH; }
        else { return CHANCE_HIGH; }
    }
    //���Ҍ��݂̏ꍇ
    else {
        if (myTurn == true) {
            if (my1 + ene1 == 5 || my1 + ene2 == 5 || my2 + ene1 == 5 || my2 + ene2 == 5) {
                return CHANCE_HIGH;
            }
            else { return CHANCE; }
        }
        else {
            if (my1 + ene1 == 5 || my1 + ene2 == 5 || my2 + ene1 == 5 || my2 + ene2 == 5) {
                return PINCH;
            }
            else { return CHANCE; }
        }
    }

    return HUMEI;
}
