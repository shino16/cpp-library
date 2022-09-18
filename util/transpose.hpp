#pragma once
#include "prelude.hpp"

template <class T, size_t... Is>
auto transpose_impl(const vector<T>& v, index_sequence<Is...>) {
  tuple<vector<decay_t<tuple_element_t<Is, T>>>...> w;
  (get<Is>(w).reserve(v.size()), ...);
  for (const auto& row : v)
    (get<Is>(w).push_back(get<Is>(row)), ...);
  return w;
}

template <class T>
auto transpose(const vector<T>& v) {
  return transpose_impl(v, make_index_sequence<tuple_size_v<T>>{});
}
