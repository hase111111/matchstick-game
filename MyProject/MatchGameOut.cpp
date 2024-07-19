#include"MatchGameCommon.h"
#include<fstream>
#include"DxLib.h"
#include<string>

/// <summary>
/// 実行に結構時間かかるのでほどほどに
/// </summary>
/// <param name="_self_harm"></param>
void VariousFunctionsForMatchGame::outputEvaluationList(bool _self_harm)
{
	const int NOT_YET = 100000;
	const bool SAIHAI = true;
	const int SAIHAI_NUM = (SAIHAI == true) ? 2 : 1;

	//ファイル書き込みの準備
	std::string filename = "OutputEvaluationList.txt";
	std::ofstream result_file;
	result_file.open(filename, std::ios::out);

	//考えうる全パターンをコンテナに入れる
	std::map<MatchField, int> brain_first;
	MatchField _temp;
	
	for (int pl1f = 0; pl1f < 5; pl1f++) { for (int pl1s = 0; pl1s < 5; pl1s++) { for (int pl2f = 0; pl2f < 5; pl2f++) { for (int pl2s = 0; pl2s < 5; pl2s++) 
	{
		for (int turn = 0; turn < 2; turn++)
		{
			for (int saihai1 = 0; saihai1 < SAIHAI_NUM; saihai1++) {	for (int saihai2 = 0; saihai2 < SAIHAI_NUM; saihai2++) {
				_temp.player1.first = pl1f;
				_temp.player1.second = pl1s;
				_temp.player2.first = pl2f;
				_temp.player2.second = pl2s;
				_temp.turn = (turn == 0) ? true : false;
				_temp.player1_avatar_num = saihai1;
				_temp.player2_avatar_num = saihai2;

				_temp.Optimisation();
				brain_first[_temp] = NOT_YET;
			}}
		}
	}}}}

	//全てを網羅し、評価結果を記録する
	for (auto i = brain_first.begin(); i != brain_first.end(); i++)
	{
		(*i).second = VariousFunctionsForMatchGame::evaluationFunction((*i).first, true, _self_harm);
	}

	//出力を行う
	result_file << "MatchField _temp;\n";

	for (auto &i : brain_first)
	{
		result_file << "_temp.player1.first = " << i.first.player1.first << ";";
		result_file << "_temp.player1.second = " << i.first.player1.second << ";";
		result_file << "_temp.player2.first = " << i.first.player2.first << ";";
		result_file << "_temp.player2.second = " << i.first.player2.second << ";";

		result_file << "_temp.turn = " << i.first.turn << ";";

		result_file << "_temp.player1_avatar_num = " << i.first.player1_avatar_num << ";";
		result_file << "_temp.player2_avatar_num = " << i.first.player2_avatar_num << ";\n";

		if (_self_harm == true) {
			result_file << "m_list_self[_temp] = " << i.second << ";\n";
		}
		else {
			result_file << "m_list[_temp] = " << i.second << ";\n";
		}
	}

	result_file.close();
}

