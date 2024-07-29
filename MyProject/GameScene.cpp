//#include "GameScene.h"
//#include "DxLib.h"
//#include "define.h"
//#include "Image.h"
//#include "Keyboard.h"
//#include "Font.h"
//#include "GameParam.h"
//#include "Sound.h"
//
//GameScene::GameScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) : AbstractScene(pScli, parameter)
//{
//	//シーンチェンジ時のエフェクト（フェードイン）を挿入する
//	m_sceneChange.init(1);
//
//	//盤面をパラメータを元に初期化する
//	m_initField(parameter);
//
//	//ゲーム開始のアニメーションを挿入する
//	if (m_field.turn == true) { m_anime.addAnime(0); }
//	else { m_anime.addAnime(1); }
//
//	//Logに現在の盤面を追加する
//	m_logDraw.pushLogByField(m_field);
//
//	//アニメーターにルールを伝える
//	m_anime.init(m_self_harm_rule, m_mod_rule);
//
//	//サウンドの読み込み
//	m_sound_hand_select = Sound::getIns()->myLoadSound("data/sound/hand_select.mp3");
//	m_sound_hand_cancel = Sound::getIns()->myLoadSound("data/sound/hand_cancel.mp3");
//}
//
//bool GameScene::update()
//{
//	//ESCが押されたら前のシーンに戻る
//	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1 && m_changescene_flag == false) 
//	{
//		m_changescene_flag = true;
//		m_sceneChange.init(0);
//		m_changescene_which = 1;
//	}
//
//	//選択中かどうかのフラグは基本オフ
//	m_is_selecting_now = false;
//
//	//シーンチェンジのエフェクトが終わったならメインの処理をする
//	if (m_sceneChange.update() == false)
//	{
//		//シーンチェンジならこれを行う
//		if (m_changescene_flag == true)
//		{
//			Parameter p;
//			if (m_changescene_which == 1)
//			{
//				mp_listenerInterface->deleteNowScene(p);
//			}
//			else if (m_changescene_which == 2)
//			{
//				Parameter p;
//
//				//ゲームの盤面を報告する
//				std::vector<MatchField> _temp_field_list;
//				m_logDraw.getFieldList(_temp_field_list);
//				p.setFieldParam(_temp_field_list);
//
//				//ゲームのルールを報告する
//				if (m_self_harm_rule == true) { p.setParam(GameParam::SELF_HARM_RULE, GameParam::TRUE_STATE); }
//				else { p.setParam(GameParam::SELF_HARM_RULE, GameParam::FALSE_STATE); }
//
//				if (m_mod_rule == true) { p.setParam(GameParam::MOD_RULE, GameParam::TRUE_STATE); }
//				else { p.setParam(GameParam::MOD_RULE, GameParam::FALSE_STATE); }
//
//				//れざるとシーンが何シーン分戻るのか
//				p.setParam(GameParam::RESULT_BACK_NUM, 2);
//
//				//シーンを追加する
//				mp_listenerInterface->addNewScene(enumScene::result, p);
//			}
//
//			return true;
//		}
//
//		//アニメーションの処理が終わったならメインの処理をする
//		if (m_anime.update() == false)
//		{
//			//ゲームが終了しているならアニメーションを再生する
//			if (m_field.isEndOfGame() == true)
//			{
//				m_changescene_flag = true;
//				m_sceneChange.init(0);
//				m_changescene_which = 2;
//			}
//			//引き分けの時アニメーションを再生する
//			else if (m_logDraw.update() == false) 
//			{
//				m_changescene_flag = true;
//				m_sceneChange.init(0);
//				m_changescene_which = 2;
//			}
//			//自分のターンの時
//			else if (m_field.turn == true)
//			{
//				//m_selectEnenmy();
//				m_is_selecting_now = true;
//				m_selectMove();
//			}
//			//敵のターンの時
//			else
//			{
//				m_selectEnenmy();
//			}
//		}
//		//アニメーションが終了したタイミングでフィールドの更新をかける
//		else if (m_anime.isEndTime() == true) {
//			m_pushNewFieldExecute();
//		}
//	}
//
//	return true;
//}
//
//void GameScene::draw() const
//{
//	//背景は白い色
//	DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(255, 255, 255), TRUE);
//
//	//腕を描画する
//	m_handDraw.draw(m_field, m_is_selecting_now, m_which_player, m_which_one_player1, m_which_one_player2, m_use_self_hurm, m_use_saihai);
//
//	//対戦ログを表示する
//	m_logDraw.draw(m_field, m_turn, m_player_is_first, m_mod_rule, m_self_harm_rule, m_enemy_level);
//
//	//各種アニメーションを上に表示
//	m_anime.draw();
//
//	//シーンチェンジ時のエフェクトを一番上に表示
//	m_sceneChange.draw();
//}
//
//void GameScene::receiveParameterInCaseOfDeleteScene(const Parameter& parameter)
//{
//}
//
//
//void GameScene::m_initField(const Parameter& _pram)
//{
//	//どっちのターンか調べる
//	if (_pram.getParam(GameParam::PLAYER_IS_FIRST) == GameParam::TRUE_STATE) {
//		m_logDraw.pushLog("貴方は先手です");
//		m_field.turn = m_player_is_first = true;
//	}
//	else {
//		m_logDraw.pushLog("貴方は後手です");
//		m_field.turn = m_player_is_first = false;
//	}
//
//	//CPU
//	if (_pram.getParam(GameParam::ENEMY_LEVEL) == GameParam::ENEMY_LEVEL_EASY) { m_enemy_level = 0; }
//	else if (_pram.getParam(GameParam::ENEMY_LEVEL) == GameParam::ENEMY_LEVEL_NORMAL) { m_enemy_level = 1; }
//	else if (_pram.getParam(GameParam::ENEMY_LEVEL) == GameParam::ENEMY_LEVEL_HARD) { m_enemy_level = 2; }
//	else { m_enemy_level = 3; }
//
//	//MODルールを使用するかどうかのフラグ
//	if (_pram.getParam(GameParam::MOD_RULE) == GameParam::TRUE_STATE) { m_mod_rule = true; }
//	else { m_mod_rule = false; }
//
//	//采配を利用するかどうかのフラグ
//	if (_pram.getParam(GameParam::SAIHAI_RULE) == GameParam::TRUE_STATE) {
//		m_field.player1_avatar_num = 1;
//		m_field.player2_avatar_num = 1;
//	}
//
//	//自傷ありかどうかのフラグ
//	if (_pram.getParam(GameParam::SELF_HARM_RULE) == GameParam::TRUE_STATE) { m_self_harm_rule = true; }
//	else { m_self_harm_rule = false; }
//}
//
//void GameScene::m_selectMove()
//{
//	//サウンドを鳴らす
//	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_C) == 1)
//	{
//		PlaySoundMem(m_sound_hand_select, DX_PLAYTYPE_BACK);
//	}
//	else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_X) == 1)
//	{
//		PlaySoundMem(m_sound_hand_cancel, DX_PLAYTYPE_BACK);
//	}
//
//	//自傷ルールがないならばフラグをオフにする
//	if (m_self_harm_rule == false) { m_use_self_hurm = false; }
//
//	//采配の処理
//	if (m_field.player1_avatar_num != 0) 
//	{
//		if (m_use_saihai % 3 == 1 || m_use_saihai % 3 == 2) 
//		{
//			//ｃキーが押されたらカウンタを回して終了
//			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_C) == 1) {
//				m_use_saihai++;
//				return;
//			}
//
//			//Xキーが押されたら終了
//			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_X) == 1) {
//				m_use_saihai = 0;
//				return;
//			}
//
//			//采配結果を算出
//			MatchField _low;
//			MatchField _high;
//			if (VariousFunctionsForMatchGame::executeCommand(VariousFunctionsForMatchGame::COMMAND_SAIHAI_LOW, m_field, _low, m_mod_rule, m_self_harm_rule) == false) {
//				m_use_saihai = 0;
//				return;
//			}
//			if (VariousFunctionsForMatchGame::executeCommand(VariousFunctionsForMatchGame::COMMAND_SAIHAI_HIGH, m_field, _high, m_mod_rule, m_self_harm_rule) == false) {
//				m_use_saihai = 0;
//				return;
//			}
//
//			//HIGHとLOWが等しいならば采配を終了
//			if (_low == _high && m_use_saihai % 3 == 2) {
//				m_use_saihai = 0;
//				return;
//			}
//
//			//Zキーが押されたら盤面を確定して終了
//			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1) 
//			{
//				//次盤面を生成してpush
//				m_pushNewFieldbyCommand((m_use_saihai % 3 == 1) ? VariousFunctionsForMatchGame::COMMAND_SAIHAI_LOW : VariousFunctionsForMatchGame::COMMAND_SAIHAI_HIGH);
//
//				//カウンタを全て初期化する
//				m_which_player = 0;
//				m_which_one_player1 = 0;
//				m_which_one_player2 = 0;
//				m_use_self_hurm = false;
//				m_use_saihai = 0;
//				return;
//			}
//
//			//采配選択中ならば後ろの処理をしない
//			return;
//		}
//		else if(m_use_saihai % 3 == 0)
//		{
//			//ｃキーが押されたらカウンタを回して終了
//			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_C) == 1) {
//				m_use_saihai++;
//				MatchField _low;
//				if (VariousFunctionsForMatchGame::executeCommand(VariousFunctionsForMatchGame::COMMAND_SAIHAI_LOW, m_field, _low, m_mod_rule, m_self_harm_rule) == false) { m_use_saihai = 0; }
//				return;
//			}
//		}
//		else { m_use_saihai = 0; }
//	}
//
//	//自分の腕を選択する状態ならば
//	if (m_which_player == 0)
//	{
//		m_use_self_hurm = false;
//
//		if (m_field.player1.first == 0) { //片手が存在しないならば固定
//			m_which_one_player1 = 1;
//		}
//		else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1) {	
//			//キー入力によって変化させる
//			m_which_one_player1++;
//		}
//
//		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1)
//		{
//			if ((m_field.player1.first != 0 && m_which_one_player1 % 2 == 0) || (m_field.player1.second != 0 && m_which_one_player1 % 2 == 1)) {
//				//ｚキーが押された時、それが0でないならば固定する
//				m_which_player = 1;
//
//				if (m_field.player2.first == 0) { m_which_one_player2 = 1; }
//			}
//		}
//	}
//	else {
//		//Xボタンでキャンセルする
//		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_X) == 1) {
//			m_which_player = 0;
//			m_which_one_player2 = 0;
//			m_use_self_hurm = false;
//			return;
//		}
//
//		//自傷ルール
//		if (m_self_harm_rule == true) 
//		{ 
//			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1) {
//				if (m_use_self_hurm == true) { 
//					m_use_self_hurm = false;
//					m_which_one_player2 = 1;
//				}
//				else {
//					if (m_which_one_player2 % 2 == 0) { 
//						m_use_self_hurm = true; 
//						if (m_field.player1.first == 0 || m_field.player1.second == 0) {
//							m_use_self_hurm = false;
//							m_which_one_player2 = 1;
//						}
//					}
//					else if (m_which_one_player2 % 2 == 1 && m_field.player2.first == 0 && (m_field.player1.first != 0 && m_field.player1.second != 0)) {
//						m_use_self_hurm = true;
//					}
//					else { m_which_one_player2 = 0; }
//				}
//			}
//			else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1) 
//			{
//				if (m_use_self_hurm == true) {
//					m_use_self_hurm = false;
//					m_which_one_player2 = 0;
//				}
//				else {
//					if (m_which_one_player2 % 2 == 1) { 
//						m_use_self_hurm = true; 
//						if (m_field.player1.first == 0 || m_field.player1.second == 0) {
//							m_use_self_hurm = false;
//							m_which_one_player2 = 0;
//						}
//					}
//					else { m_which_one_player2 = 1; }
//				}
//			}
//
//			//選択しているのが０ならば固定
//			if (m_field.player2.first == 0 && m_use_self_hurm == false) { 
//				m_which_one_player2 = 1;
//			}
//		}
//		//通常ルール
//		else { 
//			if (m_field.player2.first == 0) { //選択しているのが０ならば固定
//				m_which_one_player2 = 1;
//			}
//			else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1) {
//				m_which_one_player2++;
//			}
//		}
//
//		// Zキーが押されたならば決定
//		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1) { 
//
//			int temp_cmd = 0;
//
//			//０を攻撃しない
//			if ((m_field.player2.first != 0 && m_which_one_player2 % 2 == 0) || (m_field.player2.second != 0 && m_which_one_player2 % 2 == 1))
//			{
//				//コマンドを求める
//				if (m_use_self_hurm == true) {
//					if (m_which_one_player1 % 2 == 0) { temp_cmd = VariousFunctionsForMatchGame::COMMAND_1_SELF; }
//					else { temp_cmd = VariousFunctionsForMatchGame::COMMAND_2_SELF; }
//				}
//				else if (m_which_one_player2 % 2 == 0) {
//					if (m_which_one_player1 % 2 == 0) { temp_cmd = VariousFunctionsForMatchGame::COMMAND_1_TO_1; }
//					else { temp_cmd = VariousFunctionsForMatchGame::COMMAND_2_TO_1; }
//				}
//				else {
//					if (m_which_one_player1 % 2 == 0) { temp_cmd = VariousFunctionsForMatchGame::COMMAND_1_TO_2; }
//					else { temp_cmd = VariousFunctionsForMatchGame::COMMAND_2_TO_2; }
//				}
//
//				//アニメを追加する
//				m_pushNewFieldbyCommand(temp_cmd);
//
//				//カウンタを全て初期化する
//				m_which_player = 0;
//				m_which_one_player1 = 0;
//				m_which_one_player2 = 0;
//				m_use_self_hurm = false;
//				m_use_saihai = 0;
//			}
//		}
//	}
//}
//
//void GameScene::m_selectEnenmy()
//{
//	MatchField _new;
//
//	//新盤面を生成
//	_new = m_field;
//
//	if (VariousFunctionsForMatchGame::matchGameCOM(m_enemy_level, m_field, _new, m_self_harm_rule, m_mod_rule) == false) {
//		Parameter _p;
//		mp_listenerInterface->deleteNowScene(_p);
//		printfDx("Gamescene Class より敵の盤面生成関数がエラーを起こしました\nメニュー画面に戻ります");
//	}
//
//	//新しい盤面を挿入
//	m_pushNewField(_new);
//}
//
//
//void GameScene::m_pushNewField(MatchField& _new)
//{
//	m_newfield_data = _new;	//データを受け取る
//
//	//アニメを追加
//	m_anime.addAnime(4);
//	m_anime.addAnimeOption(m_field, _new);
//	
//	m_newfield_type = 1;	//タイプを変更
//}
//
//void GameScene::m_pushNewFieldbyCommand(int _cmd)
//{
//	m_newfield_cmd = _cmd;	//データを受け取る
//
//	//アニメを追加
//	m_anime.addAnime(4);
//	m_anime.addAnimeOption2(m_field, _cmd);
//
//	m_newfield_type = 2;	//タイプを変更
//}
//
//void GameScene::m_pushNewFieldExecute()
//{
//	//フィールドデータから更新する場合
//	if (m_newfield_type == 1) 
//	{
//		//ログを追加
//		m_logDraw.pushLogByField(m_newfield_data);
//
//		//フィールドを更新
//		m_field = m_newfield_data;
//
//		//ターンを増やす
//		m_turn++;
//	}
//	//コマンドから更新する場合
//	else if (m_newfield_type == 2) 
//	{
//		//次盤面の生成
//		MatchField _temp;
//		VariousFunctionsForMatchGame::executeCommand(m_newfield_cmd, m_field, _temp, m_mod_rule, m_self_harm_rule); //コマンドを実行
//
//		//ログを追加
//		m_logDraw.pushLogByField(_temp);
//
//		//フィールドを更新
//		m_field = _temp;
//
//		//ターンを増やす
//		m_turn++;
//	}
//
//	m_newfield_type = 0;
//	return;
//}
