#pragma once
#include "ds/fenwick.hpp"
#include "ds/bit_vector.hpp"

template <class Key, Key U, class M>
class wavelet_matrix_with_fenwick {
 public:
  using key_type = Key;
  using value_type = typename M::type;

  wavelet_matrix_with_fenwick(vector<Key> a, M m = M())
      : wavelet_matrix_with_fenwick(a, a, m) {}
  wavelet_matrix_with_fenwick(vector<Key> a, vector<value_type> b, M m = M())
      : m_(m), size_(a.size()) {
    vector<bool> bit(size_);
    vector<key_type> nxt_a(size_);
    vector<value_type> nxt_b(size_);
    repr(t, B) {
      int l = 0, r = size_;
      rep(i, size_) {
        bit[i] = a[i] >> t & 1;
        (bit[i] ? nxt_a[r - 1] : nxt_a[l]) = a[i];
        (bit[i] ? nxt_b[--r] : nxt_b[l++]) = b[i];
      }
      mat[t] = bit_vector(all(bit));
      zeros[t] = l;
      fwk[t + 1] = fenwick_tree<M>(b, m);
      reverse(nxt_a.begin() + r, nxt_a.end());
      reverse(nxt_b.begin() + r, nxt_b.end());
      swap(a, nxt_a);
      swap(b, nxt_b);
    }
    fwk[0] = fenwick_tree<M>(b, m);
  }

  int size() const { return size_; }
  key_type operator[](int i) const { return access(i); }
  key_type access(int i) const {
    key_type res = 0;
    repr(t, B) {
      if (mat[t][i]) {
        res |= key_type(1) << t;
        i = zeros[t] + mat[t].rank1(i);
      } else {
        i = mat[t].rank0(i);
      }
    }
    return res;
  }
  // #occurences of x on [l, r)
  int rank(key_type x, int l, int r) const {
    tie(l, r) = range(x, l, r);
    return r - l;
  }
  // -1 if #occurences <= k
  int select(key_type x, int l, int k) const {
    int r;
    tie(l, r) = range(x, l, size());
    l += k;
    if (l >= r) return -1;
    rep(t, B) {
      if (x >> t & 1)
        l = mat[t].select1(l - zeros[t]);
      else
        l = mat[t].select0(l);
    }
    return l;
  }
  // k-th greatest on [l, r)
  key_type quantile(int l, int r, int k) const {
    key_type res = 0;
    repr(t, B) {
      int r1 = mat[t].rank1(l, r);
      if (r1 > k) {
        res |= key_type(1) << t;
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
  key_type rquantile(int l, int r, int k) const {
    return quantile(l, r, r - l - k - 1);
  }
  int rangefreq(int l, int r, key_type ub) const {
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
  value_type range_reduce(int l, int r, key_type ub) const {
    value_type res = m_.unit();
    repr(t, B) {
      if (ub >> t & 1) {
        int r1l = mat[t].rank1(l), r1r = mat[t].rank1(r);
        res = m_.op(res, fwk[t + 1].sum(l, r));
        l = zeros[t] + r1l, r = zeros[t] + r1r;
        res = m_.op(res, m_.inv(fwk[t].sum(l, r)));
      } else {
        l = mat[t].rank0(l), r = mat[t].rank0(r);
      }
    }
    return res;
  }
  // int rangefreq(int l, int r, key_type lb, key_type ub) const {
  //   return rangefreq(B - 1, l, r, lb, ub - 1);
  // }
  int rangefreq(int l, int r, key_type lb, key_type ub) const {
    return rangefreq(l, r, ub) - rangefreq(l, r, lb);
  }
  value_type range_reduce(int l, int r, key_type lb, key_type ub) const {
    return m_.op(range_reduce(l, r, ub), m_.inv(range_reduce(l, r, lb)));
  }
  // -1 if no such elt
  key_type succ(int l, int r, key_type x) const {
    int k = rangefreq(l, r, x);
    return k == r - l ? -1 : rquantile(l, r, k);
  }
  // -1 if no such elt
  key_type pred(int l, int r, key_type x) const {
    int k = rangefreq(l, r, x);
    return k ? rquantile(l, r, k - 1) : -1;
  }

 private:
  static constexpr int calc_b(key_type u) {
    int res = 0;
    for (key_type x = u - 1; x; x /= 2) res++;
    return res;
  }
  static constexpr int B = calc_b(U);
  static_assert(B <= sizeof(key_type) * CHAR_BIT);
  M m_;
  int size_;
  array<int, B> zeros;
  array<bit_vector, B> mat;
  array<fenwick_tree<M>, B + 1> fwk;

  pair<int, int> range(key_type x, int l, int r) const {
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
  // int rangefreq(int t, int l, int r, key_type x, key_type lb, key_type
  // ub) const {
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
