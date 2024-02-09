#pragma once

#include "bit/ctz.hpp"
#include "bit/popcnt.hpp"

template <class T, int MaxN = 20>
vector<array<T, MaxN+1>> add_rank(const vector<T>& a) {
  vector<array<T, MaxN+1>> ra(a.size());
  rep(mask, a.size()) ra[mask][popcnt(mask)] = a[mask];
  return ra;
}

template <class T, int MaxN = 20>
vector<T> erase_rank(const vector<array<T, MaxN+1>>& ra) {
  vector<T> a(ra.size());
  rep(mask, a.size()) a[mask] = ra[mask][popcnt(mask)];
  return a;
}

template <class T, int MaxN = 20>
void ranked_zeta(vector<array<T, MaxN + 1>>& v) {
  for (int h = 1; h < v.size(); h <<= 1)
    for (int i = 0; i < v.size(); i += h * 2)
      rep2(j, i, i + h) {
    int jh = j + h;
    rep(d, MaxN + 1) v[jh][d] += v[j][d];
    }
}

template <class T, int MaxN = 20>
void ranked_moebius(vector<array<T, MaxN + 1>>& v) {
  for (int h = 1; h < v.size(); h <<= 1)
    for (int i = 0; i < v.size(); i += h * 2)
      rep2(j, i, i + h) {
    int jh = j + h;
    rep(d, MaxN + 1) v[jh][d] -= v[j][d];
    }
}

// Regards array as a polynomial
// High-degree terms are dropped
template <class T, int MaxN = 20>
void ranked_pointwise_mult(
    vector<array<T, MaxN + 1>>& a, const vector<array<T, MaxN + 1>>& b) {
  rep(mask, a.size()) repr(d, MaxN + 1) {
    T sum = 0;
    rep(i, d + 1) sum += a[mask][i] * b[mask][d - i];
    a[mask][d] = sum;
  }
}

// Regards array as a polynomial
// High-degree terms are dropped
template <class T, int MaxN = 20>
void ranked_pointwise_square(vector<array<T, MaxN + 1>>& a) {
  rep(mask, a.size()) repr(d, MaxN + 1) {
    T sum = 0;
    rep(i, d + 1) sum += a[mask][i] * a[mask][d - i];
    a[mask][d] = sum;
  }
}

template <class T, int MaxN = 20>
vector<T> subset_convolution_square(const vector<T>& a) {
  auto ra = add_rank<T, MaxN>(a);
  ranked_zeta<T, MaxN>(ra);
  ranked_pointwise_square<T, MaxN>(ra);
  ranked_moebius<T, MaxN>(ra);
  return erase_rank<T, MaxN>(ra);
}

template <class T, int MaxN = 20>
vector<T> subset_convolution(const vector<T>& a, const vector<T>& b) {
  if (a == b) return subset_convolution_square<T, MaxN>(a);
  auto ra = add_rank<T, MaxN>(a), rb = add_rank<T, MaxN>(b);
  ranked_zeta<T, MaxN>(ra), ranked_zeta<T, MaxN>(rb);
  ranked_pointwise_mult<T, MaxN>(ra, rb);
  ranked_moebius<T, MaxN>(ra);
  return erase_rank<T, MaxN>(ra);
}
