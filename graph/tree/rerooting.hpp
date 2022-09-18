#pragma once
#include "graph.hpp"
#include "graph/tree/dfs.hpp"
#include "func/id.hpp"

// add(&par.data, &v.data, v, edge)
template <class G, class T, class Add, class Remove, class Inv = identity>
vector<T> rerooting(
    const G& graph, vector<T> init, Add&& add = Add(), Remove remove = Remove(),
    Inv e_inv = Inv()) {
  graph_trait<G> g(graph);
  vector<T> now(move(init)), res(g.size());
  dfs_bottom_up(
      graph, 0, [&](auto&& e, int p) { add(now[p], now[e.to], e.to, e.w()); });
  res[0] = now[0];
  dfs(
      graph, 0,
      [&](auto&& e, int p) {
        remove(now[p], now[e.to], e.to, e.w());
        add(now[e.to], now[p], p, e_inv(e.w()));
        res[e.to] = now[e.to];
      },
      [&](auto&& e, int p) {
        remove(now[e.to], now[p], p, e_inv(e.w()));
        add(now[p], now[e.to], e.to, e.w());
      });
  return res;
}

// add(&par.data, &v.data, v, edge)
template <class G, class T, class Add, class Remove, class Inv = identity>
vector<T> rerooting(
    const G& graph, T unit = T(), Add&& add = Add(), Remove remove = Remove(),
    Inv e_inv = Inv()) {
  return rerooting(
      graph, vector<T>(graph_trait<G>(graph).size(), unit), add, remove, e_inv);
}
