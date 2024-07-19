#include "RuleScene.h"
#include "RuleParam.h"
#include"Keyboard.h"
#include"Define.h"
#include"DxLib.h"
#include "Font.h"
#include "Image.h"
#include "Sound.h"

RuleScene::RuleScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) :AbstractScene(pScli, parameter)
{
    //�t�F�[�h�C���̃G�t�F�N�g��}������
    m_scene_change.init(1);

    //�t�H���g�̃��[�h������
    m_font = myLoadFont("data/font/PixelMplus10_size24.dft");

    //�摜�n���h�������[�h����
    m_image = myLoadGraph("data/img/rule_arrow.png");

    //�T�E���h�n���h�������[�h����
    m_sound = Sound::getIns()->myLoadSound("data/sound/selecting.mp3");

    //�y�[�W���̏�����
    m_page = 0;
    if (parameter.getParam(RuleParam::WHICH_RULE) == RuleParam::STATE_BASIC) { m_page = 0; }
    else if (parameter.getParam(RuleParam::WHICH_RULE) == RuleParam::STATE_SLEF) { m_page = 2; }
    else if (parameter.getParam(RuleParam::WHICH_RULE) == RuleParam::STATE_SAIHAI) { m_page = 3; }
    else if (parameter.getParam(RuleParam::WHICH_RULE) == RuleParam::STATE_MOD_5) { m_page = 4; }
    else if (parameter.getParam(RuleParam::WHICH_RULE) == RuleParam::STATE_SENRYAKU) { m_page = 5; }
    else if (parameter.getParam(RuleParam::WHICH_RULE) == RuleParam::STATE_OTHER) { m_page = 7; }
    m_page_MAX = m_rule.getPageNum();
}

bool RuleScene::update()
{
    //�V�[���`�F���W�̃G�t�F�N�g�̏������I����Ă��珈�����J�n����
    if (m_scene_change.update() == false) 
    {
        //�V�[���`�F���W�̃t���O���������Ȃ�΃V�[����؂�ւ��I��
        if (m_scene_change_flag == true)
        {
            Parameter p;
            mp_listenerInterface->deleteNowScene(p);

            return true;    //�I��������
        }

        //ESCAPE�������ꂽ�Ȃ�΃V�[�����I������
        if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) 
        {
            //�t�F�[�h�A�E�g�̃G�t�F�N�g��}������
            m_scene_change.init(0);

            //�V�[���I���̃t���O�𗧂Ă�
            m_scene_change_flag = true;
        }
        else if(Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1)
        {
            m_page++;
            if (m_page >= m_page_MAX) { m_page = m_page_MAX - 1; }
            else { PlaySoundMem(m_sound, DX_PLAYTYPE_BACK); }
        }
        else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1) 
        {
            m_page--;
            if (m_page < 0) { m_page = 0; }
            else { PlaySoundMem(m_sound, DX_PLAYTYPE_BACK); }
        }
    }

    return true;
}

void RuleScene::draw() const
{
    //�w�i
    m_drawBack();

    //�{�^��
    m_drawArrow();

    //���[���̕\��
    m_rule.draw(m_page);

    //�V�[���؂�ւ��̃G�t�F�N�g����ԏ�ɕ`�悷��
    m_scene_change.draw();
}

void RuleScene::receiveParameterInCaseOfDeleteScene(const Parameter& parameter)
{
    //�t�F�[�h�C���̃G�t�F�N�g��}������
    m_scene_change.init(1);
}

void RuleScene::m_drawArrow() const
{
    const int HALFY = Define::WIN_SIZEY / 2;
    const double EX_RATE = 1.0 + 0.2 * sin((double)GetNowCount() / 1000 * 2 * Define::PI);
    const double EX_RATE_BIG = 1.4;

    if(m_page != 0)DrawRotaGraph(Define::WIN_SIZEX / 24, HALFY, (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1) ? EX_RATE_BIG : EX_RATE, 0.0, m_image, TRUE);
    if (m_page != m_page_MAX - 1)DrawRotaGraph(Define::WIN_SIZEX * 23 / 24, HALFY, (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1) ? EX_RATE_BIG : EX_RATE, 0.0, m_image, TRUE, true);
}

void RuleScene::m_drawBack() const
{
    //���n
    DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(0xda, 0xda, 0xda), TRUE);

    //�{�b�N�X
    int _sizex = Define::WIN_SIZEX * 45 / 50;
    int _sizey = Define::WIN_SIZEY * 43 / 50;
    int _y_dz = -Define::WIN_SIZEY / 16;
    int _d = -Define::WIN_SIZEY / 64;
    DrawBox((Define::WIN_SIZEX - _sizex) / 2, (Define::WIN_SIZEY + _y_dz - _sizey) / 2, (Define::WIN_SIZEX + _sizex) / 2, (Define::WIN_SIZEY + _y_dz + _sizey) / 2, GetColor(0x21, 0x21, 0x21), TRUE);
    DrawBox((Define::WIN_SIZEX - _sizex) / 2 - _d, (Define::WIN_SIZEY + _y_dz - _sizey) / 2 - _d, (Define::WIN_SIZEX + _sizex) / 2 + _d, (Define::WIN_SIZEY + _y_dz + _sizey) / 2 + _d, GetColor(0xda, 0xda, 0xda), TRUE);

    //������`��
    std::string str = std::to_string(m_page + 1) + " / " + std::to_string(m_page_MAX);
    DrawFormatStringToHandle((Define::WIN_SIZEX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font)) / 2, Define::WIN_SIZEY * 53 / 64, GetColor(0, 0, 0), m_font, str.c_str());

    str = "���E�L�[�Ńy�[�W�؂�ւ��@�@ESC�Ŗ߂�";
    DrawFormatStringToHandle(Define::WIN_SIZEX * 5 / 8 - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font) / 2, Define::WIN_SIZEY * 15 / 16, GetColor(0, 0, 0), m_font, str.c_str());
}
