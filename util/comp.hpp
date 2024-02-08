#pragma once
#include "prelude.hpp"

template <class T>
class compress {
 public:
  compress(vector<T> v = {}, bool unique = true) : data(move(v)) {
    sort(data.begin(), data.end());
    if (unique) data.erase(unique(data.begin(), data.end()), data.end());
  }
  template <class It>
  compress(It f, It l) : compress(vector<T>(f, l)) {}
  int size() const { return data.size(); }
  int operator()(const T& x) const {
    int i = lower_bound(x);
    assert(data[i] == x);
    return i;
  }
  bool contains(const T& x) const {
    return binary_search(data.begin(), data.end(), x);
  }
  const T& operator[](int i) const { return data[i]; }
  int lower_bound(const T& x) const {
    return std::lower_bound(data.begin(), data.end(), x) - data.begin();
  }
  int upper_bound(const T& x) const {
    return upper_bound(data.begin(), data.end(), x) - data.begin() - 1;
  }
  auto begin() const { return data.begin(); }
  auto end() const { return data.end(); }

 private:
  vector<T> data;
};

template <class It>
compress(It, It) -> compress<typename iterator_traits<It>::value_type>;
