#pragma once
#include "prelude.hpp"
#include "bit/clz.hpp"

template <class T>
__attribute__((pure)) int ilog2(T x) { assert(x != 0); return sizeof(T) * 8 - 1 - clz(x); }

template <class T>
__attribute__((pure)) int ilog2_ceil(T x) { return x == 0 || x == 1 ? 0 : ilog2(x - 1) + 1; }

template <class T, enable_if_t<is_signed_v<T>>* = nullptr>
__attribute__((pure)) T bit_floor(T x) { return T(1) << ilog2(x); }

template <class T, enable_if_t<is_signed_v<T>>* = nullptr>
__attribute__((pure)) T bit_ceil(T x) { return T(1) << ilog2_ceil(x); }
