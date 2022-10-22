#pragma once
#include "prelude.hpp"
#include "ds/hash_map.hpp"

namespace dfa {

struct dfa_default {
  using alphabet = char;
  template <class T>
  bool successful(T &&) const {
    return false;
  }
  template <class T>
  bool unsuccessful(T &&) const {
    return false;
  }
};

struct leq_lt_base {
  char *p;
  leq_lt_base(char *p) : p(p) {}

  using alphabet = char;
  using state = signed char;
  state init() const { return 0; }
  state next(state s, alphabet a, int i) const {
    return s ? s : (a > p[i]) - (a < p[i]);
  }
  bool successful(state s) const { return s == -1; }
  bool unsuccessful(state s) const { return s == 1; }
};

struct leq : leq_lt_base {
  using leq_lt_base::leq_lt_base;
  bool accept(state s) const { return s != 1; }
};

struct lt : leq_lt_base {
  using leq_lt_base::leq_lt_base;
  bool accept(state s) const { return s == -1; }
};

template <class X>
struct lnot : X {
  using X::X;
  bool accept(typename lnot::state s) const { return !X::accept(s); }
  bool successful(typename lnot::state s) const { return X::unsuccessful(s); }
  bool unsuccessful(typename lnot::state s) const { return X::successful(s); }
};

template <class X, class Y>
struct land {
  X x;
  Y y;
  land(X x, Y y) : x(x), y(y) {}

  static_assert(is_same_v<typename X::alphabet, typename Y::alphabet>);
  using alphabet = typename X::alphabet;
  using state = pair<typename X::state, typename Y::state>;
  state init() const { return make_pair(x.init(), y.init()); }
  state next(state s, alphabet a, int i) const {
    return make_pair(x.next(s.first, a, i), y.next(s.second, a, i));
  }
  bool accept(state s) const {
    return x.accept(s.first) && y.accept(s.second);
  }
  bool successful(state s) const {
    return x.successful(s.first) && y.successful(s.second);
  }
  bool unsuccessful(state s) const {
    return x.unsuccessful(s.first) || y.unsuccessful(s.second);
  }
};

const string digits = "0123456789";

template <class T, class X, class Iter = string::const_iterator>
T count(const X &dfa, int n, Iter alphabets_f = begin(digits),
        Iter alphabets_l = end(digits)) {
  hash_map<typename X::state, T> prv, nxt;
  nxt[dfa.init()] = T(1);
  rep(i, n) {
    prv = move(nxt);
    nxt.clear();
    for (auto [s, k] : prv) {
      rep2(p, alphabets_f, alphabets_l) {
        auto s2 = dfa.next(s, *p, i);
        if (!dfa.unsuccessful(s2)) nxt[s2] += k;
      }
    }
  }
  T ans(0);
  for (auto [s, k] : nxt) if (dfa.accept(s)) ans += k;
  return ans;
}

template <class T, class X, class Iter = string::const_iterator>
T sum(const X &dfa, int n, Iter alphabets_f = begin(digits),
        Iter alphabets_l = end(digits)) {
  hash_map<typename X::state, pair<T, T>, simple_hash<typename X::state>> prv, nxt;
  nxt[dfa.init()] = pair(T(0), T(1));
  rep(i, n) {
    prv = move(nxt);
    nxt.clear();
    for (auto [s, k] : prv) {
      rep2(p, alphabets_f, alphabets_l) {
        auto s2 = dfa.next(s, *p, i);
        if (!dfa.unsuccessful(s2)) {
          nxt[s2].first += k.first * 10 + (*p-'0') * k.second;
          nxt[s2].second += k.second;
        }
      }
    }
  }
  T ans(0);
  for (auto [s, k] : nxt) if (dfa.accept(s)) ans += k.first;
  return ans;
}

}  // namespace dfa
