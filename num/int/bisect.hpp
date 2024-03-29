#pragma once

template <class I, class F>
I bisect(I l, I r, F p) {
  while (l != r) {
    I m = ((l ^ r) >> 1) + (l & r);
    if (p(m)) l = m + 1;
    else r = m;
  }
  return l;
}
