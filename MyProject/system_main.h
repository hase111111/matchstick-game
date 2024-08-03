
#pragma once

#include <memory>

#include "game_setting_record.h"

namespace match_stick {

class SystemMain final {
public:
    SystemMain() = default;
    ~SystemMain() = default;

    bool initialize();
    void finalize() const;
    void main() const;

private:
    std::shared_ptr<GameSettingRecord> game_setting_record_ptr_;
};

}  // namespace match_stick
