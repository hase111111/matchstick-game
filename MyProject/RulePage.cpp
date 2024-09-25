#include "RulePage.h"
#include"Font.h"
#include"DxLib.h"
#include "Define.h"

RulePage::RulePage()
{
	m_setFunc();

	m_font_24 = myLoadFont("data/font/PixelMplus10_size24.dft");
	m_font_32 = myLoadFont("data/font/PixelMplus10_size32.dft");
}

void RulePage::draw(int _page) const
{
	if (m_draw_page.size() <= _page) { _page = (int)m_draw_page.size() - 1; }
	if (0 > _page) { _page = 0; }
	(this->*m_draw_page[_page])();
}

int RulePage::getPageNum() const
{
	return (int)m_draw_page.size();
}

void RulePage::m_draw_BaseRule00() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//�^�C�g���\��
	str ="��{���[�� 1 / 2";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//����
	str = "";
	str += "1. ���A�������߂�B�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@\n";
	str += "\n";
	str += "2. ���v���C���[�͗���̐l�����w�𗧂Ă�B�@�@�@�@�@�@�@�@�@�@�@�@\n";
	str += "\n";
	str += "3. ���Ԃ��瑊��̎�̂����ꂩ���I�����čU������B�U�����ꂽ\n";
	str += "   ��́A�I��������̎w�{�����ǉ��Ŏw�𗧂Ă�B �i�Ⴆ��3�{�w����\n";
	str += "   ������ő���̎w�� 1�{�����Ă������U���������A����͎w���S�{\n";
	str += "   ���Ă�B)\n";
	str += "   0 �̎�͍U�����邱�Ƃ��ł����A�܂��U���ΏۂɑI�����邱�Ƃ��ł�\n";
	str += "   �Ȃ��B\n";
	str += "\n";
	str += "4. �U���ɂ���āA���Ă��w�̐���5�ȏ�ƂȂ鎞���̎�͏���(���Ă��w\n";
	str += "   �����ׂĐ܂肽����)����B\n";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_draw_BaseRule01() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//�^�C�g���\��
	str = "��{���[�� 2 / 2";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//����
	str = "";
	str = "5. ����̎�����ׂď��ł��������A�����ƂȂ�B�@�@�@�@�@�@�@�@�@�@ \n";
	str += "\n";
	str += "6. ����Ֆʂ�4��ȏ㌻�ꂽ�Ƃ��A�����Ƃ��Ĉ��������ƂȂ�B����\n";
	str += "   �̔Ֆʂ����ꂽ�Ƃ��́A��ʍ��ɑ��݂��郍�O�̐F���ω����邽�߁A\n";
	str += "   �����p���Ĕ��f����Ƃ悢�B\n";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_draw_Saihai() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;

	//�^�C�g���\��
	str = "���[�J�����[���F�єz";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//����
	str = "";
	str += "�U���̕ς��ɍs�����Ƃ��ł���s���B\n\n";
	str += "�w�̍��v�{�����ς��Ȃ��悤�ɁA�E�ƍ��Ŏw�̐���\n";
	str += "�����邱�Ƃ��ł���B (�Ⴆ�Ύ����̎肪1�A3�̎��A\n";
	str += "2�A2 �� 0�A4 �ɕύX���邱�Ƃ��ł���B)\n\n";
	str += "�Ȃ��A�єz�͎������Ɉ�x�����s�����Ƃ��ł��Ȃ��B\n";
	str += "�܂����E�̐��������ւ��邾���̍єz�͂ł��Ȃ��B\n";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 17 / 80, GetColor(0, 0, 0), m_font_32, str.c_str());
}

void RulePage::m_draw_Self() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;

	//�^�C�g���\��
	str = "���[�J�����[���F����";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//����
	str = "";
	str += "�U���̍ۂɁA�����̎��I�����čU�����邱�Ƃ��ł�\n";
	str += "�郋�[���B\n";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 17 / 80, GetColor(0, 0, 0), m_font_32, str.c_str());
}

void RulePage::m_draw_Mod5() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//�^�C�g���\��
	str = "���[�J�����[���FMOD 5";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//����
	str = "";
	str += "�U���̍ۂɁA�����̎��I�����čU�����邱�Ƃ��ł�\n";
	str += "�U���̎��A5���������Ȃ�Ώ�]���Ƃ郋�[���B �@\n\n";
	str += "�Ⴆ��3�̎��4���U�������ꍇ�A�U�����ꂽ��� 2 \n";
	str += "3 + 4 = 7,7 mod 5 = 2 �ƂȂ�B\n\n";

	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, STR_X, GetColor(0, 0, 0), m_font_32, str.c_str());
}

