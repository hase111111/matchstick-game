
#pragma once

namespace match_stick {

//! @brief ゲーム中に登場するエンティティの基底クラス
class IEntity {
public:
    virtual ~IEntity() = default;

    //! @brief エンティティの更新処理を行う
    //! @return エンティティの削除を行うかどうか
    //! @retval true 削除しない
    //! @retval false 削除する
    [[nodiscard]]
    virtual bool update() = 0;

    //! @brief エンティティのレイヤーを取得する
    //! @return レイヤー，int型で値が大きいほど手前に表示される
    //! @note レイヤーが同じ場合は登録順に表示される
    [[nodiscard]]
    virtual int getLayer() const = 0;

    //! @brief エンティティの描画処理を行う
    virtual void draw() const = 0;
};

namespace constants {

constexpr int kNoLayer = -1;  //<! レイヤーを持たないエンティティ
constexpr int kBottomLayer = 100;  //<! 最下層のレイヤー
constexpr int kBackGroundLayer = 200;  //<! 背景のレイヤー
constexpr int kDefaultLayer = 300;  //<! デフォルトのレイヤー
constexpr int kUIBottomLayer = 400;  //<! UIの最前面のレイヤー
constexpr int kUIMiddleLayer = 500;  //<! UIの最前面のレイヤー
constexpr int kUIFrontLayer = 600;  //<! UIの最前面のレイヤー
constexpr int kFrontLayer = 700;  //<! 最前面のレイヤー

}  // namespace constants

}  // namespace match_stick
