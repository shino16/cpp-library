#pragma once
#include "graph.hpp"
#include "io.hpp"
#include "range.hpp"

template <class Weight = void, bool Directed = false, bool OneBased = true>
class csr_graph {
 public:
  constexpr static bool weighted = !is_same_v<Weight, void>;
  using weight_type = conditional_t<!weighted, Weight, int>;
  using edge_type = conditional_t<weighted, weighted_edge<Weight>, unit_edge>;

  template <class It>
  csr_graph(int n, It e, It e_last) : n(n), m(distance(e, e_last)) {
    init(e, e_last);
  }
  template <size_t Size = 1 << 26>
  csr_graph(int n, int m, stdin_reader<Size>& read = in) : n(n), m(m) {
    auto e = read_e(read);
    init(all(e));
  }
  template <size_t Size = 1 << 26>
  csr_graph(stdin_reader<Size>& read = in) : n(read), m(read) {
    auto e = read_e(read);
    init(all(e));
  }

  int size() const { return n; }
  range<typename vector<edge_type>::iterator> operator[](int v) const {
    return {ls[v], rs[v]};
  }
  template <class F>
  void adj(int v, F f) const {
    for_each(ls[v], rs[v], f);
  }

 private:
  int n, m;
  vector<edge_type> es;
  vector<typename vector<edge_type>::iterator> ls, rs;
  template <size_t Size = 1 << 26>
  auto read_e(stdin_reader<Size>& read) {
    using E = conditional_t<weighted, tuple<int, int, Weight>, pair<int, int>>;
    vector<E> res(m);
    for (auto& e : res) {
      read(e);
      if (OneBased) get<0>(e)--, get<1>(e)--;
    }
    return res;
  }
  template <class It>
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
      if constexpr (weighted)
        *--ls[from] = edge_type{to, get<2>(*it)};
      else
        *--ls[from] = edge_type{to};
      if (!Directed) {
        if constexpr (weighted)
          *--ls[to] = edge_type{from, get<2>(*it)};
        else
          *--ls[to] = edge_type{from};
      }
    }
  }
};
