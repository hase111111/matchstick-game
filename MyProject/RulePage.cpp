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

	//タイトル表示
	str ="基本ルール 1 / 2";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//文章
	str = "";
	str += "1. 先手、後手を決める。　　　　　　　　　　　　　　　　　　　　　\n";
	str += "\n";
	str += "2. 両プレイヤーは両手の人差し指を立てる。　　　　　　　　　　　　\n";
	str += "\n";
	str += "3. 先手番から相手の手のいずれか一つを選択して攻撃する。攻撃された\n";
	str += "   手は、選択した手の指本数分追加で指を立てる。 （例えば3本指が立\n";
	str += "   った手で相手の指が 1本立っている手を攻撃した時、相手は指を４本\n";
	str += "   立てる。)\n";
	str += "   0 の手は攻撃することができず、また攻撃対象に選択することができ\n";
	str += "   ない。\n";
	str += "\n";
	str += "4. 攻撃によって、立てた指の数が5以上となる時その手は消滅(立てた指\n";
	str += "   をすべて折りたたむ)する。\n";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_draw_BaseRule01() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//タイトル表示
	str = "基本ルール 2 / 2";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//文章
	str = "";
	str = "5. 相手の手をすべて消滅させた時、勝利となる。　　　　　　　　　　 \n";
	str += "\n";
	str += "6. 同一盤面が4回以上現れたとき、千日手として引き分けとなる。同一\n";
	str += "   の盤面が現れたときは、画面左に存在するログの色が変化するため、\n";
	str += "   それを用いて判断するとよい。\n";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_draw_Saihai() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;

	//タイトル表示
	str = "ローカルルール：采配";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//文章
	str = "";
	str += "攻撃の変わりに行うことができる行動。\n\n";
	str += "指の合計本数が変わらないように、右と左で指の数を\n";
	str += "かえることができる。 (例えば自分の手が1、3の時、\n";
	str += "2、2 や 0、4 に変更することができる。)\n\n";
	str += "なお、采配は試合中に一度しか行うことができない。\n";
	str += "また左右の数字を入れ替えるだけの采配はできない。\n";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 17 / 80, GetColor(0, 0, 0), m_font_32, str.c_str());
}

void RulePage::m_draw_Self() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;

	//タイトル表示
	str = "ローカルルール：自傷";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//文章
	str = "";
	str += "攻撃の際に、自分の手を選択して攻撃することができ\n";
	str += "るルール。\n";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 17 / 80, GetColor(0, 0, 0), m_font_32, str.c_str());
}

void RulePage::m_draw_Mod5() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//タイトル表示
	str = "ローカルルール：MOD 5";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//文章
	str = "";
	str += "攻撃の際に、自分の手を選択して攻撃することができ\n";
	str += "攻撃の時、5を上回ったならば剰余をとるルール。 　\n\n";
	str += "例えば3の手で4を攻撃した場合、攻撃された手は 2 \n";
	str += "3 + 4 = 7,7 mod 5 = 2 となる。\n\n";

	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, STR_X, GetColor(0, 0, 0), m_font_32, str.c_str());
}

