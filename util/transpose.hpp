#pragma once
#include "prelude.hpp"

template <class Matrix, class Tuple, size_t... Is>
void fill_transpose(Matrix& w, const vector<Tuple>& v, index_sequence<Is...>) {
  ([&] {
    get<Is>(w).reserve(v.size());
    for (auto&& e : v) get<Is>(w).push_back(get<Is>(e));
  }(), ...);
}

template <class Tuple, class T> struct tuple_of_vectors;
template <class Tuple, size_t... Is> struct tuple_of_vectors<Tuple, index_sequence<Is...>> {
  using type = tuple<vector<decay_t<decltype(get<Is>(declval<Tuple>()))>>...>;
};

template <class Tuple>
auto transpose(const vector<Tuple>& v) {
  typename tuple_of_vectors<Tuple, make_index_sequence<tuple_size_v<Tuple>>>::type w;
  fill_transpose(w, v, make_index_sequence<tuple_size_v<Tuple>>{});
  return w;
}
