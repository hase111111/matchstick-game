#include"MatchGameCommon.h"
#include<fstream>
#include"DxLib.h"
#include<string>

/// <summary>
/// ���s�Ɍ��\���Ԃ�����̂łقǂقǂ�
/// </summary>
/// <param name="_self_harm"></param>
void VariousFunctionsForMatchGame::outputEvaluationList(bool _self_harm)
{
	const int NOT_YET = 100000;
	const bool SAIHAI = true;
	const int SAIHAI_NUM = (SAIHAI == true) ? 2 : 1;

	//�t�@�C���������݂̏���
	std::string filename = "OutputEvaluationList.txt";
	std::ofstream result_file;
	result_file.open(filename, std::ios::out);

	//�l������S�p�^�[�����R���e�i�ɓ����
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

	//�S�Ă�ԗ����A�]�����ʂ��L�^����
	for (auto i = brain_first.begin(); i != brain_first.end(); i++)
	{
		(*i).second = VariousFunctionsForMatchGame::evaluationFunction((*i).first, true, _self_harm);
	}

	//�o�͂��s��
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

	//�t�@�C���������݂̏���
	std::string filename = "OutputEvaluationList.txt";
	std::ofstream result_file;
	result_file.open(filename, std::ios::out);

	//�l������S�p�^�[�����R���e�i�ɓ����
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

								//��̃f�[�^ 0�`4 / ���݂̃^�[�� 0or1 / �єz�� 0or1
								_temp.player1.first = pl1f;
								_temp.player1.second = pl1s;
								_temp.player2.first = pl2f;
								_temp.player2.second = pl2s;
								_temp.turn = (turn == 0) ? true : false;
								_temp.player1_avatar_num = saihai1;
								_temp.player2_avatar_num = saihai2;

								_temp.Optimisation();	//�œK������

								//map���g��
								brain_point[_temp] = NOT_YET;
								brain_vec[_temp] = _blank;
							}
						}
					}
				}
			}
		}
	}

	//�Q�[���؂��쐬����
	for (auto i = brain_vec.begin(); i != brain_vec.end(); i++)
	{
		makeNextFieldList((*i).second, (*i).first, true, _self_harm);
	}

	//�e�Ֆʂ��̓_����
	const int __MAX_LOOP_NUM = 20;
	int loop_cnt = 0;

	while (true)
	{
		//�̓_�������Ă��邩�m�F����
		int fin_counter = 0, fin_count = (int)brain_point.size() - 1;

		//���ۂɍ̓_����
		for (auto i = brain_vec.begin(); i != brain_vec.end(); i++)
		{
			//���Ֆʂ������ł��Ă��Ȃ�(���������Ă���)�ꍇ ���� �̓_���I����Ă��Ȃ��ꍇ
			if ((*i).second.empty() == true && brain_point[(*i).first] == NOT_YET)
			{
				if ((*i).first.isEndOfGame() == false) {	//err����
					brain_point[(*i).first] = ERROR_EVALUATION;
					printfDx("err\n");
				}
				else if ((*i).first.doesWinFirstPlayer() == true) {	//�v���C���[�����������Ă�����WIN����������
					brain_point[(*i).first] = WIN;
				}
				else {	//��������Ȃ���Δs�k�Ƃ���
					brain_point[(*i).first] = LOSE;
				}
			}
			//���Ֆʂ������ł���ꍇ ���� �̓_���I����Ă��Ȃ��ꍇ
			else if (brain_point[(*i).first] == NOT_YET)
			{
				//���Ֆʂ̍̓_�����ׂďI����Ă��邩���ׂ�
				int win_num = 0, lose_num = 0, not_yet_num = 0;
				int point_MAX = LOSE * 3, point_min = WIN * 3;

				//�S���Ֆʂ��񂵂ă|�C���g���m�F����
				for (auto& vec_itr : (*i).second)
				{
					if (brain_point[vec_itr] == NOT_YET) { //�܂��I����Ă��Ȃ�
						not_yet_num++;
					}
					//�̓_�ς�
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

				//�v���C���[���̃^�[���Ȃ�őP���I��
				if ((*i).first.turn == true)
				{
					if (win_num >= 1) { brain_point[(*i).first] = point_MAX - 1; }							//��ł����������Ֆʂ�����Ȃ�΂����I������
					else if (win_num == 0 && not_yet_num == 0) { brain_point[(*i).first] = point_MAX + 1; }	//�s�k����Ֆʂ����Ȃ��̂Ȃ畉��
				}
				//�G�̃^�[���Ȃ�ň����I��
				else {
					if (lose_num >= 1) { brain_point[(*i).first] = point_min + 1; }							//��ł��s�k�����Ֆʂ�����Ȃ�΂����I������
					else if (lose_num == 0 && not_yet_num == 0) { brain_point[(*i).first] = point_min - 1; }	//��������Ֆʂ����Ȃ��̂Ȃ�
				}

			}
			//�̓_�������Ă���ꍇ
			else if(brain_point[(*i).first] != NOT_YET)
			{
				fin_counter++;	//�J�E���^����
			}
		}

		//�̓_�I�����Ă���Ȃ烋�[�v�𔲂���
		if (fin_counter == fin_count) { break; }

		loop_cnt++;
		if (loop_cnt > __MAX_LOOP_NUM) {
			printfDx("\n�̓_�����Ֆ�...%d��/%d��\n�����I��", fin_counter, fin_count + 1);
			break;
		}
	}

	//�̓_�I�����Ă��Ȃ��Ֆʂ�0�_�ɐݒ�
	for (auto i = brain_point.begin(); i != brain_point.end(); i++)
	{
		if ((*i).second == NOT_YET) {
			(*i).second = 0;
		}
	}

	//�o�͂��s��
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
	std::string filename = "./replay/";	//�t�@�C���������肷��

	//���t�擾
	DATEDATA _date;
	GetDateTime(&_date);

	//�t�@�C�����ɓ��t���o��
	filename += std::to_string(_date.Year);		//�N
	if (_date.Mon < 10) { filename += "0"; }	//����10�ȉ��Ȃ��0��}��
	filename += std::to_string(_date.Mon);		//��
	if (_date.Day < 10) { filename += "0"; }	//����10�ȉ��Ȃ��0��}��
	filename += std::to_string(_date.Day);		//��

	filename += "_";	//�n�C�t���}��

	if (_date.Hour < 10) { filename += "0"; }	//���Ԃ�10�ȉ��Ȃ��0��}��
	filename += std::to_string(_date.Hour);		//����
	if (_date.Min < 10) { filename += "0"; }	//����10�ȉ��Ȃ��0��}��
	filename += std::to_string(_date.Min);		//��
	if (_date.Sec < 10) { filename += "0"; }	//�b��10�ȉ��Ȃ��0��}��
	filename += std::to_string(_date.Sec);		//�b

	filename += "_Match.dat";

	std::ofstream result_file;

	//�o�́E�o�C�i�����[�h�Ńt�@�C�����J��
	result_file.open(filename, std::ios::out | std::ios::binary);

	//���s�����ꍇFALSE��Ԃ�
	if (!result_file.is_open())
	{
		return false;
	}

	//���������ꍇ�t�@�C���ɏ�������

	//�^�C�g��
	char title[] = "MRE";
	result_file.write(title, sizeof(title));

	char buf;
	//MOD5���[���̓K�p
	buf = (_mod_rule == true) ? 1 : 0;
	result_file.write(&buf, sizeof(buf));

	//�������[���̓K�p
	buf = (_self_harm == true) ? 1 : 0;
	result_file.write(&buf, sizeof(buf));

	//��������t�B�[���h�f�[�^���o��
	for (auto& i : _field_list)
	{
		//�f�[�^�̊J�n�n�_��FE���d����
		buf = 'S';
		result_file.write(&buf, sizeof(buf));

		//PLAYER1�̃f�[�^
		buf = (char)i.player1.first;
		result_file.write(&buf, sizeof(buf));

		buf = (char)i.player1.second;
		result_file.write(&buf, sizeof(buf));

		//PLAYER2�̃f�[�^
		buf = (char)i.player2.first;
		result_file.write(&buf, sizeof(buf));

		buf = (char)i.player2.second;
		result_file.write(&buf, sizeof(buf));

		//TURN�̃f�[�^
		buf = (i.turn == true) ? 1 : 0;
		result_file.write(&buf, sizeof(buf));

		//�єz�̃f�[�^
		buf = (char)i.player1_avatar_num;
		result_file.write(&buf, sizeof(buf));

		buf = (char)i.player2_avatar_num;
		result_file.write(&buf, sizeof(buf));
	}

	//�f�[�^�̏I�_��FF���d����
	buf = 'E';
	result_file.write(&buf, sizeof(buf));

	result_file.close();

	return true;
}

