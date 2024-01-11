// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/inv_of_formal_power_series

#include "mod/modint.hpp"
#include "io.hpp"
#include "ps/fps.hpp"
using mint = atcoder::modint998244353;
using fps = formal_power_series<mint>;

int main() {
  int n = in;
  fps f(in.vec<mint>(n));
  fps g = f.inv();
  out.iter(all(g));
}
