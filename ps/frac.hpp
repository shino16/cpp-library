#pragma once
#include "ps/fps.hpp"

template <class T>
class fraction {
 public:
  using fps = formal_power_series<T>;
  fps numer, denom;

  fraction() : numer(fps::zero()), denom(fps::one()) { }
  fraction(fps numer) : numer(numer), denom(fps::one()) { }
  fraction(fps numer, fps denom) : numer(numer), denom(denom) { }

  T eval(T x) const { return numer.eval(x) / denom.eval(x); }
  fraction add(fraction rhs) && {
    numer = move(numer).conv(rhs.denom).add(move(rhs.numer).conv(denom));
    denom = move(denom).conv(move(rhs.denom));
    return move(*this);
  }
  fraction add(fraction rhs) const& { return fraction(*this).add(move(rhs)); }
  fraction sub(fraction rhs) && {
    numer = move(numer).conv(rhs.denom).sub(move(rhs.numer).conv(denom));
    denom = move(denom).conv(move(rhs.denom));
    return move(*this);
  }
  fraction sub(fraction rhs) const& { return fraction(*this).sub(move(rhs)); }
  fraction mul(fraction rhs) && {
    numer = move(numer).conv(move(rhs.numer));
    denom = move(denom).conv(move(rhs.denom));
    return move(*this);
  }
  fraction mul(fraction rhs) const& { return fraction(*this).mul(move(rhs)); }
  fraction div(fraction rhs) && {
    numer = move(numer).conv(move(rhs.denom));
    denom = move(denom).conv(move(rhs.numer));
    return move(*this);
  }
  fraction div(fraction rhs) const& { return fraction(*this).div(move(rhs)); }
  fraction diff() && {
    fps pd = numer.diff(), qd = denom.diff();
    numer = move(pd).conv(denom).sub(move(numer).conv(move(qd)));
    denom = move(denom).square();
    return move(*this);
  }
  fraction diff() const& { return fraction(*this).diff(); }
};
