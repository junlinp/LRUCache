#include "type_RAII.hpp"

#include <cereal/types/vector.hpp>
#include <memory>
#include <vector>

#include "gtest/gtest.h"

TEST(type_RAII, aithmetic) {
  std::shared_ptr<LRUCache::BasicTypeWrap<int>> raii =
      std::make_shared<LRUCache::TypeRAII<int>>("./int.bin");
  (*raii) = 0;
  for (int i = 0; i < 1024; i++) {
    (*raii) += 1;
    EXPECT_EQ(*raii, i + 1);
    EXPECT_EQ(i + 1, *raii);
    EXPECT_EQ(float(i + 1), *raii);
  }
  for (int i = 0; i < 1024; i++) {
    (*raii) = *raii + 1;
    EXPECT_NE(*raii, i + 1);
    EXPECT_NE(i + 1, *raii);
    EXPECT_NE(float(i + 1), *raii);
  }
  *raii = 0;
  for (int i = 0; i < 1024; i++) {
    *raii = 1 + *raii;
    EXPECT_EQ(*raii, i + 1);
    EXPECT_EQ(i + 1, *raii);
    EXPECT_EQ(float(i + 1), *raii);
  }
}

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
  std::shared_ptr<SelfDefined> raii =
      std::make_shared<LRUCache::TypeRAII<SelfDefined>>("./Struct.bin");
  SelfDefined self_defined_struct1, self_defined_struct2;
  EXPECT_EQ(self_defined_struct1.a, self_defined_struct2.a);
  EXPECT_EQ(self_defined_struct1.b, self_defined_struct2.b);
  EXPECT_EQ(self_defined_struct1, self_defined_struct2);
  EXPECT_EQ(*raii, self_defined_struct1);
  raii->a = 2.0;
  *raii = self_defined_struct1;
  EXPECT_EQ(*raii, self_defined_struct1);
  // auto raii_sub =
  //    std::dynamic_pointer_cast<LRUCache::TypeRAII<SelfDefined>>(raii);
  // EXPECT_EQ(raii_sub->SavePath(), std::string("./Struct.bin"));
}

TEST(type_RAII, STL) {
  std::shared_ptr<std::vector<int>> raii =
      std::make_shared<LRUCache::TypeRAII<std::vector<int>>>("./Vector.bin");
  *raii = std::vector<int>();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}