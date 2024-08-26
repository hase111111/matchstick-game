
#pragma once

#include <doctest.h>

#include <memory>

#include "entity_updater.h"

namespace match_stick::entity_updater_test_internal {

class TestEntity final : public IEntity {
public:
    TestEntity(const int layer) : layer_(layer) {}
    ~TestEntity() = default;

    inline int getLayer() const override {
        return layer_;
    }

    bool update() override {
        ++counter_;
        return true;
    }

    void draw() const override {}

    int getCounter() const {
        return counter_;
    }

private:
    const int layer_{ 0 };
    int counter_{ 0 };
};

class TestEntity2 final : public IEntity {
public:
    TestEntity2(const int layer) : layer_(layer) {}
    ~TestEntity2() = default;

    inline int getLayer() const override {
        return layer_;
    }

    bool update() override {
        ++counter_;
        return false;
    }

    void draw() const override {}

    int getCounter() const {
        return counter_;
    }

private:
    const int layer_{ 0 };
    int counter_{ 0 };
};

}  // namespace match_stick::entity_updater_test_internal

TEST_CASE("EntityUpdater::update") {
    using ::match_stick::entity_updater_test_internal::TestEntity;
    using ::match_stick::EntityUpdater;

    // Arrange
    EntityUpdater updater;

    auto entity1 = std::make_shared<TestEntity>(0);
    auto entity2 = std::make_shared<TestEntity>(1);

    updater.registerEntity(entity1);
    updater.registerEntity(entity2);

    // Act1
    updater.update();

    // Assert1
    CHECK_EQ(entity1->getCounter(), 1);
    CHECK_EQ(entity2->getCounter(), 1);

    // Act2
    updater.update();

    // Assert2
    CHECK_EQ(entity1->getCounter(), 2);
    CHECK_EQ(entity2->getCounter(), 2);
}

TEST_CASE("EntityUpdater::update when entity's update return false, should delete entity") {
    using ::match_stick::entity_updater_test_internal::TestEntity;
    using ::match_stick::entity_updater_test_internal::TestEntity2;
    using ::match_stick::EntityUpdater;

    // Arrange
    EntityUpdater updater;

    auto entity1 = std::make_shared<TestEntity>(0);
    auto entity2 = std::make_shared<TestEntity2>(1);  // update return false

    updater.registerEntity(entity1);
    updater.registerEntity(entity2);
    CHECK_EQ(entity2.use_count(), 2);  // entity2 is shared by updater and variable

    // Act
    updater.update();  // entity2 is deleted

    // Assert
    CHECK_EQ(entity1->getCounter(), 1);
    CHECK_EQ(entity2->getCounter(), 1);  // entity2's update is called
    CHECK_EQ(entity2.use_count(), 1);  // entity2 is shared by variable
}
