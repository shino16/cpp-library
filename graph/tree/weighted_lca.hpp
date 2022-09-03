#pragma once
#include "algebra.hpp"
#include "graph/tree/dfs.hpp"
#include "bit/ilog2.hpp"

template <class M>
class weighted_lca {
 public:
  using weight_type = typename M::type;
  using edge_type = weighted_edge<weight_type>;

  template <class G, enable_if<is_same_v<weight_type, weight_t<G>>>* = nullptr>
  weighted_lca(const G& graph, int r = 0, M m = M())
      : size(graph_trait<G>(graph).size()),
        height(ilog2(size) + 1),
        m(m),
        data(height, vector<edge_type>(size)),
        depth(size) {
    data[0][r] = {r, m.unit()};
    depth[r] = 0;
    dfs(graph, r, [&](auto&& e, int p) {
      data[0][e.to] = {p, e.w()};
      depth[e.to] = depth[p] + 1;
    });
    rep(h, height - 1) rep(x, size) { data[h + 1][x] = extend(data[h][x], h); }
  }

  int lca(int u, int v) const { return paths_to_lca(u, v).first.to; }
  // product of u-v-path
  weight_type path_prod(int u, int v) const {
    auto [eu, ev] = paths_to_lca(u, v);
    return m.op(eu.w(), m.inv(ev.w()));
  }
  // signless sum of u-v-path
  weight_type path_sum(int u, int v) const {
    auto [eu, ev] = paths_to_lca(u, v);
    return m.op(eu.w(), ev.w());
  }

 private:
  int size, height;
  M m;
  vector<vector<edge_type>> data;
  vector<int> depth;

  // edge_type ascend(int v, int d) const {
  //   return ascend(edge_type{v, m.unit()}, d);
  // }
  edge_type ascend(edge_type base, int d) const {
    rep(h, height) if (d >> h & 1) base = extend(base, h);
    return base;
  }
  edge_type extend(edge_type e, int h) const {
    auto [to, w] = data[h][e.to];
    return {to, m.op(e.w(), w)};
  }
  pair<edge_type, edge_type> paths_to_lca(int u, int v) const {
    edge_type eu = {u, m.unit()}, ev = {v, m.unit()};
    if (depth[u] < depth[v])
      ev = ascend(ev, depth[v] - depth[u]);
    else if (depth[u] > depth[v])
      eu = ascend(eu, depth[u] - depth[v]);

    if (eu.to == ev.to) return {eu, ev};
    repr(h, height) {
      if (data[h][eu.to].to != data[h][ev.to].to)
        eu = extend(eu, h), ev = extend(ev, h);
    }
    return {extend(eu, 0), extend(ev, 0)};
  }
};
