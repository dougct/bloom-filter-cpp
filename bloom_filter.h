

#include <initializer_list>
#include <vector>

class bloom_filter {
 private:
 public:
  bloom_filter() = default;

  explicit bloom_filter(size_t num_items);

  explicit bloom_filter(
      size_t num_items,
      std::vector<std::function<size_t(const char* data)>>
          hash_funcs);

  void insert(const char* data);

  bool contains(const char* data);

  friend std::ostream& operator<<(std::ostream& os, const bloom_filter& bloom);

  static inline const size_t bitsPerChar = 8;

 private:
  size_t num_items_{0};
  std::vector<char> buffer_;
  std::vector<std::function<size_t(const char* data)>> hash_functions_;
};
