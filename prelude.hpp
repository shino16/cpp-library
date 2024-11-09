#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using vc = vector<char>;
#define rep2(i, m, n) for (auto i = (m); i < (n); i++)
#define rep(i, n) rep2(i, 0, n)
#define repr2(i, m, n) for (auto i = (n); i-- > (m);)
#define repr(i, n) repr2(i, 0, n)
#define all(x) begin(x), end(x)
auto ndvec(int n, auto e) { return vector(n, e); }
auto ndvec(int n, auto ...e) { return vector(n, ndvec(e...)); }
auto comp_key(auto&& f) { return [&](auto&& a, auto&& b) { return f(a) < f(b); }; }
auto& max(const auto& a, const auto& b) { return a < b ? b : a; }
auto& min(const auto& a, const auto& b) { return b < a ? b : a; }
#if __cpp_lib_ranges
namespace R = std::ranges;
namespace V = std::views;
#endif
