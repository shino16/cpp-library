// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A

#include "arith/sqrt.hpp"
#include "arith/sat.hpp"
#include "io.hpp"
#include "util/rand.hpp"

template <class T>
void test(T in) {
  T floor = floor_sqrt(in);
  T ceil = ceil_sqrt(in);
  assert(floor * floor <= in);
  assert(sat_mul(ceil, ceil) >= in);
}

int main() {
  rep(i, 1'000'000) {
    test(rand32());
    test(rand64());
    test(LLONG_MAX - rand32());
  }

  out("Hello World");
}
