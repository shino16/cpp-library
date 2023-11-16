#pragma once
#include "graph.hpp"
#include "func/constant.hpp"

template <class Weight = constant<int, 1>, char Wall = '#'>
class grid_graph {
 public:
  template <class It>
  grid_graph(It grid, It grid_last, Weight c = Weight())
      : h(grid_last - grid + 2), w(grid[0].size() + 2), c(c),
        data(h * w, Wall) {
    rep(i, h - 2) copy(all(grid[i]), data.begin() + (i + 1) * w + 1);
  }

  int map(int r, int c) const { return (r + 1) * w + c + 1; }
  char operator[](int i) const { return data[i]; }
  char operator[](int i[2]) const { return data[map(i[0], i[1])]; }

  using weight_type = invoke_result_t<Weight, char, int>;
  int size() const { return h * w; }
  template <class F>
  void adj(int v, F f) const {
    if (data[v] == Wall) return;
    const int d[] = {-1, 1, -w, w};
    rep(i, 4) if (data[v + d[i]] != Wall)
        f(edge_t<grid_graph>{v + d[i], c(data[v + d[i]], i)});
  }

 private:
  int h, w;
  Weight c;
  vector<char> data;
};
