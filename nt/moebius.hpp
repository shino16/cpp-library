#pragma once
#include "prelude.hpp"

class moebius {
 public:
  moebius(int upto = 0) : mu(upto + 1, 1), prime(upto + 1, true) {
    prime[0] = prime[1] = false;
    for (int p = 2; p < size(); p++) if (prime[p]) {
      mu[p] *= -1;
      for (int m = p * 2; m < size(); m += p) mu[m] *= -1, prime[m] = false;
      if (1LL * p * p < size()) {
        for (int m = p * p; m < size(); m += p * p) mu[m] = 0;
      }
    }
  }
  int size() const { return mu.size(); }
  int operator[](int i) const { return mu[i]; }
  int operator()(int i) const { return mu[i]; }
  bool is_prime(int i) const { return prime[i]; }
  auto begin() const { return mu.cbegin(); }
  auto end() const { return mu.cend(); }
 private:
  vector<int> mu;
  vector<bool> prime;
};
