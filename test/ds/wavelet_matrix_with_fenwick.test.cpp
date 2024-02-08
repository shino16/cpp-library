// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/rectangle_sum

#include "io.hpp"
#include "ds/wavelet_matrix_with_fenwick.hpp"
#include "util/comp.hpp"
#include "util/transpose.hpp"

int main() {
  int n = in, q = in;
  auto xyw = in.vec<tuple<int, int, ll>>(n);
  sort(all(xyw));
  auto [x, y, w] = transpose(xyw);

  wavelet_matrix_with_fenwick<int, 1'000'000'001, addition<ll>> wm(y, w);

  while (q--) {
    int l = in, d = in, r = in, u = in;
    out(wm.range_reduce(
        lower_bound(all(x), l) - x.begin(), lower_bound(all(x), r) - x.begin(),
        d, u));
  }
}
