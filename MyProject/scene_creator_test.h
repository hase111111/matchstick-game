
//! @file scene_creator_test.h
//! @brief
//! Copyright(c) 2024 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <doctest.h>

#include <memory>

#include <magic_enum.hpp>

#include "scene_creator.h"


TEST_CASE("SceneCreator::createScene when create debug scene, should not return nullptr") {
    using match_stick::SceneCreator;
    using match_stick::SceneChangeListener;
    using match_stick::FpsController;
    using match_stick::LanguageRecord;
    using match_stick::DxLibInput;
    using match_stick::DxLibResourceLoader;
    using match_stick::SceneName;

    // Arrange
    const auto scene_change_listener = std::make_shared<SceneChangeListener>();
    const auto fps_controller = std::make_shared<FpsController>(60);
    const auto language_record = std::make_shared<LanguageRecord>();
    const auto dxlib_input = std::make_shared<DxLibInput>();
    const auto dxlib_resource_loader = std::make_shared<DxLibResourceLoader>();

    const auto scene_creator = std::make_unique<SceneCreator>(
        scene_change_listener,
        fps_controller,
        language_record,
        dxlib_input,
        dxlib_resource_loader);

    // Act
    const auto scene = scene_creator->createScene(SceneName::kDebug);

    // Assert
    CHECK(scene != nullptr);
}
