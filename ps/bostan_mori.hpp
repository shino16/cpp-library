#pragma once
#include "ps/fft.hpp"
#include "types.hpp"

// returns [x^n] p / q
template <class It1, class It2>
val_t<It1> bostan_mori(It1 p, It1 p_last, It2 q, It2 q_last, ll n) {
  using mint = val_t<It1>;
  static_assert(is_same_v<val_t<It2>, mint>);
  static_assert(is_base_of_v<atcoder::internal::modint_base, mint>);
  int k = max(2, atcoder::internal::ceil_pow2(max(p_last - p, q_last - q)));
  int d = 1 << k, half = d / 2;
  vector<mint> a(d), b(d);
  copy(p, p_last, a.begin()), copy(q, q_last, b.begin());
  fft(a), fft(b);

  const mint w = mint(atcoder::internal::primitive_root<mint::mod()>)
                     .pow((mint::mod() - 1) >> k);
  vector<mint> z(half);
  z[0] = mint(d).inv() * 2;
  rep(i, half - 1) z[i + 1] = z[i] * w;
  vector<mint> iw(k - 1), y(half);  // bits reversed
  iw[k - 2] = w.inv();
  repr(i, k - 2) iw[i] = iw[i + 1] * iw[i + 1];
  y[0] = 1;
  rep(t, k - 1) rep(i, 1 << t) y[i | 1 << t] = y[i] * iw[t];

  auto dbl = [=, z = move(z)](vector<mint>& v) {
    copy(v.begin(), v.begin() + half, v.begin() + half);
    ifft(v.begin() + half, v.end());
    rep(i, half) v[i + half] *= z[i];
    fft(v.begin() + half, v.end());
  };

  mint c = 1;
  while (true) {
    rep(i, d) a[i] *= b[i ^ 1];
    if (n & 1)
      rep(i, half) a[i] = (a[i << 1] - a[i << 1 | 1]) * y[i];
    else
      rep(i, half) a[i] = a[i << 1] + a[i << 1 | 1];
    if (n == 1) break;
    dbl(a);
    rep(i, half) b[i] = b[i << 1] * b[i << 1 | 1];
    dbl(b);
    n >>= 1, c *= 2;
  }
  return accumulate(a.begin(), a.begin() + half, mint(0)) / (c * d);
}
