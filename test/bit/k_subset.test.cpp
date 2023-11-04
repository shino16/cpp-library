#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include "io.hpp"
#include "util/rand.hpp"
#include "bit/k_subset.hpp"

vector<int> ints;
void dfs(int mask, int i, int p, int k) {
  if (i == -1) {
    if (p == k) ints.push_back(mask);
    return;
  }
  dfs(mask, i - 1, p, k);
  if (p < k) dfs(mask | 1 << i, i - 1, p + 1, k);
}

int main() {
  vector<int> ints2;
  rep(i, 1'000'000) {
    int n = rand32() % 10 + 1;
    int k = rand32() % (n + 1);
    ints.clear();
    ints2.clear();
    dfs(0, n - 1, 0, k);
    k_subset(n, k, [&](int x) { ints2.push_back(x); });
    sort(all(ints));
    sort(all(ints2));
    assert(ints == ints2);
  }

  out("Hello World");
}
