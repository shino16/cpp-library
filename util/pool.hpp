#pragma once
#include "prelude.hpp"

template <size_t N = 1 << 20>
struct pool {
  template <class T>
  struct alloc {
    static inline T* ptr =
        (T*)new (align_val_t(alignof(T))) unsigned char[sizeof(T) * N];
    static void* operator new(size_t) noexcept { return ptr++; }
    static void operator delete(void* p) { destroy_at((T*)p); }

   private:
    alloc() = default;
    friend T;
  };
};

struct no_pool {
  template <class T>
  struct alloc {};
};
