#pragma once
#include "algebra.hpp"
#include "bit/ilog2.hpp"

template <class M>
class fenwick_tree_2d {
 public:
  using value_type = typename M::type;
  fenwick_tree_2d(vector<vector<value_type>> data, M m = M())
      : m(m), data(move(data)) {
    rep(i, data.size()) data[i].insert(data.cbegin(), m.unit());
    data.insert(data.begin(), vector<value_type>(data[0].size(), m.unit()));
    rep(i, data.size()) {
      for (int j = 1; j < data[i].size(); j++) {
        if (j + lsb(j) < data[i].size()) {
          data[i][j + lsb(j)] = m.op(data[i][j + lsb(j)], data[i][j]);
        }
      }
    }
    for (int i = 1; i < data.size(); i++) {
      if (i + lsb(i) < data.size()) {
        rep(j, data[i].size()) {
          data[i + lsb(i)][j] = m.op(data[i + lsb(i)][j], data[i][j]);
        }
      }
    }
  }
  template <class Iter>
  fenwick_tree_2d(Iter f, Iter l, M m = M())
      : fenwick_tree_2d(vector<value_type>(f, l), m) {}
  fenwick_tree_2d(int n0, int n1, M m = M())
      : m(m), data(n0 + 1, vector<value_type>(n1 + 1, m.unit())) {}
  int size() const { return data.size() - 1; }
  void clear() {
    rep(i, data.size()) fill(data[i].begin(), data[i].end(), m.unit());
  }
  void add(int i0, int j0, value_type v) {
    for (int i = i0 + 1; i < data.size(); i += lsb(i))
      for (int j = j0 + 1; j < data[i].size(); j += lsb(j))
        data[i][j] = m.op(data[i][j], v);
  }
  void sub(int i, int j, value_type v) { add(i, j, m.inv(v)); }
  void assign(int i, int j, value_type v) {
    add(i, j, m.op(v, m.inv(sum(i, j, i + 1, j + 1))));
  }
  value_type sum(int ri, int rj) const {
    value_type res = m.unit();
    for (int i = ri; i; i -= lsb(i)) {
      for (int j = rj; j; j -= lsb(j)) {
        res = m.op(res, data[i][j]);
      }
    }
    return res;
  }
  value_type sum(int li, int lj, int ri, int rj) const {
    return m.op(m.op(sum(li, lj), sum(ri, rj)),
                m.inv(m.op(sum(li, rj), sum(ri, lj))));
  }

 private:
  M m;
  vector<vector<value_type>> data;
  static int lsb(int a) { return a & -a; }
};