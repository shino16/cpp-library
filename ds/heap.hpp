#pragma once
#include "func/id.hpp"

template <class T, class Cmp = less<>>
class heap {
 public:
  heap(Cmp cmp = Cmp()) : cmp(cmp), data(1) { }
  heap(int n, Cmp cmp = Cmp()) : cmp(cmp), data(1), pos(n, -1) { }
  // moves out from [second, last)
  template <class It>
  heap(It second, It last, Cmp cmp = Cmp()) : cmp(cmp) {
    init(second, last);
  }
  // moves out from [second, last)
  template <class It>
  void init(It second, It last) {
    data.resize(1), pos.clear();
    int n = distance(second, last);
    data.reserve(n), pos.resize(n);
    for (auto it = second; it != last; it++)
      data.emplace_back(data.size(), move(*it));
    iota(all(pos), 1);
    repr2(v, 1, n / 2 + 1) merge(v);
  }

  bool empty() const { return data.size() == 1; }
  void reserve(int n) { pos.resize(max<size_t>(pos.size(), n), -1); }
  bool contains(int i) const { return i < pos.size() && pos[i] != -1; }
  void insert(int i, T x) {
    assert(!contains(i));
    reserve(i + 1);
    pos[i] = data.size(), data.emplace_back(i, x);
    pushup(pos[i]);
  }
  void modify(int i, T x) {
    assert(contains(i));
    int v = pos[i];
    bool decrease = cmp(x, exchange(data[v].second, x));
    return decrease ? merge(v) : pushup(v);
  }
  void insert_or_modify(int i, T x) {
    return contains(i) ? modify(i, x) : insert(i, x);
  }
  const T& top() const { return data[1].second; }
  pair<int, T> pop() {
    pair<int, T> res = move(data[1]);
    pos[res.first] = -1;
    if (data.size() == 2) {
      data.pop_back();
      return res;
    }
    data[1] = move(data.back()), data.pop_back(), pos[data[1].first] = 1;
    merge(1);
    return res;
  }

 private:
  Cmp cmp;
  vector<pair<int, T>> data;
  vector<int> pos;
  void merge(int v) {
    if (v * 2 >= data.size()) return;
    int l = v * 2, r = v * 2 + 1;
    int c = r < data.size() && cmp(data[l].second, data[r].second) ? r : l;
    if (cmp(data[v].second, data[c].second)) {
      swap(data[v], data[c]), swap(pos[data[v].first], pos[data[c].first]);
      merge(c);
    }
  }
  void pushup(int v) {
    for (int p = v / 2; p && cmp(data[p].second, data[v].second);
         v /= 2, p /= 2)
      swap(data[p], data[v]), swap(pos[data[p].first], pos[data[v].first]);
  }
};
