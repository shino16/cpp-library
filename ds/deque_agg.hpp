#pragma once
#include "algebra.hpp"

template <class M>
class deque_aggregation {
 public:
  using value_type = typename M::type;
  deque_aggregation(M m = M())
      : m(m), front_cuml({m.unit()}), back_cuml({m.unit()}) {}

  void push_back(value_type v) {
    back_cuml.push_back(m.op(back_cuml.back(), v));
    back.push_back(v);
  }
  void push_front(value_type v) {
    front_cuml.push_back(m.op(v, front_cuml.back()));
    front.push_back(v);
  }
  value_type pop_front() {
    if (front.empty()) prepare_front();
    value_type res = front.back();
    front.pop_back(), front_cuml.pop_back();
    return res;
  }
  value_type pop_back() {
    if (back.empty()) prepare_back();
    value_type res = back.back();
    back.pop_back(), back_cuml.pop_back();
    return res;
  }
  value_type prod() const { return m.op(front_cuml.back(), back_cuml.back()); }

 private:
  M m;
  vector<value_type> front, front_cuml, back, back_cuml;
  void balance(int n, int m, vector<value_type> data) {
    front.clear(), front_cuml.resize(1), back.clear(), back_cuml.resize(1);
    repr(i, n) push_front(data[i]);
    rep(i, m) push_back(data[n + i]);
  }
  void prepare_front() {
    int n = (back.size() + 1) / 2;
    assert(n != 0);
    balance(n, back.size() - n, back);
  }
  void prepare_back() {
    int m = (front.size() + 1) / 2;
    assert(m != 0);
    reverse(all(front));
    balance(front.size() - m, m, front);
  }
};
