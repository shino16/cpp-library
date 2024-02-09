// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bitwise_xor_convolution

#include "io.hpp"
#include "poset/set.hpp"
#include "mod/modint.hpp"
using mint = atcoder::modint998244353;

int main() {
  int n = in;
  auto a = in.vec<mint>(1<<n);
  auto b = in.vec<mint>(1<<n);
  hadamard(a);
  hadamard(b);
  rep(i, 1<<n) a[i] *= b[i];
  hadamard(a, true);
  out.vec(a);
}
