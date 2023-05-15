#pragma once
#include "graph.hpp"

class hld {
 public:
  template <class G>
  hld(const G& graph, int r = 0) {
    graph_trait<G> g(graph);
    in.resize(g.size());
    out.resize(g.size());
    par.resize(g.size());
    heavy.assign(g.size(), -1);
    head.resize(g.size());
    par[r] = -1;
    dfs(g, r);
    int t = 0;
    decompose(g, t, r);
  }

  int idx(int v) const { return in[v]; }
  int lca(int u, int v) const {
    while (head[u] != head[v]) {
      if (in[u] > in[v]) swap(u, v);
      v = par[head[v]];
    }
    return in[u] < in[v] ? u : v;
  }

  // Call f(l[0], r[0]), f(l[1], r[1]), ...
  // s.t. union of [l[i], r[i]) == {idx(v) for v in u-v-path}.
  template <class F>
  void paths(int u, int v, F&& f, bool exclude_lca = true) const {
    while (head[u] != head[v]) {
      if (in[u] > in[v]) swap(u, v);
      call_f(f, idx(head[v]), idx(v) + 1);
      v = par[head[v]];
    }
    if (in[u] > in[v]) swap(u, v);
    call_f(f, idx(u) + exclude_lca, idx(v) + 1);
  }

  template <class F>
  void subtree(int v, F&& f, bool exclude_root = true) const {
    call_f(f, in[v] + exclude_root, out[v]);
  }

 private:
  vector<int> in, out, par, heavy, head;

  template <class G>
  int dfs(graph_trait<G> g, int v) {
    int total_size = 1, max_size = 0;
    g.adj(v, [&](int u) {
      if (u != par[v]) {
        par[u] = v;
        int sz = dfs(g, u);
        total_size += sz;
        if (sz > max_size) max_size = sz, heavy[v] = u;
      }
    });
    return total_size;
  }

  template <class G>
  void decompose(graph_trait<G> g, int& t, int v) {
    in[v] = t++;
    if (heavy[v] != -1) head[heavy[v]] = head[v], decompose(g, t, heavy[v]);
    g.adj(v, [&](int u) {
      if (u != par[v] && u != heavy[v]) head[u] = u, decompose(g, t, u);
    });
    out[v] = t;
  }

  template <class F>
  void call_f(F& f, int l, int r) const {
    if (r - l) f(l, r);
  }
};
