// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2286

#include "nt/totient.hpp"
#include "iter/cumsum.hpp"

vector<int> phi = totient(1000000);
vector<ll> sum = cumsuml(all(phi), 0LL);

void solve() {
  int n; scanf("%d", &n);
  printf("%lld\n", sum[n + 1] + 1);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) solve();
}
