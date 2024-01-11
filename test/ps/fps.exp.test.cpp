// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/exp_of_formal_power_series

#include "ps/fps.hpp"
#include "io.hpp"
#include "mod/modint.hpp"
using mint = atcoder::modint998244353;
using fps = formal_power_series<mint>;

int main() {
  int n = in;
  fps f(in.vec<mint>(n));
  f = f.exp();
  out.iter(all(f));
}
