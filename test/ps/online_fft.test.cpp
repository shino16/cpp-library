// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod

#include "io.hpp"
#include "ps/online_fft.hpp"
#include "mod/modint.hpp"
using mint = atcoder::modint998244353;

int main() {
  int n = in, m = in;
  auto a = in.vi(n);
  auto b = in.vi(m);
  online_fft<mint> of;
  rep(i, max(n, m)) of.push(i < n ? a[i] : 0, i < m ? b[i] : 0);
  auto c = of.finalize();
  c.resize(n + m - 1);
  out(c);
}
