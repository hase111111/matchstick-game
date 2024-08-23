
#pragma once

#include <doctest.h>

#include "scene_change_listener.h"

TEST_CASE("SceneChangeListener::requestAddScene") {
    using ::match_stick::SceneChangeListener;
    using ::match_stick::SceneName;

    // Arrange

    SceneChangeListener listener;

    CHECK_FALSE(listener.hasRequest());  // 最初はリクエストがない

    // Act
    listener.requestAddScene(SceneName::kDebug, {});

    // Assert
    CHECK(listener.hasRequest());  // リクエストがある
}

TEST_CASE("SceneChangeListener::requestDeleteScene") {
    using ::match_stick::SceneChangeListener;

    // Arrange

    SceneChangeListener listener;

    CHECK_FALSE(listener.hasRequest());  // 最初はリクエストがない

    // Act
    listener.requestDeleteScene(1, {});

    // Assert
    CHECK(listener.hasRequest());  // リクエストがある
}

TEST_CASE("SceneChangeListener::requestDeleteAllScene") {
    using ::match_stick::SceneChangeListener;

    // Arrange

    SceneChangeListener listener;

    CHECK_FALSE(listener.hasRequest());  // 最初はリクエストがない

    // Act
    listener.requestDeleteAllScene();

    // Assert
    CHECK(listener.hasRequest());  // リクエストがある
}

TEST_CASE("SceneChangeListener::receiveRequest When add scene") {
    using ::match_stick::SceneChangeListener;
    using ::match_stick::SceneName;
    using ::match_stick::SceneChangeParameter;

    // Arrange
    SceneChangeListener listener;
    SceneChangeParameter parameter{};

    CHECK_FALSE(listener.hasRequest());  // 最初はリクエストがない

    // Act.1
    parameter.setParameter("key", 1);
    listener.requestAddScene(SceneName::kDebug, parameter);

    // Assert.1
    CHECK(listener.hasRequest());  // リクエストがある

    // Act.2
    SceneName scene_name{};
    SceneChangeParameter parameter2{};
    int delete_num{};
    auto request_type = listener.receiveRequest(&scene_name, &parameter2, &delete_num);

    // Assert.2
    CHECK_EQ(request_type, SceneChangeListener::RequestType::kAddScene);
    CHECK_EQ(scene_name, SceneName::kDebug);
    CHECK_EQ(parameter2.getParameter<int>("key"), 1);

    CHECK_FALSE(listener.hasRequest());  // リクエストがなくなる
}

TEST_CASE("SceneChangeListener::receiveRequest When delete scene") {
    using ::match_stick::SceneChangeListener;
    using ::match_stick::SceneName;
    using ::match_stick::SceneChangeParameter;

    // Arrange

    SceneChangeListener listener;
    SceneChangeParameter parameter{};
    parameter.setParameter("key", 1);

    CHECK_FALSE(listener.hasRequest());  // 最初はリクエストがない

    // Act.1
    listener.requestDeleteScene(1, parameter);

    // Assert.1
    CHECK(listener.hasRequest());  // リクエストがある

    // Act.2
    SceneName scene_name{};
    SceneChangeParameter parameter2{};
    int delete_num{};
    auto request_type = listener.receiveRequest(&scene_name, &parameter2, &delete_num);

    // Assert.2
    CHECK_EQ(request_type, SceneChangeListener::RequestType::kDeleteScene);
    CHECK_EQ(delete_num, 1);
    CHECK_EQ(parameter2.getParameter<int>("key"), 1);

    CHECK_FALSE(listener.hasRequest());  // リクエストがなくなる
}

TEST_CASE("SceneChangeListener::receiveRequest When delete all scene") {
    using ::match_stick::SceneChangeListener;
    using ::match_stick::SceneName;
    using ::match_stick::SceneChangeParameter;

    // Arrange

    SceneChangeListener listener;

    CHECK_FALSE(listener.hasRequest());  // 最初はリクエストがない

    // Act.1
    listener.requestDeleteAllScene();

    // Assert.1
    CHECK(listener.hasRequest());  // リクエストがある

    // Act.2
    SceneName scene_name{};
    SceneChangeParameter parameter{};
    int delete_num{};
    auto request_type = listener.receiveRequest(&scene_name, &parameter, &delete_num);

    // Assert.2
    CHECK_EQ(request_type, SceneChangeListener::RequestType::kDeleteAllScene);

    CHECK_FALSE(listener.hasRequest());  // リクエストがなくなる
}
