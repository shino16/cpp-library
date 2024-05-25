#pragma once
#include "graph.hpp"

// f(edge, par)
template <class G, class Fin, class Fout>
void dfs(const G& graph, int s, Fin&& fin, Fout&& fout) {
  graph_trait<G> g(graph);
  vector<char> visited(g.size(), false);
  visited[s] = true;
  auto dfs_fn = [&](auto&& f, int v) {
    g.adj(v, [&](auto&& e) {
      if (!visited[e.to])
        visited[e.to] = true, fin(e, v), f(f, e.to), fout(e, v);
    });
  };
  dfs_fn(dfs_fn, s);
}

// f(edge, par)
template <class G, class F>
void dfs(const G& graph, int s, F&& f) {
  dfs(graph, s, f, [](auto&&, auto&&) {});
}

// f(edge, par)
template <class G, class F>
void dfs_bottom_up(const G& graph, int s, F&& f) {
  dfs(graph, s, [](auto&&, auto&&) {}, f);
}

// f(edge, par)
template <class G, class Fin, class Fout>
void dfs_ord(const G& graph, int s, Fin&& fin, Fout&& fout) {
  fin(s, -1);
  dfs(graph, s, [&](int v, int p) { fin(v, p); }, [&](int v, int p) { fout(v, p); });
  fout(s, -1);
}

// f(edge, par)
template <class G, class F>
void dfs_ord(const G& graph, int s, F&& f) {
  dfs_ord(graph, s, f, [](auto&&, auto&&) {});
}

// f(edge, par)
template <class G, class F>
void dfs_rev_ord(const G& graph, int s, F&& f) {
  dfs_bottom_up(graph, s, [&](int v, int p) { f(v, p); });
  f(s, -1);
}
