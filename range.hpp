#pragma once
#include "prelude.hpp"

template <class It>
struct range : pair<It, It> {
  using pair<It, It>::pair;
  It begin() const { return this->first; }
  It end() const { return this->second; }
  It cbegin() const { return begin(); }
  It cend() const { return end(); }
  int size() const { return this->second - this->first; }
};
