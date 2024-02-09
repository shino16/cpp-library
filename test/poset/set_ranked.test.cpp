// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/subset_convolution

#include "io.hpp"
#include "poset/set_ranked.hpp"
#include "mod/modint.hpp"
using mint = atcoder::modint998244353;

int main() {
  int n = in;
  auto a = in.vec<mint>(1<<n);
  auto b = in.vec<mint>(1<<n);
  out(subset_convolution<mint, 20>(a, b));
}
