#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "str/suffix_array.hpp"

char S[500001];

int main() {
  scanf("%s", S);
  int n = strlen(S);
  auto sa = sort_cyclic_shifts(S, S+n+1);
  sa.erase(sa.begin());
  rep(i, n) printf("%d%c", sa[i], " \n"[i==n-1]);
}
