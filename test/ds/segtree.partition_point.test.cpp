#define PROBLEM "https://yukicoder.me/problems/3277"

#include "io.hpp"
#include "ds/segtree.hpp"

int main() {
  int n = in, q = in;
  auto a = in.vec<int>(n);
  segment_tree seg(all(a), minimum<int>{});
  while (q--) {
    int op = in, l = in, r = in;
    if (op == 1) {
      l--, r--;
      int tmp = seg.prod(r, r + 1);
      seg.exec(l, [&](auto& v) { swap(v, tmp); });
      seg.exec(r, [&](auto& v) { v = tmp; });
    } else {
      l--;
      int mini = seg.prod(l, r);
      int i = seg.partition_point(l, [&](auto v) { return v > mini; });
      out(i);
    }
  }
}
