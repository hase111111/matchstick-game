
#pragma once

#include <doctest.h>

#include "scene_change_parameter.h"

TEST_CASE("SceneChangeParameter::setParameter") {
    using ::match_stick::SceneChangeParameter;

    // Arrange
    SceneChangeParameter parameter;

    // Act
    parameter.setParameter("int", 42);
    parameter.setParameter("double", 3.14);
    parameter.setParameter("string", std::string{ "Hello, World!" });

    // Assert
    CHECK(parameter.hasParameter("int"));
    CHECK(parameter.hasParameter("double"));
    CHECK(parameter.hasParameter("string"));

    // 存在しないキーを指定した場合は false を返す
    CHECK_FALSE(parameter.hasParameter("not_exist"));
}

TEST_CASE("SceneChangeParameter::getParameter") {
    using ::match_stick::SceneChangeParameter;

    // Arrange
    SceneChangeParameter parameter;
    parameter.setParameter("int", 42);
    parameter.setParameter("double", 3.14);
    parameter.setParameter("string", std::string{ "Hello, World!" });

    // Act
    auto int_value = parameter.getParameter<int>("int");
    auto double_value = parameter.getParameter<double>("double");
    auto string_value = parameter.getParameter<std::string>("string");

    // Assert
    CHECK_EQ(int_value, 42);
    CHECK_EQ(double_value, 3.14);
    CHECK_EQ(string_value, "Hello, World!");
}

TEST_CASE("SceneChangeParameter::reset") {
    using ::match_stick::SceneChangeParameter;

    // Arrange
    SceneChangeParameter parameter;

    parameter.setParameter("int", 42);
    parameter.setParameter("double", 3.14);
    parameter.setParameter("string", std::string{ "Hello, World!" });

    CHECK(parameter.hasParameter("int"));
    CHECK(parameter.hasParameter("double"));
    CHECK(parameter.hasParameter("string"));

    // Act
    parameter.reset();

    // Assert
    CHECK_FALSE(parameter.hasParameter("int"));
    CHECK_FALSE(parameter.hasParameter("double"));
    CHECK_FALSE(parameter.hasParameter("string"));
}
