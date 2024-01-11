// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A


#include "arith/sgn.hpp"
#include "io.hpp"

template <class T>
void test_type(T in, T out) {
  assert(sgn(in) == out);
}

int main() {
  test_type(-2, -1);
  test_type(0, 0);
  test_type(3, 1);
  test_type(-2LL, -1LL);
  test_type(0LL, 0LL);
  test_type(3LL, 1LL);

  out("Hello World");
}
