#pragma once
#include "ds/bit_vector.hpp"

template <uint64_t U, class T = unsigned>
class wavelet_matrix {
 public:
  template <class It>
  wavelet_matrix(It first, It last) : wavelet_matrix(vector<T>(first, last)) { }
  wavelet_matrix(vector<T> a) : size_(a.size()) {
    vector<bool> bit(size_);
    vector<T> nxt(size_);
    repr(t, B) {
      int l = 0, r = size_;
      rep(i, size_) {
        bit[i] = a[i] >> t & 1;
        (bit[i] ? nxt[--r] : nxt[l++]) = a[i];
      }
      mat[t] = bit_vector(all(bit));
      zeros[t] = l;
      reverse(nxt.begin() + r, nxt.end());
      swap(a, nxt);
    }
  }

  int size() const { return size_; }
  T operator[](int i) const { return access(i); }
  T access(int i) const {
    T res = 0;
    repr(t, B) {
      if (mat[t][i]) {
        res |= T(1) << t;
        i = zeros[t] + mat[t].rank1(i);
      } else {
        i = mat[t].rank0(i);
      }
    }
    return res;
  }
  // #occurences of x on [l, r)
  int rank(T x, int l, int r) const {
    tie(l, r) = range(x, l, r);
    return r - l;
  }
  // -1 if #occurences <= k
  int select(T x, int l, int k) const {
    int r;
    tie(l, r) = range(x, l, size());
    l += k;
    if (l >= r) return -1;
    rep(t, B) {
      if (x >> t & 1) l = mat[t].select1(l - zeros[t]);
      else l = mat[t].select0(l);
    }
    return l;
  }
  // k-th greatest on [l, r)
  T quantile(int l, int r, int k) const {
    T res = 0;
    repr(t, B) {
      int r1 = mat[t].rank1(l, r);
      if (r1 > k) {
        res |= T(1) << t;
        l = zeros[t] + mat[t].rank1(l);
        r = l + r1;
      } else {
        k -= r1;
        int r0 = r - l - r1;
        l = mat[t].rank0(l);
        r = l + r0;
      }
    }
    return res;
  }
  // k-th smallest on [l, r)
  T rquantile(int l, int r, int k) const {
    return quantile(l, r, r - l - k - 1);
  }
  int rangefreq(int l, int r, T ub) const {
    int res = 0;
    repr(t, B) {
      if (ub >> t & 1) {
        int r1l = mat[t].rank1(l), r1r = mat[t].rank1(r);
        int r0lr = (r - l) - (r1r - r1l);
        res += r0lr;
        l = zeros[t] + r1l, r = zeros[t] + r1r;
      } else {
        l = mat[t].rank0(l), r = mat[t].rank0(r);
      }
    }
    return res;
  }
  // int rangefreq(int l, int r, T lb, T ub) const {
  //   return rangefreq(B - 1, l, r, lb, ub - 1);
  // }
  int rangefreq(int l, int r, T lb, T ub) const {
    return rangefreq(l, r, ub) - rangefreq(l, r, lb);
  }
  // -1 if no such elt
  T succ(int l, int r, T x) const {
    int k = rangefreq(l, r, x);
    return k == r - l ? -1 : rquantile(l, r, k);
  }
  // -1 if no such elt
  T pred(int l, int r, T x) const {
    int k = rangefreq(l, r, x);
    return k ? rquantile(l, r, k - 1) : -1;
  }

 private:
  static constexpr int calc_b(T u) {
    int res = 0;
    for (T x = u - 1; x; x /= 2) res++;
    return res;
  }
  static constexpr int B = calc_b(U);
  static_assert(B <= sizeof(T) * CHAR_BIT);
  int size_;
  array<int, B> zeros;
  array<bit_vector, B> mat;
  pair<int, int> range(T x, int l, int r) const {
    repr(t, B) {
      if (x >> t & 1) {
        l = zeros[t] + mat[t].rank1(l);
        r = zeros[t] + mat[t].rank1(r);
      } else {
        l = mat[t].rank0(l);
        r = mat[t].rank0(r);
      }
    }
    return make_pair(l, r);
  }
  // // inclusive
  // int rangefreq(int t, int l, int r, T x, T lb, T ub) const {
  //   if (t == -1 || ()) return r - l;
  //   if (lb >> t & 1) {
  //     l = zeros[t] + mat[t].rank1(l);
  //     r = zeros[t] + mat[t].rank1(r);
  //     return rangefreq(t - 1, l, r, lb, ub);
  //   } else if (~ub >> t & 1) {
  //     l = mat[t].rank0(l);
  //     r = mat[t].rank0(r);
  //     return rangefreq(t - 1, l, r, lb, ub);
  //   } else {
  //     l = mat[t].rank0(l);
  //     r = zeros[t] + mat[t].rank1(r);
  //     return rangefreq(t - 1, l, zeros[t], lb, ~0) +
  //            rangefreq(t - 1, zeros[t], r, 0, ub);
  //   }
  // }
};
