#pragma once
#include "graph/tree/dfs.hpp"
#include "bit/ilog2.hpp"

class lca {
 public:
  template <class G>
  lca(const G& g, int r = 0)
      : size(graph_trait<G>(g).size() + 1),
        height(ilog2(size) + 1),
        data(height, vector<int>(size)),
        dep(size) {
    int sentinel = size - 1;
    data[0][r] = data[0][sentinel] = sentinel;
    dep[r] = 1;
    dfs(g, r, [&](auto&& e, int p) {
      data[0][e.to] = p;
      dep[e.to] = dep[p] + 1;
    });
    rep(h, height - 1) rep(x, size) data[h + 1][x] = data[h][data[h][x]];
  }

  int par(int v) const { return data[0][v]; }
  int ascend(int v, int d) const {
    rep(h, height) if (d >> h & 1) v = data[h][v];
    return v == size - 1 ? -1 : v;
  }
  int operator()(int u, int v) const {
    if (dep[u] < dep[v])
      v = ascend(v, dep[v] - dep[u]);
    else if (dep[u] > dep[v])
      u = ascend(u, dep[u] - dep[v]);
    repr(h, height) {
      if (data[h][u] != data[h][v]) u = data[h][u], v = data[h][v];
    }
    return u == v ? u : data[0][u];
  }
  int depth(int v) const { return dep[v]; }

 private:
  int size, height;
  vector<vector<int>> data;
  vector<int> dep;
};
