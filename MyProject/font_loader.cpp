
#include "font_loader.h"

#include <DxLib.h>

#include "dxlib_assert.h"


namespace homerun
{

int FontLoader::LoadAndGetFontHandle(const std::string& file_path, const int edge)
{
    // �t�H���g�����łɓǂݍ���ł���Ȃ炻�̃n���h����Ԃ��D
    if (font_handle_.count(file_path) != 0)
    {
        return font_handle_.at(file_path);
    }

    // �ǂݍ��ށD
    int font_handle;
    font_handle = LoadFontDataToHandle(file_path.c_str(), edge);

    ASSERT(font_handle >= 0, "Failed to load font. File Path : " + file_path);  // assert���œǂݍ��ݏ��������Ă͂����Ȃ��̂Œ��ӁD

    // �ǂݍ��񂾃p�X���L�^����D
    font_handle_[file_path] = font_handle;

    // �ő吔������Ȃ�΃G���[���b�Z�[�W��\������D
    ASSERT(font_handle_.size() <= kMaxFontHandleNum, "The number of loaded fonts exceeds the maximum number of fonts.");

    return font_handle_.at(file_path);;
}

}
