#define PROBLEM \
  "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include <atcoder/modint>

#include "bbst/implicit_treap.hpp"
using mint = atcoder::modint998244353;

struct affine {
  mint a = 1, b = 0;
  void then(affine rhs) { *this = affine{a * rhs.a, b * rhs.a + rhs.b}; }
};

struct T {
  mint a, sum;
  affine f;
  bool rev;
};

int main() {
  auto prop = [](auto &n, auto &v) {
      // printf("  prop cnt = %d, a = %d, sum = %d, f = {%d, %d}\n", n.cnt, v.a.val(), v.sum.val(), v.f.a.val(), v.f.b.val());
    if (v.f.a != 1 || v.f.b != 0) {
      v.a = v.a * v.f.a + v.f.b;
      v.sum = v.sum * v.f.a + v.f.b * n.cnt;
      if (n.l) n.l->val().f.then(v.f);
      if (n.r) n.r->val().f.then(v.f);
      v.f = affine{};
    }
    if (v.rev) {
      swap(n.l, n.r);
      if (n.l) n.l->val().rev ^= true;
      if (n.r) n.r->val().rev ^= true;
      v.rev = false;
    }
  };
  auto upd = [](auto &n, auto &v) {
    assert(v.f.a == 1 && v.f.b == 0);
    v.sum = v.a + (n.l ? n.l->val().sum : 0) + (n.r ? n.r->val().sum : 0);
  };

  int n, q;
  scanf("%d%d", &n, &q);
  vector<T> a(n);
  rep(i, n) {
    int x;
    scanf("%d", &x);
    a[i] = T{x, x, {}, false};
  }

  implicit_treap<T, decltype(upd), decltype(prop)> tree(all(a), upd, prop);

  while (q--) {
    int cmd;
    scanf("%d", &cmd);
    if (cmd == 0) {
      int i, x;
      scanf("%d%d", &i, &x);
      tree.insert(i, T{x, x, {}, false});
    } else if (cmd == 1) {
      int i;
      scanf("%d", &i);
      tree.erase(i);
    } else if (cmd == 2) {
      int l, r;
      scanf("%d%d", &l, &r);
      tree.apply_on(l, r, [](auto &v) { v.rev ^= true; });
    } else if (cmd == 3) {
      int l, r, b, c;
      scanf("%d%d%d%d", &l, &r, &b, &c);
      tree.apply_on(l, r, [=](auto &v) { v.f.then(affine{b, c}); });
    } else {
      int l, r;
      scanf("%d%d", &l, &r);
      mint ans;
      tree.apply_on(l, r, [&](auto &v) { ans = v.sum; });
      printf("%d\n", ans.val());
    }
  }
}
