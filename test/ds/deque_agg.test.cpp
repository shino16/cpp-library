#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include "ds/deque_agg.hpp"
#include <mod/modint.hpp>
using mint = atcoder::modint998244353;

struct affine {
  mint a = 1, b = 0;
  affine then(affine rhs) const {
    return {a * rhs.a, b * rhs.a + rhs.b};
  }
};

int main() {
  int q; scanf("%d", &q);
  monoid compose(CONST(affine{}), [&](auto&& a, auto&& b) { return a.then(b); });
  deque_aggregation deq(compose);
  while (q--) {
    int cmd; scanf("%d", &cmd);
    if (cmd == 0) {
      int a, b; scanf("%d%d", &a, &b);
      deq.push_back(affine{mint(a), mint(b)});
    } else if (cmd == 1) {
      deq.pop_front();
    } else {
      int x; scanf("%d", &x);
      auto [a, b] = deq.prod();
      printf("%d\n", (a*x+b).val());
    }
  }
}
