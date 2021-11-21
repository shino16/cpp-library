#pragma once
#include "prelude.hpp"

template <class X = int, class Y = ll>
class slope_trick {
 public:
  slope_trick() { L.push(Min), R.push(Max); }
  Y min() { return min_f; }
  // f(x) <- f(x) + s
  void add(Y s) { min_f += s; }
  // add max(0, x-a)
  void add_inc(X a = Min) {
    X l0 = L.top() + add_L;
    L.push(a - add_L), R.push(L.top() + add_L - add_R), L.pop();
    min_f += max(0, l0 - a);
  }
  // add max(0, a-x)
  void add_dec(X a = Max) {
    X r0 = R.top() + add_R;
    R.push(a - add_R), L.push(R.top() + add_R - add_L), R.pop();
    min_f += max(0, a - r0);
  }
  // add |x-a|
  void add_abs(X a) { add_inc(a), add_dec(a); }
  void min_left() { inner(R).clear(); }
  void min_right() { inner(L).clear(); }
  // f(x) <- min_{d in [l, r]} f(x+d)
  void sliding_min(X l, X r) { add_L -= r, add_R -= l; }
  // f(x) <- f(x-d)
  void slide(X d) { add_L += d, add_R += d; }
  // O(n)
  Y evaluate_at(X x) {
    Y y = min_f;
    for (auto l : inner(L)) y += max(0, (l + add_L) - x);
    for (auto r : inner(R)) y += max(0, x - (r + add_R));
    return y;
  }

 private:
  priority_queue<X> L;
  priority_queue<X, vector<X>, greater<X>> R;
  Y min_f = 0;
  X add_L = 0, add_R = 0;

  static constexpr X Min = numeric_limits<X>::min() / 2;
  static constexpr X Max = numeric_limits<X>::max() / 2;
  template <class T, class S, class C>
  S& inner(priority_queue<T, S, C>& q) {
    struct get_t : priority_queue<T, S, C> {
      static S& get(priority_queue<T, S, C>& q) { return q.*&get_t::c; }
    };
    return get_t::get(q);
  }
};