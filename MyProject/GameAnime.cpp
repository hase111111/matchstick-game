//#include "GameAnime.h"
//#include "Font.h"
//#include "DxLib.h"
//#include "Define.h"
//#include "Image.h"
//#include "Sound.h"
//#include "Setting.h"
//
//using namespace VariousFunctionsForMatchGame;
//
//GameAnime::GameAnime()
//{
//	m_ANIME_END_TIMES[0] = 4 * 60;
//	m_ANIME_END_TIMES[1] = 4 * 60;
//	m_ANIME_END_TIMES[2] = 0;
//	m_ANIME_END_TIMES[3] = 5 * 60;
//	m_ANIME_END_TIMES[4] = 30;
//	m_ANIME_END_TIMES[5] = (int)(2.5 * 60);
//	m_ANIME_END_TIMES[6] = (int)(2.5 * 60);
//	m_ANIME_END_TIMES[7] = 2 * 60;
//	m_ANIME_END_TIMES[8] = 30;
//
//	//フォントのセット
//	m_font_32 = myLoadFont("data/font/PixelMplus10_size32.dft");
//
//	//画像のセット
//	m_gr_hand[0] = myLoadGraph("data/img/hand/0_hand.png");
//	m_gr_hand[1] = myLoadGraph("data/img/hand/1_hand.png");
//	m_gr_hand[2] = myLoadGraph("data/img/hand/2_hand.png");
//	m_gr_hand[3] = myLoadGraph("data/img/hand/3_hand.png");
//	m_gr_hand[4] = myLoadGraph("data/img/hand/4_hand.png");
//	m_gr_hand[5] = myLoadGraph("data/img/hand/5_hand.png");
//
//	//サウンドの読み込み
//	m_sound_attack = Sound::getIns()->myLoadSound("data/sound/attack.mp3");
//	m_sound_start = Sound::getIns()->myLoadSound("data/sound/battle_start.mp3");
//
//	//アニメ設定
//	m_anime_cut_flag = Setting::getIns()->getSettingAnime();
//}
//
//void GameAnime::init(bool _self, bool _mod, bool _set_anime_cut)
//{
//	m_self_harm = _self;
//	m_mod_rule = _mod;
//
//	//TRUEの時アニメカットフラグを切る
//	if (_set_anime_cut == true) 
//	{
//		m_anime_cut_flag = false;
//	}
//}
//
//void GameAnime::addAnime(const int _command)
//{
//	m_counter = 0;			//カウンタを戻す
//	m_command = _command;	//コマンドを記録
//}
//
//void GameAnime::addAnimeOption(MatchField _old, MatchField _new)
//{
//	m_old = _old;
//	m_new = _new;
//	m_hand_cmd = getCommand(m_old, m_new, m_mod_rule, m_self_harm);
//}
//
//void GameAnime::addAnimeOption2(MatchField _old, int _hand_cmd)
//{
//	m_old = _old;
//	m_hand_cmd = _hand_cmd;
//
//	MatchField _temp;
//	if (executeCommand(m_hand_cmd, _old, _temp, m_mod_rule, m_self_harm) == true) {
//		m_new = _temp;
//	}
//	else {
//		m_hand_cmd = COMMAND_ERROR;
//	}
//}
//
//
//bool GameAnime::update()
//{
//	if (m_counter == 1 && m_anime_cut_flag == true) { 
//		m_counter = 10000000;
//		return false;
//	}
//
//	m_counter++;	//カウンタを進める
//
//	if (m_ANIME_END_TIMES[m_command] < m_counter) 
//	{
//
//		//あんまよくない処理だが、変則アニメーションを行う
//		if (m_command == 4) 
//		{
//			m_counter = 0;	//カウンタのリセット
//
//			//行うアニメーションのタイプによって処理を変更する
//			if (m_hand_cmd == COMMAND_1_TO_1 || m_hand_cmd == COMMAND_1_TO_2 || m_hand_cmd == COMMAND_2_TO_1 || m_hand_cmd == COMMAND_2_TO_2) {
//				m_command = 5;
//			}
//			else if (m_hand_cmd == COMMAND_1_SELF || m_hand_cmd == COMMAND_2_SELF) {
//				m_command = 6;
//			}
//			else if (m_hand_cmd == COMMAND_SAIHAI_LOW || m_hand_cmd == COMMAND_SAIHAI_HIGH) {
//				m_command = 7;
//			}
//			else {
//				printfDx("不明なコマンド[%d]です。アニメーションを終了します/GameAnimeClass.update関数\n", m_hand_cmd);
//				m_command = 8;
//			}
//
//			return true;
//		}
//		else if (m_command == 5 || m_command == 6 || m_command == 7) {
//			m_counter = 0;
//			m_command = 8;
//			return true;
//		}
//
//		return false;
//	}
//
//	return true;
//}
//
//void GameAnime::draw() const
//{
//	//カウンタが過ぎ去っているならば処理を行わない
//	if (m_ANIME_END_TIMES[m_command] < m_counter) { return; }
//
//	//コマンドの種類によって処理を分ける
//	switch (m_command)
//	{
//	case 0:
//		//ゲームスタートのアニメーション先行時
//		m_drawAnime00();
//		break;
//
//	case 1:
//		//ゲームスタートのアニメーション後攻時
//		m_drawAnime01();
//		break;
//
//	case 2:
//		//  虚無
//		m_drawAnime02();
//		break;
//
//	case 3:
//		//ゲーム終了時のアニメーション勝利
//		m_drawAnime03();
//		break;
//
//	case 4:
//		//攻撃アニメーション　始め
//		m_drawAnime04();
//		break;
//
//	case 5:
//		//通常攻撃アニメーション
//		m_drawAnime05();
//		break;
//
//	case 6:
//		//自傷アニメーション
//		m_drawAnime06();
//		break;
//
//	case 7:
//		//采配アニメーション
//		m_drawAnime07();
//		break;
//
//	case 8:
//		//通常攻撃アニメーション　終了
//		m_drawAnime08();
//		break;
//
//	default:
//		//アニメーションがないならば何もしない
//		break;
//	}
//}
//
//bool GameAnime::isEndTime() const
//{
//	if (m_anime_cut_flag == true) { return true; }
//
//	int _half = m_ANIME_END_TIMES[m_command];
//
//	if (m_counter == _half) {
//		return true;
//	}
//
//	return false;
//}
//
//
////各種アニメーション関数
//void GameAnime::m_drawAnime00() const
//{
//	const int BOX_COLOR = GetColor(0x77, 0x77, 0x77);
//	const int TOPY = Define::WIN_SIZEY * 3 / 8;
//	const int BOTTOMY = Define::WIN_SIZEY * 5 / 8;
//	const int HALFX = Define::WIN_SIZEX / 2;
//
//	const int TIME_LINE_STARTED = 30;
//	const int TIME_CHAR_APPEAR = TIME_LINE_STARTED;
//	//線を引く
//	if (m_counter < m_ANIME_END_TIMES[0] / 6) 
//	{
//		DrawBox(0, TOPY, HALFX * m_counter / (m_ANIME_END_TIMES[0] / 6), BOTTOMY, BOX_COLOR, TRUE);
//		DrawBox(Define::WIN_SIZEX - HALFX * m_counter / (m_ANIME_END_TIMES[0] / 6), TOPY, Define::WIN_SIZEX, BOTTOMY, BOX_COLOR, TRUE);
//	}
//	else if (m_counter > m_ANIME_END_TIMES[0] * 5 / 6) 
//	{
//		DrawBox(0,TOPY, HALFX * (m_ANIME_END_TIMES[0] - m_counter) / (m_ANIME_END_TIMES[0] / 6), Define::WIN_SIZEY * 5 / 8, GetColor(0x77, 0x77, 0x77), TRUE);
//		DrawBox(Define::WIN_SIZEX - HALFX * (m_ANIME_END_TIMES[0] - m_counter) / (m_ANIME_END_TIMES[0] / 6), TOPY, Define::WIN_SIZEX, Define::WIN_SIZEY * 5 / 8, GetColor(0x77, 0x77, 0x77), TRUE);
//	}
//	else 
//	{
//		DrawBox(0, Define::WIN_SIZEY * 3 / 8, Define::WIN_SIZEX, Define::WIN_SIZEY * 5 / 8, GetColor(0x77, 0x77, 0x77), TRUE);
//
//		//時間に応じて文字を薄くする
//		if (m_ANIME_END_TIMES[0] * 2 / 6 > m_counter) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (m_counter - m_ANIME_END_TIMES[0] / 6) / (m_ANIME_END_TIMES[0] / 6)); }
//		else if (m_ANIME_END_TIMES[0] * 4 / 6 < m_counter) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (m_ANIME_END_TIMES[0] * 5 / 6 - m_counter) / (m_ANIME_END_TIMES[0] / 6)); }
//
//		//表示する
//		DrawFormatStringToHandle(HALFX - GetDrawStringWidthToHandle("!!!勝負開始!!!", 15, m_font_32) / 2, Define::WIN_SIZEY * 27 / 64, GetColor(0, 0, 0), m_font_32, "!!!勝負開始!!!");
//		DrawFormatStringToHandle(HALFX - GetDrawStringWidthToHandle("あなたは先手です", 17, m_font_32) / 2, Define::WIN_SIZEY * 33 / 64, GetColor(0, 0, 0), m_font_32, "あなたは先手です");
//		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
//	}
//
//	if (m_counter == 1) { PlaySoundMem(m_sound_start, DX_PLAYTYPE_BACK); }
//}
//
//void GameAnime::m_drawAnime01() const
//{
//	const int BOX_COLOR = GetColor(0x77, 0x77, 0x77);
//	const int TOPY = Define::WIN_SIZEY * 3 / 8;
//	const int BOTTOMY = Define::WIN_SIZEY * 5 / 8;
//	const int HALFX = Define::WIN_SIZEX / 2;
//
//	//線を引く
//	if (m_counter < m_ANIME_END_TIMES[0] / 6)
//	{
//		DrawBox(0, TOPY, HALFX * m_counter / (m_ANIME_END_TIMES[0] / 6), BOTTOMY, BOX_COLOR, TRUE);
//		DrawBox(Define::WIN_SIZEX - HALFX * m_counter / (m_ANIME_END_TIMES[0] / 6), TOPY, Define::WIN_SIZEX, BOTTOMY, BOX_COLOR, TRUE);
//	}
//	else if (m_counter > m_ANIME_END_TIMES[0] * 5 / 6)
//	{
//		DrawBox(0, TOPY, HALFX * (m_ANIME_END_TIMES[0] - m_counter) / (m_ANIME_END_TIMES[0] / 6), Define::WIN_SIZEY * 5 / 8, GetColor(0x77, 0x77, 0x77), TRUE);
//		DrawBox(Define::WIN_SIZEX - HALFX * (m_ANIME_END_TIMES[0] - m_counter) / (m_ANIME_END_TIMES[0] / 6), TOPY, Define::WIN_SIZEX, Define::WIN_SIZEY * 5 / 8, GetColor(0x77, 0x77, 0x77), TRUE);
//	}
//	else
//	{
//		DrawBox(0, Define::WIN_SIZEY * 3 / 8, Define::WIN_SIZEX, Define::WIN_SIZEY * 5 / 8, GetColor(0x77, 0x77, 0x77), TRUE);
//
//		//時間に応じて文字を薄くする
//		if (m_ANIME_END_TIMES[0] * 2 / 6 > m_counter) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (m_counter - m_ANIME_END_TIMES[0] / 6) / (m_ANIME_END_TIMES[0] / 6)); }
//		else if (m_ANIME_END_TIMES[0] * 4 / 6 < m_counter) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (m_ANIME_END_TIMES[0] * 5 / 6 - m_counter) / (m_ANIME_END_TIMES[0] / 6)); }
//
//		//表示する
//		DrawFormatStringToHandle(HALFX - GetDrawStringWidthToHandle("!!!勝負開始!!!", 15, m_font_32) / 2, Define::WIN_SIZEY * 27 / 64, GetColor(0, 0, 0), m_font_32, "!!!勝負開始!!!");
//		DrawFormatStringToHandle(HALFX - GetDrawStringWidthToHandle("あなたは後手です", 17, m_font_32) / 2, Define::WIN_SIZEY * 33 / 64, GetColor(0, 0, 0), m_font_32, "あなたは後手です");
//		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
//	}
//
//	if (m_counter == 1) { PlaySoundMem(m_sound_start, DX_PLAYTYPE_BACK); }
//}
//
//void GameAnime::m_drawAnime02() const
//{
//}
//
//void GameAnime::m_drawAnime03() const
//{
//	const int BOX_COLOR = GetColor(0x77, 0x77, 0x77);
//	const int TOPY = Define::WIN_SIZEY * 3 / 8;
//	const int BOTTOMY = Define::WIN_SIZEY * 5 / 8;
//	const int HALFX = Define::WIN_SIZEX / 2;
//
//	const int TIME_LINE_STARTED = 30;
//	const int TIME_CHAR_APPEAR = TIME_LINE_STARTED;
//	//線を引く
//	if (m_counter < m_ANIME_END_TIMES[0] / 6)
//	{
//		DrawBox(0, TOPY, HALFX * m_counter / (m_ANIME_END_TIMES[0] / 6), BOTTOMY, BOX_COLOR, TRUE);
//		DrawBox(Define::WIN_SIZEX - HALFX * m_counter / (m_ANIME_END_TIMES[0] / 6), TOPY, Define::WIN_SIZEX, BOTTOMY, BOX_COLOR, TRUE);
//	}
//	else if (m_counter > m_ANIME_END_TIMES[0] * 5 / 6)
//	{
//		DrawBox(0, TOPY, HALFX * (m_ANIME_END_TIMES[0] - m_counter) / (m_ANIME_END_TIMES[0] / 6), Define::WIN_SIZEY * 5 / 8, GetColor(0x77, 0x77, 0x77), TRUE);
//		DrawBox(Define::WIN_SIZEX - HALFX * (m_ANIME_END_TIMES[0] - m_counter) / (m_ANIME_END_TIMES[0] / 6), TOPY, Define::WIN_SIZEX, Define::WIN_SIZEY * 5 / 8, GetColor(0x77, 0x77, 0x77), TRUE);
//	}
//	else
//	{
//		DrawBox(0, Define::WIN_SIZEY * 3 / 8, Define::WIN_SIZEX, Define::WIN_SIZEY * 5 / 8, GetColor(0x77, 0x77, 0x77), TRUE);
//
//		//時間に応じて文字を薄くする
//		if (m_ANIME_END_TIMES[0] * 2 / 6 > m_counter) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (m_counter - m_ANIME_END_TIMES[0] / 6) / (m_ANIME_END_TIMES[0] / 6)); }
//		else if (m_ANIME_END_TIMES[0] * 4 / 6 < m_counter) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (m_ANIME_END_TIMES[0] * 5 / 6 - m_counter) / (m_ANIME_END_TIMES[0] / 6)); }
//
//		//表示する
//		DrawFormatStringToHandle(HALFX - GetDrawStringWidthToHandle("あなたの勝ちです", 17, m_font_32) / 2, Define::WIN_SIZEY * 30 / 64, GetColor(0, 0, 0), m_font_32, "あなたの勝ちです");
//		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
//	}
//}
//
////行動アニメーションはじめ
//void GameAnime::m_drawAnime04() const //再生時間を過ぎたなら他のアニメーションに移行する変則処理
//{
//	//両となり
//	DrawBox(0, 0, (Define::WIN_SIZEX * 9 / 32) * m_counter / m_ANIME_END_TIMES[4], Define::WIN_SIZEY, GetColor(0xa3, 0xa3, 0xa3), TRUE);
//	DrawBox(Define::WIN_SIZEX, 0, Define::WIN_SIZEX - (Define::WIN_SIZEX * 9 / 32) * m_counter / m_ANIME_END_TIMES[4], Define::WIN_SIZEY, GetColor(0xa3, 0xa3, 0xa3), TRUE);
//
//	const int BOX_X = Define::WIN_SIZEX * 13 / 16;
//	const int BOX_Y = Define::WIN_SIZEY * 14 / 16;
//	const int BOX_COLOR = GetColor(0x67, 0x67, 0x67);
//	const int CENTER_X = Define::WIN_SIZEX / 2;
//	const int CENTER_Y = Define::WIN_SIZEY / 2;
//
//	//最初の時間で広がる四角のアニメーション
//	int temp_box_x = BOX_X * m_counter / m_ANIME_END_TIMES[4];
//	int temp_box_y = BOX_Y * m_counter / m_ANIME_END_TIMES[4];
//	DrawBox(CENTER_X - temp_box_x / 2, CENTER_Y - temp_box_y / 2, CENTER_X + temp_box_x / 2, CENTER_Y + temp_box_y / 2, BOX_COLOR, TRUE);
//}
//
////攻撃アニメーション
//void GameAnime::m_drawAnime05() const
//{
//	//背景
//	m_drawAnimeAttackBack();
//
//	//時間
//	const int TIME_DISPLAY_HAND = m_ANIME_END_TIMES[5] / 6;						//この時間までに手を表示する
//	const int TIME_START_ATTACK = m_ANIME_END_TIMES[5] * 3 / 12;				//この時間から攻撃開始
//	const int TIME_END_ATTACK = m_ANIME_END_TIMES[5] * 8 / 12;					//この時間で攻撃終了
//	const int TIME_ATTCK = TIME_END_ATTACK - TIME_START_ATTACK;
//	const int TIME_HITTING = m_ANIME_END_TIMES[5] * 23 / 48;					//攻撃が当たった瞬間
//	const int TIME_SWAP_START = m_ANIME_END_TIMES[5] * 28 / 48;
//	const int TIME_SWAP_END = m_ANIME_END_TIMES[5] * 35 / 48;
//	const int TIME_END_HAND = m_ANIME_END_TIMES[5] - m_ANIME_END_TIMES[5] / 6;	//この時間から手を消す
//
//	//透過処理
//	if (m_counter < TIME_DISPLAY_HAND) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * m_counter / TIME_DISPLAY_HAND); }
//	else if (TIME_END_HAND < m_counter) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 255 * (m_counter - TIME_END_HAND) / (m_ANIME_END_TIMES[5] - TIME_END_HAND)); }
//
//	//手の表示
//	if (TIME_HITTING > m_counter) {
//		m_drawAnimeAttackOldHand();
//	}
//	else {
//		m_drawAnimeAttackHitHand(TIME_SWAP_START, TIME_SWAP_END);
//	}
//
//	//文字の表示
//	m_drawAnimeAttackChar();
//
//	//ここまで
//	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
//
//	//攻撃アニメーション
//	if (m_counter > TIME_START_ATTACK) {
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
//
//		if (m_hand_cmd == COMMAND_1_TO_1) //１～１
//		{
//			int pos = (int)(2.0 * Define::WIN_SIZEY * pow(((double)m_counter - TIME_START_ATTACK) / TIME_ATTCK, 2));
//			if (m_old.turn == true && m_old.player1.first < 6) {
//				DrawRotaGraph(Define::WIN_SIZEX * 19 / 64, Define::WIN_SIZEY * 12 / 16 - pos, 1.0, 0.0, m_gr_hand[m_old.player1.first], TRUE, TRUE, FALSE);
//			}
//			else if (m_old.turn == false && m_old.player2.first < 6) {
//				DrawRotaGraph(Define::WIN_SIZEX * 19 / 64, Define::WIN_SIZEY * 4 / 16 + pos, 1.0, 0.0, m_gr_hand[m_old.player2.first], TRUE, TRUE, TRUE);
//			}
//		}
//		else if (m_hand_cmd == COMMAND_1_TO_2) //１～２
//		{
//			int posy = (int)(2.0 * Define::WIN_SIZEY * pow(((double)m_counter - TIME_START_ATTACK) / TIME_ATTCK, 2));
//			int posx = (int)(2.0 * Define::WIN_SIZEY * pow(((double)m_counter - TIME_START_ATTACK) / TIME_ATTCK, 2) * 1.55);
//			if (m_old.turn == true && m_old.player1.first < 6) {
//				DrawRotaGraph(Define::WIN_SIZEX * 19 / 64 + posx, Define::WIN_SIZEY * 12 / 16 - posy, 1.0, atan2(1.55, 1), m_gr_hand[m_old.player1.first], TRUE, TRUE, FALSE);
//			}
//			else if (m_old.turn == false && m_old.player2.first < 6) {
//				DrawRotaGraph(Define::WIN_SIZEX * 19 / 64 + posx, Define::WIN_SIZEY * 4 / 16 + posy, 1.0, atan2(-1.55, 1), m_gr_hand[m_old.player2.first], TRUE, TRUE, TRUE);
//			}
//		}
//		else if (m_hand_cmd == COMMAND_2_TO_1) //２～１
//		{
//			int posy = (int)(2.0 * Define::WIN_SIZEY * pow(((double)m_counter - TIME_START_ATTACK) / TIME_ATTCK, 2));
//			int posx = (int)(2.0 * Define::WIN_SIZEY * pow(((double)m_counter - TIME_START_ATTACK) / TIME_ATTCK, 2) * 1.55);
//			if (m_old.turn == true && m_old.player1.second < 6) {
//				DrawRotaGraph(Define::WIN_SIZEX * 45 / 64 - posx, Define::WIN_SIZEY * 12 / 16 - posy, 1.0, atan2(1.55, -1), m_gr_hand[m_old.player1.second], TRUE, FALSE, TRUE);
//			}
//			else if (m_old.turn == false && m_old.player2.second < 6) {
//				DrawRotaGraph(Define::WIN_SIZEX * 45 / 64 - posx, Define::WIN_SIZEY * 4 / 16 + posy, 1.0, atan2(-1.55, -1), m_gr_hand[m_old.player2.second], TRUE, FALSE, FALSE);
//			}
//		}
//		else if (m_hand_cmd == COMMAND_2_TO_2) //２～２
//		{
//			int pos = (int)(2.0 * Define::WIN_SIZEY * pow(((double)m_counter - TIME_START_ATTACK) / TIME_ATTCK, 2));
//			if (m_old.turn == true && m_old.player1.second < 6) {
//				DrawRotaGraph(Define::WIN_SIZEX * 45 / 64, Define::WIN_SIZEY * 12 / 16 - pos, 1.0, 0.0, m_gr_hand[m_old.player1.second], TRUE, FALSE, FALSE);
//			}
//			else if (m_old.turn == false && m_old.player2.second < 6) {
//				DrawRotaGraph(Define::WIN_SIZEX * 45 / 64, Define::WIN_SIZEY * 4 / 16 + pos, 1.0, 0.0, m_gr_hand[m_old.player2.second], TRUE, FALSE, TRUE);
//			}
//		}
//
//		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
//	}
//
//	//音を鳴らす
//	if (m_counter == TIME_HITTING) { PlaySoundMem(m_sound_attack, DX_PLAYTYPE_BACK); }
//}
//
////自傷アニメーション
//void GameAnime::m_drawAnime06() const
//{
//	//背景
//	m_drawAnimeAttackBack();
//
//	//時間
//	const int TIME_DISPLAY_HAND = m_ANIME_END_TIMES[6] / 6;						//この時間までに手を表示する
//	const int TIME_START_ATTACK = m_ANIME_END_TIMES[6] * 3 / 12;				//この時間から攻撃開始
//	const int TIME_END_ATTACK = m_ANIME_END_TIMES[6] * 8 / 12;					//この時間で攻撃終了
//	const int TIME_ATTACK = TIME_END_ATTACK - TIME_START_ATTACK;
//	const int TIME_HITTING = m_ANIME_END_TIMES[6] * 23 / 48;					//攻撃が当たった瞬間
//	const int TIME_SWAP_START = m_ANIME_END_TIMES[6] * 28 / 48;
//	const int TIME_SWAP_END = m_ANIME_END_TIMES[6] * 35 / 48;
//	const int TIME_END_HAND = m_ANIME_END_TIMES[6] - m_ANIME_END_TIMES[6] / 6;	//この時間から手を消す
//
//	//透過処理
//	if (m_counter < TIME_DISPLAY_HAND) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * m_counter / TIME_DISPLAY_HAND); }
//	else if (TIME_END_HAND < m_counter) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 255 * (m_counter - TIME_END_HAND) / (m_ANIME_END_TIMES[5] - TIME_END_HAND)); }
//
//	//手の描画
//	if (m_counter < TIME_HITTING) { m_drawAnimeAttackOldHand(); }
//	else { m_drawAnimeSelfAttackHitHand(TIME_SWAP_START, TIME_SWAP_END); }
//
//	//文字
//	m_drawAnimeSelfAttackChar();
//
//	//ここまで
//	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
//
//	//攻撃アニメーション
//	if (m_counter > TIME_START_ATTACK) {
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
//
//		//位置移動
//		int posx = (int)(2.0 * Define::WIN_SIZEY * pow(((double)m_counter - TIME_START_ATTACK) / TIME_ATTACK, 2) * 1.55);
//		if (m_hand_cmd == COMMAND_2_SELF) { posx = -1 * posx; }
//
//		//攻撃モーション
//		if (m_hand_cmd == COMMAND_1_SELF && m_old.turn == true && m_old.player1.first < 6) {
//			DrawRotaGraph(Define::WIN_SIZEX * 19 / 64 + posx, Define::WIN_SIZEY * 12 / 16, 1.0, Define::PI / 2, m_gr_hand[m_old.player1.first], TRUE, TRUE, FALSE);
//		}
//		else if (m_hand_cmd == COMMAND_2_SELF && m_old.turn == true && m_old.player1.second < 6) {
//			DrawRotaGraph(Define::WIN_SIZEX * 45 / 64 + posx, Define::WIN_SIZEY * 12 / 16, 1.0, -Define::PI / 2, m_gr_hand[m_old.player1.second], TRUE, FALSE, FALSE);
//		}
//		else if (m_hand_cmd == COMMAND_1_SELF && m_old.turn == false && m_old.player2.first < 6) {
//			DrawRotaGraph(Define::WIN_SIZEX * 19 / 64 + posx, Define::WIN_SIZEY * 4 / 16, 1.0, -Define::PI / 2, m_gr_hand[m_old.player2.first], TRUE, TRUE, TRUE);
//		}
//		else if (m_hand_cmd == COMMAND_2_SELF && m_old.turn == false && m_old.player2.second < 6) {
//			DrawRotaGraph(Define::WIN_SIZEX * 45 / 64 + posx, Define::WIN_SIZEY * 4 / 16, 1.0, Define::PI / 2, m_gr_hand[m_old.player2.second], TRUE, FALSE, TRUE);
//		}
//
//		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
//	}
//
//	//音を鳴らす
//	if (m_counter == TIME_HITTING) { PlaySoundMem(m_sound_attack, DX_PLAYTYPE_BACK); }
//}
//
////采配アニメーション
//void GameAnime::m_drawAnime07() const
//{
//	m_drawAnimeAttackBack();
//
//	if (m_counter < m_ANIME_END_TIMES[7] * 2 / 5) {
//		int pos = (int)(Define::WIN_SIZEX * 13.0 / 64.0 * pow((double)m_counter / ((double)m_ANIME_END_TIMES[7] * 2.0 / 5.0), 2.0));
//		int pos1 = (m_old.turn == true) ? pos : 0;
//		int pos2 = (m_old.turn == false) ? pos : 0;
//		DrawRotaGraph(Define::WIN_SIZEX * 19 / 64 + pos1, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[m_old.player1.first < 6 ? m_old.player1.first : 0], TRUE, TRUE, FALSE);
//		DrawRotaGraph(Define::WIN_SIZEX * 45 / 64 - pos1, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[m_old.player1.second < 6 ? m_old.player1.second : 0], TRUE, FALSE, FALSE);
//		DrawRotaGraph(Define::WIN_SIZEX * 19 / 64 + pos2, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[m_old.player2.first < 6 ? m_old.player2.first : 0], TRUE, TRUE, TRUE);
//		DrawRotaGraph(Define::WIN_SIZEX * 45 / 64 - pos2, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[m_old.player2.second < 6 ? m_old.player2.second : 0], TRUE, FALSE, TRUE);
//	}
//	else if (m_counter < m_ANIME_END_TIMES[7] * 4 / 5) {
//		int pos = (int)(-Define::WIN_SIZEX * 13.0 / 64.0 + (int)(Define::WIN_SIZEX * 13.0 / 64.0 * pow(((double)m_counter - ((double)m_ANIME_END_TIMES[7] * 2.0 / 5.0)) / ((double)m_ANIME_END_TIMES[7] * 2.0 / 5.0), 2)));
//		int pos1 = (m_old.turn == true) ? pos : 0;
//		int pos2 = (m_old.turn == false) ? pos : 0;
//		DrawRotaGraph(Define::WIN_SIZEX * 19 / 64 - pos1, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[m_old.player1.first < 6 ? m_new.player1.first : 0], TRUE, TRUE, FALSE);
//		DrawRotaGraph(Define::WIN_SIZEX * 45 / 64 + pos1, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[m_old.player1.second < 6 ? m_new.player1.second : 0], TRUE, FALSE, FALSE);
//		DrawRotaGraph(Define::WIN_SIZEX * 19 / 64 - pos2, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[m_old.player2.first < 6 ? m_new.player2.first : 0], TRUE, TRUE, TRUE);
//		DrawRotaGraph(Define::WIN_SIZEX * 45 / 64 + pos2, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[m_old.player2.second < 6 ? m_new.player2.second : 0], TRUE, FALSE, TRUE);
//	}
//	else {
//		DrawRotaGraph(Define::WIN_SIZEX * 19 / 64, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[m_old.player1.first < 6 ? m_new.player1.first : 0], TRUE, TRUE, FALSE);
//		DrawRotaGraph(Define::WIN_SIZEX * 45 / 64, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[m_old.player1.second < 6 ? m_new.player1.second : 0], TRUE, FALSE, FALSE);
//		DrawRotaGraph(Define::WIN_SIZEX * 19 / 64, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[m_old.player2.first < 6 ? m_new.player2.first : 0], TRUE, TRUE, TRUE);
//		DrawRotaGraph(Define::WIN_SIZEX * 45 / 64, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[m_old.player2.second < 6 ? m_new.player2.second : 0], TRUE, FALSE, TRUE);
//	}
//
//	//文字の表示
//	std::string str = (m_old.turn == true) ? "あなたの采配" : "敵の采配";
//	DrawFormatStringToHandle((Define::WIN_SIZEX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32)) / 2, Define::WIN_SIZEY * 31 / 64, GetColor(0, 0, 0), m_font_32, str.c_str());
//
//	if (m_old.turn == true) { str = "[ " + std::to_string(m_old.player1.first) + " , " + std::to_string(m_old.player1.second) + " ] → [ " + std::to_string(m_new.player1.first) + " , " + std::to_string(m_new.player1.second) + " ]"; }
//	else { str = "[ " + std::to_string(m_old.player2.first) + " , " + std::to_string(m_old.player2.second) + " ] → [ " + std::to_string(m_new.player2.first) + " , " + std::to_string(m_new.player2.second) + " ]"; }
//	int posy = (m_old.turn == true) ? Define::WIN_SIZEY * 55 / 64 : Define::WIN_SIZEY * 5 / 64;
//	DrawFormatStringToHandle((Define::WIN_SIZEX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32)) / 2, posy, GetColor(0, 0, 0), m_font_32, str.c_str());
//
//	//音を鳴らす
//	if (m_counter == m_ANIME_END_TIMES[7] * 2 / 5) { PlaySoundMem(m_sound_attack, DX_PLAYTYPE_BACK); }
//}
//
////各種行動アニメーション終わり
//void GameAnime::m_drawAnime08() const
//{
//	//両となり
//	DrawBox(0, 0, (Define::WIN_SIZEX * 9 / 32) * (m_ANIME_END_TIMES[8] - m_counter) / m_ANIME_END_TIMES[8], Define::WIN_SIZEY, GetColor(0xa3, 0xa3, 0xa3), TRUE);
//	DrawBox(Define::WIN_SIZEX, 0, Define::WIN_SIZEX - (Define::WIN_SIZEX * 9 / 32) * (m_ANIME_END_TIMES[8] - m_counter) / m_ANIME_END_TIMES[8], Define::WIN_SIZEY, GetColor(0xa3, 0xa3, 0xa3), TRUE);
//
//	const int BOX_X = Define::WIN_SIZEX * 13 / 16;
//	const int BOX_Y = Define::WIN_SIZEY * 14 / 16;
//	const int BOX_COLOR = GetColor(0x67, 0x67, 0x67);
//	const int CENTER_X = Define::WIN_SIZEX / 2;
//	const int CENTER_Y = Define::WIN_SIZEY / 2;
//
//	//最初の時間で広がる四角のアニメーション
//	int temp_box_x = BOX_X * (m_ANIME_END_TIMES[8] - m_counter) / m_ANIME_END_TIMES[8];
//	int temp_box_y = BOX_Y * (m_ANIME_END_TIMES[8] - m_counter) / m_ANIME_END_TIMES[8];
//	DrawBox(CENTER_X - temp_box_x / 2, CENTER_Y - temp_box_y / 2, CENTER_X + temp_box_x / 2, CENTER_Y + temp_box_y / 2, BOX_COLOR, TRUE);
//}
//
//
////アニメーションの処理をまとめた関数
//void GameAnime::m_drawAnimeAttackBack() const
//{
//	DrawBox(Define::WIN_SIZEX * 9 / 32, 0, 0, Define::WIN_SIZEY, GetColor(0xa3, 0xa3, 0xa3), TRUE);
//	DrawBox(Define::WIN_SIZEX * 23 / 32, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(0xa3, 0xa3, 0xa3), TRUE);
//
//	const int BOX_X = Define::WIN_SIZEX * 13 / 16;
//	const int BOX_Y = Define::WIN_SIZEY * 14 / 16;
//	const int BOX_COLOR = GetColor(0x67, 0x67, 0x67);
//	const int CENTER_X = Define::WIN_SIZEX / 2;
//	const int CENTER_Y = Define::WIN_SIZEY / 2;
//	DrawBox(CENTER_X - BOX_X / 2, CENTER_Y - BOX_Y / 2, CENTER_X + BOX_X / 2, CENTER_Y + BOX_Y / 2, BOX_COLOR, TRUE);
//}
//
//void GameAnime::m_drawAnimeAttackOldHand() const
//{
//	DrawRotaGraph(Define::WIN_SIZEX * 19 / 64, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[m_old.player1.first < 6 ? m_old.player1.first : 0], TRUE, TRUE, FALSE);
//	DrawRotaGraph(Define::WIN_SIZEX * 45 / 64, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[m_old.player1.second < 6 ? m_old.player1.second : 0], TRUE, FALSE, FALSE);
//	DrawRotaGraph(Define::WIN_SIZEX * 19 / 64, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[m_old.player2.first < 6 ? m_old.player2.first : 0], TRUE, TRUE, TRUE);
//	DrawRotaGraph(Define::WIN_SIZEX * 45 / 64, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[m_old.player2.second < 6 ? m_old.player2.second : 0], TRUE, FALSE, TRUE);
//}
//
//void GameAnime::m_drawAnimeAttackHitHand(int _start_cnt, int _end_cnt) const
//{
//	int res_my1 = 0, res_my2 = 0, res_ene1 = 0, res_ene2 = 0;
//
//	if (m_hand_cmd == COMMAND_1_TO_1 || m_hand_cmd == COMMAND_2_TO_1 || m_hand_cmd == COMMAND_1_TO_2 || m_hand_cmd == COMMAND_2_TO_2) 
//	{
//		if ((m_hand_cmd == COMMAND_1_TO_1 && m_old.turn == false) || (m_hand_cmd == COMMAND_2_TO_1 && m_old.turn == false))
//		{//自分の１が攻撃される時
//			res_my1 = (m_hand_cmd == COMMAND_1_TO_1) ? (m_old.player1.first + m_old.player2.first) : (m_old.player1.first + m_old.player2.second);
//			res_my1 = (res_my1 >= 5) ? ((m_mod_rule == true) ? res_my1 % 5 : 0) : res_my1;
//			res_my2 = m_old.player1.second < 5 ? m_old.player1.second : 0;
//			res_ene1 = m_old.player2.first < 5 ? m_old.player2.first : 0;
//			res_ene2 = m_old.player2.second < 5 ? m_old.player2.second : 0;
//		}
//		else if ((m_hand_cmd == COMMAND_1_TO_1 && m_old.turn == true) || (m_hand_cmd == COMMAND_2_TO_1 && m_old.turn == true))
//		{//相手の１を攻撃するとき
//			res_my1 = m_old.player1.first < 5 ? m_old.player1.first : 0;
//			res_my2 = m_old.player1.second < 5 ? m_old.player1.second : 0;
//			res_ene1 = (m_hand_cmd == COMMAND_1_TO_1) ? (m_old.player1.first + m_old.player2.first) : (m_old.player1.second + m_old.player2.first);
//			res_ene1 = (res_ene1 >= 5) ? ((m_mod_rule == true) ? res_ene1 % 5 : 0) : res_ene1;
//			res_ene2 = m_old.player2.second < 5 ? m_old.player2.second : 0;
//		}
//		else if ((m_hand_cmd == COMMAND_1_TO_2 && m_old.turn == false) || (m_hand_cmd == COMMAND_2_TO_2 && m_old.turn == false)) 
//		{//自分の２が攻撃されるとき
//			res_my1 = m_old.player1.first < 5 ? m_old.player1.first : 0;
//			res_my2 = (m_hand_cmd == COMMAND_1_TO_2) ? (m_old.player1.second + m_old.player2.first) : (m_old.player1.second + m_old.player2.second);
//			res_my2 = (res_my2 >= 5) ? ((m_mod_rule == true) ? res_my2 % 5 : 0) : res_my2;
//			res_ene1 = m_old.player2.first < 5 ? m_old.player2.first : 0;
//			res_ene2 = m_old.player2.second < 5 ? m_old.player2.second : 0;
//		}
//		else if ((m_hand_cmd == COMMAND_1_TO_2 && m_old.turn == true) || (m_hand_cmd == COMMAND_2_TO_2 && m_old.turn == true)) 
//		{//相手の２を攻撃するとき
//			res_my1 = m_old.player1.first < 5 ? m_old.player1.first : 0;
//			res_my2 = m_old.player1.second < 5 ? m_old.player1.second : 0;
//			res_ene1 = m_old.player2.first < 5 ? m_old.player2.first : 0;
//			res_ene2 = (m_hand_cmd == COMMAND_1_TO_2) ? (m_old.player1.first + m_old.player2.second) : (m_old.player1.second + m_old.player2.second);
//			res_ene2 = (res_ene2 >= 5) ? ((m_mod_rule == true) ? res_ene2 % 5 : 0) : res_ene2;
//		}
//
//		//表示位置をスワップする処理
//		int posx = 0;
//		if (_start_cnt < m_counter ) {
//			posx = Define::WIN_SIZEX * 26 / 64 * (m_counter - _start_cnt) / (_end_cnt - _start_cnt);
//			if (_end_cnt < m_counter) { posx = Define::WIN_SIZEX * 26 / 64; }
//		}
//
//		int pos_pl1 = (res_my1 > res_my2) ? posx : 0;
//		bool turn_pl1 = (res_my1 > res_my2 && (_start_cnt + _end_cnt) / 2 < m_counter);
//		int pos_pl2 = (res_ene1 > res_ene2) ? posx : 0;
//		bool turn_pl2 = ((res_ene1 > res_ene2) && (_start_cnt + _end_cnt) / 2 < m_counter);
//
//		//手の描画
//		DrawRotaGraph(Define::WIN_SIZEX * 19 / 64 + pos_pl1, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[res_my1], TRUE, !turn_pl1, FALSE);
//		DrawRotaGraph(Define::WIN_SIZEX * 45 / 64 - pos_pl1, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[res_my2], TRUE, turn_pl1, FALSE);
//		DrawRotaGraph(Define::WIN_SIZEX * 19 / 64 + pos_pl2, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[res_ene1], TRUE, !turn_pl2, TRUE);
//		DrawRotaGraph(Define::WIN_SIZEX * 45 / 64 - pos_pl2, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[res_ene2], TRUE, turn_pl2, TRUE);
//	}
//	else {
//		const int HALFX = Define::WIN_SIZEX / 2;
//		std::string str = "コマンドが違います-" + std::to_string(m_hand_cmd);
//		DrawFormatStringToHandle(HALFX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 20 / 64, GetColor(0, 0, 0), m_font_32, str.c_str());
//	}
//}
//
//void GameAnime::m_drawAnimeSelfAttackHitHand(int _start_cnt, int _end_cnt) const
//{
//	int res_my1 = m_old.player1.first;
//	int res_my2 = m_old.player1.second;
//	int res_ene1 = m_old.player2.first;
//	int res_ene2 = m_old.player2.second;
//
//	if (m_hand_cmd == COMMAND_1_SELF && m_old.turn == true)
//	{//自分の１が攻撃する時
//		res_my2 = m_old.player1.first + m_old.player1.second;
//		res_my2 = (res_my2 >= 5) ? ((m_mod_rule == true) ? res_my2 % 5 : 0) : res_my2;
//	}
//	else if (m_hand_cmd == COMMAND_1_SELF && m_old.turn == false)
//	{//相手の１が攻撃するとき
//		res_ene2 = m_old.player2.first + m_old.player2.second;
//		res_ene2 = (res_ene2 >= 5) ? ((m_mod_rule == true) ? res_ene2 % 5 : 0) : res_ene2;
//	}
//	else if (m_hand_cmd == COMMAND_2_SELF && m_old.turn == true)
//	{//自分の２が攻撃するとき
//		res_my1 = m_old.player1.first + m_old.player1.second;
//		res_my1 = (res_my1 >= 5) ? ((m_mod_rule == true) ? res_my1 % 5 : 0) : res_my1;
//	}
//	else if (m_hand_cmd == COMMAND_2_SELF && m_old.turn == false)
//	{//相手の２が攻撃するとき
//		res_ene1 = m_old.player2.first + m_old.player2.second;
//		res_ene1 = (res_ene1 >= 5) ? ((m_mod_rule == true) ? res_ene1 % 5 : 0) : res_ene1;
//	}
//
//	//表示位置をスワップする処理
//	int posx = 0;
//	if (_start_cnt < m_counter) {
//		posx = Define::WIN_SIZEX * 26 / 64 * (m_counter - _start_cnt) / (_end_cnt - _start_cnt);
//		if (_end_cnt < m_counter) { posx = Define::WIN_SIZEX * 26 / 64; }
//	}
//
//	int pos_pl1 = (res_my1 > res_my2) ? posx : 0;
//	bool turn_pl1 = (res_my1 > res_my2 && (_start_cnt + _end_cnt) / 2 < m_counter);
//	int pos_pl2 = (res_ene1 > res_ene2) ? posx : 0;
//	bool turn_pl2 = ((res_ene1 > res_ene2) && (_start_cnt + _end_cnt) / 2 < m_counter);
//
//	//手の描画
//	DrawRotaGraph(Define::WIN_SIZEX * 19 / 64 + pos_pl1, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[res_my1 < 6 ? res_my1 : 0], TRUE, !turn_pl1, FALSE);
//	DrawRotaGraph(Define::WIN_SIZEX * 45 / 64 - pos_pl1, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[res_my2 < 6 ? res_my2 : 0], TRUE, turn_pl1, FALSE);
//	DrawRotaGraph(Define::WIN_SIZEX * 19 / 64 + pos_pl2, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[res_ene1 < 6 ? res_ene1 : 0], TRUE, !turn_pl2, TRUE);
//	DrawRotaGraph(Define::WIN_SIZEX * 45 / 64 - pos_pl2, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[res_ene2 < 6 ? res_ene2 : 0], TRUE, turn_pl2, TRUE);
//}
//
//void GameAnime::m_drawAnimeAttackChar() const
//{
//	int posx = 0, posy = 0, atk = 0, hit = 0, res = 0;
//
//	//x座標の算出
//	if (m_hand_cmd == COMMAND_1_TO_1 || m_hand_cmd == COMMAND_2_TO_1) {
//		posx = Define::WIN_SIZEX * 18 / 64 - (GetDrawStringWidthToHandle("0 + 0 → 0", 11, m_font_32)) / 2;
//	}
//	else {
//		posx = Define::WIN_SIZEX * 46 / 64 - (GetDrawStringWidthToHandle("0 + 0 → 0", 11, m_font_32)) / 2;
//	}
//
//	//y座標の算出
//	if (m_old.turn == true) {
//		posy = Define::WIN_SIZEY * 5 / 64;
//	}
//	else {
//		posy = Define::WIN_SIZEY * 55 / 64;
//	}
//
//	//計算式
//	if (m_hand_cmd == COMMAND_1_TO_1) {
//		atk = m_old.turn ? m_old.player1.first : m_old.player2.first;
//		hit = m_old.turn ? m_old.player2.first : m_old.player1.first;
//	}
//	else if (m_hand_cmd == COMMAND_1_TO_2) {
//		atk = m_old.turn ? m_old.player1.first : m_old.player2.first;
//		hit = m_old.turn ? m_old.player2.second : m_old.player1.second;
//	}
//	else if (m_hand_cmd == COMMAND_2_TO_1) {
//		atk = m_old.turn ? m_old.player1.second : m_old.player2.second;
//		hit = m_old.turn ? m_old.player2.first : m_old.player1.first;
//	}
//	else if (m_hand_cmd == COMMAND_2_TO_2) {
//		atk = m_old.turn ? m_old.player1.second : m_old.player2.second;
//		hit = m_old.turn ? m_old.player2.second : m_old.player1.second;
//	}
//
//	res = m_mod_rule ? ((atk + hit) % 5) : (atk + hit);
//	res = res >= 5 ? 0 : res;
//
//	//描画
//	std::string str = std::to_string(atk) + " + " + std::to_string(hit) + " → " + std::to_string(res);
//	DrawFormatStringToHandle(posx, posy, GetColor(0, 0, 0), m_font_32, str.c_str());
//
//	//どっちが攻撃中なのか表示
//	const int HALFX = Define::WIN_SIZEX / 2;
//	str = (m_old.turn == true) ? "あなたの攻撃！" : "敵の攻撃！";
//	DrawFormatStringToHandle(HALFX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 31 / 64, GetColor(0, 0, 0), m_font_32, str.c_str());
//}
//
//void GameAnime::m_drawAnimeSelfAttackChar() const
//{
//	std::string str;
//	str = (m_old.turn == true) ? "あなたの自傷行動" : "敵の自傷行動";
//	DrawFormatStringToHandle((Define::WIN_SIZEX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32)) / 2, Define::WIN_SIZEY * 31 / 64, GetColor(0, 0, 0), m_font_32, str.c_str());
//
//	int posx = 0, posy = 0, atk = 0, hit = 0, res = 0;
//
//	//x座標の算出
//	if (m_hand_cmd == COMMAND_1_SELF) {
//		posx = Define::WIN_SIZEX * 46 / 64 - (GetDrawStringWidthToHandle("0 + 0 → 0", 11, m_font_32)) / 2;
//	}
//	else {
//		posx = Define::WIN_SIZEX * 18 / 64 - (GetDrawStringWidthToHandle("0 + 0 → 0", 11, m_font_32)) / 2;
//	}
//
//	//y座標の算出
//	if (m_old.turn != true) {
//		posy = Define::WIN_SIZEY * 5 / 64;
//	}
//	else {
//		posy = Define::WIN_SIZEY * 55 / 64;
//	}
//
//	//計算式
//	if (m_hand_cmd == COMMAND_1_SELF) {
//		atk = m_old.turn ? m_old.player1.first : m_old.player2.first;
//		hit = m_old.turn ? m_old.player1.second : m_old.player2.second;
//	}
//	else if (m_hand_cmd == COMMAND_2_SELF) {
//		atk = m_old.turn ? m_old.player1.second : m_old.player2.second;
//		hit = m_old.turn ? m_old.player1.first : m_old.player2.first;
//	}
//
//	res = m_mod_rule ? ((atk + hit) % 5) : (atk + hit);
//	res = res >= 5 ? 0 : res;
//
//	//描画
//	str = std::to_string(atk) + " + " + std::to_string(hit) + " → " + std::to_string(res);
//	DrawFormatStringToHandle(posx, posy, GetColor(0, 0, 0), m_font_32, str.c_str());
//}
