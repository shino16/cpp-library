#pragma once

#include "bit/ctz.hpp"
#include "bit/popcnt.hpp"

template <class T>
vector<vector<T>> ranked_zeta(vector<T> v) {
  int n = ctz(v.size());
  vector zv(1<<n, vector<T>(n+1));
  rep(mask, 1<<n) zv[mask][popcnt(mask)] = v[mask];
  rep(i, n) rep(mask, 1 << n) if (~mask >> i & 1) v[mask | 1 << i] += v[mask];
}

template <class T>
void zeta_r(vector<T>& v) {
  int n = ctz(v.size());
  rep(i, n) rep(mask, 1 << n) if (~mask >> i & 1) v[mask] += v[mask | 1 << i];
}

template <class T>
void moebius(vector<T>& v) {
  int n = ctz(v.size());
  rep(i, n) rep(mask, 1 << n) if (~mask >> i & 1) v[mask | 1 << i] -= v[mask];
}

template <class T>
void moebius_r(vector<T>& v) {
  int n = ctz(v.size());
  rep(i, n) rep(mask, 1 << n) if (~mask >> i & 1) v[mask] -= v[mask | 1 << i];
}
