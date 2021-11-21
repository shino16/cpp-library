#pragma once
#include "prelude.hpp"

template <class T, size_t K>
class kd_tree {
 public:
  struct point {
    int id;
    array<T, K> coord;
  };

  kd_tree() = default;
  template <class Iter>
  kd_tree(Iter f, Iter l) : root(build(f, l, 0)) {}

  template <class Iter>
  void build(Iter f, Iter l) {
    ns.clear();
    ns.reserve(l - f);
    root = build(f, l, 0);
  }

  template <class Iter>
  vector<int> find(Iter range) {
    vector<int> ans;
    search(root, range, 0, [&](auto &pt) { ans.push_back(pt.id); });
    return ans;
  }

 private:
  struct node {
    point pt;
    int l, r;
  };
  vector<node> ns;
  int root;

  template <class Iter>
  int build(Iter f, Iter l, int k) {
    if (f == l) return -1;
    Iter m = f + (l - f) / 2;
    nth_element(f, m, l,
                [=](auto &&a, auto &&b) { return a.coord[k] < b.coord[k]; });
    ns.emplace_back(
        node{*m, build(f, m, (k + 1) % K), build(next(m), l, (k + 1) % K)});
    return ns.size() - 1;
  }
  template <class Iter, class F>
  void search(int idx, Iter range, int k, F &&f) {
    if (idx == -1) return;
    bool inside = true;
    rep(i, K) if (ns[idx].pt.coord[i] < range[i].first ||
                  range[i].second <= ns[idx].pt.coord[i]) {
      inside = false;
      break;
    }
    if (inside) f(ns[idx].pt);
    T x = ns[idx].pt.coord[k];
    if (range[k].first <= x) search(ns[idx].l, range, (k + 1) % K, f);
    if (x < range[k].second) search(ns[idx].r, range, (k + 1) % K, f);
  }
};
