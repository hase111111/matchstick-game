#include "TitleAnime.h"
#include "Define.h"
#include "DxLib.h"
#include "Image.h"
#include "Font.h"

//コンストラクタでは変数の初期化を行うのみ
TitleAnime::TitleAnime() :
    m_HAND_SIZEX(70.0),
    m_HAND_SIZEY(100.0),
    m_font_20(Font::getIns()->getFontHandle("data/font/PixelMplus10_size20.dft")),
    m_font_32(Font::getIns()->getFontHandle("data/font/PixelMplus10_size32.dft")),
    m_font_64(Font::getIns()->getFontHandle("data/font/PixelMplus10_size64.dft")),
    m_GAMETITLE("マッチ棒ゲーム"),
    m_GAMETITLE_STR_LEN(GetDrawStringWidthToHandle(m_GAMETITLE.c_str(), (int)m_GAMETITLE.size(), m_font_64)),
    m_ANNOUNCE("Push Z Key To Start"),
    m_ANNOUNCE_STR_LEN(GetDrawStringWidthToHandle(m_ANNOUNCE.c_str(), (int)m_ANNOUNCE.size(), m_font_32)),
    m_COPYRIGHT("(C) 2021 Saidai Game Production"),
    m_COPYRIGHT_STR_LEN(GetDrawStringWidthToHandle(m_COPYRIGHT.c_str(), (int)m_COPYRIGHT.size(), m_font_20)),
    m_counter(0)
{
    //画像ハンドルをロードする
    m_gr_back = myLoadGraph("data/img/title_back.png");
    m_gr_hand[0] = myLoadGraph("data/img/hand/0_hand.png");
    m_gr_hand[1] = myLoadGraph("data/img/hand/1_hand.png");
    m_gr_hand[2] = myLoadGraph("data/img/hand/2_hand.png");
    m_gr_hand[3] = myLoadGraph("data/img/hand/3_hand.png");
    m_gr_hand[4] = myLoadGraph("data/img/hand/4_hand.png");
    m_gr_hand[5] = myLoadGraph("data/img/hand/5_hand.png");
    m_gr_hand[6] = myLoadGraph("data/img/hand/piece.png");

    //腕のアニメーションの更新をする
    m_InitHandAnime();
}

bool TitleAnime::update()
{
    //アニメーションを更新して終了
    m_updateHandAnime();

    ++m_counter;

    return true;
}

void TitleAnime::draw() const
{
    //背景のグラデーション画像
    DrawRotaGraph(Define::WIN_SIZEX / 2, Define::WIN_SIZEY / 2, 1.0, 0.0, m_gr_back, TRUE);

    //後ろで動く手のアニメーション
    m_drawHandAnime();

    //タイトルの画像＆コピーライト
    m_DrawGameName();
}

void TitleAnime::m_InitHandAnime()
{
    const int _hand_num = 10; //10この腕を生成する
    HandAnime _add;

    //腕を生成する
    for (int i = 0; i < _hand_num; i++)
    {
        //画面を十等分した座標を起点の座標として登録する
        _add.base_x = (double)Define::WIN_SIZEX / _hand_num * i + m_HAND_SIZEX / 2 + 10;

        //ベース座標から-10～10ずれた座標に設置する
        _add.x = _add.base_x;// +(double)GetRand(30) - 15.0;

        //画面外に設置（0～腕6分程度ずらす）
        _add.y = (double)Define::WIN_SIZEY + m_HAND_SIZEY / 2.0 + (double)GetRand(m_HAND_SIZEY * 6);

        //イラストはランダムに設定する
        _add.gr = GetRand(6);

        //速度を1.5～4.0に設定する
        _add.v = 1.5 + GetRand(250) / 100.0;

        m_hand_anime.push_back(_add);//追加する
    }
}

void TitleAnime::m_updateHandAnime()
{
    //全ての手を上へ移動させる & 画面外に行ったなら下へ戻す
    for (auto& i : m_hand_anime)
    {
        i.y -= i.v;

        //腕の位置をリセットする処理
        if (i.y + m_HAND_SIZEY / 2 < 0) {
            //ベース座標から-10～10ずれた座標に設置する
            i.x = i.base_x + (double)GetRand(30) - 15.0;

            //画面外に設置（0～腕2分程度ずらす）
            i.y = (double)Define::WIN_SIZEY + m_HAND_SIZEY / 2.0;

            //イラストはランダムに設定する
            i.gr = GetRand(6);

            //速度を1.5～4.0に設定する
            i.v = 1.5 + GetRand(250) / 100.0;
        }
    }
}

void TitleAnime::m_drawHandAnime() const
{
    int _blend = 0;

    for (auto& i : m_hand_anime)
    {
        //画面上部に行くほど透明になる
        _blend = 150 - (int)(128 * (Define::WIN_SIZEY - i.y) / Define::WIN_SIZEY);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, _blend);

        //描画
        DrawRotaGraph((int)i.x, (int)i.y, 1.0, 0.0, m_gr_hand[i.gr], TRUE);
    }

    SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL,0);
}

void TitleAnime::m_DrawGameName() const
{
    //タイトル
    DrawFormatStringToHandle((Define::WIN_SIZEX - m_GAMETITLE_STR_LEN) / 2, Define::WIN_SIZEY / 8, GetColor(0, 0, 0), m_font_64, m_GAMETITLE.c_str());

    //アナウンス
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * abs(cos((double)m_counter / 15.0)));
    DrawFormatStringToHandle((Define::WIN_SIZEX - m_ANNOUNCE_STR_LEN) / 2, Define::WIN_SIZEY * 6 / 8, GetColor(0, 0, 0), m_font_32, m_ANNOUNCE.c_str());
    SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

    //コピーライト
    DrawFormatStringToHandle(Define::WIN_SIZEX * 31 / 32 - m_COPYRIGHT_STR_LEN, Define::WIN_SIZEY * 61 / 64, GetColor(0, 0, 0), m_font_20, m_COPYRIGHT.c_str());
}
