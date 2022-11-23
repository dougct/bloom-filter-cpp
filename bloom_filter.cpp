

#include <functional>
#include <iostream>

#include "bloom_filter.h"


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
    const auto bit = hash % (num_items_ * bitsPerChar);
    buffer_[bit / bitsPerChar] |= 1 << (bit % bitsPerChar);
  }
}

bool bloom_filter::contains(const char* data) {
  for (const auto& hash_func : hash_functions_) {
    const auto hash = hash_func(data);
    const auto bit = hash % (num_items_ * bitsPerChar);
    if (!(buffer_[bit / bitsPerChar] & (1 << (bit % bitsPerChar)))) {
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
