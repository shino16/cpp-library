#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include "nt/convolve.hpp"
#include "nt/totient.hpp"
#include "nt/moebius.hpp"

const int N = 1000000;
int f[N];
moebius mu(N);
auto phi = totient(N);

int main() {
  iota(all(f), 0);
  auto phi2 = convolve(all(f), all(mu));
  rep2(i, 1, phi2.size()) assert(phi[i] == phi2[i]);
  phi2 = convolve_multiplicative(all(f), all(mu));
  rep2(i, 1, phi2.size()) assert(phi[i] == phi2[i]);

  printf("Hello World\n");
}
