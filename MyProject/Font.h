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

	//�t�H���g�̓ǂݍ��݂̍ő吔��ݒ肷��
	const int MAX_FONT_HANDLE_NUM = 6;
};

inline int myLoadFont(const std::string path) {
	return Font::getIns()->getFontHandle(path);
}