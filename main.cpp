#include <iostream>

#include "bloom_filter.h"

namespace {

size_t djb2(const char* _str) {
  const char* str = _str;
  size_t hash = 5381;
  char c;
  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

size_t jenkins(const char* _str) {
  const char* key = _str;
  size_t hash = 0;
  while (*key) {
    hash += *key;
    hash += (hash << 10);
    hash ^= (hash >> 6);
    key++;
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}

}  // namespace

int main() {
  const char* hello = "hello";
  const char* hello_world = "hello world";
  const char* world = "world";
  const char* typo = "wordl";

  auto bloomf = bloom_filter(8, {djb2, jenkins});

  std::cout << "Shouldn't be present - " << hello << ": ";
  std::cout << bloomf.contains(hello) << std::endl;

  bloomf.insert(hello);
  std::cout << "Should be present - " << hello << ": ";
  std::cout << bloomf.contains(hello) << std::endl;

  std::cout << "Shouldn't be present - " << hello_world << ": ";
  std::cout << bloomf.contains(hello_world) << std::endl;

  bloomf.insert(hello_world);
  std::cout << "Should be present - " << hello_world << ": ";
  std::cout << bloomf.contains(hello_world) << std::endl;

  std::cout << "Shouldn't be present - " << world << ": ";
  std::cout << bloomf.contains(world) << std::endl;

  bloomf.insert(world);
  std::cout << "Should be present - " << world << ": ";
  std::cout << bloomf.contains(world) << std::endl;

  std::cout << "Shouldn't be present (probably) - " << typo << ": ";
  std::cout << bloomf.contains(typo) << std::endl;

  return 0;
}
