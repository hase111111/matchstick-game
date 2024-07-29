//#pragma once
//#include<memory>
//#include<vector>
//#include"Singleton.h"
//#include<map>
//#include<string>
///*
//分身可能回数
//mod 5ルール
//自傷ルール
//*/
//
//struct MatchField
//{
//	MatchField();
//	MatchField(int p1l, int p1r, int p2l, int p2r, bool _turn);
//	MatchField(int p1l, int p1r, int p2l, int p2r, bool _turn, int _pl1_avatar_num, int _pl2_avatar_num);
//
//	std::pair<int, int> player1;
//	std::pair<int, int> player2;
//	bool turn;
//	int player1_avatar_num, player2_avatar_num;
//
//	void Optimisation(bool _mod_rule = false);
//	void WriteDown();
//	bool doesWinFirstPlayer() const;
//	bool doesWinSecondPlayer() const;
//	bool isEndOfGame() const;
//
//	//オペレータを定義する
//	bool operator == (const MatchField& rhs) const;
//	bool operator != (const MatchField& rhs) const;
//	bool operator < (const MatchField& rhs) const;
//};
//
//namespace VariousFunctionsForMatchGame 
//{
//	//定数
//	const int DEAD_LINE = 5;
//	const int SENNICHITE = 4;
//
//	void changeMoreFiveToZero(int& _num, bool _mod_rule = false);
//	bool comparePairUnit(std::pair<int, int> _p1, std::pair<int, int> _p2);
//	void makeNextFieldList(std::vector<MatchField>& _list, MatchField _now, bool _mod_rule = false, bool _self_harm = false);
//
//	//COM
//	constexpr int WIN = 1000;
//	constexpr int LOSE = -1000;
//	constexpr int ERROR_LOOP = 15;
//	constexpr int ERROR_EVALUATION = 0;
//
//	/// <param name="_level">0でeasy 1でnormal 2でhard それ以外ならばeasy</param>
//	bool matchGameCOM(const int _level, const MatchField& _field, MatchField& _result, const bool _self_harm, const bool _mod_rule);
//
//	bool matchGameCOM_Easy(const MatchField& _field, MatchField& _result, bool _self_harm = false);
//	bool matchGameCOM_EasyForMod(const MatchField& _field, MatchField& _result, bool _self_harm = false);
//	bool matchGameCOM_Rand(const MatchField& _field, MatchField& _result, bool _self_harm, const bool _mod_rule);
//	bool matchGameCOM_Hard(const MatchField& _field, MatchField& _result, bool _self_harm = false);
//	bool matchGameCOM_HardForMod(const MatchField& _field, MatchField& _result, bool _self_harm = false);
//
//	int evaluationFunction(const MatchField _field, const  bool _player, const  bool _self_harm = false, int _loop_num = 0);
//	int evaluationFunctionForMod(const MatchField _field, const  bool _player, const bool _self_harm, const int _loop_num);
//	int evaluationFunctionForModSaiten(const MatchField _field, const  bool _player);
//
//	//攻撃のアニメーション用のコマンド
//	constexpr int COMMAND_ERROR = -1;
//	constexpr int COMMAND_1_TO_1 = 0;
//	constexpr int COMMAND_1_TO_2 = 1;
//	constexpr int COMMAND_2_TO_1 = 2;
//	constexpr int COMMAND_2_TO_2 = 3;
//	constexpr int COMMAND_1_SELF = 4;
//	constexpr int COMMAND_2_SELF = 5;
//	constexpr int COMMAND_SAIHAI_LOW = 6;
//	constexpr int COMMAND_SAIHAI_HIGH = 7;
//
//	int getCommand(const MatchField& _old, const MatchField& _new, bool _mod_rule = false, bool _self_harm = false);
//	bool executeCommand(const int _command, const MatchField& _old, MatchField& _new, bool _mod_rule = false, bool _self_harm = false);
//
//	//入出力系関数
//	void outputEvaluationList(bool _self_harm);
//	void outputEvaluationListForMod(bool _self_harm);
//	bool outputFieldList(const std::vector<MatchField>& _field_list, const bool _mod_rule, const bool _self_harm);
//	bool inputFieldList(const std::string _filename, std::vector<MatchField>& _field_list, bool& _mod_rule, bool& _self_harm);
//}
//
////評価関数の値をあらかじめ全て算出したうえで記録することで高速思考を可能にしたい
//class MatchGameList final : public Singleton<MatchGameList> 
//{
//	MatchGameList() = default;
//	friend Singleton< MatchGameList >;
//
//public:
//	void init();
//	void init_add();
//	bool evaluationFunctionList(const MatchField& _field, const bool _player, const bool _self_harm, int& _result);
//	bool evaluationFunctionListForMod(const MatchField& _field, const bool _player, const bool _self_harm, int& _result);
//
//private:
//	std::map<MatchField, int> m_list;
//	std::map<MatchField, int> m_list_self;
//	std::map<MatchField, int> m_list_mod;
//	std::map<MatchField, int> m_list_mod_self;
//
//	bool m_is_init = false;
//};
