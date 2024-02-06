#pragma once

#include "nt/primes.hpp"
#include "util/rand.hpp"

int random_prime(int l, int r) {
  while (true) {
    int x = rand32() % (r-l) + l;
    if (is_prime(x)) return x;
  }
}