void RulePage::m_draw_Senryaku00() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//�^�C�g���\��
	str = "�헪�w�� 1 / 2";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//����
	str = "";
	str += "���̃Q�[���ɂ����đ厖�Ȑ�p�͈ȉ��̒ʂ�ł���B�@�@�@�@�@�@�@ \n";
	str += "\n";
	str += "�E[0,1]�ɂ��Ȃ�\n";
	str += "\n";
	str += "�E�єz�͎����̎肪�Ў�ɂȂ������̂ݎg�p����\n";
	str += "\n";
	str += "�E���肪[0,1]�̎��́A�����Ȃǂ���g���Ă�����L�[�v����\n";
	str += "\n";
	str += "�����̐헪��p���邱�Ƃ�NORMAL�܂ł�CPU�ɂ͊ȒP�ɏ������邱��\n";
	str += "���ł��邾�낤�BHARD�ȏ��CPU�ɏ����������ꍇ�A�ō���Փx��CPU\n";
	str += "�Ɛ킢���̍s����^�����邱�Ƃ��悢���낤�B(�헪�w�����)\n";

	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_draw_Senryaku01() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//�^�C�g���\��
	str = "�헪�w�� 2 / 2";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//����
	str = "";
	str += "�����A�Ԃ����Ⴏ�Ă��܂��Ƃ��̃Q�[���ɂ͐������̌��ׂ�����B��\n";
	str += "�̈��Mod 5���[�����̗p���Ȃ��ꍇ�A���K���A���K���ł��邱\n";
	str += "�Ƃ��B���̂��߁A��ɍőP���I�ё�����IMPOSSIBLE��CPU�ɂ́A����\n";
	str += "������ɍőP���I�����Ă��������邱�Ƃ��ł��Ȃ��ꍇ������B\n";
	str += "\n";
	str += "�������MOD 5�̃��[����K�p�����ꍇ�A���҂��őP���I�ё�����\n";
	str += "��������ƂȂ��Ă��܂����Ƃł���B���̂��߁A���̏ꍇ���ō���\n";
	str += "�Փx��CPU�ɂ͏������邱�Ƃ��ł��Ȃ��B\n";
	str += "\n";
	str += "���̂��߁A�헪�������ɍœK�������Ƃ��Ă��K���Ƃ͂Ȃ�Ȃ��B���F\n";
	str += "�q�ǂ��̎�V�тƂ������Ƃł���......�B";

	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_draw_Other00() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//�^�C�g���\��
	str = "�̗p����Ă��Ȃ����[���ƕ⑫ 1 / 3";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//����
	str = "";
	str += "�E���g\n";
	str += "�@�w�������Ă���肪�Ў�݂̂̏ꍇ�A�񐔐����Ȃ��єz�����邱��\n";
	str += "�@���ł��郋�[���B���̃��[�������݂���ꍇ�A���������Ɏ�������\n";
	str += "�@���Ƃ����ɗe�ՂɂȂ邽�߁A�̗p���Ȃ������B\n";
	str += "\n";
	str += "�E�U�ȏ�ŏ���\n";
	str += "�@�w�̖{����6�{�𒴂����Ƃ��ɁA���ł��郋�[���B���̃Q�[���ł�\n";
	str += "�@MOD 5���[�����̗p�������߁A���̃��[���Ƒg�ݍ��킹��Ə�������\n";
	str += "�@�|�ł���B����č̗p���Ȃ������B\n";


	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_draw_Other01() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//�^�C�g���\��
	str = "�̗p����Ă��Ȃ����[���ƕ⑫ 2 / 3";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//����
	str = "";
	str += "�E��������\n";
	str += "�@���̃Q�[���ł͓���Ֆʂ�4��ȏ㌻�ꂽ�Ƃ����������Ƃ��郋�[\n";
	str += "�@�������݂��邪�A���̃��[���͂��̃Q�[���I���W�i���̂��̂ł�\n";
	str += "�@��B���̃��[�������݂��Ȃ��ꍇ�A�ΐ�𖳌��ɑ����邱�Ƃ��ł�\n";
	str += "�@�邽�߁A�����h�����߂ɂ��̃��[����ǉ������B\n";
	str += "\n";
	str += "�E�єz 1 / 2\n";
	str += "�@�єz����������x�����g�����Ƃ��ł��Ȃ��Ƃ������[�������̃Q�[\n";
	str += "�@���I���W�i���̂��̂ł���B�����͍єz�����������x�ł��g������\n";
	str += "�@�ł��郋�[�����̗p����\�肾�������A�s�k�ڑO�̏󋵂���e�Ղ�\n";
	str += "�@���������Ɏ������ނ��Ƃ��ł��邽�߁A�Q�[������傫�����Ȃ���\n";
	str += "�@�̂Ƃ��č̗p���Ȃ������B";

	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_draw_Other02() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//�^�C�g���\��
	str = "�̗p����Ă��Ȃ����[���ƕ⑫ 3 / 3";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//����
	str = "";
	str += "�E�єz 2 / 2\n";
	str += "�E���̃Q�[���ł́A����̐��������ւ��邾���̍єz���֎~���Ă�\n";
	str += "�@��B����͈��ՂȎ��ԉ҂���h�����߂ł���B(�Ԃ����Ⴏ��ƁA��\n";
	str += "�@�E�̐����������Ƀ\�[�g���Ă���̂œ���ւ����ł���ƃv���O��\n";
	str += "�@�����ʓ|�ɂȂ�̂ō̗p�������Ȃ������B)\n";
	str += "\n";
	str += "�E�⑫\n";
	str += "�@���̃Q�[���̃^�C�g���́u�}�b�`�_�Q�[���v�Ƃ��Ă��邪�A�n���\n";
	str += "�@����Ă��̎�V�т̌Ăѕ��͈Ⴄ�悤�ł���B�u�푈�v�u����΂��v\n";
	str += "�@�u�u���t�B���v�ȂǗl�X�ł���B�Ȃ��A����҂̒n���ł͐푈�ƌĂ�\n";
	str += "�@��邱�Ƃ����������B\n";

	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_setFunc()
{
	m_draw_page.push_back(&RulePage::m_draw_BaseRule00);
	m_draw_page.push_back(&RulePage::m_draw_BaseRule01);
	m_draw_page.push_back(&RulePage::m_draw_Saihai);
	m_draw_page.push_back(&RulePage::m_draw_Self);
	m_draw_page.push_back(&RulePage::m_draw_Mod5);
	m_draw_page.push_back(&RulePage::m_draw_Senryaku00);
	m_draw_page.push_back(&RulePage::m_draw_Senryaku01);
	m_draw_page.push_back(&RulePage::m_draw_Other00);
	m_draw_page.push_back(&RulePage::m_draw_Other01);
	m_draw_page.push_back(&RulePage::m_draw_Other02);
}
