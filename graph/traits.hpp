#pragma once
#include "prelude.hpp"

struct unit_edge {
  int to;
  operator int() const { return to; }
  int w() const { return 1; }
};

template <class Weight>
struct weighted_edge {
  int to;
  Weight weight;
  operator int() const { return to; }
  Weight w() const { return weight; }
};

template <class Inner>
struct basic_graph {
  using weight_type = void;
  const Inner& inner;
  basic_graph(const Inner& g) : inner(g) { }
  template <class F>
  void adj(int v, F f) const {
    for (auto u : inner[v]) f(unit_edge{u});
  }
  int deg(int v) const { return inner[v].size(); }
};

template <class Inner, class Weight>
struct basic_weighted_graph {
  using weight_type = Weight;
  const Inner& inner;
  basic_weighted_graph(const Inner& g) : inner(g) { }
  template <class F>
  void adj(int v, F f) const {
    for (auto [u, w] : inner[v]) f(weighted_edge<weight_type>{u, w});
  }
  int deg(int v) const { return inner[v].size(); }
};

template <class Inner>
struct graph_trait {
  using weight_type = typename Inner::weight_type;
  const Inner& g;
  graph_trait(const Inner& g) : g(g) { }
  int size() const { return g.size(); }
  template <class F>
  void adj(int v, F f) const {
    g.adj(v, f);
  }
};

template <class T>
constexpr bool is_weighted_v =
    !is_same_v<typename graph_trait<T>::weight_type, void>;

template <class T>
using weight_t =
    conditional_t<is_weighted_v<T>, typename graph_trait<T>::weight_type, int>;

template <class T>
using edge_t =
    conditional_t<is_weighted_v<T>, weighted_edge<weight_t<T>>, unit_edge>;

template <size_t N>
struct graph_trait<vector<int>[N]> : basic_graph<vector<int>[N]> {
  using basic_graph<vector<int>[N]>::basic_graph;
  int size() const { return N; }
};

template <>
struct graph_trait<vector<vector<int>>> : basic_graph<vector<vector<int>>> {
  using basic_graph<vector<vector<int>>>::basic_graph;
  int size() const { return this->inner.size(); }
};

template <size_t N, class Weight>
struct graph_trait<vector<pair<int, Weight>>[N]>
    : basic_weighted_graph<vector<pair<int, Weight>>[N], Weight> {
      using basic_weighted_graph<
          vector<pair<int, Weight>>[N], Weight>::basic_weighted_graph;
      int size() const { return N; }
    };

template <class Weight>
struct graph_trait<vector<vector<pair<int, Weight>>>>
    : basic_weighted_graph<vector<vector<pair<int, Weight>>>, Weight> {
  using basic_weighted_graph<
      vector<vector<pair<int, Weight>>>, Weight>::basic_weighted_graph;
  int size() const { return this->inner.size(); }
};
