#pragma once
#include "prelude.hpp"

class factorizer {
 public:
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
  vector<int> operator()(int n) const {
    vector<int> res;
    while (n != 1) res.push_back(lpf[n]), n /= lpf[n];
    return res;
  }

 private:
  vector<int> lpf, ps;
};
