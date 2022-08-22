#pragma once
#include "prelude.hpp"

vector<int> totient(int upto) {
  vector<int> phi(upto + 1);
  iota(all(phi), 0);
  rep2(p, 2, phi.size()) {
    if (phi[p] == p) {
      for (int m = p; m < phi.size(); m += p)
        phi[m] -= phi[m] / p;
    }
  }
  return phi;
}
