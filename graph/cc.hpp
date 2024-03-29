#pragma once
#include "graph.hpp"

// graph: bidirectional
template <class G, class weight_type = typename graph_trait<G>::weight_type>
vector<pair<csr_graph<weight_type>, vector<int>>> components(
    const G& graph) {
  graph_trait<G> g{graph};
  vector<pair<csr_graph<weight_type>, vector<int>>> res;
  vector<int> pi(g.size(), -1);
  using E = conditional_t<
      is_weighted_v<G>, tuple<int, int, weight_t<G>>, pair<int, int>>;
  rep(s, g.size()) if (pi[s] == -1) {
    vector<int> q;
    vector<E> es;
    auto dfs = [&](auto&& f, int v) -> void {
      pi[v] = q.size();
      q.push_back(v);
      g.adj(v, [&](auto e) {
        if (pi[e.to] == -1) f(f, e.to);
        if constexpr (is_weighted_v<G>)
          es.emplace_back(pi[v], pi[e.to], e.w());
        else
          es.emplace_back(pi[v], pi[e.to]);
      });
    };
    dfs(dfs, s);
    int n = q.size();
    res.emplace_back(csr_graph<weight_type>::directed(n, all(es)), move(q));
  }
  return res;
}
