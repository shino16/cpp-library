// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/pow_of_formal_power_series

#include "mod/modint.hpp"
#include "io.hpp"
#include "ps/fps.hpp"
#include "ps/exp.hpp"
using mint = atcoder::modint998244353;
using fps = formal_power_series<mint>;

int main() {
  int n = in; ll m = in;
  fps f(in.vec<mint>(n));
  f = move(f).pow(m);
  out.iter(all(f));
}
