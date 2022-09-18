#pragma once
#include "graph.hpp"

template <class G, class F>
void bfs01(const G& graph, int s, F&& f) {
  graph_trait<G> g(graph);
  vector<char> visited(g.size(), false);
  deque<int> togo;
  togo.push_back(s), visited[s] = true;
  while (!togo.empty()) {
    int v = togo.front(); togo.pop_front();
    g.adj(v, [&](auto&& e) {
      if (!visited[e.to]) {
        visited[e.to] = true, f(e, v);
        if (e.w()) togo.push_back(e.to);
        else togo.push_front(e.to);
      }
    });
  }
}

template <class G>
vector<int> dist01(const G& graph, int s) {
  graph_trait<G> g(graph);
  vector<int> res(g.size(), numeric_limits<int>::max());
  res[s] = 0;
  bfs(graph, s, [&](int v, int p) { res[v] = res[p] + 1; });
  return res;
}
