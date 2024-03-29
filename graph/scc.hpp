#pragma once
#include "graph.hpp"

template <class G>
class scc {
 public:
  scc(const G& graph) : g(graph), id_(g.size()), n_cpnts(0) {
    vector<char> visited(g.size(), false);
    vector<int> post_ord;
    post_ord.reserve(g.size());
    vector<vector<int>> rev_graph(g.size());
    auto dfs = [&](auto&& f, int v) -> void {
      visited[v] = true;
      g.adj(v, [&](int u) {
        rev_graph[u].push_back(v);
        if (!visited[u]) f(f, u);
      });
      post_ord.push_back(v);
    };
    rep(v, g.size()) if (!visited[v]) dfs(dfs, v);
    reverse(all(post_ord));
    fill(all(visited), false);
    auto dfs2 = [&](auto&& f, int v) -> void {
      visited[v] = true;
      id_[v] = n_cpnts;
      for (auto u : rev_graph[v])
        if (!visited[u]) f(f, u);
    };
    for (auto v : post_ord)
      if (!visited[v]) dfs2(dfs2, v), n_cpnts++;
  }
  // which component v belongs to
  int operator()(int v) const { return id_[v]; }
  int group_of(int v) const { return id_[v]; }
  int n_groups() const { return n_cpnts; }

  vector<vector<int>> groups() const {
    vector<vector<int>> res(n_cpnts);
    rep(v, g.size()) res[id_[v]].push_back(v);
    return res;
  }

  template <class G1 = G, enable_if_t<!is_weighted_v<G1>>* = nullptr>
  vector<vector<vector<int>>> components() const {
    vector<int> v;
    return components(v);
  }
  template <class G1 = G, enable_if_t<!is_weighted_v<G1>>* = nullptr>
  vector<vector<vector<int>>> components(vector<int>& mapping) const {
    vector<int> sizes(n_cpnts, 0);
    mapping.resize(g.size());
    rep(v, g.size()) mapping[v] = sizes[id_[v]]++;
    vector<vector<vector<int>>> res(n_cpnts);
    rep(i, n_cpnts) res[i].resize(sizes[i]);
    rep(v, g.size()) g.adj(v, [&](int u) {
      if (id_[v] == id_[u]) res[id_[v]][mapping[v]].push_back(mapping[u]);
    });
    return res;
  }

  template <class G1 = G, enable_if_t<is_weighted_v<G1>>* = nullptr>
  vector<vector<vector<pair<int, weight_t<G>>>>> components() const {
    vector<int> v;
    return components(v);
  }
  template <class G1 = G, enable_if_t<is_weighted_v<G1>>* = nullptr>
  vector<vector<vector<pair<int, weight_t<G>>>>> components(
      vector<int>& mapping) const {
    vector<int> sizes(n_cpnts, 0);
    mapping.resize(g.size());
    rep(v, g.size()) mapping[v] = sizes[id_[v]]++;
    vector<vector<vector<pair<int, weight_t<G>>>>> res(n_cpnts);
    rep(i, n_cpnts) res[i].resize(sizes[i]);
    rep(v, g.size()) g.adj(v, [&](auto&& e) {
      if (id_[v] == id_[e.to])
        res[id_[v]][mapping[v]].emplace_back(mapping[e.to], e.w());
    });
    return res;
  }

  template <class G1 = G, enable_if_t<!is_weighted_v<G1>>* = nullptr>
  vector<vector<int>> contract() const {
    vector<vector<int>> res(n_cpnts);
    rep(v, g.size()) g.adj(v, [&](int u) {
      if (id_[v] != id_[u]) res[id_[v]].push_back(id_[u]);
    });
    return res;
  }

  template <class G1 = G, enable_if_t<is_weighted_v<G1>>* = nullptr>
  vector<vector<pair<int, weight_t<G>>>> contract() const {
    vector<vector<pair<int, weight_t<G>>>> res(n_cpnts);
    rep(v, g.size()) g.adj(v, [&](auto&& e) {
      if (id_[v] != id_[e.to]) res[v].emplace_back(e.to, e.w());
    });
    return res;
  }

 private:
  graph_trait<G> g;
  vector<int> id_;
  int n_cpnts;
};
