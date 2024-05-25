#pragma once
#include "ps/fft.hpp"
#include "mod/inv.hpp"

template <class T>
vector<T> exp(const vector<T>& p, int deg) {
  if (p.empty()) return vector<T>{T(1)};
  assert(p[0] == 0);
  if (deg == -1) deg = p.size();
  int z = 1 << atcoder::internal::ceil_pow2(deg);
  vector<T> f = {1}, ffft = {1}, g = {1}, gfft = {1};
  vector<T> deriv(z);
  rep(i, p.size() - 1) deriv[i] = p[i + 1] * (i + 1);
  vector<T> h(1), q(1);
  for (auto pt : {&f, &ffft, &g, &gfft, &h, &q}) pt->reserve(z);
  const T i2 = T(2).inv();
  T im = 1, imm = 1, im2 = i2;
  for (int m = 1; m < z; m <<= 1, im = im2, imm = im * im, im2 *= i2) {
    ffft.assign(all(f)), fft(ffft, m * 2);
    rep(i, m) h[i] = ffft[i] * gfft[i];
    ifft(h), fill(h.begin(), h.begin() + (m + 1) / 2, 0), fft(h);
    rep(i, m) h[i] *= -gfft[i];
    ifft(h);
    rep2(i, (m + 1) / 2, m) g.push_back(h[i] * imm);
    gfft.assign(all(g)), fft(gfft, m * 2);
    h.assign(deriv.begin(), deriv.begin() + m - 1), fft(h, m);
    rep(i, m) q[i] = ffft[i] * h[i];
    ifft(q);
    h.resize(m * 2);
    rep(i, m - 1) h[i + 1] = f[i + 1] * (i + 1);
    rep(i, m) h[i + 1] -= q[i] * im;
    h[0] = -q[m - 1] * im;
    fft(h);
    q.resize(m * 2);
    rep(i, m * 2) q[i] = gfft[i] * h[i];
    ifft(q);
    h.assign(p.begin() + m, p.begin() + min((int)p.size(), m * 2));
    h.resize(m, 0);
    repr(i, m) h[i] -= q[i] * im2 * inverse(i + m);
    fft(h, m * 2);
    rep(i, m * 2) q[i] = ffft[i] * h[i];
    ifft(q);
    f.resize(m * 2);
    rep(i, m) f[i + m] = q[i] * im2;
  }
  f.resize(deg);
  return f;
}
