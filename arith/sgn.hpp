#pragma once
#include "prelude.hpp"

template <class T>
T sgn(T x) { return (x > 0) - (x < 0); }
