#pragma once
#include "prelude.hpp"

namespace io_details {

constexpr int SZ = 1 << 26;
char in[SZ], out[SZ], *s, *t;

struct Pre {
  char num[40000];
  constexpr Pre() : num() {
    for (int i = 0; i < 10000; i++) {
      for (int n = i, j = 4; j--;) num[i * 4 + j] = n % 10 + '0', n /= 10;
    }
  }
} constexpr pre;

void read(char& x) {
  while (*s <= ' ') s++;
  x = *s++;
}
void read(char *str) {
  while (*s <= ' ') s++;
  char *s0 = s; while (*s > ' ') s++;
  memcpy(str, s0, s - s0); str[s - s0] = 0;
}
template <class T> enable_if_t<is_integral_v<T>, void> read(T& x) {
  bool neg = false; while (*s <= ' ') s++;
  if constexpr (is_signed_v<T>) neg = *s == '-' ? s++, true : false;
  x = 0; while (*s > ' ') x = x * 10 + (*s++ & 0x0F);
  if constexpr (is_signed_v<T>) { if (neg) x = -x; }
}
template <class T> auto read(T& v) -> decltype(v.val(), void()) { uint x; read(x); v = x; }
template <class T, class T2, class... Rest>
void read(T& x, T2& y, Rest& ... rest) { read(x); read(y, rest...); }
void write(char x) { *t++ = x; }
template <class T> enable_if_t<is_integral_v<T>, void> write(T x) {
  if (!x) { *t++ = '0'; return; }
  if constexpr (is_signed_v<T>) { if (x < 0) *t++ = '-', x = -x; }
  int i = 12; static char buf[16];
  while (x >= 10000) {
    memcpy(buf + i, pre.num + (x % 10000) * 4, 4); x /= 10000; i -= 4;
  }
  if (x < 100) {
    if (x < 10) *t++ = '0' + x;
    else {
      uint32_t q = (uint32_t(x) * 205) >> 11, r = uint32_t(x) - q * 10;
      *t++ = '0' + q, *t++ = '0' + r;
    }
  } else {
    if (x < 1000) memcpy(t, pre.num + (x << 2) + 1, 3), t += 3;
    else memcpy(t, pre.num + (x << 2), 4), t += 4;
  }
  memcpy(t, buf + i + 4, 12 - i); t += 12 - i;
}
template <class T> auto write(T x) -> decltype(x.val(), void()) { write(x.val()); }
void write(const string& str) { memcpy(t, str.c_str(), str.size()), t += str.size(); }
void write(const vector<char>& str) { memcpy(t, &*str.begin(), str.size()), t += str.size(); }
void write(const char* str) { int len = strlen(str); memcpy(t, str, len), t += len; }
template <class T> void prtln(T x) { write(x); write('\n'); }
template <class T, class... Rest>
void prtln(T x, Rest... rest) { write(x), write(' '), prtln(rest...); }
template <class T, enable_if_t<!is_same_v<T, char>>* = nullptr>
void prtln(const vector<T>& v, char sep = ' ') {
  for (auto&& e : v) write(e), write(sep);
  *(t - 1) = '\n';
}
template <class T>
void prtln(T* first, T* last, char sep = ' ') {
  while (first != last) write(*first++), write(sep);
  *(t - 1) = '\n';
}

class IO {
 public:
  IO() { s = in, t = out, in[fread(in, 1, sizeof(in), stdin)] = 0; }
  ~IO() { fwrite(out, 1, t - out, stdout); }
} io_dummy;

}  // namespace io_details

using io_details::prtln;
using io_details::read;
using io_details::write;
