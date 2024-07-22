
#ifndef HOMERUN_SOUND_EFFECT_LOADER_H_
#define HOMERUN_SOUND_EFFECT_LOADER_H_

#include <map>
#include <string>

namespace homerun
{

//! @brief SE��ǂݍ��ރN���X�D
class SoundEffectLoader final
{
public:
    int LoadAndGetSoundHandle(const std::string& file_path);

    void ChangeAllSoundVolume(int volume);

private:
    std::map<std::string, int> sound_handle_;  //!< SE���i�[����z��D�L�[�̓t�@�C���p�X�D

    int volume_percent_{ 100 };  //!< SE�̉��ʁD
};

}  // namespace homerun

#endif  // HOMERUN_SOUND_EFFECT_LOADER_H_
