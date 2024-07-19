#include "DxLib.h"
#include "TitleScene.h"
#include "Keyboard.h"
#include "Define.h"
#include "Font.h"
#include "Sound.h"
#include "GameParam.h"

TitleScene::TitleScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) : 
	AbstractScene(pScli, parameter),
	m_scene_change(false),
	m_sound(Sound::getIns()->myLoadSound("data/sound/op.mp3"))
{
	m_change.init(-1);
}

bool TitleScene::update()
{
	m_anime.update();

	if (m_change.update() == false) {

		if (m_scene_change == true) {
			//シーンチェンジのエフェクトが終了した段階でシーンを変更する
			Parameter _p;
			mp_listenerInterface->addNewScene(enumScene::menu, _p);
		}

		//Zキーが押されたらシーン切り替え
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1) 
		{
			m_scene_change = true;	//シーン変更フラグを立てる
			m_change.init(2);		//シーンチェンジエフェクトを再生
			PlaySoundMem(m_sound, DX_PLAYTYPE_BACK);	//サウンドを再生
		}

		//ESCキーが押されたらゲーム終了
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1)
		{
			return false;
		}
	}

	return true;
}

void TitleScene::draw() const
{
	//背景
	DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(255, 255, 255), TRUE);

	//コピーライト＆背景のアニメーション
	m_anime.draw();

	//シーンチェンジのエフェクト
	m_change.draw();
}

void TitleScene::receiveParameterInCaseOfDeleteScene(const Parameter& parameter)
{
	//シーンチェンジ用のクラスとフラグをリセットする
	m_scene_change = false;
	m_change.init(3);
}
