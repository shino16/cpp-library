#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"


#include "arith/div.hpp"
#include "io.hpp"

int main() {
  int a[] = {7, 7, -7, -7};
  int b[] = {3, -3, 3, -3};
  rep(i, 4) {
    assert(div_floor(a[i], b[i]) == floor(1.0 * a[i] / b[i]));
    assert(div_ceil(a[i], b[i]) == ceil(1.0 * a[i] / b[i]));
    int r = rem(a[i], b[i]);
    assert(0 <= r && r < abs(b[i]));
    assert((a[i] - r) % b[i] == 0);
  }
}
