
#pragma once

#include <algorithm>
#include <array>
#include <string>
#include <utility>
#include <vector>

#include "match_game_rule.h"

namespace match_stick {

struct MatchGameField final {
    static constexpr int kMaxHand = 3;

    enum class State {
        kPlayer1Win,
        kPlayer2Win,
        kGameContinue,
        kDraw,
    };

    constexpr MatchGameField() = default;

    constexpr bool operator ==(const MatchGameField& other) const {
        return player1_hand == other.player1_hand &&
            player2_hand == other.player2_hand &&
            player1_turn == other.player1_turn;
    }

    constexpr bool operator !=(const MatchGameField& other) const {
        return !(*this == other);
    }

    constexpr bool operator <(const MatchGameField& other) const {
        if (player1_hand != other.player1_hand) {
            return player1_hand < other.player1_hand;
        }

        if (player2_hand != other.player2_hand) {
            return player2_hand < other.player2_hand;
        }

        return player1_turn < other.player1_turn;
    }

    std::array<int, kMaxHand> player1_hand{ 0, 0, 0 };
    std::array<int, kMaxHand> player2_hand{ 0, 0, 0 };

    bool player1_turn{ true };

    std::string toString() const;

    //! @brief 現在の盤面が終了状態かどうかを返す．
    constexpr State getState(const MatchGameRule& rule) const {
        if (player1_hand[0] == 0 && player1_hand[1] == 0 && player1_hand[2] == 0) {
            return rule.reverse_valid ? State::kPlayer2Win : State::kPlayer1Win;
        }

        if (player2_hand[0] == 0 && player2_hand[1] == 0 && player2_hand[2] == 0) {
            return rule.reverse_valid ? State::kPlayer1Win : State::kPlayer2Win;
        }

        if (player1_hand[0] == 0 && player1_hand[1] == 0 && player1_hand[2] == 0 &&
            player2_hand[0] == 0 && player2_hand[1] == 0 && player2_hand[2] == 0) {
            return State::kDraw;
        }

        return State::kGameContinue;
    }

    //! @brief 手を昇順に並び替える．
    constexpr void sortHand() {
        std::sort(player1_hand.begin(), player1_hand.end());
        std::sort(player2_hand.begin(), player2_hand.end());
    }

    //! @brief 初期盤面を生成する．
    static constexpr MatchGameField createInitialField(const MatchGameRule& rule) {
        MatchGameField field;

        field.player1_hand[0] = rule.max_start_valid ? 4 : 1;
        field.player1_hand[1] = rule.max_start_valid ? 4 : 1;
        field.player1_hand[2] = 0;

        field.player2_hand[0] = rule.max_start_valid ? 4 : 1;
        field.player2_hand[1] = rule.max_start_valid ? 4 : 1;
        field.player2_hand[2] = 0;

        return field;
    }

    //! @brief 次の盤面を生成する．
    std::vector<MatchGameField> createNextFieldList(const MatchGameRule& rule) const;

    //! @brief 攻撃を行う．ターンプレイヤーが相手プレイヤーの手札を攻撃する．
    //! @param attack_player_index 攻撃するプレイヤーの手札のインデックス
    //! @param attacked_player_index 攻撃されるプレイヤーの手札のインデックス
    void attack(const MatchGameRule& rule, int attack_player_hand_index, int attacked_player_hand_index);

    //! @brief プレイヤーの手を負の数にする．
    void changeNegativeNumber(const MatchGameRule& rule, int hand_index);

    //! @brief 自傷を行う．
    void selfHarm(const MatchGameRule& rule, int attack_hand_index, int attacked_hand_index);
};

}  // namespace match_stick
