#pragma once
#include "util/pool.hpp"

template <class T>
struct xor_mask_enabled {
  void set_mask(T s2) { s = s2; }
  void add_mask(T s2) { s ^= s2; }
  T mask() const { return s; }

 private:
  T s = 0;
};

template <class T>
struct xor_mask_disabled {
  constexpr T mask() const { return 0; }
};

// [0, U]
template <
    class T, T U, class Alloc = pool<>,
    template <class> class XorMask = xor_mask_disabled>
class binary_trie : public XorMask<T> {
 private:
  struct node : Alloc::template alloc<node> {
    node *l = nullptr, *r = nullptr;
    int cnt = 0;
  };

 public:
  binary_trie() = default;

  int size() const { return root->cnt; }
  bool empty() const { return size() == 0; }
  void insert(T x) { insert(root, x, B - 1); }
  void erase(T x) { erase(root, x, B - 1); }
  int count(T x) const { return count(root, x, B - 1); }
  // returns -1 if empty
  T max() const { return empty() ? -1 : max(root, 0, B - 1); }
  // returns -1 if empty
  T min() const { return empty() ? -1 : min(root, 0, B - 1); }
  T find(int k) const { return find(root, 0, k, B - 1); }

 private:
  static constexpr int calc_b(T u) {
    int b = 0;
    while (u) u >>= 1, b++;
    return b;
  }
  static constexpr int B = calc_b(U);

  node* root = new node;

  T bit_at(T x, int i) const { return (x ^ this->mask()) >> i & 1; }
  node* insert(node* p, T x, int i) {
    if (!p)
      p = new node;
    p->cnt++;
    if (i != -1) {
      if (bit_at(x, i)) p->r = insert(p->r, x, i - 1);
      else p->l = insert(p->l, x, i - 1);
    }
    return p;
  }
  void erase(node* p, T x, int i) {
    p->cnt--;
    if (i != -1) {
      if (bit_at(x, i)) erase(p->r, x, i - 1);
      else erase(p->l, x, i - 1);
    }
  }
  int count_tree(const node* p) const { return p ? p->cnt : 0; }
  int count(const node* p, T x, int i) const {
    return !p             ? 0
           : i == -1      ? p->cnt
           : bit_at(x, i) ? count(p->r, x, i - 1)
                          : count(p->l, x, i - 1);
  }
  T max(const node* p, T x, int i) const {
    if (i == -1) return x;
    if (this->mask() >> i & 1)
      return count_tree(p->l) ? max(p->l, x | 1 << i, i - 1)
                              : max(p->r, x, i - 1);
    else
      return count_tree(p->r) ? max(p->r, x | 1 << i, i - 1)
                              : max(p->l, x, i - 1);
  }
  T min(const node* p, T x, int i) const {
    if (i == -1) return x;
    if (this->mask() >> i & 1)
      return count_tree(p->r) ? min(p->r, x, i - 1)
                              : min(p->l, x | 1 << i, i - 1);
    else
      return count_tree(p->l) ? min(p->l, x, i - 1)
                              : min(p->r, x | 1 << i, i - 1);
  }
  T find(const node* p, T x, int k, int i) const {
    if (i == -1) {
      assert(k == 0 && p->cnt != 0);
      return x;
    }
    if (this->mask() >> i & 1)
      return count_tree(p->r) < k
                 ? find(p->r, x, k, i - 1)
                 : find(p->l, x | 1 << i, k - count_tree(p->r), i - 1);
    else
      return count_tree(p->l) < k
                 ? find(p->l, x, k, i - 1)
                 : find(p->r, x | 1 << i, k - count_tree(p->l), i - 1);
  }
};
