#pragma once
#include "prelude.hpp"
#include <ext/pb_ds/assoc_container.hpp>

template <class K, class V, class Hash = hash<K>>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;
