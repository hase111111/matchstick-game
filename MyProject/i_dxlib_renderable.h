
#pragma once

namespace match_stick {

class IDxLibRenderable {
public:
    virtual ~IDxLibRenderable() = default;

    virtual int getLayer() const = 0;

    virtual void draw() const = 0;
};

namespace constants {

constexpr int kBottomLayer = 0;  //<! 最下層のレイヤー
constexpr int kBackGroundLayer = 100;  //<! 背景のレイヤー
constexpr int kDefaultLayer = 200;  //<! デフォルトのレイヤー
constexpr int kUIBottomLayer = 300;  //<! UIの最前面のレイヤー
constexpr int kUIMiddleLayer = 400;  //<! UIの最前面のレイヤー
constexpr int kUIFrontLayer = 500;  //<! UIの最前面のレイヤー
constexpr int kFrontLayer = 600;  //<! 最前面のレイヤー

}  // namespace constants

}  // namespace match_stick
