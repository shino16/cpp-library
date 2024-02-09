// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bitwise_and_convolution

#include "io.hpp"
#include "set_ps/zeta.hpp"
#include "mod/modint.hpp"
using mint = atcoder::modint998244353;

int main() {
  int n = in;
  auto a = in.vec<mint>(1<<n);
  auto b = in.vec<mint>(1<<n);
  zeta_r(a);
  zeta_r(b);
  rep(i, 1<<n) a[i] *= b[i];
  moebius_r(a);
  out.vec(a);
}
