#pragma once
#include "prelude.hpp"

#ifdef LOCAL
#define dbg(x)                                                  \
  do {                                                          \
    cerr << __FILE__ << ":" << __LINE__ << ": " << #x << " = "; \
    debug(x);                                                   \
    cerr << endl;                                               \
  } while (false)
#else
#define dbg(x) \
  do {         \
  } while (false)
#endif

template <class T>
auto debug(T x) -> decltype(cerr << x, void()) { cerr << x; }
template <class T>
auto debug(const T &v) -> decltype(debug(v.val()), void()) { debug(v.val()); }
template <class Iter>
void debug_iter(Iter, Iter);
template <class T>
auto debug(const T &v) -> decltype(debug_iter(begin(v), end(v)), void()) {
  debug_iter(begin(v), end(v));
}
template <class T, int N>
void debug(const T (&v)[N]) { debug_iter(v, v + N); }
template <class T, int N>
void debug(const array<T, N> &v) { debug_iter(v.begin(), v.end()); }
template <class Iter>
void debug_iter(Iter first, Iter last) {
  cerr << "[";
  while (first != last) debug(*first++), cerr << ", ";
  cerr << "]";
}
template <class T, size_t... I>
void debug_tuple(const T &v, index_sequence<I...>);
template <class T>
auto debug(const T &v) -> decltype(tuple_size<T>::value, void()) {
  debug_tuple(v, make_index_sequence<tuple_size_v<T>>());
}
template <class T, size_t... I>
void debug_tuple(const T &v, index_sequence<I...>) {
  cerr << "(";
  ((debug(get<I>(v)), cerr << ", "), ...);
  cerr << ")";
}
