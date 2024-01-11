// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0570

#include "dfa/multiple_of.hpp"
#include "mod/modint.hpp"
using mint = atcoder::static_modint<10000>;
#include "io.hpp"

enum zig_state {
  INC,
  DEC,
  ZERO,
  INIT,
  FAIL,
};

struct zig_zag : dfa::dfa_default {
  using state = pair<char, zig_state>;
  state init() const { return state('0', ZERO); }
  state next(state s, char c, int) const {
    switch (s.second) {
      case FAIL:
        return s;
      case ZERO:
        if (c == '0')
          return s;
        else
          return state(c, INIT);
      case INIT:
        return state(c, s.first < c ? INC : s.first > c ? DEC : FAIL);
      case INC:
        return state(c, s.first > c ? DEC : FAIL);
      case DEC:
        return state(c, s.first < c ? INC : FAIL);
    }
    assert(false);
  }
  bool accept(state s) const { return s.second != FAIL; }
  bool unsuccessful(state s) const { return s.second == FAIL; }
};

int main() {
  string A = in, B = in;
  int n = B.size();
  A.insert(0, n - A.size(), '0');
  int M = in;
  auto dfa = dfa::land(zig_zag(), dfa::multiple_of(M), dfa::leq(B.c_str()),
                       dfa::lnot<dfa::lt>(A.c_str()));
  mint ans = dfa::count<mint>(dfa, B.size());
  out(ans.val());
}
