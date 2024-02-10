// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod

#include "io.hpp"
#include "ps/semi_online_fft.hpp"
#include "mod/modint.hpp"
using mint = atcoder::modint998244353;

int main() {
  int n = in, m = in;
  auto a = in.vec<mint>(n);
  auto b = in.vi(m);
  semi_online_fft<mint> of(a);
  rep(i, m) of.push(b[i]);
  auto c = of.finalize();
  c.resize(n + m - 1);
  out(c);
}