bool VariousFunctionsForMatchGame::inputFieldList(const std::string _filename, std::vector<MatchField>& _field_list, bool& _mod_rule, bool& _self_harm)
{
	std::ifstream _file;

	//���́E�o�C�i�����[�h�Ńt�@�C�����J��
	_file.open(_filename, std::ios::in | std::ios::binary);

	//���s�����ꍇFALSE��Ԃ�
	if (!_file.is_open())
	{
		return false;
	}

	char buf;

	//�^�C�g���� MRE �ł��邱�Ƃ��m�F����
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
	_file.read(&buf, sizeof(buf));		//������ǂݍ���

	//���[����ǂݍ���
	if (_file.eof() == true) { return false; }
	_file.read(&buf, sizeof(buf));
	if (buf != 1 && buf != 0) { return false; }
	_mod_rule = (buf == 1) ? true : false;

	if (_file.eof() == true) { return false; }
	_file.read(&buf, sizeof(buf));
	if (buf != 1 && buf != 0) { return false; }
	_self_harm = (buf == 1) ? true : false;

	//�t�@�C���̏I�[�ɂȂ�܂Ń��[�v
	MatchField _temp_field;

	while (_file.eof() == false)
	{
		//�擪�̕������m�F
		if (_file.eof() == true) { return false; }
		_file.read(&buf, sizeof(buf));
		if (buf == 'E') { break; }		//E�Ȃ�I��
		if (buf != 'S') { return false; }	//S�łȂ��Ȃ�G���[

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

		//���[��
		if (_file.eof() == true) { return false; }
		_file.read(&buf, sizeof(buf));
		if (buf != 1 && buf != 0) { return false; }
		_temp_field.turn = (buf == 1) ? true : false;

		//�єz
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
