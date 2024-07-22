
#ifndef HOMERUN_FONT_LOADER_H_
#define HOMERUN_FONT_LOADER_H_

#include <map>
#include <string>


namespace homerun
{

class FontLoader final
{
public:
    int LoadAndGetFontHandle(const std::string& file_path, int edge = 0);

private:
    static constexpr int kMaxFontHandleNum = 10;  //! �t�H���g�̓ǂݍ��݂̍ő吔��ݒ肷��D

    std::map<std::string, int> font_handle_;  //!< �t�H���g���i�[����z��D�L�[�̓t�@�C���p�X�D
};

}  // namespace homerun

#endif  // HOMERUN_FONT_LOADER_H_
