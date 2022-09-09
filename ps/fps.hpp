#pragma once
#include "mod/inv.hpp"
#include "mod/sqrt.hpp"
#include "arith/sat.hpp"
#include "ps/fft.hpp"
#include "ps/exp.hpp"
#include "ps/inv.hpp"
#include "ps/bostan_mori.hpp"

template <
    class T,
    enable_if_t<is_base_of_v<atcoder::internal::modint_base, T>>* = nullptr>
class formal_power_series : public vector<T> {
 private:
  using fps = formal_power_series<T>;

 public:
  using sparse = vector<pair<int, T>>;

  using vector<T>::vector;
  formal_power_series(vector<T> v) : vector<T>(move(v)) { }
  formal_power_series(sparse p) : vector<T>() {
    resize(p.back().first + 1);
    for (auto [k, c] : p) (*this)[k] += c;
  }
  static fps one() { return fps({T(1)}); }
  static fps zero() { return fps{}; }

  int size() const { return vector<T>::size(); }
  const vector<T>& as_vec() const { return (const vector<T>&)*this; }
  vector<T>& as_vec() { return (vector<T>&)*this; }
  vector<T> into_vec() { return move(as_vec()); }
  T eval(T x) const {
    T pow(1), ans(0);
    for (auto e : *this) ans += e * pow, pow *= x;
    return ans;
  }
  void trunc() {
    while (!this->empty() && this->back() == T(0)) this->pop_back();
  }
  fps& mul(T c) {
    for (auto& e : *this) e *= c;
    return *this;
  }
  fps add(const fps& v) && {
    this->resize(max(size(), v.size()));
    rep(i, v.size()) (*this)[i] += v[i];
    return move(*this);
  }
  fps add(const fps& v) const& { return fps(*this).add(v); }
  fps sub(const fps& v) && {
    this->resize(max(size(), v.size()));
    rep(i, v.size()) (*this)[i] -= v[i];
    return move(*this);
  }
  fps sub(const fps& v) const& { return fps(*this).sub(v); }
  fps conv(fps v, int deg = -1) && {
    if (~deg) this->resize(min(size(), deg)), v.resize(min(v.size(), deg));
    auto f = convolution(into_vec(), v.into_vec());
    if (~deg) f.resize(deg);
    return f;
  }
  fps conv(fps v, int deg = -1) const& { return fps(*this).conv(move(v), deg); }
  fps diff() && {
    rep(i, size() - 1) (*this)[i] = (*this)[i + 1] * (i + 1);
    this->pop_back();
    return move(*this);
  }
  fps diff() const& { return fps(*this).diff(); }
  fps integr() && {
    this->push_back(0);
    repr(i, size() - 1) (*this)[i + 1] = (*this)[i] * inverse(i + 1);
    (*this)[0] = 0;
    return move(*this);
  }
  fps integr() const& { return fps(*this).integr(); }
  fps inv(int deg = -1) const& { return fps(::inv(as_vec(), deg)); }
  fps div(const fps& v, int deg = -1) && {
    return move(*this).conv(v.inv(deg), deg);
  }
  fps div(const fps& v, int deg = -1) const& { return fps(*this).div(v, deg); }
  fps log(int deg = -1) && {
    return inv(deg - 1).conv(move(*this).diff(), deg - 1).integr();
  }
  fps log(int deg = -1) const& { return fps(*this).log(deg); }
  fps exp(int deg = -1) const& { return ::exp(as_vec(), deg); }
  fps pow(ll k, int deg = -1) && {
    if (deg == -1) deg = size();
    int z = -1;
    rep(i, size())
      if ((*this)[i] != 0) {
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
  fps square(int deg = -1) && {
    if (deg == -1) deg = size() * 2 - 1;
    int n = 1 << atcoder::internal::ceil_pow2(deg);
    fft(as_vec(), n * 2);
    for (auto& e : *this) e *= e;
    ifft(as_vec());
    auto in2 = inverse(n * 2);
    this->resize(deg);
    for (auto& e : *this) e *= in2;
    return move(*this);
  }
  fps square(int deg = -1) const& { return fps(*this).square(deg); }
  T div_at(fps f, ll n) && { return bostan_mori(into_vec(), f.into_vec(), n); }
  T div_at(fps f, ll n) const& { return fps(*this).div_at(move(f), n); }
  optional<fps> sqrt(int deg = -1) && {
    if (deg == -1) deg = size();
    this->resize(deg);
    if (this->empty()) return move(*this);
    if ((*this)[0] == 0) {
      int b = 0;
      while (b < size() && (*this)[b] == 0) b++;
      if (b == size()) return move(*this);
      if (b % 2 != 0) return nullopt;
      this->erase(this->begin(), this->begin() + b);
      auto ans = move(*this).sqrt(deg - b / 2);
      if (ans) ans->insert(ans->begin(), b / 2, T(0));
      return ans;
    }
    auto x = mod_sqrt((*this)[0]);
    if (!x) return nullopt;
    fps f = {*x};
    int z = 1 << atcoder::internal::ceil_pow2(deg);
    f.reserve(z);
    const T i2 = inverse(2);
    for (int m = 1; m < z; m *= 2) {
      fps h(this->begin(), this->begin() + min(m * 2, size()));
      fps hf = move(h).div(f, m * 2);
      f = move(f).add(hf).mul(i2);
    }
    f.resize(deg);
    return f;
  }

  fps div_poly(fps g) && {
    int d = size() - g.size() + 1;
    if (d <= 0) return zero();
    reverse(all(*this));
    reverse(all(g));
    fps q = move(*this).div(move(g), d);
    reverse(all(q));
    return q;
  }
  fps div_poly(fps g) const& { return fps(*this).div_poly(move(g)); }
  pair<fps, fps> div_rem_poly(fps g) && {
    int d = g.size() - 1;
    fps q = div_poly(g);
    fps r = move(*this).sub(move(g).conv(q, d));
    r.resize(d);
    r.trunc();
    return pair(move(q), move(r));
  }
  pair<fps, fps> div_rem_poly(fps g) const& {
    return fps(*this).div_rem_poly(move(g));
  }

  fps conv(sparse v) && {
    if (v.empty()) return zero();
    if (v.front().first == 0) v.front().second -= T(1);
    repr(i, size())
      for (auto [k, c] : v) {
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
  static fps prod(It first, It last) {
    if (first == last) return one();
    vector<fps> vec(first, last);
    vec.reserve(distance(first, last) * 2);
    for (int i = 0; i + 1 < vec.size(); i += 2)
      vec.push_back(move(vec[i]).conv(move(vec[i + 1])));
    return vec.back();
  }
};
