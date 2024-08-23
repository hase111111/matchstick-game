
#pragma once

// DOCTEST_CONFIG_IMPLEMENT が定義されていない場合は定義する
#ifndef DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_CONFIG_IMPLEMENT
#endif  // ifndef DOCTEST_CONFIG_IMPLEMENT

namespace match_stick {

class TestRunner final {
public:
    TestRunner() = default;
    ~TestRunner() = default;

    bool run() const;
};

}  // namespace match_stick
