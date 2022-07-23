#pragma once
#include "graph.hpp"

template <class G, class F>
void bfs(const G& graph, int s, F&& f) {
  graph_trait<G> g(graph);
  vector<char> visited(g.size(), false);
  vector<int> togo;
  togo.reserve(g.size());
  auto nxt = togo.begin();
  togo.push_back(s), visited[s] = true;
  while (nxt != togo.end()) {
    int v = *nxt++;
    g.adj(v, [&](auto&& e) {
      if (!visited[e.to()])
        visited[e.to()] = true, f(e, v), togo.push_back(e.to());
    });
  }
}

template <class G, class F>
void bfs_ord(const G& graph, int s, F&& f) {
  f(s, -1);
  dfs(graph, s, [&](int v, int p) { f(v, p); });
}

template <class G>
vector<int> dist(const G& graph, int s) {
  graph_trait<G> g(graph);
  vector<int> res(g.size(), numeric_limits<int>::max());
  res[s] = 0;
  bfs(graph, s, [&](int v, int p) { res[v] = res[p] + 1; });
  return res;
}
