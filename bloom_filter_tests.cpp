#include "gtest/gtest.h"

#include "bloom_filter.h"
#include "hash_functions.h"

TEST(BloomFilter, SimpleTest) {
  const char* hello = "hello";
  const char* hello_world = "hello world";
  const char* world = "world";
  const char* typo = "wordl";

  auto bloomf = bloom_filter(8, {djb2, jenkins});

  EXPECT_FALSE(bloomf.contains(hello));

  bloomf.insert(hello);
  EXPECT_TRUE(bloomf.contains(hello));

  EXPECT_FALSE(bloomf.contains(hello_world));
  bloomf.insert(hello_world);
  EXPECT_TRUE(bloomf.contains(hello_world));

  EXPECT_FALSE(bloomf.contains(world));
  bloomf.insert(world);
  EXPECT_TRUE(bloomf.contains(world));

  EXPECT_FALSE(bloomf.contains(typo));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
