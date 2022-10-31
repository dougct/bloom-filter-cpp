

#include <functional>
#include <iostream>

#include "bloom_filter.h"

const size_t bloom_filter::BSIZE = 8;

bloom_filter::~bloom_filter() {
  alloc_.deallocate(buffer_, num_items_);
}

bloom_filter::bloom_filter(size_t num_items) : num_items_(num_items) {
  buffer_ = alloc_.allocate(num_items);
  std::fill(buffer_, buffer_ + num_items, 0);
}

bloom_filter::bloom_filter(
    size_t num_items,
    std::initializer_list<std::function<size_t(const char* data)>> hash_funcs)
    : num_items_(num_items), hash_functions_(hash_funcs) {
  buffer_ = alloc_.allocate(num_items);
  std::fill(buffer_, buffer_ + num_items_, 0);
}

void bloom_filter::insert(const char* data) {
  for (const auto& hash_func : hash_functions_) {
    auto hash = hash_func(data);
    hash %= (num_items_ * BSIZE);
    buffer_[hash / BSIZE] |= 1 << (hash % BSIZE);
  }
}

bool bloom_filter::contains(const char* data) {
  for (const auto& hash_func : hash_functions_) {
    auto hash = hash_func(data);
    auto bit = hash % (num_items_ * BSIZE);
    if (!(buffer_[bit / BSIZE] & (1 << (bit % BSIZE)))) {
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
