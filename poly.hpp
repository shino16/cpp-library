// #pragma once
// #include "prelude.hpp"

// template <class T>
// class polynomial {
//  private:
//   using self = polynomial<T>;
//   vector<T> coef;

//  public:
//   template <class... Args>
//   polynomial(Args&&... args): coef(forward<Args>(args)...) {}

//   T& operator[](size_t i) { return coef[i]; }
//   const T& operator[](size_t i) const { return coef[i]; }
//   size_t size() const { return coef.size(); }

//   self operator+(const self& that) && {
//     coef.resize(max(coef.size(), that.size()));
//     rep(i, b.size()) coef[i] += that[i];
//     return *this;
//   }
//   self& operator+=(const self& that) {
//     return *this = (*this + that);
//   }

//   self sub(const self& b) && {
//     a.resize(max(a.size(), b.size()));
//     rep(i, b.size()) a[i] -= b[i];
//     return a;
//   }

//   vector<mint> mul(mint r) {
//     rep(i, a.size()) a[i] *= r;
//     return a;
//   }

//   vector<mint> conv(vector<mint> a, vector<mint> b, int deg = -1) {
//     if (~deg)
//       a.resize(min<int>(a.size(), deg)),
//         b.resize(min<int>(b.size(), deg));
//     auto f = convolution(a, b);
//     if (~deg) f.resize(deg);
//     return f;
//   }

//   vector<mint> diff(vector<mint> a) {
//     rep(i, a.size() - 1) a[i] = a[i + 1] * (i + 1);
//     a.pop_back();
//     return a;
//   }

//   vector<mint> integr(vector<mint> a) {
//     a.push_back(0);
//     repr(i, a.size() - 1) a[i + 1] = a[i] / (i + 1);
//     a[0] = 0;
//     return a;
//   }

//   vector<mint> inv(vector<mint> f, int deg) {
//     assert(f[0] != 0);
//     vector<mint> g = {f[0].inv()};
//     for (int m = 1; m < deg; m *= 2) {
//       auto h = conv(f, g, m * 2);
//       fill(h.begin(), h.begin() + m, 0);
//       auto hg = conv(h, g, m * 2);
//       rep(i, m * 2) hg[i] = -hg[i];
//       g.insert(g.end(), hg.begin() + m, hg.end());
//     }
//     g.resize(deg);
//     return g;
//   }

//   vector<mint> log(vector<mint> a, int deg) {
//     assert(a[0] == 1);
//     vector<mint> a2 = a;
//     return integr(conv(diff(move(a)), inv(move(a2), deg - 1), deg - 1));
//   }

//   vector<mint> exp(vector<mint> h, int deg) {
//     assert(h[0] == 0);
//     int n = 1 << atcoder::internal::ceil_pow2(deg);
//     h.resize(n);
//     vector<mint> f = {1}, g = {1};
//     vector<mint> q(h.size() - 1);
//     rep(i, q.size()) q[i] = h[i + 1] * (i + 1);
//     for (int m = 1; m < n; m *= 2) {
//       auto fgg = conv(conv(f, g, m), g, m);
//       g.resize(m);
//       rep(i, m) g[i] = g[i] * 2 - fgg[i];
//       auto fq = conv(f, {q.begin(), q.begin() + m - 1});
//       rep(i, fq.size()) fq[i] =
//         -fq[i] + (i < f.size() - 1 ? f[i + 1] * (i + 1) : 0);
//       auto w = conv(g, fq, m * 2 - 1);
//       rep(i, m - 1) w[i] += q[i];
//       w.push_back(0);
//       repr(i, m * 2 - 1) w[i + 1] = h[i + 1] - w[i] / (i + 1);
//       w[0] = h[0];
//       auto fw = conv(f, w, m * 2);
//       f.resize(m * 2);
//       rep(i, m * 2) f[i] += fw[i];
//     }
//     return f;
//   }
// };
