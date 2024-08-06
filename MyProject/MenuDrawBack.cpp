//#include "MenuDrawBack.h"
//#include"DxLib.h"
//#include"define.h"
//#include"Font.h"
//
//MenuDrawBack::MenuDrawBack()
//{
//	m_font_handle = myLoadFont("data/font/PixelMplus10_size20.dft");
//}
//
//void MenuDrawBack::update()
//{
//	m_counter++;
//}
//
//void MenuDrawBack::draw() const
//{
//	//背景
//	DrawBox(0, 0, Define::kWindowSizeX, Define::kWindowSizeY, GetColor(0xda, 0xda, 0xda), TRUE);
//
//	//文字
//	int len = GetDrawStringWidthToHandle(MESSAGE.c_str(), (int)MESSAGE.size(), m_font_handle);
//	DrawStringToHandle(-(m_counter % len), Define::kWindowSizeY * 61 / 64, MESSAGE.c_str(), GetColor(0x00, 0x00, 0x00), m_font_handle);
//	DrawStringToHandle(-(m_counter % len) + len, Define::kWindowSizeY * 61 / 64, MESSAGE.c_str(), GetColor(0x00, 0x00, 0x00), m_font_handle);
//}
