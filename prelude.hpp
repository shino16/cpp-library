#pragma once
#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#endif
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep2(i, m, n) for (auto i = (m); i < (n); i++)
#define rep(i, n) rep2(i, 0, n)
#define repr2(i, m, n) for (auto i = (n); i-- > (m);)
#define repr(i, n) repr2(i, 0, n)
#define all(x) begin(x), end(x)
template <class T> auto ndvec(int n, T e) { return vector(n, e); }
template <class... Ts> auto ndvec(int n, Ts... e) { return vector(n, ndvec(e...)); }
