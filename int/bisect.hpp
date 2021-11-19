#pragma once

template <class T, class F>
T bisect(T l, T r, const F& f) {
  assert(l <= r);
  while (l != r) {
    T m = (l & r) + ((l ^ r) >> 1);
    if (f(m)) l = m + 1;
    else r = m;
  }
  return r;
}
