// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1508

#include "bbst/implicit_treap.hpp"

struct T {
  int a = -1, mini = -1;
  bool rev = false;
};

int main() {
  auto upd = [](auto &n, auto &v) {
    v.mini = v.a;
    if (n.l) v.mini = min(v.mini, n.l->val().mini);
    if (n.r) v.mini = min(v.mini, n.r->val().mini);
  };
  auto prop = [](auto &n, auto &v) {
    if (!v.rev) return;
    swap(n.l, n.r);
    if (n.l) n.l->val().rev ^= true;
    if (n.r) n.r->val().rev ^= true;
    v.rev = false;
  };

  int n, q;
  scanf("%d%d", &n, &q);
  vector<T> a(n);
  rep(i, n) scanf("%d", &a[i].a), a[i].mini = a[i].a;
  implicit_treap<T, decltype(upd), decltype(prop)> tree(all(a), upd, prop);
  while (q--) {
    int x, l, r; scanf("%d%d%d", &x, &l, &r);
    r++;
    if (x == 0) {
      tree.apply_on(l, r, [](auto &n) { n.rev ^= true; });
      tree.apply_on(l + 1, r, [](auto &n) { n.rev ^= true; });
    } else if (x == 1) {
      int ans;
      tree.apply_on(l, r, [&](auto &n) { ans = n.mini; });
      printf("%d\n", ans);
    } else {
      tree.apply_on(l, l+1, [&](auto &n) { n.mini = n.a = r - 1; });
    }
  }
}
