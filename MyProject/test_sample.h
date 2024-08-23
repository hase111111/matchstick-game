
#pragma once

#include <doctest.h>

namespace match_stick {

class Sample final {
public:
    Sample() = default;
    ~Sample() = default;

    inline int add(int a, int b) const {
        return a + b;
    }
};

}  // namespace match_stick

TEST_CASE("Sample::add") {
    match_stick::Sample sample;

    CHECK(sample.add(1, 2) == 3);
    CHECK(sample.add(2, 3) == 5);
    CHECK(sample.add(3, 4) == 7);
    CHECK(sample.add(4, 5) == 9);
    CHECK(sample.add(5, 6) == 11);
}
