#include <cppcore/Common/DateTime.h>
#include "gtest/gtest.h"

using namespace cppcore;

class DateTimeTest : public testing::Test {};

TEST_F(DateTimeTest, CreateTest) {
    DateTime dt;
    const time_t ts = ::time(nullptr);
    tm now{};
#if defined(_WIN32)
    ::localtime_s(&now, &ts);
+#else
    ::localtime_r(&ts, &now);
+#endif
    EXPECT_EQ(dt.year, static_cast<uint32_t>(now.tm_year + 1900));
    EXPECT_GE(dt.month, 1u);
    EXPECT_LE(dt.month, 12u);
    EXPECT_GE(dt.day, 1u);
    EXPECT_LE(dt.day, 31u);
}
