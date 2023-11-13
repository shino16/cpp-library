#pragma once
#include "prelude.hpp"

// Uses == for deletion
template <class T, class Comp = less<T>>
class deletable_heap: public priority_queue<T, vector<T>, Comp> {
 public:
  using priority_queue<T, vector<T>, Comp>::priority_queue;
  auto top() { return prepare(), base_t::top(); }
  void pop() { prepare(), base_t::pop(); }
  bool empty() { return prepare(), base_t::empty(); }
  // Assumes x is contained
  void del(T x) { to_del.push(move(x)); }
  auto size() const { return base_t::size() - to_del.size(); }
 private:
  using base_t = priority_queue<T, vector<T>, Comp>;
  base_t to_del;
  void prepare() {
    while (!to_del.empty() && base_t::top() == to_del.top())
      base_t::pop(), to_del.pop();
  }
};
