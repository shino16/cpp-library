#pragma once

#include "graph/tree/dfs.hpp"
#include "graph/tree/lca.hpp"

template <class G>
struct aux_tree {
 public:
  aux_tree(G& graph, int r = 0) : g(graph), lc(graph, r) {
    ord.resize(g.size());
    mp.assign(g.size(), -1);
    int t = 0;
    dfs_ord(g, r, [&](int v, int) { ord[v] = t++; });
  }
  pair<csr_graph<void>, vector<int>> get(vector<int> vs) {
    if (vs.empty()) vs.push_back(0);
    sort(all(vs), [&](int u, int v) { return ord[u] < ord[v]; });
    vs.erase(unique(all(vs)), vs.end());
    mp[vs[0]] = 0;
    vector<int> id = {vs[0]}, stack = {vs[0]};
    vector<pair<int, int>> es;
    rep2(i, 1, vs.size()) {
      int w = lc(vs[i - 1], vs[i]);
      if (mp[vs[i]] == -1) mp[vs[i]] = id.size(), id.push_back(vs[i]);
      if (mp[w] == -1) mp[w] = id.size(), id.push_back(w);
      if (w != vs[i-1]) {
        int v = stack.back();
        stack.pop_back();
        while (!stack.empty() && lc.depth(stack.back()) > lc.depth(w)) {
          es.emplace_back(mp[stack.back()], mp[v]);
          v = stack.back(), stack.pop_back();
        }
        es.emplace_back(mp[w], mp[v]);
        if (stack.empty() || stack.back() != w) stack.push_back(w);
      }
      stack.push_back(vs[i]);
    }
    while (stack.size() >= 2) {
      int v = stack.back();
      stack.pop_back();
      es.emplace_back(mp[stack.back()], mp[v]);
    }
    int k = id.size();
    rep(i, k) mp[id[i]] = -1;
    return pair(csr_graph(k, all(es)), move(id));
  }

 private:
  vector<int> ord;
  graph_trait<G> g;
  lca lc;
  vector<int> mp;
};
