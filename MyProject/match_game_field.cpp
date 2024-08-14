
#include "match_game_field.h"

#include <cmath>

#include "dxlib_assert.h"

namespace match_stick {

std::string MatchGameField::toString() const {
    std::string str = "Player1: ";
    for (int i = 0; i < kMaxHand; ++i) {
        str += std::to_string(player1_hand[i]) + " ";
    }

    str += "Player2: ";
    for (int i = 0; i < kMaxHand; ++i) {
        str += std::to_string(player2_hand[i]) + " ";
    }

    str += "Turn: ";
    str += player1_turn ? "Player1" : "Player2";

    return str;
}

std::vector<std::tuple<MatchGameField, MatchGameField::Move>>
MatchGameField::createNextFieldList(const MatchGameRule& rule) const {
    std::vector<std::tuple<MatchGameField, MatchGameField::Move>> result;

    // 攻撃による次の状態を生成する．
    for (int i = 0; i < kMaxHand; ++i) {
        for (int j = 0; j < kMaxHand; ++j) {
            if (player1_turn && (player1_hand[i] == 0 || player2_hand[j] == 0)) {
                continue;
            }

            if (!player1_turn && (player2_hand[i] == 0 || player1_hand[j] == 0)) {
                continue;
            }

            MatchGameField next_field = *this;
            next_field.attack(rule, i, j);

            Move move;
            move.type = Move::Type::kAttack;
            move.attack_index = i;
            move.attacked_index = j;

            result.push_back({ next_field, move });
        }
    }

    // 負の数による次の状態を生成する．
    if (rule.negative_number_valid) {
        for (int i = 0; i < kMaxHand; ++i) {
            if (player1_turn && player1_hand[i] == 0) {
                continue;
            }

            if (!player1_turn && player2_hand[i] == 0) {
                continue;
            }

            MatchGameField next_field = *this;
            next_field.changeNegativeNumber(rule, i);

            Move move;
            move.type = Move::Type::kChangeNegativeNumber;
            move.change_negative_number_index = i;

            result.push_back({ next_field ,move });
        }
    }

    // 自傷による次の状態を生成する．
    if (rule.self_harm_valid) {
        for (int i = 0; i < kMaxHand; ++i) {
            for (int j = 0; j < kMaxHand; ++j) {
                if (i == j) {
                    continue;
                }

                if (player1_turn && (player1_hand[i] == 0 || player1_hand[j] == 0)) {
                    continue;
                }

                if (!player1_turn && (player2_hand[i] == 0 || player2_hand[j] == 0)) {
                    continue;
                }

                MatchGameField next_field = *this;
                next_field.selfHarm(rule, i, j);

                Move move;
                move.type = Move::Type::kSelfHarm;
                move.attack_index = i;
                move.attacked_index = j;

                result.push_back({ next_field, move });
            }
        }
    }

    return result;
}

void MatchGameField::attack(const MatchGameRule& rule,
    const int attack_index, const int attacked_index) {
    ASSERT(0 <= attack_index && attack_index < kMaxHand, "The index is invalid.");
    ASSERT(0 <= attacked_index && attacked_index < kMaxHand, "The index is invalid.");

    // 考えるべきことは，カットオフルールの場合は切り捨てること．
    const int cut_off_number = rule.five_over_valid ? 10 : 5;

    // 攻撃と防御の手札を取得する．
    int& attack = player1_turn ? player1_hand[attack_index] : player2_hand[attack_index];
    int& defense = player1_turn ? player2_hand[attacked_index] : player1_hand[attacked_index];

    ASSERT(attack != 0, "The attack hand is zero.");
    ASSERT(defense != 0, "The defense hand is zero.");

    // プレイヤー1の攻撃
    defense += attack;

    if (rule.cut_off_valid) {
        // カットオフルールの場合は，切り捨てる．
        defense = abs(defense) >= cut_off_number ? 0 : defense;
    } else {
        // 負の数になった場合はいったん正にする．
        const bool is_positive = defense > 0;
        defense = is_positive ? defense : -defense;

        // cut_off_number で割った余りを求める． 10で割った場合は，5ちょうどになる場合0にする．
        defense %= cut_off_number;
        defense = defense == 5 ? 0 : defense;

        // 負の数だった場合は，もとに戻す．
        defense = is_positive ? defense : -defense;
    }

    player1_turn = !player1_turn;
}

void MatchGameField::changeNegativeNumber(const MatchGameRule& rule, const int hand_index) {
    ASSERT(rule.negative_number_valid, "The negative number is invalid.");
    ASSERT(0 <= hand_index && hand_index < kMaxHand, "The index is invalid.");

    int& hand = player1_turn ? player1_hand[hand_index] : player2_hand[hand_index];

    ASSERT(hand != 0, "The hand is zero.");

    // 負の数にする．
    hand = -hand;

    player1_turn = !player1_turn;
}

void MatchGameField::selfHarm(const MatchGameRule& rule, const int attack_hand_index, const int attacked_hand_index) {
    ASSERT(rule.self_harm_valid, "The self harm is invalid.");
    ASSERT(0 <= attack_hand_index && attack_hand_index < kMaxHand, "The index is invalid.");
    ASSERT(0 <= attacked_hand_index && attacked_hand_index < kMaxHand, "The index is invalid.");

    int& attack = player1_turn ? player1_hand[attack_hand_index] : player2_hand[attack_hand_index];
    int& defense = player1_turn ? player1_hand[attacked_hand_index] : player2_hand[attacked_hand_index];

    ASSERT(attack != 0, "The attack hand is zero.");
    ASSERT(defense != 0, "The defense hand is zero.");

    // 考えるべきことは，カットオフルールの場合は切り捨てること．
    const int cut_off_number = rule.five_over_valid ? 10 : 5;

    // プレイヤー1の攻撃
    defense += attack;

    if (rule.cut_off_valid) {
        // カットオフルールの場合は，切り捨てる．
        defense = abs(defense) >= cut_off_number ? 0 : defense;
    } else {
        // 負の数になった場合はいったん正にする．
        const bool is_positive = defense > 0;
        defense = is_positive ? defense : -defense;

        // cut_off_number で割った余りを求める． 10で割った場合は，5ちょうどになる場合0にする．
        defense %= cut_off_number;
        defense = defense == 5 ? 0 : defense;

        // 負の数だった場合は，もとに戻す．
        defense = is_positive ? defense : -defense;
    }

    player1_turn = !player1_turn;
}

std::vector<MatchGameField> MatchGameField::createFreeSortFieldList(const MatchGameRule& rule) const {
    ASSERT(rule.free_sort_valid, "The free sort is invalid.");
    ASSERT(getAliveHandNum(player1_turn) == 1, "The hand num is invalid.");
    ASSERT(getAliveHandNum(player1_turn) == 0, "The hand num is invalid.");

    std::vector<MatchGameField> next_field_list;

    // 合計値を取得する．

    return next_field_list;
}

std::string MatchGameField::Move::toString() const {
    switch (type) {
    case match_stick::MatchGameField::Move::Type::kNone: {
        return "None";
    }
    case match_stick::MatchGameField::Move::Type::kAttack: {
        return "Attack: " + std::to_string(attack_index) + " -> " + std::to_string(attacked_index);
    }
    case match_stick::MatchGameField::Move::Type::kChangeNegativeNumber: {
        return "ChangeNegativeNumber: " + std::to_string(change_negative_number_index);
    }
    case match_stick::MatchGameField::Move::Type::kSelfHarm: {
        return "SelfHarm: " + std::to_string(attack_index) + " -> " + std::to_string(attacked_index);
    }
    case match_stick::MatchGameField::Move::Type::kFreeSort: {
        return "FreeSort";
    }
    default:
        ASSERT_MUST_NOT_REACH_HERE();
        break;
    }

    return "";
}

}  // namespace match_stick
