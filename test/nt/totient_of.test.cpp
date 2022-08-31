#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_D"

#include "nt/totient_of.hpp"

int main() {
  int n; scanf("%d", &n);
  printf("%d\n", totient_of(n));
}