void VariousFunctionsForMatchGame::outputEvaluationListForMod(bool _self_harm)
{
	const int NOT_YET = 100000;
	const bool SAIHAI = true;
	const int SAIHAI_NUM = (SAIHAI == true) ? 2 : 1;

	//ファイル書き込みの準備
	std::string filename = "OutputEvaluationList.txt";
	std::ofstream result_file;
	result_file.open(filename, std::ios::out);

	//考えうる全パターンをコンテナに入れる
	std::map<MatchField, int> brain_point;
	std::map<MatchField, std::vector<MatchField>> brain_vec;
	MatchField _temp;
	std::vector<MatchField> _blank;

	for (int pl1f = 0; pl1f < 5; pl1f++) {
		for (int pl1s = 0; pl1s < 5; pl1s++) {
			for (int pl2f = 0; pl2f < 5; pl2f++) {
				for (int pl2s = 0; pl2s < 5; pl2s++)
				{
					for (int turn = 0; turn < 2; turn++)
					{
						for (int saihai1 = 0; saihai1 < SAIHAI_NUM; saihai1++) {
							for (int saihai2 = 0; saihai2 < SAIHAI_NUM; saihai2++) {

								//手のデータ 0～4 / 現在のターン 0or1 / 采配回数 0or1
								_temp.player1.first = pl1f;
								_temp.player1.second = pl1s;
								_temp.player2.first = pl2f;
								_temp.player2.second = pl2s;
								_temp.turn = (turn == 0) ? true : false;
								_temp.player1_avatar_num = saihai1;
								_temp.player2_avatar_num = saihai2;

								_temp.Optimisation();	//最適化する

								//mapを拡張
								brain_point[_temp] = NOT_YET;
								brain_vec[_temp] = _blank;
							}
						}
					}
				}
			}
		}
	}

	//ゲーム木を作成する
	for (auto i = brain_vec.begin(); i != brain_vec.end(); i++)
	{
		makeNextFieldList((*i).second, (*i).first, true, _self_harm);
	}

	//各盤面を採点する
	const int __MAX_LOOP_NUM = 20;
	int loop_cnt = 0;

	while (true)
	{
		//採点完了しているか確認する
		int fin_counter = 0, fin_count = (int)brain_point.size() - 1;

		//実際に採点する
		for (auto i = brain_vec.begin(); i != brain_vec.end(); i++)
		{
			//次盤面が生成できていない(決着がついている)場合 かつ 採点し終わっていない場合
			if ((*i).second.empty() == true && brain_point[(*i).first] == NOT_YET)
			{
				if ((*i).first.isEndOfGame() == false) {	//err発生
					brain_point[(*i).first] = ERROR_EVALUATION;
					printfDx("err\n");
				}
				else if ((*i).first.doesWinFirstPlayer() == true) {	//プレイヤー側が勝利していたらWINを代入させる
					brain_point[(*i).first] = WIN;
				}
				else {	//そうじゃなければ敗北とする
					brain_point[(*i).first] = LOSE;
				}
			}
			//次盤面が生成できる場合 かつ 採点し終わっていない場合
			else if (brain_point[(*i).first] == NOT_YET)
			{
				//次盤面の採点がすべて終わっているか調べる
				int win_num = 0, lose_num = 0, not_yet_num = 0;
				int point_MAX = LOSE * 3, point_min = WIN * 3;

				//全次盤面を回してポイントを確認する
				for (auto& vec_itr : (*i).second)
				{
					if (brain_point[vec_itr] == NOT_YET) { //まだ終わっていない
						not_yet_num++;
					}
					//採点済み
					else 
					{	
						if (brain_point[vec_itr] > WIN - 30) { 
							win_num++; 
						}
						if (brain_point[vec_itr] < LOSE + 30) { 
							lose_num++; 
						}

						if (point_MAX <= brain_point[vec_itr]) point_MAX = brain_point[vec_itr];
						if (point_min >= brain_point[vec_itr]) point_min = brain_point[vec_itr];
					}
				}

				//プレイヤー側のターンなら最善手を選ぶ
				if ((*i).first.turn == true)
				{
					if (win_num >= 1) { brain_point[(*i).first] = point_MAX - 1; }							//一つでも勝利した盤面があるならばそれを選択する
					else if (win_num == 0 && not_yet_num == 0) { brain_point[(*i).first] = point_MAX + 1; }	//敗北する盤面しかないのなら負け
				}
				//敵のターンなら最悪手を選ぶ
				else {
					if (lose_num >= 1) { brain_point[(*i).first] = point_min + 1; }							//一つでも敗北した盤面があるならばそれを選択する
					else if (lose_num == 0 && not_yet_num == 0) { brain_point[(*i).first] = point_min - 1; }	//勝利する盤面しかないのなら
				}

			}
			//採点完了している場合
			else if(brain_point[(*i).first] != NOT_YET)
			{
				fin_counter++;	//カウンタを回す
			}
		}

		//採点終了しているならループを抜ける
		if (fin_counter == fin_count) { break; }

		loop_cnt++;
		if (loop_cnt > __MAX_LOOP_NUM) {
			printfDx("\n採点完了盤面...%d個/%d個中\n強制終了", fin_counter, fin_count + 1);
			break;
		}
	}

	//採点終了していない盤面を0点に設定
	for (auto i = brain_point.begin(); i != brain_point.end(); i++)
	{
		if ((*i).second == NOT_YET) {
			(*i).second = 0;
		}
	}

	//出力を行う
	{
		result_file << "MatchField _temp;\n";

		for (auto& i : brain_point)
		{
			result_file << "_temp.player1.first = " << i.first.player1.first << ";";
			result_file << "_temp.player1.second = " << i.first.player1.second << ";";
			result_file << "_temp.player2.first = " << i.first.player2.first << ";";
			result_file << "_temp.player2.second = " << i.first.player2.second << ";";

			result_file << "_temp.turn = " << i.first.turn << ";";

			result_file << "_temp.player1_avatar_num = " << i.first.player1_avatar_num << ";";
			result_file << "_temp.player2_avatar_num = " << i.first.player2_avatar_num << ";\n";

			if (_self_harm == true) {
				result_file << "m_list_mod_self[_temp] = " << i.second << ";\n";
			}
			else {
				result_file << "m_list_mod[_temp] = " << i.second << ";\n";
			}
		}
	}

	result_file.close();
}

