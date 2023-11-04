#pragma once
#include "ds/hash_map.hpp"
#include "prelude.hpp"

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
  const char *p;
  leq_lt_base(const char *p) : p(p) {}

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

template <class X, class... Xs>
struct land {
  tuple<X, Xs...> xs;
  land(X x, Xs... xs_) : xs(move(x), move(xs_)...) {}

  static_assert((is_same_v<typename X::alphabet, typename Xs::alphabet> &&
                 ... && true));
  using alphabet = typename X::alphabet;
  using state = tuple<typename X::state, typename Xs::state...>;
  state init() const { return init(make_index_sequence<1 + sizeof...(Xs)>{}); }
  template <size_t... Is>
  state init(index_sequence<Is...>) const {
    return tuple(get<Is>(xs).init()...);
  }
  state next(state s, alphabet a, int i) const {
    return next(s, a, i, make_index_sequence<1 + sizeof...(Xs)>{});
  }
  template <size_t... Is>
  state next(state s, alphabet a, int i, index_sequence<Is...>) const {
    return tuple(get<Is>(xs).next(get<Is>(s), a, i)...);
  }
  bool accept(state s) const {
    return accept(s, make_index_sequence<1 + sizeof...(Xs)>{});
  }
  template <size_t... Is>
  bool accept(state s, index_sequence<Is...>) const {
    return (get<Is>(xs).accept(get<Is>(s)) && ... && true);
  }
  bool successful(state s) const {
    return successful(s, make_index_sequence<1 + sizeof...(Xs)>{});
  }
  template <size_t... Is>
  bool successful(state s, index_sequence<Is...>) const {
    return (get<Is>(xs).successful(get<Is>(s)) && ... && true);
  }
  bool unsuccessful(state s) const {
    return unsuccessful(s, make_index_sequence<1 + sizeof...(Xs)>{});
  }
  template <size_t... Is>
  bool unsuccessful(state s, index_sequence<Is...>) const {
    return (get<Is>(xs).unsuccessful(get<Is>(s)) || ... || false);
  }
};

const string digits = "0123456789";

template <class T, class X, class Iter = string::const_iterator>
T count(const X &dfa, int n, Iter alphabets_f = begin(digits),
        Iter alphabets_l = end(digits)) {
  hash_map<typename X::state, T> prv, nxt;
  // map<typename X::state, T> prv, nxt;
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
  for (auto [s, k] : nxt)
    if (dfa.accept(s)) ans += k;
  return ans;
}

template <class T, class X, class Iter = string::const_iterator>
T sum(const X &dfa, int n, Iter alphabets_f = begin(digits),
      Iter alphabets_l = end(digits)) {
  hash_map<typename X::state, pair<T, T>> prv, nxt;
  nxt[dfa.init()] = pair(T(0), T(1));
  rep(i, n) {
    prv = move(nxt);
    nxt.clear();
    for (auto [s, k] : prv) {
      rep2(p, alphabets_f, alphabets_l) {
        auto s2 = dfa.next(s, *p, i);
        if (!dfa.unsuccessful(s2)) {
          nxt[s2].first += k.first * 10 + (*p - '0') * k.second;
          nxt[s2].second += k.second;
        }
      }
    }
  }
  T ans(0);
  for (auto [s, k] : nxt)
    if (dfa.accept(s)) ans += k.first;
  return ans;
}

}  // namespace dfa
