#include "ResultScene.h"
#include "DxLib.h"
#include "GameParam.h"
#include "Keyboard.h"
#include "Sound.h"

ResultScene::ResultScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) : AbstractScene(pScli,parameter)
{
	//ゲームクラスからルールを受け取る
	if (parameter.getParam(GameParam::SELF_HARM_RULE) == GameParam::TRUE_STATE) { m_self_rule = true; }
	else { m_self_rule = false; }

	if (parameter.getParam(GameParam::MOD_RULE) == GameParam::TRUE_STATE) { m_mod_rule = true; }
	else { m_mod_rule = false; }
	m_drawKey.init(m_mod_rule, m_self_rule);

	m_scene_back_num = parameter.getParam(GameParam::RESULT_BACK_NUM);
	m_scene_back_num = (m_scene_back_num == 1 || m_scene_back_num == 2) ? m_scene_back_num : 1;
	if (m_scene_back_num == 1) { m_replay_save = true; }

	//フィールドをゲームクラスから受け取る
	parameter.getFieldParam(m_field_list);

	//フィールドリストを確認して不正なデータかどうか調べる
	clsDx();
	if (m_isIllegalFieldList(m_field_list) == true) 
	{
		m_illegal_field = true;
		printfDx("不正なフィールドデータです\n"); 
	}

	//文字描画用関数にデータを教える
	if (m_illegal_field == false) 
	{
		m_drawString.init(m_field_list, m_mod_rule, m_self_rule);
		m_drawString.update(0);

		m_drawHand.init(m_field_list);
		m_drawHand.update(0);
	}

	//シーンチェンジのエフェクトを挿入する
	m_sceneChange.init(1);
}

bool ResultScene::update()
{
	if (m_sceneChange.update() == false)
	{
		//不正なデータでなければ処理を行う
		if (m_illegal_field == false)
		{
			//シーンチェンジのフラグがたっているならシーンを切り替える
			if (m_scene_change == true)
			{
				Parameter p;
				mp_listenerInterface->deleteNowScene(p, m_scene_back_num);	//2シーン戻す
			}

			//ESCキーが押された場合シーンチェンジをする
			if (m_drawKey.update(m_field_list, m_select_field, m_replay_save, m_replay_fail) == false)
			{
				m_sceneChange.init(0);	//シーンチェンジのエフェクトを挿入
				m_scene_change = true;	//シーンチェンジのフラグをオンにする				
			}

			//描画用関数に現在選択している場所を教える
			m_drawString.update(m_select_field);
			m_drawHand.update(m_select_field);
		}
		//不正なデータだった場合シーンを終了する
		else
		{
			if (m_scene_change == true)
			{
				//シーンチェンジをする
				Parameter p;
				mp_listenerInterface->deleteNowScene(p, m_scene_back_num);	//2シーン又は1シーン戻す
			}
			else
			{
				m_sceneChange.init(0);	//シーンチェンジのエフェクトを挿入
				m_scene_change = true;	//シーンチェンジのフラグをオンにする	
			}
		}
	}

	return true;
}

void ResultScene::draw() const
{
	//背景
	m_drawBack.draw();

	//文字表示
	m_drawString.draw(m_replay_save, m_replay_fail);

	//手の表示
	m_drawHand.draw();

	//シーンチェンジエフェクト
	m_sceneChange.draw();
}

void ResultScene::receiveParameterInCaseOfDeleteScene(const Parameter& parameter)
{
	//シーンチェンジのエフェクトを挿入する
	m_sceneChange.init(1);
}

//フィールドリストが不正かどうか調べる
bool ResultScene::m_isIllegalFieldList(const std::vector<MatchField>& _field) const
{
	//フィールドの数が 0 or 1 なら不正とする
	if (_field.size() == 0 || _field.size() == 1) 
	{
		printfDx("フィールドが空,あるいは1のみです\n\n");
		return true; 
	}

	//まずは勝敗がついているかどうか調べる
	if (_field.back().isEndOfGame() == false) 
	{
		//勝敗がついていない場合引き分けかどうか調べる
		std::map<MatchField, int> _map_checker;

		//マップクラスを用いて各盤面が登場した回数をカウントする
		for (auto &i : _field)
		{
			_map_checker[i]++;
		}

		//一番多く登場した盤面の登場回数を記録する
		int _MAX_field_num = -1;

		for (auto &i : _map_checker)
		{
			if (i.second > _MAX_field_num) { _MAX_field_num = i.second; }
		}

		//千日手と判断される回数を下回っていた場合不正
		if (_MAX_field_num < VariousFunctionsForMatchGame::SENNICHITE) 
		{
			printfDx("勝負がついていませんが、千日手ではありませんでした\n");
			return true;
		}
	}
	else {
		//勝負がついている場合両者勝利となっていないか確かめる
		if(_field.back().doesWinFirstPlayer() == true && _field.back().doesWinSecondPlayer() == true)
		{
			//両者勝利となる盤面は不正
			printfDx("両者勝利判定となる盤面です\n");
			return true;
		}
	}

	//次に、盤面が正しい順序で並んでいるか調べる
	MatchField _next;
	int command = 0;

	for (size_t i = 0; i < _field.size(); i++)
	{
		//盤面が最後の盤面でない場合
		if (i < _field.size() - 1)
		{
			//次盤面へのコマンドを取得する
			command = VariousFunctionsForMatchGame::getCommand(_field.at(i), _field.at(i + 1), m_mod_rule, m_self_rule);

			//コマンドが不正なものか調べる
			if (command == VariousFunctionsForMatchGame::COMMAND_ERROR)
			{
				printfDx("盤面に連続性がありません%d\n", i);
				return true;
			}
		}
	}

	//全て調べ終わったならふせいでない
	return false;
}


