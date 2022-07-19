#pragma once
#include "graph.hpp"
#include "util/rand.hpp"

vector<vector<int>> random_tree(int n) {
  vector<int> code(n - 2);
  rep(i, n) code[i] = rand32() % n;
  vector<int> deg(n, 1);
  for (auto v : code) deg[v]++;
  priority_queue<int> leaves;
  vector<vector<int>> G(n);
  rep(i, n) if (deg[i] == 1) leaves.push(i);
  for (auto v : code) {
    int u = leaves.top(); leaves.pop();
    G[u].push_back(v);
    G[v].push_back(u);
    if (--deg[v] == 1) leaves.push(v);
  }
  int v = leaves.top();
  G[v].push_back(n-1);
  G[n-1].push_back(v);
  return G;
}