void RulePage::m_draw_Senryaku00() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//タイトル表示
	str = "戦略指南 1 / 2";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//文章
	str = "";
	str += "このゲームにおいて大事な戦術は以下の通りである。　　　　　　　 \n";
	str += "\n";
	str += "・[0,1]にしない\n";
	str += "\n";
	str += "・采配は自分の手が片手になった時のみ使用する\n";
	str += "\n";
	str += "・相手が[0,1]の時は、自傷などを駆使してそれをキープする\n";
	str += "\n";
	str += "これらの戦略を用いることでNORMALまでのCPUには簡単に勝利すること\n";
	str += "ができるだろう。HARD以上のCPUに勝利したい場合、最高難易度のCPU\n";
	str += "と戦いその行動を真似することがよいだろう。(戦略指南放棄)\n";

	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_draw_Senryaku01() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//タイトル表示
	str = "戦略指南 2 / 2";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//文章
	str = "";
	str += "ただ、ぶっちゃけてしまうとこのゲームには数多くの欠陥がある。そ\n";
	str += "の一つがMod 5ルールを採用しない場合、先手必勝、後手必勝であるこ\n";
	str += "とだ。そのため、常に最善手を選び続けるIMPOSSIBLEのCPUには、あな\n";
	str += "たが常に最善手を選択しても勝利することができない場合がある。\n";
	str += "\n";
	str += "もう一つはMOD 5のルールを適用した場合、両者が最善手を選び続ける\n";
	str += "限り千日手となってしまうことである。そのため、この場合も最高難\n";
	str += "易度のCPUには勝利することができない。\n";
	str += "\n";
	str += "そのため、戦略をいかに最適化したとしても必勝とはならない。所詮\n";
	str += "子どもの手遊びということである......。";

	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_draw_Other00() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//タイトル表示
	str = "採用されていないルールと補足 1 / 3";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//文章
	str = "";
	str += "・分身\n";
	str += "　指が立っている手が片手のみの場合、回数制限なく采配をすること\n";
	str += "　ができるルール。このルールが存在する場合、引き分けに持ち込む\n";
	str += "　ことが非常に容易になるため、採用しなかった。\n";
	str += "\n";
	str += "・６以上で消滅\n";
	str += "　指の本数が6本を超えたときに、消滅するルール。このゲームでは\n";
	str += "　MOD 5ルールを採用したため、このルールと組み合わせると処理が面\n";
	str += "　倒である。よって採用しなかった。\n";


	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_draw_Other01() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//タイトル表示
	str = "採用されていないルールと補足 2 / 3";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//文章
	str = "";
	str += "・引き分け\n";
	str += "　このゲームでは同一盤面が4回以上現れたとき引き分けとするルー\n";
	str += "　ルが存在するが、このルールはこのゲームオリジナルのものであ\n";
	str += "　る。このルールが存在しない場合、対戦を無限に続けることができ\n";
	str += "　るため、それを防ぐためにこのルールを追加した。\n";
	str += "\n";
	str += "・采配 1 / 2\n";
	str += "　采配を試合中一度しか使うことができないというルールもこのゲー\n";
	str += "　ムオリジナルのものである。当初は采配を試合中何度でも使うこと\n";
	str += "　できるルールを採用する予定だったが、敗北目前の状況から容易に\n";
	str += "　引き分けに持ち込むことができるため、ゲーム性を大きく損なうも\n";
	str += "　のとして採用しなかった。";

	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_24) / 2, STR_X, GetColor(0, 0, 0), m_font_24, str.c_str());
}

void RulePage::m_draw_Other02() const
{
	std::string str;
	const int POSX_HALF = Define::WIN_SIZEX / 2;
	const int STR_Y = 24;
	const int STR_X = Define::WIN_SIZEY * 17 / 80;

	//タイトル表示
	str = "採用されていないルールと補足 3 / 3";
	DrawFormatStringToHandle(POSX_HALF - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY * 3 / 32, GetColor(0, 0, 0), m_font_32, str.c_str());

	//文章
	str = "";
	str += "・采配 2 / 2\n";
	str += "・このゲームでは、両手の数字を入れ替えるだけの采配を禁止してい\n";
	str += "　る。これは安易な時間稼ぎを防ぐためである。(ぶっちゃけると、左\n";
	str += "　右の数字を昇順にソートしているので入れ替えができるとプログラ\n";
	str += "　ムが面倒になるので採用したくなかった。)\n";
	str += "\n";
	str += "・補足\n";
	str += "　このゲームのタイトルは「マッチ棒ゲーム」としてあるが、地域に\n";
	str += "　よってこの手遊びの呼び方は違うようである。「戦争」「割りばし」\n";
	str += "　「ブラフィン」など様々である。なお、制作者の地元では戦争と呼ば\n";
	str += "　れることが多かった。\n";

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
