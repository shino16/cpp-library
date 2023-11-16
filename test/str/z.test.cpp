#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include "str/z.hpp"

vector<int> occurences(char* s_first, char* s_last, char* p_first,
                       char* p_last, char sep = '$') {
  int n = s_last - s_first, m = p_last - p_first;
  vector<char> s(n + m + 1);
  copy(p_first, p_last, s.begin());
  s[m] = sep;
  copy(s_first, s_last, s.begin() + m + 1);
  auto z = z_algo(all(s));
  vector<int> res;
  res.reserve(max(0, n - m + 1));
  rep(i, n - m + 1) if (z[m + 1 + i] == m) res.push_back(i);
  return res;
}

char T[1000001], P[10001];

int main() {
  scanf("%s%s", T, P);
  int n = strlen(T);
  int m = strlen(P);
  for (int i : occurences(T, T + n, P, P + m)) printf("%d\n", i);
}
