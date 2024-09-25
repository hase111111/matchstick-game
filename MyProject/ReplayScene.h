#pragma once
#include "AbstractScene.h"
#include"SceneChangeEffect.h"
#include"MatchGameCommon.h"
#include<vector>
#include"GameAnime.h"
#include"GameHand.h"
#include"GameLog.h"

class ReplayScene : public AbstractScene
{
public:
	ReplayScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);

	bool update() override;
	void draw() const override;

	void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) override;

private:
	//クラス
	SceneChangeEffect m_sceneChange;	//シーンチェンジのエフェクト
	GameAnime m_gameAnime;
	GameHand m_gameHand;
	GameLog m_gameLog;

	//ゲーム用のパラメータ
	bool m_mod_rule = false;		//MOD 5ルールが適用されているかのフラグ
	bool m_self_rule = false;		//自傷ルールが採用されているかのフラグ
	std::vector<MatchField> m_field_list;	//フィールドのリスト

	//マッチゲームの盤面
	MatchField m_field;
	int m_turn = 0;
	bool m_player_is_first;

	//変数・フラグ
	bool m_illegal_field = false;	//不正な盤面かどうかのフラグ
	bool m_scene_change = false;	//このフラグが立った時にシーンを戻す

	//関数
	void m_loadParam(const Parameter parameter);	//パラメータを受け取る
	bool m_isIllegalFieldList(const std::vector<MatchField>& _field) const;		//不正なフィールドリストかどうかを調べる
};
