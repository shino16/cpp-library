#pragma once
#include "prelude.hpp"

struct unit_edge {
  int v;
  int to() const { return v; }
  operator int() const { return to(); }
  int w() const { return 1; }
};

template <class Weight>
struct weighted_edge {
  int v;
  Weight weight;
  int to() const { return v; }
  operator int() const { return to(); }
  Weight w() const { return weight; }
};

template <class Inner>
struct basic_graph {
  using weight_type = int;
  constexpr static bool weighted = false;
  const Inner& inner;
  basic_graph(const Inner& g) : inner(g) {}
  template <class F>
  void adj(int v, F&& f) const {
    for (auto u : inner[v]) f(unit_edge{u});
  }
};

template <class Inner, class Weight>
struct basic_weighted_graph {
  using weight_type = Weight;
  constexpr static bool weighted = true;
  const Inner& inner;
  basic_weighted_graph(const Inner& g) : inner(g) {}
  template <class F>
  void adj(int v, F&& f) const {
    for (auto [u, w] : inner[v]) f(weighted_edge<weight_type>{u, w});
  }
};

template <class T>
struct graph_trait : public T {
  graph_trait(T t) : T(move(t)) {}
};

template <class T>
using W = typename graph_trait<T>::weight_type;

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
  using basic_weighted_graph<vector<pair<int, Weight>>[N],
                             Weight>::basic_weighted_graph;
  int size() const { return N; }
};

template <class Weight>
struct graph_trait<vector<vector<pair<int, Weight>>>>
    : basic_weighted_graph<vector<vector<pair<int, Weight>>>, Weight> {
  using basic_weighted_graph<vector<vector<pair<int, Weight>>>,
                             Weight>::basic_weighted_graph;
  int size() const { return this->inner.size(); }
};
