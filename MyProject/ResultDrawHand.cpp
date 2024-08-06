//#include "ResultDrawHand.h"
//#include "Image.h"
//#include "DxLib.h"
//#include "define.h"
//
//ResultDrawHand::ResultDrawHand()
//{
//	m_gr_hand[0] = myLoadGraph("data/img/hand/0_hand.png");
//	m_gr_hand[1] = myLoadGraph("data/img/hand/1_hand.png");
//	m_gr_hand[2] = myLoadGraph("data/img/hand/2_hand.png");
//	m_gr_hand[3] = myLoadGraph("data/img/hand/3_hand.png");
//	m_gr_hand[4] = myLoadGraph("data/img/hand/4_hand.png");
//	m_gr_hand[5] = myLoadGraph("data/img/hand/5_hand.png");
//	m_gr_hand[6] = myLoadGraph("data/img/hand/piece.png");
//}
//
//void ResultDrawHand::init(const std::vector<MatchField> _list)
//{
//	//フィールドリストを読み込む
//	for (auto& i : _list)
//	{
//		m_field_list.push_back(i);
//	}
//
//	m_init_flag = true;
//}
//
//void ResultDrawHand::update(const int _select)
//{
//	if (m_init_flag == false) { return; }
//
//	m_select_field = _select;
//}
//
//void ResultDrawHand::draw() const
//{
//	if (m_init_flag == false) { return; }
//
//	int Field_HalfX = Define::kWindowSizeX * 79 / 128;
//	int Field_HandX = Define::kWindowSizeX * 19 / 128;
//	int Field_HalfY = Define::kWindowSizeY * 54 / 128;
//	int Field_HandY = Define::kWindowSizeY * 19 / 128;
//
//	if (0 <= m_select_field && m_select_field < (int)m_field_list.size())
//	{
//		//左下
//		if (0 <= m_field_list.at(m_select_field).player1.first && m_field_list.at(m_select_field).player1.first < 6)
//		{
//			DrawRotaGraph(Field_HalfX - Field_HandX, Field_HalfY + Field_HandY, 0.7, 0, m_gr_hand[m_field_list.at(m_select_field).player1.first], TRUE, true);
//		}
//
//		//右下
//		if (0 <= m_field_list.at(m_select_field).player1.second && m_field_list.at(m_select_field).player1.second < 6)
//		{
//			DrawRotaGraph(Field_HalfX + Field_HandX, Field_HalfY + Field_HandY, 0.7, 0, m_gr_hand[m_field_list.at(m_select_field).player1.second], TRUE);
//		}
//
//		//左下
//		if (0 <= m_field_list.at(m_select_field).player2.first && m_field_list.at(m_select_field).player2.first < 6)
//		{
//			DrawRotaGraph(Field_HalfX - Field_HandX, Field_HalfY - Field_HandY, 0.7, 0, m_gr_hand[m_field_list.at(m_select_field).player2.first], TRUE, true, true);
//		}
//
//		//右下
//		if (0 <= m_field_list.at(m_select_field).player2.second && m_field_list.at(m_select_field).player2.second < 6)
//		{
//			DrawRotaGraph(Field_HalfX + Field_HandX, Field_HalfY - Field_HandY, 0.7, 0, m_gr_hand[m_field_list.at(m_select_field).player2.second], TRUE, false, true);
//		}
//	}
//}
