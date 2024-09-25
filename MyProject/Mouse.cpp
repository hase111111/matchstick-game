#include "Mouse.h"
#include "DxLib.h"

Mouse::Mouse() {
    m_posx = 0;
    m_poy = 0;
    m_pushing_count_left = 0;
    m_pushing_count_middle = 0;
    m_pushing_count_right = 0;
    m_releasing_count_left = 0;
    m_releasing_count_middle = 0;
    m_releasing_count_right = 0;
}

bool Mouse::update()
{
    //�}�E�X�̈ʒu�擾
    GetMousePoint(&m_posx, &m_poy);

    //���N���b�N
    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
        //������Ă���Ȃ�
        m_pushing_count_left++;
        m_releasing_count_left = 0;
    }
    else {
        //������Ă���Ȃ�
        m_pushing_count_left = 0;
        m_releasing_count_left++;
    }

    //�E�N���b�N
    if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
        //������Ă���Ȃ�
        m_pushing_count_right++;
        m_releasing_count_right = 0;
    }
    else {
        //������Ă���Ȃ�
        m_pushing_count_right = 0;
        m_releasing_count_right++;
    }

    //�z�[���h�{�^��
    if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0) {
        //������Ă���Ȃ�
        m_pushing_count_middle++;
        m_releasing_count_middle = 0;
    }
    else {
        //������Ă���Ȃ�
        m_pushing_count_middle = 0;
        m_releasing_count_middle++;
    }

    return false;
}

int Mouse::getPosX() const
{
    return m_posx;
}

int Mouse::getPosY() const
{
    return m_poy;
}

int Mouse::getPushingCountLeft() const
{
    return m_pushing_count_left;
}

int Mouse::getPushingCountRight() const
{
    return m_pushing_count_right;
}

int Mouse::getPushingCountMiddle() const
{
    return m_pushing_count_middle;
}

int Mouse::getReleasingCountLeft() const
{
    return m_releasing_count_left;
}

int Mouse::getReleasingCountRight() const
{
    return m_releasing_count_right;
}

int Mouse::getReleasingCountMiddle() const
{
    return m_releasing_count_middle;
}
