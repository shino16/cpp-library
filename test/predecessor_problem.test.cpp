#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"

#include "ds/w_ary_tree.hpp"

int main() {
  w_ary_tree<10000001> S;

  int n, q; scanf("%d%d", &n, &q);
  static char s[10000001]; scanf("%s", s);
  rep(i, n) if (s[i] == '1') S.insert(i);
  while (q--) {
    int c, k; scanf("%d%d", &c, &k);
    if (c == 0) S.insert(k);
    else if (c == 1) S.erase(k);
    else if (c == 2) printf("%d\n", S.contains(k));
    else if (c == 3) printf("%ld\n", S.succ(k));
    else printf("%ld\n", S.pred(k+1));
  }
}