bool VariousFunctionsForMatchGame::outputFieldList(const std::vector<MatchField>& _field_list, const bool _mod_rule, const bool _self_harm)
{
	std::string filename = "./replay/";	//ファイル名を決定する

	//日付取得
	DATEDATA _date;
	GetDateTime(&_date);

	//ファイル名に日付を出力
	filename += std::to_string(_date.Year);		//年
	if (_date.Mon < 10) { filename += "0"; }	//月が10以下ならば0を挿入
	filename += std::to_string(_date.Mon);		//月
	if (_date.Day < 10) { filename += "0"; }	//日が10以下ならば0を挿入
	filename += std::to_string(_date.Day);		//日

	filename += "_";	//ハイフン挿入

	if (_date.Hour < 10) { filename += "0"; }	//時間が10以下ならば0を挿入
	filename += std::to_string(_date.Hour);		//時間
	if (_date.Min < 10) { filename += "0"; }	//分が10以下ならば0を挿入
	filename += std::to_string(_date.Min);		//分
	if (_date.Sec < 10) { filename += "0"; }	//秒が10以下ならば0を挿入
	filename += std::to_string(_date.Sec);		//秒

	filename += "_Match.dat";

	std::ofstream result_file;

	//出力・バイナリモードでファイルを開く
	result_file.open(filename, std::ios::out | std::ios::binary);

	//失敗した場合FALSEを返す
	if (!result_file.is_open())
	{
		return false;
	}

	//成功した場合ファイルに書き込む

	//タイトル
	char title[] = "MRE";
	result_file.write(title, sizeof(title));

	char buf;
	//MOD5ルールの適用
	buf = (_mod_rule == true) ? 1 : 0;
	result_file.write(&buf, sizeof(buf));

	//自傷ルールの適用
	buf = (_self_harm == true) ? 1 : 0;
	result_file.write(&buf, sizeof(buf));

	//ここからフィールドデータを出力
	for (auto& i : _field_list)
	{
		//データの開始地点にFEを仕込む
		buf = 'S';
		result_file.write(&buf, sizeof(buf));

		//PLAYER1のデータ
		buf = (char)i.player1.first;
		result_file.write(&buf, sizeof(buf));

		buf = (char)i.player1.second;
		result_file.write(&buf, sizeof(buf));

		//PLAYER2のデータ
		buf = (char)i.player2.first;
		result_file.write(&buf, sizeof(buf));

		buf = (char)i.player2.second;
		result_file.write(&buf, sizeof(buf));

		//TURNのデータ
		buf = (i.turn == true) ? 1 : 0;
		result_file.write(&buf, sizeof(buf));

		//采配のデータ
		buf = (char)i.player1_avatar_num;
		result_file.write(&buf, sizeof(buf));

		buf = (char)i.player2_avatar_num;
		result_file.write(&buf, sizeof(buf));
	}

	//データの終点にFFを仕込む
	buf = 'E';
	result_file.write(&buf, sizeof(buf));

	result_file.close();

	return true;
}

bool VariousFunctionsForMatchGame::inputFieldList(const std::string _filename, std::vector<MatchField>& _field_list, bool& _mod_rule, bool& _self_harm)
{
	std::ifstream _file;

	//入力・バイナリモードでファイルを開く
	_file.open(_filename, std::ios::in | std::ios::binary);

	//失敗した場合FALSEを返す
	if (!_file.is_open())
	{
		return false;
	}

	char buf;

	//タイトルが MRE であることを確認する
	if (_file.eof() == true) { return false; }
	_file.read(&buf, sizeof(buf));
	if (buf != 'M') { return false; }

	if (_file.eof() == true) { return false; }
	_file.read(&buf, sizeof(buf));
	if (buf != 'R') { return false; }

	if (_file.eof() == true) { return false; }
	_file.read(&buf, sizeof(buf));
	if (buf != 'E') { return false; }

	if (_file.eof() == true) { return false; }
	_file.read(&buf, sizeof(buf));		//虚無を読み込む

	//ルールを読み込む
	if (_file.eof() == true) { return false; }
	_file.read(&buf, sizeof(buf));
	if (buf != 1 && buf != 0) { return false; }
	_mod_rule = (buf == 1) ? true : false;

	if (_file.eof() == true) { return false; }
	_file.read(&buf, sizeof(buf));
	if (buf != 1 && buf != 0) { return false; }
	_self_harm = (buf == 1) ? true : false;

	//ファイルの終端になるまでループ
	MatchField _temp_field;

	while (_file.eof() == false)
	{
		//先頭の文字を確認
		if (_file.eof() == true) { return false; }
		_file.read(&buf, sizeof(buf));
		if (buf == 'E') { break; }		//Eなら終了
		if (buf != 'S') { return false; }	//Sでないならエラー

		//player1
		if (_file.eof() == true) { return false; }
		_file.read(&buf, sizeof(buf));
		_temp_field.player1.first = (int)buf;

		if (_file.eof() == true) { return false; }
		_file.read(&buf, sizeof(buf));
		_temp_field.player1.second = (int)buf;

		//player2
		if (_file.eof() == true) { return false; }
		_file.read(&buf, sizeof(buf));
		_temp_field.player2.first = (int)buf;

		if (_file.eof() == true) { return false; }
		_file.read(&buf, sizeof(buf));
		_temp_field.player2.second = (int)buf;

		//たーん
		if (_file.eof() == true) { return false; }
		_file.read(&buf, sizeof(buf));
		if (buf != 1 && buf != 0) { return false; }
		_temp_field.turn = (buf == 1) ? true : false;

		//采配
		if (_file.eof() == true) { return false; }
		_file.read(&buf, sizeof(buf));
		_temp_field.player1_avatar_num = (int)buf;

		if (_file.eof() == true) { return false; }
		_file.read(&buf, sizeof(buf));
		_temp_field.player2_avatar_num = (int)buf;

		_temp_field.Optimisation();
		_field_list.push_back(_temp_field);
	}

	return true;
}
