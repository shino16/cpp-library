// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B

#include "str/kmp.hpp"

char T[1000001], P[10001];

int main() {
  scanf("%s%s", T, P);
  int n = strlen(T);
  int m = strlen(P);
  for (int i : occurences(T, T + n, P, P + m)) printf("%d\n", i);
}
