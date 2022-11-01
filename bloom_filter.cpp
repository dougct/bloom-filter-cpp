

#include <functional>
#include <iostream>

#include "bloom_filter.h"

const size_t bloom_filter::BSIZE = 8;

bloom_filter::bloom_filter(size_t num_items)
    : num_items_(num_items), buffer_(num_items, 0) {}

bloom_filter::bloom_filter(
    size_t num_items,
    std::initializer_list<std::function<size_t(const char* data)>> hash_funcs)
    : num_items_(num_items),
      buffer_(num_items, 0),
      hash_functions_(hash_funcs) {}

void bloom_filter::insert(const char* data) {
  for (const auto& hash_func : hash_functions_) {
    const auto hash = hash_func(data);
    const auto target_bit = hash % (num_items_ * BSIZE);
    const auto target_byte = target_bit / BSIZE;
    buffer_[target_byte] |= 1 << (target_bit % BSIZE);
  }
}

bool bloom_filter::contains(const char* data) {
  for (const auto& hash_func : hash_functions_) {
    const auto hash = hash_func(data);
    const auto target_bit = hash % (num_items_ * BSIZE);
    const auto target_byte = target_bit / BSIZE;
    if (!(buffer_[target_byte] & (1 << (target_bit % BSIZE)))) {
      return false;
    }
  }
  return true;
}

std::ostream& operator<<(std::ostream& os, const bloom_filter& bloom) {
  for (size_t i = 0; i < bloom.num_items_; i++) {
    os << std::bitset<8>(bloom.buffer_[i]) << " ";
  }
  os << std::endl;
  return os;
}
