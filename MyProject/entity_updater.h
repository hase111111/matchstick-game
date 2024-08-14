
#pragma once

#include <vector>
#include <memory>

#include "i_entity.h"

namespace match_stick {

//! @brief entity の更新を管理するクラス．
class EntityUpdater final {
public:
    EntityUpdater() = default;
    ~EntityUpdater() = default;

    //! @brief entity を登録する．
    //! @param entity_ptr 登録する entity，nullptr の場合は ASSERT で落ちる．
    void registerEntity(const std::shared_ptr<IEntity>& entity_ptr);

    //! @brief entity の update を呼び出す
    //! @details false を返した entity は削除する．
    void update();

    //! @brief 登録された renderable を描画する．
    //! @details レイヤー順にソートして描画する．
    void draw() const;

private:
    std::vector<std::shared_ptr<IEntity>> entities_;  //!< 登録された entity
};

}  // namespace match_stick
