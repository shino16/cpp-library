#pragma once
#include "prelude.hpp"
#include <ext/pb_ds/assoc_container.hpp>

template <class T, class Hash = hash<T>>
using hash_set = __gnu_pbds::gp_hash_table<T, __gnu_pbds::null_type, Hash>;
