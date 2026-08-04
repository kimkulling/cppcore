/*
-------------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2026 Kim Kulling

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-------------------------------------------------------------------------------------------------
*/
#include <cppcore/IO/TAsyncLoader.h>

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <thread>

using namespace cppcore;

class TAsyncLoaderTest : public testing::Test {};

TEST_F(TAsyncLoaderTest, createTest) {
    TAsyncLoader<int> loader;
    EXPECT_EQ(0u, loader.numPending());
    EXPECT_FALSE(loader.hasPending());
}

TEST_F(TAsyncLoaderTest, loadReturnsResultTest) {
    TAsyncLoader<int> loader;
    std::future<int> request = loader.load([]() { return 42; });
    EXPECT_EQ(42, request.get());
}

TEST_F(TAsyncLoaderTest, loadRunsAsyncFunctionTest) {
    TAsyncLoader<int> loader;
    std::atomic<bool> released{false};
    std::future<int> request = loader.load([&released]() {
        while (!released.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        return 7;
    });

    EXPECT_TRUE(loader.hasPending());
    EXPECT_EQ(1u, loader.numPending());

    released.store(true);
    EXPECT_EQ(7, request.get());
}

TEST_F(TAsyncLoaderTest, waitForAllTest) {
    TAsyncLoader<int> loader;
    std::future<int> r1 = loader.load([]() { return 1; });
    std::future<int> r2 = loader.load([]() { return 2; });
    std::future<int> r3 = loader.load([]() { return 3; });

    loader.waitForAll();

    EXPECT_EQ(0u, loader.numPending());
    EXPECT_FALSE(loader.hasPending());
    EXPECT_EQ(1, r1.get());
    EXPECT_EQ(2, r2.get());
    EXPECT_EQ(3, r3.get());
}
