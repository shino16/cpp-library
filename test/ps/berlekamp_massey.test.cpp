// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/find_linear_recurrence

#include "io.hpp"
#include "ps/berlekamp_massey.hpp"
using mint = atcoder::modint998244353;

int main() {
  int n = in;
  auto a = in.vec<mint>(n);
  auto c = berlekamp_massey(all(a));
  out(c.size());
  out.iter(all(c));
}
