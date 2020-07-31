#include "type_RAII.hpp"

#include "gtest/gtest.h"
TEST(T, t) { EXPECT_TRUE(true); }

TEST(type_RAII, aithmetic) { LRUCache::TypeRAII<int> raii("./aithmetic.bin"); }

struct SelfDefined {
  int a;
  double b;

  template <class Archive>
  void serialize(Archive& ar) {
    ar(a, b);
  }
};
TEST(type_RAII, Struct) {
  LRUCache::TypeRAII<SelfDefined> raii("./Struct.bin");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}