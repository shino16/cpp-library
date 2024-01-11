// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1638

#include "graph/grid.hpp"
#include "graph/dijkstra.hpp"
#include "io.hpp"

int main() {
  int h = in, w = in, u = in, d = in, r = in, l = in;
  ll k = in, p = in;

  int xs = --in, ys = --in, xt = --in, yt = --in;

  auto grid = in.vec<string>(h);
  auto weight = [=](char c, int dir) {
    return (c == '@' ? p : 0) + ((int[]){l, r, u, d})[dir];
  };
  grid_graph graph(all(grid), weight);
  ll ans = dijkstra(graph, graph.map(xs, ys))[graph.map(xt, yt)];
  out.Yes(ans <= k);
  (void)w;
}
