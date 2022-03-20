#pragma once
#include "prelude.hpp"

template <class T>
class compress {
 public:
  compress(vector<T> data) : data(move(data)) { init(); }
  template <class Iter>
  compress(Iter f, Iter l) : data(f, l) { init(); }
  int size() const { return data.size(); }
  int operator()(const T& x) const {
    auto it = lower_bound(data.begin(), data.end(), x);
    assert(*it == x);
    return it - data.begin();
  }
  bool has(const T& x) const {
    return binary_search(data.begin(), data.end(), x);
  }
  const T& operator[](int i) const { return data[i]; }

 private:
  vector<T> data;
  void init() {
    sort(data.begin(), data.end());
    data.erase(unique(data.begin(), data.end()), data.end());
  }
};