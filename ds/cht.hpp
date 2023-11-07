#pragma once
#include "arith/sqrt.hpp"
#include "la/vec.hpp"
#include "num/int/bisect.hpp"

template <class T>
using linear_fn = pair<T, T>;

template <class T>
T apply(linear_fn<T> f, T x) {
  return f.first * x + f.second;
}

// checked (CF 660F)

// min/max of linear functions
template <class T, bool Maximize = false>
class convex_hull_trick {
 public:
  convex_hull_trick() : ready(true), hull({linear_fn<T>{0, sentinel()}}) {}
  template <class It>
  convex_hull_trick(It first, It last) {
    init(first, last);
  }
  void clear() {
    hull.clear(), edges.clear();
    hull.emplace_back(0, sentinel());
  }
  template <bool Sorted = false, class It>
  void init(It first, It last) {
    clear();
    int n = distance(first, last);
    hull.reserve(n + 1), edges.reserve(n);
    if (!Sorted) sort(first, last);
    for (auto it = first; it != last; it++) {
      while (!edges.empty() &&
             (det(edges.back(), *it - hull.back()) <= 0) ^ Maximize)
        hull.pop_back(), edges.pop_back();
      edges.push_back(*it - hull.back()), hull.push_back(*it);
    }
    ready = true;
  }
  void rebuild() {
    vector<linear_fn<T>> fs(all(hull));
    fs.insert(fs.end(), all(aux));
    sort(all(fs));
    init(all(fs));
  }

  void add(linear_fn<T> f) { aux.push_back(f), ready = false; }
  void add(T a, T b) { aux.emplace_back(a, b), ready = false; }

  T apply(T x) {
    assert(ready);
    linear_fn<T> f(1, -x);
    int i = bisect<int>(0, edges.size(), [&](int j) {
      return (det(f, edges[j]) < 0) ^ Maximize;
    });
    T ans = ::apply(hull[i], x);
    for (auto g : aux) ans = min(ans, ::apply(g, x));
    return ans;
  }

 private:
  bool ready;
  vector<linear_fn<T>> hull, edges, aux;
  static T sentinel() {
    return floor_sqrt(numeric_limits<T>::max()) * (Maximize ? -1 : 1);
  }
};
