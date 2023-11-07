#pragma once
#include "arith/sat.hpp"
#include "prelude.hpp"

vector<bool> sieve(int upto) {
  vector<bool> prime(upto + 1, true);
  prime[0] = prime[1] = false;
  for (int p = 2; p * p <= upto; p++)
    if (prime[p])
      for (int q = p * p; q <= upto; q += p) prime[q] = false;
  return prime;
}

vector<int> primes(int upto) {
  vector<int> ans;
  vector<bool> sieved = sieve(upto);
  for (int n = 2; n <= upto; n++)
    if (sieved[n]) ans.push_back(n);
  return ans;
}

bool is_prime(int n) {
  if (n == 2) return true;
  if (n % 2 == 0) return false;
  for (int d = 3; sat_mul(d, d) <= n; d += 2)
    if (n % d == 0) return false;
  return true;
}
