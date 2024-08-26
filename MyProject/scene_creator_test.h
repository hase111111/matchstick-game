
#pragma once

#include <magic_enum.hpp>

#include <doctest.h>

#include "scene_creator.h"

TEST_CASE("SceneCreator::createScene when create title scene, should not return nullptr") {
    using match_stick::SceneCreator;

    // Arrange
    const auto scene_change_listener = std::make_shared<match_stick::SceneChangeListener>();
    const auto fps_controller = std::make_shared<match_stick::FpsController>(60);
    const auto language_record = std::make_shared<match_stick::LanguageRecord>();
    const auto dxlib_input = std::make_shared<match_stick::DxLibInput>();
    const auto dxlib_resource_loader = std::make_shared<match_stick::DxLibResourceLoader>();

    const auto scene_creator = std::make_unique<SceneCreator>(
        scene_change_listener,
        fps_controller,
        language_record,
        dxlib_input,
        dxlib_resource_loader);

    // Act
    const auto scene = scene_creator->createScene(match_stick::SceneName::kTitle);

    // Assert
    CHECK(scene != nullptr);
}
