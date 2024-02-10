#pragma once
#include "graph.hpp"
#include "range.hpp"

template <size_t>
struct stdin_reader;

template <class Weight = void>
class csr_graph {
 private:
  struct directed_t {};

 public:
  using weight_type = Weight;

  csr_graph() = default;
  template <class It>
  csr_graph(int n, It e, It e_last) : n(n), m(distance(e, e_last)) {
    init<false>(e, e_last);
  }
  template <size_t Size = 1 << 26>
  csr_graph(int n, int m, stdin_reader<Size>& read) : n(n), m(m) {
    auto e = read_e(read);
    init<false>(all(e));
  }

  template <class It>
  static csr_graph directed(int n, It e, It e_last) {
    return csr_graph(directed_t{}, n, e, e_last);
  }
  template <size_t Size = 1 << 26>
  static csr_graph directed(int n, int m, stdin_reader<Size>& read) {
    return csr_graph(directed_t{}, n, m, read);
  }

  template <size_t Size = 1 << 26>
  static csr_graph tree(int n, stdin_reader<Size>& read) {
    return csr_graph(n, n - 1, read);
  }
  template <size_t Size = 1 << 26>
  static csr_graph tree(stdin_reader<Size>& read) {
    int n = read;
    return csr_graph(n, n - 1, read);
  }

  int size() const { return n; }
  range<typename vector<edge_t<csr_graph>>::iterator> operator[](int v) const {
    return {ls[v], rs[v]};
  }
  int deg(int v) { return rs[v] - ls[v]; }
  template <class F>
  void adj(int v, F f) const {
    for_each(ls[v], rs[v], f);
  }

 private:
  template <class It>
  csr_graph(directed_t, int n, It e, It e_last) : n(n), m(distance(e, e_last)) {
    init<true>(e, e_last);
  }
  template <size_t Size = 1 << 26>
  csr_graph(directed_t, int n, int m, stdin_reader<Size>& read) : n(n), m(m) {
    auto e = read_e(read);
    init<true>(all(e));
  }

  vector<typename vector<edge_t<csr_graph>>::iterator> ls, rs;
  int n, m;
  vector<edge_t<csr_graph>> es;
  template <bool OneBased = true, size_t Size = 1 << 26>
  auto read_e(stdin_reader<Size>& read) {
    using E = conditional_t<is_weighted_v<csr_graph>, tuple<int, int, Weight>,
                            pair<int, int>>;
    vector<E> res(m);
    for (auto& e : res) {
      read(e);
      if (OneBased) get<0>(e)--, get<1>(e)--;
    }
    return res;
  }
  template <bool Directed, class It>
  void init(It e, It e_last) {
    if (!Directed) m *= 2;
    es.resize(m);
    ls.resize(n), rs.resize(n);
    vector<int> sz(n);
    for (auto it = e; it != e_last; it++) {
      int from = get<0>(*it), to = get<1>(*it);
      sz[from]++;
      if (!Directed) sz[to]++;
    }
    partial_sum(all(sz), sz.begin());
    rep(v, n) ls[v] = rs[v] = es.begin() + sz[v];
    for (auto it = e; it != e_last; it++) {
      int from = get<0>(*it), to = get<1>(*it);
      if constexpr (is_weighted_v<csr_graph>)
        *--ls[from] = edge_t<csr_graph>{to, get<2>(*it)};
      else
        *--ls[from] = edge_t<csr_graph>{to};
      if (!Directed) {
        if constexpr (is_weighted_v<csr_graph>)
          *--ls[to] = edge_t<csr_graph>{from, get<2>(*it)};
        else
          *--ls[to] = edge_t<csr_graph>{from};
      }
    }
  }
};
