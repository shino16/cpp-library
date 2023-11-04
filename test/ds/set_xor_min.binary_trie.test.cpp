#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include "io.hpp"
#include "ds/hash_set.hpp"
#include "ds/binary_trie.hpp"

int main() {
  binary_trie<int, (1 << 30) - 1, pool<1 << 24>, xor_mask_enabled> trie;
  hash_set<int> s;
  int q = in;
  while (q--) {
    int cmd = in, x = in;
    if (cmd == 0) {
      if (s.insert(x).second) trie.insert(x);
    } else if (cmd == 1) {
      if (s.erase(x)) trie.erase(x);
    } else {
      trie.set_mask(x);
      out(trie.min());
      trie.set_mask(0);
    }
  }
}
