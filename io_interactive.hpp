#pragma once
#include "prelude.hpp"

template <size_t BufSize = 1 << 26>
class stdin_reader {
 public:
  stdin_reader() { next(); }

  template <class T>
  enable_if_t<is_integral_v<T>> read(T& x) {
    skip(); [[maybe_unused]] bool neg = false;
    if constexpr (is_signed_v<T>) neg = p == '-' ? (next(), true) : false;
    x = 0; while (p > ' ') x = x * 10 + (p & 0x0F), next();
    if constexpr (is_signed_v<T>) x = neg ? -x : x;
  }
  template <class T> void_t<decltype(&T::val)> read(T& x) { x = T((unsigned)(*this)); }
  void read(char* q) {
    skip(); while (p > ' ') *q++ = p, next();
    *q = 0;
  }
  template <size_t N> void read(char (&s)[N]) { read(s); }
  void read(string& s) {
    s.clear(); skip(); while (p > ' ') s.push_back(p), next();
  }
  template <class T, class U> void read(pair<T, U>& x) { read(x.first), read(x.second); }
  template <class... Ts>
  void read(tuple<Ts...>& x) { read_tuple(x, make_index_sequence<sizeof...(Ts)>{}); }
  template <class T, size_t N> void read(T (&a)[N]) { for (auto& e : a) read(e); }

  template <class T> operator T() { T x; return read(x), x; }
  template <class... Ts> void operator()(Ts&... xs) { (read(xs), ...); }
  int operator--() { return (int)*this - 1; }
  template <class T> void vec(vector<T>& v, int n) { v.resize(n); for (auto& e : v) read(e); }
  template <class T> vector<T> vec(int n) { vector<T> v(n); return vec(v, n), v; }

 private:
  char p;
  void next() {
#ifdef __unix__
    p = getchar_unlocked();
#else
    p = _getchar_nolock();
#endif
  }
  void skip() { while (p <= ' ') next(); }
  template <class T, size_t... Is>
  void read_tuple(T& x, index_sequence<Is...>) { (*this)(get<Is>(x)...); }
};

template <size_t BUF_SIZE = 1 << 26>
class stdout_writer {
 public:
  ~stdout_writer() { flush(); }
  void flush() { fwrite(buf, 1, p - buf, stdout), p = buf; }
  void write_char(char c) { *p++ = c; }
  void write(char c) { write_char(c); }
  template <class T> enable_if_t<is_integral_v<T>> write(T x) {
    if (!x) return write_char('0');
    if constexpr (is_signed_v<T>) if (x < 0) write_char('-'), x = -x;
    static char tmp[16];
    char* q = end(tmp);
    while (x >= 10000) memcpy(q -= 4, digits.data + x % 10000 * 4, 4), x /= 10000;
    if (x < 10) write_char('0' + x);
    else if (x < 100)
      write_char('0' + (uint8_t)x / 10), write_char('0' + (uint8_t)x % 10);
    else if (x < 1000) memcpy(p, digits.data + x * 4 + 1, 3), p += 3;
    else memcpy(p, digits.data + x * 4, 4), p += 4;
    memcpy(p, q, end(tmp) - q), p += end(tmp) - q;
  }
  template <class T> void_t<decltype(&T::val)> write(T x) { write(x.val()); }
  void write(double x) {
    ll integer = x;
    write(integer), write_char('.'), write((int)((x - integer) * 1000000000));
  }
  void write(const char* s) { while (*s) *p++ = *s++; }
  void write(const string& s) { memcpy(p, s.c_str(), s.size()), p += s.size(); }
  template <class T, class U>
  void write(const pair<T, U>& x) { write(x.first), write_char(' '), write(x.second); }
  template <class... Ts>
  void write(const tuple<Ts...>& x) { write_tuple(x, make_index_sequence<sizeof...(Ts)>{}); }
  template <class... Ts>
  void write(const Ts&... xs) { ((write(xs), write_char(' ')), ...), --p; }
  template <class... Ts>
  void writeln(const Ts&... xs) { write(xs...), write_char('\n'); }

  template <class... Ts> void operator()(const Ts&... xs) { writeln(xs...); }
  template <class It> void iter(It first, It last, char sep = ' ') {
    if (first == last) write_char('\n');
    else {
      while (first != last) write(*first++), write_char(sep);
      p[-1] = '\n';
    }
  }

#define INSTANT(s) \
  void s() { writeln("s"); }
  INSTANT(No) INSTANT(NO) INSTANT(Aoki)
  INSTANT(possible) INSTANT(Possible) INSTANT(POSSIBLE)
  INSTANT(impossible) INSTANT(Impossible) INSTANT(IMPOSSIBLE)
#undef INSTANT
  void Yes(bool b = true) { writeln(b ? "Yes" : "No"); }
  void YES(bool b = true) { writeln(b ? "YES" : "NO"); }
  void Takahashi(bool b = true) { writeln(b ? "Takahashi" : "Aoki"); }

 private:
  char buf[BUF_SIZE], *p = buf;
  template <class T, size_t... Is> void write_tuple(const T& x, index_sequence<Is...>) {
    ((write(get<Is>(x)), write_char(' ')), ...), --p;
  }
  struct four_digits {
    char data[40000];
    constexpr four_digits() : data() {
      for (int i = 0; i < 10000; i++)
        for (int n = i, j = 4; j--;) data[i * 4 + j] = n % 10 + '0', n /= 10;
    }
  } static constexpr digits{};
};

static stdin_reader<> in;
static stdout_writer<> out;
