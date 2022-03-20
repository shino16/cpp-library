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
class basic_graph {
 public:
  using weight_type = int;

  basic_graph(Inner& g) : inner(g) {}

  template <class F>
  void adj(int v, F&& f) const {
    for (auto u : inner[v]) f(unit_edge{u});
  }

 protected:
  Inner& inner;
};

template <class Inner, class Weight>
class basic_weighted_graph {
 public:
  using weight_type = Weight;

  basic_weighted_graph(Inner& g) : inner(g) {}

  template <class F>
  void adj(int v, F&& f) const {
    for (auto [u, w] : inner[v]) f(weighted_edge<weight_type>{u, w});
  }

 protected:
  Inner& inner;
};

template <class T>
class graph_trait;

template <class T>
using W = typename graph_trait<T>::weight_type;

template <size_t N>
class graph_trait<vector<int>[N]> : public basic_graph<vector<int>[N]> {
  using basic_graph<vector<int>[N]>::basic_graph;

 public:
  int size() const { return N; }
};

template <>
class graph_trait<vector<vector<int>>>
    : public basic_graph<vector<vector<int>>> {
  using basic_graph<vector<vector<int>>>::basic_graph;

 public:
  int size() const { return basic_graph<vector<vector<int>>>::inner.size(); }
};

template <size_t N, class Weight>
class graph_trait<vector<pair<int, Weight>>[N]>
    : public basic_weighted_graph<vector<pair<int, Weight>>[N], Weight> {
  using basic_weighted_graph<vector<pair<int, Weight>>[N],
                             Weight>::basic_weighted_graph;

 public:
  int size() const { return N; }
};

template <class Weight>
class graph_trait<vector<vector<pair<int, Weight>>>>
    : public basic_weighted_graph<vector<vector<pair<int, Weight>>>, Weight> {
  using basic_weighted_graph<vector<vector<pair<int, Weight>>>,
                             Weight>::basic_weighted_graph;

 public:
  int size() const { return basic_graph<vector<vector<int>>>::inner.size(); }
};
