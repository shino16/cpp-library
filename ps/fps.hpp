#pragma once
#include "math/inv.hpp"
#include "math/sat.hpp"
#include "ps/fft.hpp"

template <class T,
          enable_if_t<is_base_of_v<atcoder::internal::modint_base, T>>* =
              nullptr>
class formal_power_series : public vector<T> {
 private:
  using fps = formal_power_series<T>;

 public:
  using sparse = vector<pair<int, T>>;

  using vector<T>::vector;
  formal_power_series(vector<T> v) : vector<T>(move(v)) {}
  formal_power_series(sparse p) : vector<T>() {
    resize(p.back().first + 1);
    for (auto [k, c] : p) (*this)[k] += c;
  }
  static fps unit() { return fps({T(1)}); }
  static fps zero() { return fps{}; }

  int size() const { return vector<T>::size(); }
  const vector<T>& as_vec() const { return (vector<T>&)*this; }
  vector<T>& as_vec() { return (vector<T>&)*this; }
  vector<T> into_vec() { return move(as_vec()); }
  fps& mul(T c) {
    for (auto& e : *this) e *= c;
    return *this;
  }
  fps conv(fps v, int deg = -1) && {
    if (~deg) this->resize(min(size(), deg)), v.resize(min(v.size(), deg));
    auto f = convolution(into_vec(), v.into_vec());
    if (~deg) f.resize(deg);
    return f;
  }
  fps conv(fps v, int deg = -1) const& { return fps(*this).conv(move(v), deg); }
  fps diff() && {
    rep(i, size() - 1)(*this)[i] = (*this)[i + 1] * (i + 1);
    this->pop_back();
    return move(*this);
  }
  fps diff() const& { return fps(*this).diff(); }
  fps integr() && {
    this->push_back(0);
    repr(i, size() - 1)(*this)[i + 1] = (*this)[i] * inverse<T>(i + 1);
    (*this)[0] = 0;
    return move(*this);
  }
  fps integr() const& { return fps(*this).integr(); }
  fps inv(int deg = -1) const& {
    assert((*this)[0] != 0);
    if (deg == -1) deg = size();
    int z = 1 << atcoder::internal::ceil_pow2(deg);
    vector<T> g = {1 / (*this)[0]}, gfft(1);
    vector<T> h;
    g.reserve(z), gfft.reserve(z), h.reserve(z);
    const T i4 = T(4).inv();
    T imm4 = i4;
    for (int m = 1; m < z; m <<= 1, imm4 *= i4) {
      h.assign(this->begin(), this->begin() + min(size(), m * 2));
      h.resize(m * 2);
      copy(all(g), gfft.begin()), gfft.resize(m * 2);
      fft(h), fft(gfft);
      rep(i, m * 2) h[i] *= gfft[i];
      ifft(h), fill(h.begin(), h.begin() + m, 0), fft(h);
      rep(i, m * 2) h[i] *= -gfft[i];
      ifft(h);
      rep2(i, m, m * 2) g.push_back(h[i] * imm4);
    }
    g.resize(deg);
    return fps(move(g));
  }
  fps div(const fps& v, int deg = -1) && {
    return move(*this).conv(v.inv(deg), deg);
  }
  fps div(const fps& v, int deg = -1) const& { return fps(*this).div(v, deg); }
  fps log(int deg = -1) && {
    return inv(deg - 1).conv(move(*this).diff(), deg - 1).integr();
  }
  fps log(int deg = -1) const& { return fps(*this).log(); }
  fps exp(int deg = -1) const& {
    assert((*this)[0] == 0);
    if (deg == -1) deg = size();
    int z = 1 << atcoder::internal::ceil_pow2(deg);
    vector<T> f = {1}, ffft = {1}, g = {1}, gfft = {1};
    vector<T> deriv = fps(*this).diff().into_vec();
    vector<T> h(1), q(1);
    for (auto p : {&f, &ffft, &g, &gfft, &h, &q}) p->reserve(z);
    deriv.resize(z);
    const T i2 = T(2).inv();
    T im = 1, imm = 1, im2 = i2;
    for (int m = 1; m < z; m <<= 1, im = im2, imm = im * im, im2 *= i2) {
      ffft.assign(all(f)), ffft.resize(m * 2), fft(ffft);
      rep(i, m) h[i] = ffft[i] * gfft[i];
      ifft(h), fill(h.begin(), h.begin() + (m + 1) / 2, 0), fft(h);
      rep(i, m) h[i] *= -gfft[i];
      ifft(h);
      rep2(i, (m + 1) / 2, m) g.push_back(h[i] * imm);
      gfft.assign(all(g)), gfft.resize(m * 2), fft(gfft);
      h.assign(deriv.begin(), deriv.begin() + m - 1), h.resize(m), fft(h);
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
      h.assign(this->begin() + m, this->begin() + min(size(), m * 2));
      repr(i, m) h[i] -= q[i] * im2 * inverse<T>(i + m);
      h.resize(m * 2), fft(h);
      rep(i, m * 2) q[i] = ffft[i] * h[i];
      ifft(q);
      f.resize(m * 2);
      rep(i, m) f[i + m] = q[i] * im2;
    }
    f.resize(deg);
    return f;
  }
  fps pow(ll k, int deg = -1) && {
    if (deg == -1) deg = size();
    int z = -1;
    rep(i, size()) if ((*this)[i] != 0) {
      z = i;
      break;
    }
    if (z == -1 || sat_mul<ll>(z, k) > deg) {
      fps res(deg, 0);
      res[0] = k == 0;
      return res;
    }
    ll rest = deg - z * k;
    this->erase(this->begin(), this->begin() + z);
    T c = (*this)[0].pow(k);
    fps f = move(*this).log(rest).mul(k).exp(rest);
    for (auto& e : f) e *= c;
    f.resize(deg);
    copy_backward(f.begin(), f.begin() + rest, f.end());
    fill(f.begin(), f.begin() + z * k, 0);
    return f;
  }
  fps pow(ll k, int deg = -1) const& { return fps(*this).pow(k, deg); }
  T div_at(fps f, ll n) && {
    int k = max(2, 1 + atcoder::internal::ceil_pow2(max(size(), f.size())));
    int d = 1 << k, half = d / 2;
    vector<T> a = into_vec(), b = f.into_vec();
    a.resize(d), b.resize(d);
    fft(a), fft(b);

    const T w =
        T(atcoder::internal::primitive_root<T::mod()>).pow((T::mod() - 1) >> k);
    vector<T> z(half);
    z[0] = T(d).inv() * 2;
    rep(i, half - 1) z[i + 1] = z[i] * w;
    vector<T> iw(k - 1), y(half);  // bit-reversed
    iw[k - 2] = w.inv();
    repr(i, k - 2) iw[i] = iw[i + 1] * iw[i + 1];
    y[0] = 1;
    rep(t, k - 1) rep(i, 1 << t) y[i | 1 << t] = y[i] * iw[t];

    auto dbl = [&](vector<T>& v) {
      copy(v.begin(), v.begin() + half, v.begin() + half);
      ifft(v.begin() + half, v.end());
      rep(i, half) v[i + half] *= z[i];
      fft(v.begin() + half, v.end());
    };

    T c = 1;
    while (true) {
      rep(i, d) a[i] *= b[i ^ 1];
      if (n & 1)
        rep(i, half) a[i] = (a[i << 1] - a[i << 1 | 1]) * y[i];
      else
        rep(i, half) a[i] = a[i << 1] + a[i << 1 | 1];
      if (n == 1) {
        return accumulate(a.begin(), a.begin() + half, T(0)) / (c * d);
      }
      dbl(a);
      rep(i, half) b[i] = b[i << 1] * b[i << 1 | 1];
      dbl(b);
      n >>= 1, c *= 2;
    }
  }
  T div_at(fps f, ll n) const& { return fps(*this).div_at(move(f), n); }

  fps conv(sparse v) && {
    if (v.empty()) return zero();
    if (v.front().first == 0) v.front().second -= T(1);
    repr(i, size()) for (auto [k, c] : v) {
      if (k > i) break;
      (*this)[i] += (*this)[i - k] * c;
    }
    return move(*this);
  }
  fps conv(sparse v) const& { return fps(*this).conv(move(v)); }
  fps div(sparse v) && {
    auto [k0, r] = v.front();
    assert(k0 == 0 && r != T(0));
    T ir = r.inv();
    v.pop_front();
    rep(i, size()) {
      for (auto [k, c] : v) {
        if (k > i) break;
        (*this)[i] -= (*this)[i - k] * c;
      }
      (*this)[i] *= ir;
    }
    return move(*this);
  }
  fps div(sparse v) const& { return fps(*this).div(move(v)); }

  template <class It>
  static fps prod(It a, It a_last) {
    if (a == a_last) return unit();
    vector<fps> vec(a, a_last);
    vec.reserve(distance(a, a_last) * 2);
    for (int i = 0; i + 1 < vec.size(); i += 2)
      vec.push_back(move(vec[i]).conv(move(vec[i + 1])));
    return vec.back();
  }
};
