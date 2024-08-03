
#include "match_game_sample.h"

#include <DxLib.h>

#include "dxlib_debug_print.h"
#include "match_game_field.h"

namespace match_stick {

void MatchGameSample::run() {
    MatchGameRule rule;
    rule.self_harm_valid = true;
    rule.negative_number_valid = true;
    MatchGameField field = MatchGameField::createInitialField(rule);

    DEBUG_PRINT(field.toString());

    // ループを回す．
    while (true) {
        // 次の状態を生成する．
        std::vector<MatchGameField> next_field_list = field.createNextFieldList(rule);

        // 次の状態を選択する．
        field = next_field_list[GetRand(static_cast<int>(next_field_list.size() - 1))];
        DEBUG_PRINT(field.toString());

        // 終了状態かどうかを確認する．
        MatchGameField::State state = field.getState(rule);
        if (state != MatchGameField::State::kGameContinue) {
            break;
        }
    }

    DEBUG_PRINT_LINE();
}

}  // namespace match_stick
