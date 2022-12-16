#include <cstddef>

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
