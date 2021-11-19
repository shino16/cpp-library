#pragma once
#include "prelude.hpp"

vector<bool> sieve(int upto) {
  vector<bool> prime(upto + 1, true);
  prime[0] = prime[1] = false;
  for (int p = 0; p <= upto; p++)
    if (prime[p])
      for (int q = p * 2; q <= upto; q += p) prime[q] = false;
  return prime;
}

vector<int> primes(int upto) {
  vector<int> ans;
  vector<bool> sieved = sieve(upto);
  for (int n = 2; n <= upto; n++)
    if (sieved[n]) ans.push_back(n);
  return ans;
}
