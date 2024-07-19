#pragma once
#include "Singleton.h"
#include <map>
#include<string>

class Image final : public Singleton<Image> {

public:
    Image() {};
    ~Image() = default;

    void release();
    int LoadGraph_EX(const std::string str);

private:
    std::map<std::string, int> m_images;
};

inline int myLoadGraph(const std::string str) {
    return Image::getIns()->LoadGraph_EX(str);
}
