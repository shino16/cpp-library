#pragma once

#include "prelude.hpp"

vector<ll> divisors(ll n) {
  assert(n > 0);
  vector<ll> small, big;
  for (ll d = 1; d * d <= n; d++) if (n % d == 0)
    small.push_back(d), big.push_back(n / d);
  if (small.back() == big.back()) big.pop_back();
  small.insert(small.end(), big.rbegin(), big.rend());
  return small;
}
