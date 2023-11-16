#pragma once

template <class T, class Cmp = less<>>
class heap {
 public:
  heap(Cmp cmp = Cmp()) : cmp(cmp), data(1) {}
  heap(int n, Cmp cmp = Cmp()) : cmp(cmp), data(1), pos(n, -1) {}
  // moves out from [first, last)
  template <class It>
  heap(It first, It last, Cmp cmp = Cmp()) : cmp(cmp) {
    init(first, last);
  }
  // moves out from [first, last)
  template <class It>
  void init(It first, It last) {
    data.resize(1), pos.clear();
    int n = distance(first, last);
    data.reserve(n), pos.resize(n);
    for (auto it = first; it != last; it++)
      data.emplace_back(data.size(), move(*it));
    iota(all(pos), 1);
    repr2(v, 1, n / 2 + 1) merge(v);
  }

  bool empty() const { return data.size() == 1; }
  int size() const { return data.size() - 1; }
  void reserve(int n) { pos.resize(max<size_t>(pos.size(), n), -1); }
  bool contains(int i) const { return i < pos.size() && pos[i] != -1; }
  void insert(int i, T x) {
    reserve(i + 1);
    pos[i] = data.size(), data.emplace_back(x, i);
    pushup(pos[i]);
  }
  void modify(int i, T x) {
    int v = pos[i];
    bool decrease = cmp(x, exchange(data[v].first, x));
    return decrease ? merge(v) : pushup(v);
  }
  void insert_or_modify(int i, T x) {
    return contains(i) ? modify(i, x) : insert(i, x);
  }
  const pair<T, int>& top() const { return data[1]; }
  pair<T, int> pop() { return erase(data[1].second); }
  pair<T, int> erase(int i) {
    int idx = exchange(pos[i], -1);
    pair<T, int> res = exchange(data[idx], move(data.back()));
    data.pop_back();
    if (idx != data.size()) pos[data[idx].second] = idx, merge(idx);
    return res;
  }

 private:
  Cmp cmp;
  vector<pair<T, int>> data;
  vector<int> pos;
  void merge(int v) {
    if (v * 2 >= data.size()) return;
    int l = v * 2, r = v * 2 + 1;
    int c = r < data.size() && cmp(data[l].first, data[r].first) ? r : l;
    if (cmp(data[v].first, data[c].first)) {
      swap(data[v], data[c]), swap(pos[data[v].second], pos[data[c].second]);
      merge(c);
    }
  }
  void pushup(int v) {
    for (int p = v / 2; p && cmp(data[p].first, data[v].first); v /= 2, p /= 2)
      swap(data[p], data[v]), swap(pos[data[p].second], pos[data[v].second]);
  }
};
