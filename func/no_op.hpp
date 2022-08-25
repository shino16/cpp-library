#pragma once
#include "prelude.hpp"

struct no_op {
  template <class... Ts>
  void operator()(Ts&&...) const {}
};
