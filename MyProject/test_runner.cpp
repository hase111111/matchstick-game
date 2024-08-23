
#include "test_runner.h"

#include <doctest.h>

#include "test_register.h"

namespace match_stick {

bool TestRunner::run() const {
    // テストを実行する
    doctest::Context context;

    context.setOption("no-breaks", true);

    int res = context.run();

    return res == 0;
}

}  // namespace match_stick
