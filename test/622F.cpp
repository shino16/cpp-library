#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include "atcoder/modint"
#include "math/interpolate_val.hpp"
using mint = atcoder::modint1000000007;

mint a[1000015];
mint solve(int n, int k) {
  a[0] = 0;
  rep(i, k + 5) a[i + 1] = a[i] + mint(i + 1).pow(k);
  mint ans = interpolate_consecutive(a, a + k + 5, mint(n));
  return ans;
}

int main() {
  assert(solve(203702132, 355473) == 229710810);
  assert(solve(1000000000, 999935) == 729344740);

  printf("Hello World\n");
}
