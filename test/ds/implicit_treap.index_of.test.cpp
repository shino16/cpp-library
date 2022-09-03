#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2890"

#include "bbst/implicit_treap.hpp"

int main() {
  int n, q;
  scanf("%d%d", &n, &q);

  auto prop = [&](auto &n, auto &v) {
    if (!v.second) return;
    swap(n.l, n.r);
    if (n.l) n.l->val().second ^= true;
    if (n.r) n.r->val().second ^= true;
    v.second = false;
  };
  implicit_treap<pair<int, bool>, no_op, decltype(prop)> tree(no_op{}, prop);
  vector<decltype(tree.begin())> its(n+1);

  rep(i, n) {
    int a; scanf("%d", &a);
    its[a] = tree.insert(i, {a, false});
  }
  bool flip = q % 2;
  while (q--) {
    int x; scanf("%d", &x);
    int k = tree.index_of(its[x]);
    tree.apply_on(0, k, [](auto &v) { v.second ^= true; });
    tree.apply_on(k + 1, n, [](auto &v) { v.second ^= true; });
  }
  if (flip) tree.root().second ^= true;
  tree.propagate_all();
  decltype(tree)::const_iterator it = tree.begin();
  printf("%d", it++->first);
  while (it != tree.end()) printf(" %d", it++->first);
  printf("\n");
}
