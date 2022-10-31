
#include <bitset>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <vector>

// static const std::size_t bits_per_char = 0x08;  // 8 bits in 1 char(unsigned)

// static const unsigned char bit_mask[bits_per_char] = {
//     0x01,  // 00000001
//     0x02,  // 00000010
//     0x04,  // 00000100
//     0x08,  // 00001000
//     0x10,  // 00010000
//     0x20,  // 00100000
//     0x40,  // 01000000
//     0x80   // 10000000
// };

class bloom_filter {
 private:
 public:
  ~bloom_filter();

  bloom_filter() = default;

  explicit bloom_filter(size_t num_items);

  explicit bloom_filter(
      size_t num_items,
      std::initializer_list<std::function<size_t(const char* data)>>
          hash_funcs);

  void insert(const char* data);

  bool contains(const char* data);

  friend std::ostream& operator<<(std::ostream& os, const bloom_filter& bloom);

  static const size_t BSIZE;

 private:
  size_t num_items_{0};
  std::vector<std::function<size_t(const char* data)>> hash_functions_;
  char* buffer_;
  std::allocator<char> alloc_;
};
