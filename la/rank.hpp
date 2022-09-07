#pragma once
#include "la/row_reduce.hpp"

// Row-reduces a
template <class T>
int rank(vector<vector<T>>& a) {
  return row_unreduced(a).second;
}
