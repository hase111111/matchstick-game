#pragma once
#include "Singleton.h"
#include <map>
#include <string>

class Font final : public Singleton<Font> {
private:
	Font() = default;
	friend Singleton<Font>;

public:
	int getFontHandle(const std::string _path);

private:
	std::map<std::string, int> m_path;

	//ƒtƒHƒ“ƒg‚Ì“Ç‚Ýž‚Ý‚ÌÅ‘å”‚ðÝ’è‚·‚é
	const int MAX_FONT_HANDLE_NUM = 6;
};

inline int myLoadFont(const std::string path) {
	return Font::getIns()->getFontHandle(path);
}