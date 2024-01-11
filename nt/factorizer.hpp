#pragma once
#include "prelude.hpp"

class factorizer {
 public:
  vector<int> lpf, ps;

  factorizer(int upto = 0) : lpf(upto + 1) {
    rep2(p, 2, lpf.size()) {
      if (lpf[p] == 0) lpf[p] = p, ps.push_back(p);
      for (auto q : ps) {
        if (q > lpf[p] || p * q > upto) break;
        lpf[p * q] = q;
      }
    }
  }

  int size() const { return lpf.size(); }
  vector<pair<int, int>> operator()(int n) const {
    vector<pair<int, int>> res;
    for (; n != 1; n /= lpf[n])
      if (!res.empty() && res.back().first == lpf[n]) res.back().second++;
      else res.emplace_back(lpf[n], 1);
    return res;
  }
};
