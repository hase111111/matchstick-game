#include "SceneChangeEffect.h"
#include "Define.h"
#include "DxLib.h"
#include "Sound.h"

SceneChangeEffect::SceneChangeEffect() : m_COLOR(GetColor(0x55, 0x55, 0x55))
{
	m_sound_fade_in = Sound::getIns()->myLoadSound("data/sound/fade_in.mp3");
	m_sound_fade_out = Sound::getIns()->myLoadSound("data/sound/fade_out.mp3");
}

void SceneChangeEffect::init(const int _mode) 
{
	m_counter = 0;	//�J�E���^�̏�����
	m_mode = _mode;	//���[�h��ݒ�
}

bool SceneChangeEffect::update()
{
	++m_counter;

	//���ɃA�j���[�V�������I�����Ă����Ȃ�false��Ԃ�
	if (m_END_TIME < m_counter)return false;

	//�}�C�i�X���[�h�̎���false��Ԃ�
	if (m_mode < 0) return false;

	return true;
}

void SceneChangeEffect::draw() const
{
	int temp_y = 0;

	switch (m_mode)
	{
	//�t�F�[�h�A�E�g�̃G�t�F�N�g
	case 0:	
		//�T�E���h��炷
		if(m_counter == 1)PlaySoundMem(m_sound_fade_out,DX_PLAYTYPE_BACK);

		//�т̕`��
		for (int i = 0; i < m_WIN_DIV; i++)
		{
			temp_y = Define::WIN_SIZEY * (m_counter - m_END_TIME * i / m_WIN_DIV) / (m_END_TIME / m_WIN_DIV);
			DrawBox(Define::WIN_SIZEX / m_WIN_DIV * i, 0, Define::WIN_SIZEX * (i + 1) / m_WIN_DIV, temp_y, m_COLOR, TRUE);
		}

		break;

	//�t�F�[�h�C���̃G�t�F�N�g
	case 1:
		//�T�E���h��炷
		if (m_counter == 1)PlaySoundMem(m_sound_fade_in, DX_PLAYTYPE_BACK);

		//�т̕`��
		for (int i = 0; i < m_WIN_DIV; i++)
		{
			temp_y = Define::WIN_SIZEY * (m_counter - m_END_TIME * (m_WIN_DIV - 1 - i) / m_WIN_DIV) / (m_END_TIME / m_WIN_DIV);
			DrawBox(Define::WIN_SIZEX / m_WIN_DIV * (m_WIN_DIV - 1 - i), temp_y, Define::WIN_SIZEX * (m_WIN_DIV - i) / m_WIN_DIV, Define::WIN_SIZEY, m_COLOR, TRUE);
		}

		break;

	//�t�F�[�h�A�E�g
	case 2:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * m_counter / m_END_TIME);
		DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;

	//�t�F�[�h�A�E�g
	case 3:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (m_END_TIME - m_counter) / m_END_TIME);
		DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;

	default:

		break;
	}

}
