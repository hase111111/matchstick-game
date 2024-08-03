
#pragma once

namespace match_stick {

struct MatchGameRule final {
    constexpr MatchGameRule() = default;

    bool cut_off_valid{ false };
    bool five_over_valid{ false };
    bool max_start_valid{ false };
    bool reverse_valid{ false };
    bool negative_number_valid{ false };
    bool triple_hand_valid{ false };

    bool self_harm_valid{ false };
    bool free_sort_valid{ false };
    bool division_valid{ false };
    bool union_valid{ false };
};

}  // namespace match_stick