#pragma once
#include "prelude.hpp"

template <class Self, class Node, class T, bool Const>
class bidirectional_iterator_impl {
 public:
  using difference_type = ptrdiff_t;
  using value_type = T;
  using pointer = conditional_t<Const, const T *, T *>;
  using reference = conditional_t<Const, const T &, T &>;
  using iterator_category = bidirectional_iterator_tag;

 private:
  using self_type = Self;
  using node_pointer = conditional_t<Const, const Node *, Node *>;

 public:
  bidirectional_iterator_impl(Node *p) : ptr(p) { }
  bidirectional_iterator_impl(const Node *p = nullptr) : ptr(p) {} // ill-formed if !Const
  // reference operator*() const { return ptr->*Val(); }
  // pointer operator->() const { return &**this; }
  bool operator==(self_type rhs) const { return ptr == rhs.ptr; }
  bool operator!=(self_type rhs) const { return ptr != rhs.ptr; }
  self_type &operator++() {
    if (ptr->r) {
      ptr = ptr->r;
      while (ptr->l) ptr = ptr->l;
    } else {
      while (ptr->par->r == ptr) ptr = ptr->par;
      ptr = ptr->par;
    }
    return *(self_type *)this;
  }
  self_type operator++(int) {
    self_type res(ptr);
    ++*this;
    return res;
  }
  self_type &operator--() {
    if (ptr->l) {
      ptr = ptr->l;
      while (ptr->r) ptr = ptr->r;
    } else {
      while (ptr->par->l == ptr) ptr = ptr->par;
      ptr = ptr->par;
    }
    return *(self_type *)this;
  }
  self_type operator--(int) {
    self_type res(ptr);
    --*this;
    return res;
  }

  node_pointer ptr;
};
