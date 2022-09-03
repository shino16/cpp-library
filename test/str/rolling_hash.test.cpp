#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include "str/rolling_hash.hpp"

char T[1000001], P[10001];

int main() {
  scanf("%s%s", T, P);
  int n = strlen(T);
  int m = strlen(P);
  rolling_hash hash(T, T+n);
  auto hP = hash(P, P+m);
  rep(i, n-m+1) if (hash(i, i+m) == hP) printf("%d\n", i);
}
