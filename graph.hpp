#pragma once
#include "prelude.hpp"

template <class G> struct graph_trait;

template <class G> using W = typename graph_trait<G>::W;
template <class G> using V = typename graph_trait<G>::V;

template <class G, class E>
struct sparse_graph {
  struct details {
    static int to(int e) { return e; }
    template <class T> static int to(const pair<int, T>& e) { return e.first; }
    static int w(int) { return 1; }
    template <class T> static T w(const pair<int, T>& e) { return e.second; }
  };
  const G& g;
  using V = int;
  using W = decltype(details::w(declval<E>()));
  int size() const { return std::size(g); }
  int id(V v) const { return v; }
  template <class F>
  void adj(int v, const F& f) const { for (auto&& u : g[v]) f(details::to(u)); }
  template <class F>
  void adj_w(int v, const F& f) const { for (auto&& u : g[v]) f(details::to(u), details::w(u)); }
  int operator()(V v) const { return id(v); }
};

template <class E, size_t N>
struct graph_trait<vector<E>[N]> : sparse_graph<vector<E>[N], E> { };

template <class E>
struct graph_trait<vector<vector<E>>> : sparse_graph<vector<vector<E>>, E> { };
