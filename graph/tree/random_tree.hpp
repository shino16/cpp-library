#pragma once
#include "graph.hpp"
#include "util/rand.hpp"

vector<vector<int>> random_tree(int n, const vector<int>& code) {
  vector<int> degree(n, 1);
  for (int i : code) degree[i]++;

  set<int> leaves;
  for (int i = 0; i < n; i++)
    if (degree[i] == 1) leaves.insert(i);

  vector<vector<int>> G(n);
  for (int v : code) {
    int leaf = *leaves.begin();
    leaves.erase(leaves.begin());

    G[leaf].push_back(v);
    G[v].push_back(leaf);
    if (--degree[v] == 1) leaves.insert(v);
  }
  G[*leaves.begin()].push_back(n-1);
  G[n-1].push_back(*leaves.begin());
  return G;
}

vector<vector<int>> random_tree(int n) {
  vector<int> code(n - 2);
  rep(i, n) code[i] = rand32() % n;
  return random_tree(n, code);
}
