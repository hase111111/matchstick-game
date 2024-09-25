#pragma once
#include"AbstractScene.h"
#include"SceneChangeEffect.h"
#include"MatchGameCommon.h"
#include<vector>
#include"ResultDrawBack.h"
#include"ResultString.h"
#include"ResultDrawHand.h"
#include"ResultKey.h"

class ResultScene final : public AbstractScene 
{
public:
	ResultScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);

	bool update() override;
	void draw() const override;
	void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) override;

private:
	SceneChangeEffect m_sceneChange;
	ResultDrawBack m_drawBack;
	ResultString m_drawString;
	ResultDrawHand m_drawHand;
	ResultKey m_drawKey;

	std::vector<MatchField> m_field_list;

	//関数
	bool m_isIllegalFieldList(const std::vector<MatchField>& _field) const;

	//変数・フラグ
	bool m_illegal_field = false;	//不正な盤面かどうかのフラグ

	bool m_mod_rule = false;		//MOD 5ルールが適用されているかのフラグ
	bool m_self_rule = false;		//自傷ルールが採用されているかのフラグ

	bool m_scene_change = false;	//このフラグが立った時にシーンを戻す
	int m_scene_back_num = 0;		//何シーン戻るか

	bool m_replay_save = false;		//リプレイを保存済みかどうか調べるフラグ
	bool m_replay_fail = false;		//リプレイを保存に失敗したか調べるフラグ

	int m_select_field = 0;
};