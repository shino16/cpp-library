#pragma once
#include "math/inv.hpp"
#include "math/sat.hpp"
#include "ps/fft.hpp"
#include "ps/exp.hpp"
#include "ps/inv.hpp"
#include "ps/bostan_mori.hpp"

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
  T div_at(fps f, ll n) && { return bostan_mori(into_vec(), f.into_vec(), n); }
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
