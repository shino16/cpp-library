#pragma once
#include "graph0.hpp"
#include "prelude.hpp"

template <class G, class F1, class F2>
void dfs(const G& graph, V<G> s, const F1& fin, const F2& fout, V<G> p = -1) {
  graph_trait<G> g{graph};
  auto dfs = [&](auto&& dfs, V<G> v, V<G> p) -> void {
    g.adj(v, [&](auto u) {
      if (u != p) fin(u, v), dfs(dfs, u, v), fout(u, v);
    });
  };
  dfs(dfs, s, p);
}

template <class G, class F>
void dfs(const G& graph, V<G> s, const F& f, V<G> p = -1) {
  dfs(graph, s, [](auto&&...){}, f, p);
}

template <class G, class F>
void dfs_down(const G& graph, V<G> s, const F& f, V<G> p = -1) {
  dfs(graph, s, f, [](auto&&...){}, p);
}
