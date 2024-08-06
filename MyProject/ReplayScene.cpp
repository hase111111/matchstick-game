//#include "ReplayScene.h"
//#include "GameParam.h"
//#include "DxLib.h"
//#include "Keyboard.h"
//#include "define.h"
//
//ReplayScene::ReplayScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) : AbstractScene(pScli, parameter)
//{
//	//パラメータを読み込む
//	m_loadParam(parameter);
//
//	//シーンチェンジのエフェクトを挿入する
//	m_sceneChange.init(1);
//
//	//フィールドリストを確認して不正なデータかどうか調べる
//	if (m_isIllegalFieldList(m_field_list) == true)
//	{
//		m_illegal_field = true;
//		//printfDx("不正なフィールドデータです\n");
//	}
//	//不正でないなら各クラスを初期化
//	else 
//	{
//		m_gameAnime.init(m_self_rule, m_mod_rule,true);	//アニメにルールを伝える
//		m_field = m_field_list.at(m_turn);			//先頭のフィールドを伝える
//
//		//アニメーションをセットする
//		if (m_field.turn == true) { m_gameAnime.addAnime(0); }
//		else { m_gameAnime.addAnime(1); }
//
//		//ログを追加
//		if (m_field.turn == true) { m_gameLog.pushLog("貴方は先手です"); }
//		else { m_gameLog.pushLog("貴方は後手です"); }
//		m_gameLog.pushLogByField(m_field_list.at(m_turn));
//	}
//}
//
//bool ReplayScene::update()
//{
//
//	if (m_sceneChange.update() == false)
//	{
//		//シーンチェンジフラグが立っているならばシーンを戻す
//		if (m_scene_change == true) 
//		{
//			Parameter p;
//			mp_listenerInterface->deleteNowScene(p);
//		}
//		//立っていないならば通常の処理を行う
//		else 
//		{
//			//異常なフィールドリストを読み込んでいる場合終了する
//			if (m_illegal_field == true) 
//			{
//				m_sceneChange.init(0);
//				m_scene_change = true;
//			}
//			//異常でないならば普通に処理をする
//			else 
//			{
//				//ESCAPEキーが押されたらシーンを終了
//				if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) 
//				{
//					m_sceneChange.init(0);
//					m_scene_change = true;
//				}
//				else 
//				{
//					//アニメーション終了している時のみ実行
//					if (m_gameAnime.update() == false) 
//					{
//						//フィールドを全て表示しきったならば終わる
//						if (m_turn + 1 >= (int)m_field_list.size()) 
//						{
//							m_sceneChange.init(0);
//							m_scene_change = true;
//							return true;
//						}
//						else 
//						{
//							m_gameAnime.addAnime(4);
//							m_gameAnime.addAnimeOption(m_field_list.at(m_turn), m_field_list.at((size_t)m_turn + 1));
//							m_gameLog.pushLogByField(m_field_list.at((size_t)m_turn + 1));
//							m_turn++;
//						}
//					}
//					//アニメの再生が終わったならばフィールドを書き換える
//					else if (m_gameAnime.isEndTime() == true) 
//					{
//						if (m_turn < (int)m_field_list.size()) 
//						{
//							m_field = m_field_list.at(m_turn);
//						}
//					}
//				}
//			}
//		}
//	}
//
//	return true;
//}
//
//void ReplayScene::draw() const
//{
//	//背景は白い色
//	DrawBox(0, 0, Define::kWindowSizeX, Define::kWindowSizeY, GetColor(255, 255, 255), TRUE);
//
//	//腕を描画する
//	m_gameHand.draw(m_field, false, 0, 0, 0, false, false);
//
//	//対戦ログを表示する
//	m_gameLog.draw(m_field, m_turn + 1, m_player_is_first, m_mod_rule, m_self_rule, 20000000);
//
//	//各種アニメーションを上に表示
//	m_gameAnime.draw();
//
//	//シーンチェンジのエフェクトを描画
//	m_sceneChange.draw();
//}
//
//void ReplayScene::receiveParameterInCaseOfDeleteScene(const Parameter& parameter)
//{
//	//シーンチェンジのエフェクトを挿入する
//	m_sceneChange.init(1);
//}
//
//void ReplayScene::m_loadParam(const Parameter parameter)
//{
//	//ゲームクラスからルールを受け取る
//	if (parameter.getParam(GameParam::SELF_HARM_RULE) == GameParam::TRUE_STATE) { m_self_rule = true; }
//	else { m_self_rule = false; }
//
//	if (parameter.getParam(GameParam::MOD_RULE) == GameParam::TRUE_STATE) { m_mod_rule = true; }
//	else { m_mod_rule = false; }
//
//	//フィールドをゲームクラスから受け取る
//	parameter.getFieldParam(m_field_list);
//}
//
//bool ReplayScene::m_isIllegalFieldList(const std::vector<MatchField>& _field) const
//{
//	//フィールドの数が 0 or 1 なら不正とする
//	if (_field.size() == 0 || _field.size() == 1)
//	{
//		printfDx("フィールドが空,あるいは1のみです\n\n");
//		return true;
//	}
//
//	//まずは勝敗がついているかどうか調べる
//	if (_field.back().isEndOfGame() == false)
//	{
//		//勝敗がついていない場合引き分けかどうか調べる
//		std::map<MatchField, int> _map_checker;
//
//		//マップクラスを用いて各盤面が登場した回数をカウントする
//		for (auto& i : _field)
//		{
//			_map_checker[i]++;
//		}
//
//		//一番多く登場した盤面の登場回数を記録する
//		int _MAX_field_num = -1;
//
//		for (auto& i : _map_checker)
//		{
//			if (i.second > _MAX_field_num) { _MAX_field_num = i.second; }
//		}
//
//		//千日手と判断される回数を下回っていた場合不正
//		if (_MAX_field_num < VariousFunctionsForMatchGame::SENNICHITE)
//		{
//			printfDx("勝負がついていませんが、千日手ではありませんでした\n");
//			return true;
//		}
//	}
//	else {
//		//勝負がついている場合両者勝利となっていないか確かめる
//		if (_field.back().doesWinFirstPlayer() == true && _field.back().doesWinSecondPlayer() == true)
//		{
//			//両者勝利となる盤面は不正
//			printfDx("両者勝利判定となる盤面です\n");
//			return true;
//		}
//	}
//
//	//次に、盤面が正しい順序で並んでいるか調べる
//	MatchField _next;
//	int command = 0;
//
//	for (size_t i = 0; i < _field.size(); i++)
//	{
//		//盤面が最後の盤面でない場合
//		if (i < _field.size() - 1)
//		{
//			//次盤面へのコマンドを取得する
//			command = VariousFunctionsForMatchGame::getCommand(_field.at(i), _field.at(i + 1), m_mod_rule, m_self_rule);
//
//			//コマンドが不正なものか調べる
//			if (command == VariousFunctionsForMatchGame::COMMAND_ERROR)
//			{
//				printfDx("盤面に連続性がありません%d\n", i);
//				return true;
//			}
//		}
//	}
//
//	//全て調べ終わったならふせいでない
//	return false;
//}
