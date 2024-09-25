#include "ResultDrawBack.h"
#include "DxLib.h"
#include "Define.h"

ResultDrawBack::ResultDrawBack()
{
}

void ResultDrawBack::draw() const
{
	//背景色
	DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(0xa9, 0xa9, 0xa9), TRUE);

	//ログの表示位置
	int Log_HalfX = Define::WIN_SIZEX * 17 / 128;
	int Log_BoxX = Define::WIN_SIZEX * 14 / 64;
	int Log_BoxY = Define::WIN_SIZEY * 59 / 64;

	DrawBox(Log_HalfX - Log_BoxX / 2, Define::WIN_SIZEY / 2 - Log_BoxY / 2, Log_HalfX + Log_BoxX / 2, Define::WIN_SIZEY / 2 + Log_BoxY / 2, GetColor(0xff, 0xff, 0xff), TRUE);

	//フィールドの表示位置
	int Field_HalfX = Define::WIN_SIZEX * 79 / 128;
	int Field_BoxX = Define::WIN_SIZEX * 45 / 64;
	int Field_HalfY = Define::WIN_SIZEY * 39 / 128;
	int Field_BoxY = Define::WIN_SIZEY * 34 / 64;
	DrawBox(Field_HalfX - Field_BoxX / 2, Field_HalfY - Field_BoxY / 2, Field_HalfX + Field_BoxX / 2, Field_HalfY + Log_BoxY / 2, GetColor(0xff, 0xff, 0xff), TRUE);

	//採点結果の表示位置
	int Result_HalfX = Define::WIN_SIZEX * 79 / 128;
	int Result_BoxX = Define::WIN_SIZEX * 45 / 64;
	int Result_HalfY = Define::WIN_SIZEY * 112 / 128;
	int Result_BoxY = Define::WIN_SIZEY * 10 / 64;
	DrawBox(Result_HalfX - Result_BoxX / 2, Result_HalfY - Result_BoxY / 2, Result_HalfX + Result_BoxX / 2, Result_HalfY + Result_BoxY / 2, GetColor(0xff, 0xff, 0xff), TRUE);
}
