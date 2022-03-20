#pragma once
#include "prelude.hpp"
#include "bit/clz.hpp"

template <class T>
int ilog2(T x) { assert(x != 0); return sizeof(T) * 8 - 1 - clz(x); }

template <class T>
int ilog2_ceil(T x) { return x == 0 || x == 1 ? 1 : ilog2(x - 1) + 1; }

template <class T>
T bit_floor(T x) { return T(1) << ilog2(x); }

template <class T>
T bit_ceil(T x) { return T(1) << ilog2_ceil(x); }
