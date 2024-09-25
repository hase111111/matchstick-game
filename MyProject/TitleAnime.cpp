#include "TitleAnime.h"
#include "Define.h"
#include "DxLib.h"
#include "Image.h"
#include "Font.h"

//�R���X�g���N�^�ł͕ϐ��̏��������s���̂�
TitleAnime::TitleAnime() :
    m_HAND_SIZEX(70.0),
    m_HAND_SIZEY(100.0),
    m_font_20(Font::getIns()->getFontHandle("data/font/PixelMplus10_size20.dft")),
    m_font_32(Font::getIns()->getFontHandle("data/font/PixelMplus10_size32.dft")),
    m_font_64(Font::getIns()->getFontHandle("data/font/PixelMplus10_size64.dft")),
    m_GAMETITLE("�}�b�`�_�Q�[��"),
    m_GAMETITLE_STR_LEN(GetDrawStringWidthToHandle(m_GAMETITLE.c_str(), (int)m_GAMETITLE.size(), m_font_64)),
    m_ANNOUNCE("Push Z Key To Start"),
    m_ANNOUNCE_STR_LEN(GetDrawStringWidthToHandle(m_ANNOUNCE.c_str(), (int)m_ANNOUNCE.size(), m_font_32)),
    m_COPYRIGHT("(C) 2021 Saidai Game Production"),
    m_COPYRIGHT_STR_LEN(GetDrawStringWidthToHandle(m_COPYRIGHT.c_str(), (int)m_COPYRIGHT.size(), m_font_20)),
    m_counter(0)
{
    //�摜�n���h�������[�h����
    m_gr_back = myLoadGraph("data/img/title_back.png");
    m_gr_hand[0] = myLoadGraph("data/img/hand/0_hand.png");
    m_gr_hand[1] = myLoadGraph("data/img/hand/1_hand.png");
    m_gr_hand[2] = myLoadGraph("data/img/hand/2_hand.png");
    m_gr_hand[3] = myLoadGraph("data/img/hand/3_hand.png");
    m_gr_hand[4] = myLoadGraph("data/img/hand/4_hand.png");
    m_gr_hand[5] = myLoadGraph("data/img/hand/5_hand.png");
    m_gr_hand[6] = myLoadGraph("data/img/hand/piece.png");

    //�r�̃A�j���[�V�����̍X�V������
    m_InitHandAnime();
}

bool TitleAnime::update()
{
    //�A�j���[�V�������X�V���ďI��
    m_updateHandAnime();

    ++m_counter;

    return true;
}

void TitleAnime::draw() const
{
    //�w�i�̃O���f�[�V�����摜
    DrawRotaGraph(Define::WIN_SIZEX / 2, Define::WIN_SIZEY / 2, 1.0, 0.0, m_gr_back, TRUE);

    //���œ�����̃A�j���[�V����
    m_drawHandAnime();

    //�^�C�g���̉摜���R�s�[���C�g
    m_DrawGameName();
}

void TitleAnime::m_InitHandAnime()
{
    const int _hand_num = 10; //10���̘r�𐶐�����
    HandAnime _add;

    //�r�𐶐�����
    for (int i = 0; i < _hand_num; i++)
    {
        //��ʂ��\�����������W���N�_�̍��W�Ƃ��ēo�^����
        _add.base_x = (double)Define::WIN_SIZEX / _hand_num * i + m_HAND_SIZEX / 2 + 10;

        //�x�[�X���W����-10�`10���ꂽ���W�ɐݒu����
        _add.x = _add.base_x;// +(double)GetRand(30) - 15.0;

        //��ʊO�ɐݒu�i0�`�r6�����x���炷�j
        _add.y = (double)Define::WIN_SIZEY + m_HAND_SIZEY / 2.0 + (double)GetRand(m_HAND_SIZEY * 6);

        //�C���X�g�̓����_���ɐݒ肷��
        _add.gr = GetRand(6);

        //���x��1.5�`4.0�ɐݒ肷��
        _add.v = 1.5 + GetRand(250) / 100.0;

        m_hand_anime.push_back(_add);//�ǉ�����
    }
}

void TitleAnime::m_updateHandAnime()
{
    //�S�Ă̎����ֈړ������� & ��ʊO�ɍs�����Ȃ牺�֖߂�
    for (auto& i : m_hand_anime)
    {
        i.y -= i.v;

        //�r�̈ʒu�����Z�b�g���鏈��
        if (i.y + m_HAND_SIZEY / 2 < 0) {
            //�x�[�X���W����-10�`10���ꂽ���W�ɐݒu����
            i.x = i.base_x + (double)GetRand(30) - 15.0;

            //��ʊO�ɐݒu�i0�`�r2�����x���炷�j
            i.y = (double)Define::WIN_SIZEY + m_HAND_SIZEY / 2.0;

            //�C���X�g�̓����_���ɐݒ肷��
            i.gr = GetRand(6);

            //���x��1.5�`4.0�ɐݒ肷��
            i.v = 1.5 + GetRand(250) / 100.0;
        }
    }
}

void TitleAnime::m_drawHandAnime() const
{
    int _blend = 0;

    for (auto& i : m_hand_anime)
    {
        //��ʏ㕔�ɍs���قǓ����ɂȂ�
        _blend = 150 - (int)(128 * (Define::WIN_SIZEY - i.y) / Define::WIN_SIZEY);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, _blend);

        //�`��
        DrawRotaGraph((int)i.x, (int)i.y, 1.0, 0.0, m_gr_hand[i.gr], TRUE);
    }

    SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL,0);
}

void TitleAnime::m_DrawGameName() const
{
    //�^�C�g��
    DrawFormatStringToHandle((Define::WIN_SIZEX - m_GAMETITLE_STR_LEN) / 2, Define::WIN_SIZEY / 8, GetColor(0, 0, 0), m_font_64, m_GAMETITLE.c_str());

    //�A�i�E���X
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * abs(cos((double)m_counter / 15.0)));
    DrawFormatStringToHandle((Define::WIN_SIZEX - m_ANNOUNCE_STR_LEN) / 2, Define::WIN_SIZEY * 6 / 8, GetColor(0, 0, 0), m_font_32, m_ANNOUNCE.c_str());
    SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

    //�R�s�[���C�g
    DrawFormatStringToHandle(Define::WIN_SIZEX * 31 / 32 - m_COPYRIGHT_STR_LEN, Define::WIN_SIZEY * 61 / 64, GetColor(0, 0, 0), m_font_20, m_COPYRIGHT.c_str());
}
