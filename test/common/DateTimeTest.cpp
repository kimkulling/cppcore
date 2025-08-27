#include <cppcore/Common/DateTime.h>
#include "gtest/gtest.h"

using namespace cppcore;

class DateTimeTest : public testing::Test {};

TEST_F(DateTimeTest, CreateTest) {
    DateTime dt;
    EXPECT_EQ(dt.year, 2025);
}
