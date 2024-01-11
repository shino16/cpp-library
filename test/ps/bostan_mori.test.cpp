// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence

#include "mod/modint.hpp"
#include "io.hpp"
#include "ps/fps.hpp"
using mint = atcoder::modint998244353;
using fps = formal_power_series<mint>;

int main() {
  int d = in;
  ll k = in;
  auto a = fps(in.vec<mint>(d));
  auto c = fps(in.vec<mint>(d));
  rep(i, d) c[i] = -c[i];
  c.insert(c.begin(), 1);
  mint ans = move(a).conv(c, d).div_at(move(c), k);
  out(ans);
}
