#pragma once

#include "bbst/iterator.hpp"
#include "func/no_op.hpp"
#include "util/pool.hpp"
#include "util/rand.hpp"

template <class T, class Comp = less<T>, class Update = no_op,
          class Propagate = no_op, class Alloc = pool<>>
class implicit_treap {
  class node;
  class node_base;
  using link = node_base *;

  class node_base {
   public:
    link l = nullptr, r = nullptr, par = nullptr;
    int cnt = 1;
    uint32_t key = rand32();
    T &val() { return ((node *)this)->val; }
    const T &val() const { return ((const node *)this)->val; }
  };
  class node : public node_base, public Alloc::template alloc<node> {
   public:
    T val;
    node(T val) : val(move(val)) {}
  };

 private:
 public:
  struct iterator : bidirectional_iterator_impl<iterator, node_base, T, false> {
    using base_type =
        bidirectional_iterator_impl<iterator, node_base, T, false>;
    using base_type::base_type;
    T &operator*() const { return base_type::ptr->val(); }
    T *operator->() const { return &**this; }
  };
  struct const_iterator
      : bidirectional_iterator_impl<const_iterator, node_base, T, true> {
    using base_type =
        bidirectional_iterator_impl<const_iterator, node_base, T, true>;
    using base_type::base_type;
    const T &operator*() const { return base_type::ptr->val(); }
    const T *operator->() const { return &**this; }
  };

 public:
  implicit_treap(Update upd = Update(), Propagate prop = Propagate())
      : upd(upd), prop(prop) {}

  implicit_treap(const implicit_treap &rhs) : upd(rhs.upd), prop(rhs.prop) {
    set_l(&head, deep_copy(rhs.head.l));
  }
  implicit_treap(implicit_treap &&rhs)
      : upd(move(rhs.upd)), prop(move(rhs.prop)) {
    set_l(&head, rhs.head.l);
    rhs.head.l = nullptr;
  }
  implicit_treap &operator=(const implicit_treap &rhs) {
    set_l(&head, deep_copy(rhs.head.l));
    return *this;
  }
  implicit_treap &operator=(implicit_treap &&rhs) {
    set_l(&head, rhs.head.l), rhs.head.l = nullptr;
    return *this;
  }

  const_iterator cbegin() const {
    auto ptr = &head;
    while (ptr->l) ptr = ptr->l;
    return const_iterator(ptr);
  }
  const_iterator begin() const { return cbegin(); }
  iterator begin() {
    auto ptr = &head;
    while (ptr->l) ptr = ptr->l;
    return iterator(ptr);
  }
  const_iterator cend() const { return const_iterator(&head); }
  const_iterator end() const { return cend(); }
  iterator end() { return iterator(&head); }
  const_iterator croot() const {
    return const_iterator(head.l ? head.l : &head);
  }
  const_iterator root() const { return croot(); }
  iterator root() { return iterator(head.l ? head.l : &head); }
  const_iterator find(int k) const { return const_iterator(find(head.l, k)); }
  // iterator find(int k) { return iterator(find(head.l, k)); }

  template <class F>
  void apply_on(int i, int j, F f) {
    auto [lm, r] = split(j);
    auto [l, m] = lm.split(i);
    f(m.root());
    *this = move(l.append(m).append(r));
  }

  int size() const { return count(head.l); }
  implicit_treap &append(implicit_treap &rhs) {
    set_l(&head, merge(head.l, rhs.head.l));
    rhs.head.l = nullptr;
    return *this;
  }
  pair<implicit_treap, implicit_treap> split(int k) {
    auto [l, r] = split(head.l, k);
    implicit_treap left(l, upd, prop);
    set_l(&head, r);
    return pair(move(left), move(*this));
  }
  implicit_treap &insert(int k, T v) {
    auto [l, r] = split(k);
    implicit_treap m((link) new node(move(v)), upd, prop);
    set_l(&head, l.append(m).append(r).head.l);
    return *this;
  }
  implicit_treap &erase(const_iterator it) {
    if (it.ptr == it.ptr->par->l)
      set_l(it.ptr->par, merge(it.ptr->l, it.ptr->r)), update(*it.ptr->par);
    else
      set_r(it.ptr->par, merge(it.ptr->l, it.ptr->r)), update(*it.ptr->par);
    return *this;
  }

 private:
  implicit_treap(link root, Update upd, Propagate prop) : upd(upd), prop(prop) {
    set_l(&head, root);
  }

  node_base head;
  Update upd;
  Propagate prop;
  int count(link p) const { return p ? p->cnt : 0; }
  void update(node_base &n) const { update((node &)n); }
  void update(node &n) const {
    n.cnt = 1 + count(n.l) + count(n.r);
    upd(n);
  }
  void propagate(node_base &n) const { propagate((node &)n); }
  void propagate(node &n) const { prop(n); }
  void set_l(link par, link p) const {
    par->l = p;
    if (p) p->par = par;
  }
  void set_r(link par, link p) const {
    par->r = p;
    if (p) p->par = par;
  }
  link merge(link l, link r) const {
    if (!l) return r;
    if (!r) return l;
    if (l->key > r->key) {
      return propagate(*l), set_r(l, merge(l->r, r)), update(*l), l;
    } else {
      return propagate(*r), set_l(r, merge(l, r->l)), update(*r), r;
    }
  }
  pair<link, link> split(link p, int k) const {
    if (!p) {
      assert(k == 0);
      return pair(nullptr, nullptr);
    }
    propagate(*p);
    if (count(p->l) < k) {
      auto [l, r] = split(p->r, k - count(p->l) - 1);
      set_r(p, l), update(*p);
      return pair(p, r);
    } else {
      auto [l, r] = split(p->l, k);
      set_l(p, r), update(*p);
      return pair(l, p);
    }
  }
  link find(link p, int k) const {
    return count(p->l) == k  ? p
           : count(p->l) < k ? find(p->r, k - count(p->l) - 1)
                             : find(p->l, k);
  }
  link deep_copy(link p) const {
    if (!p) return nullptr;
    link q = (link) new node(*(node *)p);
    set_l(q, deep_copy(p->l));
    set_r(q, deep_copy(p->r));
    return q;
  }
};
