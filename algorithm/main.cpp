#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;

using ll = int64_t;
using mint = modint998244353;

#define fastio()                      \
  do {                                \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
  } while (0)

#define rep(i, n) for (ll i = 0; i < (n); i++)
#define rep2(i, b, e) for (ll i = (b); i < (e); i++)

#ifdef ATCODER
#define debug(x) \
  do {           \
  } while (0)
#else
#define debug(x)                                   \
  do {                                             \
    cerr << #x << ": " << format("{}", x) << endl; \
  } while (0)
#endif

template <class T>
bool chmin(T& a, T b) { return a > b ? (a = b, true) : false; }
template <class T>
bool chmax(T& a, T b) { return a < b ? (a = b, true) : false; }

template <class T>
vector<vector<T>> make2d(ll h, ll w, T v) { return vector<vector<T>>(h, vector<T>(w, v)); }

// f(x) = true となる最大の x を求める
ll binary_search(
    function<bool(ll)> f,
    ll l,
    ll r) {
  while (r - l > 1) {
    ll const mid = l + (r - l) / 2;
    if (f(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }

  return l;
}

int main(void) {
  fastio();
  ll N, K;
  cin >> N >> K;

  vector<ll> A(N);
  rep(i, N) {
    cin >> A[i];
  }

  return 0;
}
