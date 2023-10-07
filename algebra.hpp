#pragma once
#include "prelude.hpp"

#define CONST(val) [=] { return val; }
#define WRAP_FN(func) \
  [](auto&&... args) { return func(forward<decltype(args)>(args)...); }

template <class Unit, class Op>
struct monoid : private Unit, private Op {
  using type = decltype(declval<Unit>()());
  monoid(Unit unit, Op op) : Unit(unit), Op(op) {}
  type unit() const { return Unit::operator()(); }
  type op(type a, type b) const { return Op::operator()(a, b); }
};

template <class Unit, class Op, class Inv>
struct group : monoid<Unit, Op>, private Inv {
  using type = typename monoid<Unit, Op>::type;
  group(Unit unit, Op op, Inv inv) : monoid<Unit, Op>(unit, op), Inv(inv) {}
  type inv(type a) const { return Inv::operator()(a); }
};

template <class T>
struct addition {
  using type = T;
  type unit() const { return 0; }
  type op(type a, type b) const { return a + b; }
  type inv(type a) const { return -a; }
};

template <class T>
struct maximum {
  using type = T;
  type unit() const { return numeric_limits<T>::min(); }
  type op(type a, type b) const { return a > b ? a : b; }
};

template <class T>
struct minimum {
  using type = T;
  type unit() const { return numeric_limits<T>::max(); }
  type op(type a, type b) const { return a > b ? b : a; }
};

template <class T, T nul = -1>
struct assign {
  using type = T;
  type unit() const { return nul; }
  type op(type a, type b) const { return b == nul ? a : b; }
};
