#include "type_RAII.hpp"

#include "gtest/gtest.h"
TEST(T, t) { EXPECT_TRUE(true); }

TEST(type_RAII, aithmetic) { LRUCache::TypeRAII<int> raii("./aithmetic.bin"); }

struct SelfDefined {
  int a;
  double b;
  SelfDefined() : a(1), b(0.0) {}
  bool operator==(const SelfDefined& rhs) const {
    return a == rhs.a && b == rhs.b;
  }
  template <class Archive>
  void serialize(Archive& ar) {
    ar(a, b);
  }
};
TEST(type_RAII, Struct) {
  LRUCache::TypeRAII<SelfDefined> raii("./Struct.bin");
  SelfDefined self_defined_struct1, self_defined_struct2;
  EXPECT_EQ(self_defined_struct1.a, self_defined_struct2.a);
  EXPECT_EQ(self_defined_struct1.b, self_defined_struct2.b);
  EXPECT_EQ(self_defined_struct1, self_defined_struct2);
  EXPECT_EQ(raii, self_defined_struct1);
  raii.a = 2.0;
  raii = self_defined_struct1;
  EXPECT_EQ(raii, self_defined_struct1);
  EXPECT_EQ(raii.SavePath(), std::string("./Struct.bin"));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}