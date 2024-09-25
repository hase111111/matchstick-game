#include "Setting.h"
#include <fstream>
#include <string>

void Setting::loadSettingFile()
{
	std::string filename = "./setting.conf";
	std::ifstream result_file;

	//入力・バイナリモードでファイルを開く
	result_file.open(filename, std::ios::in | std::ios::binary);

	//読み込みに失敗した場合終了
	if (result_file.is_open() == false) 
	{
		setDefState();	//デフォルトのステータスをセットする
		saveSettingFile(m_vol, m_window_mode, m_anime_cut);
		return;
	}

	//データを読み込む
	char buf = 0;

	if (result_file.eof() == true) { return; }	//ファイルの終端ならば終了
	result_file.read(&buf, sizeof(buf));		//ファイルから一文字読み込む
	m_vol = (int)buf;							//代入する
	m_vol = (m_vol < 0) ? 0 : m_vol;
	m_vol = (m_vol > 100) ? 100 : m_vol;

	if (result_file.eof() == true) { return; }	//ファイルの終端ならば終了
	result_file.read(&buf, sizeof(buf));		//ファイルから一文字読み込む
	m_window_mode = (buf != 0) ? true : false;

	if (result_file.eof() == true) { return; }	//ファイルの終端ならば終了
	result_file.read(&buf, sizeof(buf));		//ファイルから一文字読み込む
	m_anime_cut = (buf != 0) ? true : false;

	//ファイルを閉じる
	result_file.close();
}

void Setting::saveSettingFile(const int _vol, const bool _win, const bool _anime)
{
	std::string filename = "./setting.conf";
	std::ofstream result_file;

	//出力・バイナリモードでファイルを開く
	result_file.open(filename, std::ios::out | std::ios::binary);

	//読み込みに失敗した場合終了
	if (result_file.is_open() == false)
	{
		return;
	}

	//データを書き込む
	char buf = 0;

	//音量の書き込み
	m_vol = (_vol < 0) ? 0 : _vol;
	m_vol = (_vol > 100) ? 100 : _vol;

	buf = (char)m_vol;
	result_file.write(&buf, sizeof(buf));

	//フルスク
	m_window_mode = _win;
	buf = (m_window_mode == true) ? 1 : 0;
	result_file.write(&buf, sizeof(buf));

	//アニメ
	m_anime_cut = _anime;
	buf = (m_anime_cut == true) ? 1 : 0;
	result_file.write(&buf, sizeof(buf));

	//ファイルを閉じる
	result_file.close();
}

int Setting::getSettingVol(const bool def_flag) const
{
	if (def_flag == true) return m_DEF_VOL;
	return m_vol;
}

bool Setting::getSettingFulWin(const bool def_flag) const
{
	if (def_flag == true) return m_DEF_WIN;
	return m_window_mode;
}

bool Setting::getSettingAnime(const bool def_flag) const
{
	if (def_flag == true) return m_DEF_ANIME;
	return m_anime_cut;
}

void Setting::setDefState()
{
	m_vol = m_DEF_VOL;
	m_anime_cut = m_DEF_ANIME;
	m_window_mode = m_DEF_WIN;
}
