#pragma once
#include "graph.hpp"
#include "graph/tree/dfs.hpp"

struct identity {
  template <class T>
  auto operator()(T&& x) const {
    return forward<T>(x);
  }
};

template <class G, class T, class Add, class Remove, class Inv = identity>
vector<T> rerooting(const G& graph, T unit = T(), Add&& add = Add(),
                    Remove remove = Remove(), Inv e_inv = Inv()) {
  graph_trait<G> g(graph);
  vector<T> now(g.size(), unit), res(g.size(), unit);
  dfs_bottom_up(graph, 0, [&](auto&& e, int p) {
    add(now[p], now[e.to()], e.to(), e.w());
  });
  res[0] = now[0];
  dfs(graph, 0,
      [&](auto&& e, int p) {
        remove(now[p], now[e.to()], e.to(), e.w());
        add(now[e.to()], now[p], p, e_inv(e.w()));
        res[e.to()] = now[e.to()];
      },
      [&](auto&& e, int p) {
        remove(now[e.to()], now[p], p, e_inv(e.w()));
        add(now[p], now[e.to()], e.to(), e.w());
      });
  return res;
}
