
#include <bitset>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <vector>

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
