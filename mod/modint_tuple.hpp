#pragma once

#include "mod/modint.hpp"
#include "prelude.hpp"

template <int... Ms>
struct modint_tuple : tuple<atcoder::static_modint<Ms>...> {
 public:
  using tuple<atcoder::static_modint<Ms>...>::tuple;

  template <class T>
  modint_tuple(T v) : tuple<atcoder::static_modint<Ms>...>(((void)Ms, v)...) {}

  static constexpr array<int, sizeof...(Ms)> mod() { return {Ms...}; }
  constexpr array<unsigned, sizeof...(Ms)> val() const {
    return {get<atcoder::static_modint<Ms>>(*this).val()...};
  }
  constexpr modint_tuple pow(ll n) const {
    return {get<atcoder::static_modint<Ms>>(*this).pow(n)...};
  }
  constexpr modint_tuple inv() const {
    return {get<atcoder::static_modint<Ms>>(*this).inv()...};
  }

  constexpr modint_tuple& operator++() {
    (++get<atcoder::static_modint<Ms>>(*this), ...);
    return *this;
  }
  constexpr modint_tuple& operator--() {
    (--get<atcoder::static_modint<Ms>>(*this), ...);
    return *this;
  }
  constexpr modint_tuple operator++(int) {
    auto old = *this;
    (++get<atcoder::static_modint<Ms>>(*this), ...);
    return old;
  }
  constexpr modint_tuple operator--(int) {
    auto old = *this;
    (--get<atcoder::static_modint<Ms>>(*this), ...);
    return old;
  }

  constexpr modint_tuple operator+() const { return *this; }
  constexpr modint_tuple operator-() const { return modint_tuple() - *this; }

#define BIN_OP(op, op_assign)                                           \
  constexpr modint_tuple& operator op_assign(const modint_tuple& rhs) { \
    ((get<atcoder::static_modint<Ms>>(*this)                            \
          op_assign get<atcoder::static_modint<Ms>>(rhs),               \
      void()),                                                          \
     ...);                                                              \
    return *this;                                                       \
  }                                                                     \
  constexpr friend modint_tuple operator op(                            \
      const modint_tuple& lhs, const modint_tuple& rhs) {               \
    return modint_tuple(lhs) op_assign rhs;                             \
  }

  BIN_OP(+, +=) BIN_OP(-, -=) BIN_OP(*, *=) BIN_OP(/, /=)

  friend bool operator<(const modint_tuple& lhs, const modint_tuple& rhs) {
      return lhs.val() < rhs.val();
  }
};
