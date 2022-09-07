#pragma once
#include "la/inv.hpp"

template <class T>
class matrix : public vector<vector<T>> {
 public:
  using vector<vector<T>>::vector;
  matrix(int n, int m) : vector<vector<T>>(n, vector<T>(m)){ }

  vector<vector<T>>& as_vec() { return (vector<vector<T>>&)*this; }
  const vector<vector<T>>& as_vec() const { return (vector<vector<T>>&)*this; }
  vector<vector<T>> into_vec() { return move(as_vec()); }
  int n() const { return this->size(); }
  int m() const { return (*this)[0].size(); }

  matrix add(const matrix& a) && {
    assert(n() == a.n() && m() == a.m());
    rep(i, n()) rep(j, m()) (*this)[i][j] += a[i][j];
    return move(*this);
  }
  matrix add(const matrix& a) const& { return matrix(*this).add(a); }
  matrix sub(const matrix& a) && {
    assert(n() == a.n() && m() == a.m());
    rep(i, n()) rep(j, m()) (*this)[i][j] -= a[i][j];
    return move(*this);
  }
  matrix sub(const matrix& a) const& { return matrix(*this).sub(a); }
  matrix mul(const matrix& a) const {
    assert(m() == a.n());
    matrix b(n(), a.m());
    rep(i, n()) rep(k, m()) rep(j, a.m()) b[i][j] += (*this)[i][k] * a[k][j];
    return b;
  }
  matrix inv() && {
    assert(invert(as_vec()));
    return move(*this);
  }
  matrix inv() const& { return matrix(*this).inv(); }
};
