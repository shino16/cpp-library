#pragma once

#include "bbst/iterator.hpp"
#include "bit/ilog2.hpp"
#include "func/no_op.hpp"
#include "util/pool.hpp"
#include "util/rand.hpp"

template <
    class T, class Update = no_op, class Propagate = no_op,
    class Alloc = pool<>>
class implicit_treap {
  class node;
  class node_base;
  using link = node_base*;
  using clink = const node_base*;

  class node_base {
   public:
    link l = nullptr, r = nullptr, par = nullptr;
    int cnt = 1;
    uint32_t key = rand32();
    T& val() { return ((node*)this)->val; }
    const T& val() const { return ((const node*)this)->val; }
  };
  class node : public node_base, public Alloc::template alloc<node> {
   public:
    T val;
    node(T val) : val(move(val)) { }
  };

 private:
 public:
  class iterator
      : public bidirectional_iterator_impl<iterator, node_base, T, false> {
    using base_type =
        bidirectional_iterator_impl<iterator, node_base, T, false>;

   public:
    using base_type::base_type;
    T& operator*() const { return base_type::ptr->val(); }
    T* operator->() const { return &**this; }
  };

  class const_iterator
      : public bidirectional_iterator_impl<const_iterator, node_base, T, true> {
    using base_type =
        bidirectional_iterator_impl<const_iterator, node_base, T, true>;

   public:
    using base_type::base_type;
    const_iterator(iterator it) : base_type(it.ptr) { }
    const T& operator*() const { return base_type::ptr->val(); }
    const T* operator->() const { return &**this; }
  };

 public:
  implicit_treap(Update upd = Update(), Propagate prop = Propagate())
      : upd(upd), prop(prop) { }
  template <class It>
  implicit_treap(
      It first, It last, Update upd = Update(), Propagate prop = Propagate())
      : upd(upd), prop(prop) {
    vector<link> ps(bit_ceil(distance(first, last)) * 2);
    for (auto it = ps.begin(); first != last; it++, first++)
      *it = (link) new node(*first);
    for (int i = 0; i + 1 < ps.size(); i += 2)
      ps.push_back(merge(ps[i], ps[i + 1]));
    set_l(&head, ps.back());
  }

  implicit_treap(const implicit_treap& rhs) : upd(rhs.upd), prop(rhs.prop) {
    set_l(&head, deep_copy(rhs.head.l));
  }
  implicit_treap(implicit_treap&& rhs) : upd(rhs.upd), prop(rhs.prop) {
    set_l(&head, rhs.head.l);
    rhs.head.l = nullptr;
  }
  implicit_treap& operator=(const implicit_treap& rhs) {
    set_l(&head, deep_copy(rhs.head.l));
    return *this;
  }
  implicit_treap& operator=(implicit_treap&& rhs) {
    set_l(&head, rhs.head.l), rhs.head.l = nullptr;
    return *this;
  }

  const_iterator begin() const {
    auto ptr = &head;
    while (ptr->l) ptr = ptr->l;
    return const_iterator(ptr);
  }
  const_iterator end() const { return const_iterator(&head); }
  const T& root() const { return head.l->val(); }
  T& root() { return head.l->val(); }
  const_iterator find(int k) const { return const_iterator(find(head.l, k)); }

  template <class F>
  void apply_on(int i, int j, F f) {
    if (i == j) return;
    auto [lm, r] = split(j);
    auto [l, m] = lm.split(i);
    f(m.root());
    *this = move(l.join(m).join(r));
  }

  int size() const { return count(head.l); }
  implicit_treap& join(implicit_treap& rhs) {
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
  const_iterator insert(int k, T v) {
    auto p = (link) new node(move(v));
    set_l(&head, insert(head.l, k, p));
    return const_iterator(p);
  }
  void erase(int i) { set_l(&head, erase(head.l, i)); }
  int index_of(const_iterator it) {
    auto p = const_cast<link>(it.ptr);
    propagate(*p);
    int ans = count(p->l);
    for (; p->par != &head; p = p->par) {
      if (p->par->r == p) ans += count(p->par->l) + 1;
      auto l0 = p->par->l;
      propagate(*p->par);
      if (l0 != p->par->l) ans = count(p->par) - ans - 1;
    }
    return ans;
  }
  void propagate_all() { propagate_all(head.l); }

 private:
  implicit_treap(link root, Update upd, Propagate prop) : upd(upd), prop(prop) {
    set_l(&head, root);
  }

  node_base head;
  Update upd;
  Propagate prop;
  int count(link p) const { return p ? p->cnt : 0; }
  void propagate(node_base& n) { prop(n, n.val()); }
  void update(node_base& n) { update((node&)n); }
  void update(node& n) {
    n.cnt = 1 + count(n.l) + count(n.r);
    if (n.l) propagate(*n.l);
    if (n.r) propagate(*n.r);
    upd((node_base&)n, n.val);
  }
  void set_l(link par, link p) {
    par->l = p;
    if (p) p->par = par;
  }
  void set_r(link par, link p) {
    par->r = p;
    if (p) p->par = par;
  }
  link merge(link l, link r) {
    if (!l) return r;
    if (!r) return l;
    if (l->key > r->key) {
      return propagate(*l), set_r(l, merge(l->r, r)), update(*l), l;
    } else {
      return propagate(*r), set_l(r, merge(l, r->l)), update(*r), r;
    }
  }
  pair<link, link> split(link p, int k) {
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
  link insert(link p, int k, link x) {
    if (!p) {
      assert(k == 0);
      return x;
    }
    propagate(*p);
    if (x->key > p->key) {
      auto [l, r] = split(p, k);
      return set_l(x, l), set_r(x, r), update(*x), x;
    } else if (count(p->l) < k) {
      return set_r(p, insert(p->r, k - count(p->l) - 1, x)), update(*p), p;
    } else {
      return set_l(p, insert(p->l, k, x)), update(*p), p;
    }
  }
  link erase(link p, int k) {
    assert(p);
    propagate(*p);
    if (count(p->l) < k) {
      return set_r(p, erase(p->r, k - count(p->l) - 1)), update(*p), p;
    } else if (count(p->l) > k) {
      return set_l(p, erase(p->l, k)), update(*p), p;
    } else {
      return merge(p->l, p->r);
    }
  }
  link find(link p, int k) const {
    return count(p->l) == k  ? p
           : count(p->l) < k ? find(p->r, k - count(p->l) - 1)
                             : find(p->l, k);
  }
  link deep_copy(link p) {
    if (!p) return nullptr;
    link q = (link) new node(*(node*)p);
    set_l(q, deep_copy(p->l));
    set_r(q, deep_copy(p->r));
    return q;
  }
  void propagate_all(link p) {
    if (!p) return;
    propagate(*p);
    propagate_all(p->l), propagate_all(p->r);
  }
};
