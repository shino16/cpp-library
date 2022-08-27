#pragma once
#include "atcoder/convolution.hpp"
#include "prelude.hpp"

template <class T,
          enable_if_t<is_base_of_v<atcoder::internal::modint_base, T>>* =
              nullptr>
class poly : vector<T> {
  using vector<T>::vector;
  poly(vector<T> v) : vector<T>(move(v)) {}

  const vector<T>& as_vec() const { return (vector<T>&)*this; }
  vector<T>& as_vec() { return (vector<T>&)*this; }
  vector<T> into_vec() { return move(as_vec()); }
  poly& conv(const poly& v) { return *this = conv(into_vec(), v.as_vec()); }
  poly& diff() { return *this = diff(into_vec()); }
  poly& integr() { return *this = integr(into_vec()); }
  poly& inv(int deg) { return *this = inv(into_vec(), deg); }
  poly& div(const poly& v, int deg) {
    return *this = div(into_vec(), v.as_vec(), deg);
  }
  poly& log(int deg) { return *this = log(into_vec(), deg); }
  poly& exp(int deg) { return *this = exp(into_vec(), deg); }
};

template <class T>
vector<T> conv(vector<T> a, vector<T> b, int deg = -1) {
  if (~deg) a.resize(min(a.size(), deg)), b.resize(min(b.size(), deg));
  auto f = convolution(a, b);
  if (~deg) f.resize(deg);
  return f;
}

template <class T>
vector<T> diff(vector<T> a) {
  rep(i, a.size() - 1) a[i] = a[i + 1] * (i + 1);
  a.pop_back();
  return a;
}

template <class T>
vector<T> integr(vector<T> a) {
  a.push_back(0);
  repr(i, a.size() - 1) a[i + 1] = a[i] / (i + 1);
  a[0] = 0;
  return a;
}

template <class T>
vector<T> inv(vector<T> f, int deg) {
  assert(f[0] != 0);
  vector<T> g = {1 / f[0]};
  for (int m = 1; m < deg; m *= 2) {
    auto h = conv(f, g, m * 2);
    fill(h.begin(), h.begin() + m, 0);
    auto hg = conv(h, g, m * 2);
    rep(i, m * 2) hg[i] = -hg[i];
    g.insert(g.end(), hg.begin() + m, hg.end());
  }
  g.resize(deg);
  return g;
}

template <class T>
vector<T> div(vector<T> a, vector<T> b, int deg) {
  return conv(a, inv(b, deg), deg);
}

template <class T>
vector<T> log(vector<T> a, int deg) {
  assert(a[0] == 1);
  return integr(div(diff(a), a2, deg - 1), deg - 1);
}

template <class T>
vector<T> exp(vector<T> h, int deg) {
  assert(h[0] == 0);
  int n = 1 << atcoder::internal::ceil_pow2(deg);
  h.resize(n);
  vector<T> f = {1}, g = {1};
  vector<T> q(h.size() - 1);
  rep(i, q.size()) q[i] = h[i + 1] * (i + 1);
  for (int m = 1; m < n; m *= 2) {
    auto fgg = conv(conv(f, g, m), g, m);
    g.resize(m);
    rep(i, m) g[i] = g[i] * 2 - fgg[i];
    auto fq = conv(f, {q.begin(), q.begin() + m - 1});
    rep(i, fq.size()) fq[i] =
        -fq[i] + (i < f.size() - 1 ? f[i + 1] * (i + 1) : 0);
    auto w = conv(g, fq, m * 2 - 1);
    rep(i, m - 1) w[i] += q[i];
    w.push_back(0);
    repr(i, m * 2 - 1) w[i + 1] = h[i + 1] - w[i] / (i + 1);
    w[0] = h[0];
    auto fw = conv(f, w, m * 2);
    f.resize(m * 2);
    rep(i, m * 2) f[i] += fw[i];
  }
  return f;
}
