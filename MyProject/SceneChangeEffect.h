//#pragma once
//
//class SceneChangeEffect
//{
//public:
//	SceneChangeEffect();
//	~SceneChangeEffect() = default;
//
//	void init(const int _mode);
//	bool update();
//	void draw() const;
//
//private:
//	int m_counter = 0;	//アニメーションを動かすカウンタ
//	int m_mode = 0;		//どのアニメーションを動かすかのフラグ
//
//	//サウンドハンドル
//	int m_sound_fade_in = 0;
//	int m_sound_fade_out = 0;
//
//	const int m_WIN_DIV = 6;	//画面を6等分する
//	const int m_END_TIME = 50;	//アニメーションを行う時間
//	const int m_COLOR;
//};