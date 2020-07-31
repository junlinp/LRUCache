#include "type_RAII.hpp"

#include "gtest/gtest.h"
TEST(T, t) { EXPECT_TRUE(true); }

TEST(type_RAII, aithmetic) { LRUCache::TypeRAII<int> raii("./aithmetic.bin"); }

int main(int argc, char** argv) {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}