//#include "ResultDrawBack.h"
//#include "DxLib.h"
//#include "define.h"
//
//ResultDrawBack::ResultDrawBack()
//{
//}
//
//void ResultDrawBack::draw() const
//{
//	//背景色
//	DrawBox(0, 0, Define::kWindowSizeX, Define::kWindowSizeY, GetColor(0xa9, 0xa9, 0xa9), TRUE);
//
//	//ログの表示位置
//	int Log_HalfX = Define::kWindowSizeX * 17 / 128;
//	int Log_BoxX = Define::kWindowSizeX * 14 / 64;
//	int Log_BoxY = Define::kWindowSizeY * 59 / 64;
//
//	DrawBox(Log_HalfX - Log_BoxX / 2, Define::kWindowSizeY / 2 - Log_BoxY / 2, Log_HalfX + Log_BoxX / 2, Define::kWindowSizeY / 2 + Log_BoxY / 2, GetColor(0xff, 0xff, 0xff), TRUE);
//
//	//フィールドの表示位置
//	int Field_HalfX = Define::kWindowSizeX * 79 / 128;
//	int Field_BoxX = Define::kWindowSizeX * 45 / 64;
//	int Field_HalfY = Define::kWindowSizeY * 39 / 128;
//	int Field_BoxY = Define::kWindowSizeY * 34 / 64;
//	DrawBox(Field_HalfX - Field_BoxX / 2, Field_HalfY - Field_BoxY / 2, Field_HalfX + Field_BoxX / 2, Field_HalfY + Log_BoxY / 2, GetColor(0xff, 0xff, 0xff), TRUE);
//
//	//採点結果の表示位置
//	int Result_HalfX = Define::kWindowSizeX * 79 / 128;
//	int Result_BoxX = Define::kWindowSizeX * 45 / 64;
//	int Result_HalfY = Define::kWindowSizeY * 112 / 128;
//	int Result_BoxY = Define::kWindowSizeY * 10 / 64;
//	DrawBox(Result_HalfX - Result_BoxX / 2, Result_HalfY - Result_BoxY / 2, Result_HalfX + Result_BoxX / 2, Result_HalfY + Result_BoxY / 2, GetColor(0xff, 0xff, 0xff), TRUE);
//}
