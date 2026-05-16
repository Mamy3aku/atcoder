// Visual Studio, gcc のどちらでも動くように、bits/stdc++.h をインクルードせず、必要なヘッダを個別にインクルードする
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <random>
#include <ranges>
#include <string>
#include <vector>

using namespace std;
using ll = int64_t;

// デバッグ出力には必ずこのマクロを利用する
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

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define rep2(i, a, b) for (int i = (a); i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

struct Timer {
  using Clock = std::chrono::steady_clock;
  Clock::time_point startTime_;

  static constexpr int64_t TIME_LIMIT_MS = 1990 * 1;

  Timer() : startTime_(Clock::now()) {}

  int64_t elapsedMilliSeconds() const {
    return chrono::duration_cast<chrono::milliseconds>(Clock::now() - startTime_).count();
  }

  int64_t elapsedMicroSeconds() const {
    return chrono::duration_cast<chrono::microseconds>(Clock::now() - startTime_).count();
  }

  bool isTimeLimitExceeded() const {
    return elapsedMilliSeconds() >= TIME_LIMIT_MS;
  }

} gTimer;

// 競技プログラミング用の固定サイズ配列コンテナ
// 範囲外参照などは一切考慮しない
namespace FixedSizeContainers {
template <typename T, size_t N>
struct FixedSizeArray {
  using RawContainer = array<T, N>;
  RawContainer data_;

  size_t size_ = 0;

  FixedSizeArray() : size_(0) {}

  size_t size() const {
    return size_;
  }

  bool empty() const {
    return size_ == 0;
  }

  void clear() {
    size_ = 0;
  }

  void push_back(const T& value) {
    assert(size_ < N);
    data_[size_++] = value;
  }

  void push_back(T&& value) {
    assert(size_ < N);
    data_[size_++] = move(value);
  }

  T& back() {
    return data_[size_ - 1];
  }

  const T& back() const {
    return data_[size_ - 1];
  }

  void pop_back() {
    --size_;
  }

  T& front() {
    return data_[0];
  }

  const T& front() const {
    return data_[0];
  }

  T& operator[](size_t index) {
    return data_[index];
  }

  const T& operator[](size_t index) const {
    return data_[index];
  }

  typename RawContainer::iterator begin() {
    return data_.begin();
  }

  typename RawContainer::const_iterator begin() const {
    return data_.begin();
  }

  typename RawContainer::iterator end() {
    return data_.begin() + size_;
  }

  typename RawContainer::const_iterator end() const {
    return data_.begin() + size_;
  }

  typename RawContainer::reverse_iterator rbegin() {
    return RawContainer::reverse_iterator(data_.begin() + size_);
  }

  typename RawContainer::const_reverse_iterator rbegin() const {
    return RawContainer::const_reverse_iterator(data_.begin() + size_);
  }

  typename RawContainer::reverse_iterator rend() {
    return RawContainer::reverse_iterator(data_.begin());
  }

  typename RawContainer::const_reverse_iterator rend() const {
    return RawContainer::const_reverse_iterator(data_.begin());
  }
};

template <typename T, typename Comp, size_t N>
struct FixedSizePriorityQueue {
  using RawContainer = array<T, N>;
  RawContainer data_;
  size_t size_ = 0;

  FixedSizePriorityQueue() : size_(0) {}

  size_t size() const {
    return size_;
  }

  bool empty() const {
    return size_ == 0;
  }

  void clear() {
    size_ = 0;
  }

  void push(const T& value) {
    data_[size_++] = value;
    push_heap(data_.begin(), data_.begin() + size_, Comp());
  }

  void push(T&& value) {
    data_[size_++] = move(value);
    push_heap(data_.begin(), data_.begin() + size_, Comp());
  }

  const T& top() const {
    return data_.front();
  }

  void pop() {
    pop_heap(data_.begin(), data_.begin() + size_, Comp());
    --size_;
  }
};

template <typename T, size_t N>
using FixedSizePriorityQueueAsc = FixedSizePriorityQueue<T, greater<T>, N>;

template <typename T, size_t N>
using FixedSizePriorityQueueDesc = FixedSizePriorityQueue<T, less<T>, N>;

// [0, N) の整数を格納できる集合
template <typename Int, size_t N>
struct SerialNumberSet {
  using RawContainer = array<Int, N>;
  RawContainer data_, pos_;
  bitset<N> exists_;
  size_t size_ = 0;

  size_t size() const {
    return size_;
  }

  bool empty() const {
    return size_ == 0;
  }

  void clear() {
    size_ = 0;
    exists_.reset();
  }

  void insert(Int value) {
    pos_[value] = size_;
    exists_.set(value);
    data_[size_++] = value;
  }

  void erase(Int value) {
    // value を削除する
    exists_.reset(value);

    // 最後の要素を削除する要素の位置に移動
    size_t const index = pos_[value];
    pos_[data_[size_ - 1]] = index;
    data_[index] = data_[size_ - 1];
    --size_;
  }

  bool contains(Int value) const {
    return exists_.test(value);
  }

  typename RawContainer::iterator begin() {
    return data_.begin();
  }

  typename RawContainer::const_iterator begin() const {
    return data_.begin();
  }

  typename RawContainer::iterator end() {
    return data_.begin() + size_;
  }

  typename RawContainer::const_iterator end() const {
    return data_.begin() + size_;
  }
};
}  // namespace FixedSizeContainers

using namespace FixedSizeContainers;

struct Xoshiro128ss {
  using result_type = uint32_t;

  uint32_t s[4];

  static inline uint32_t rotl(const uint32_t x, int k) noexcept {
    return (x << k) | (x >> (32 - k));
  }

  struct SplitMix64 {
    uint64_t x;
    explicit SplitMix64(uint64_t seed) : x(seed) {}

    inline uint64_t next() noexcept {
      uint64_t z = (x += 0x9e3779b97f4a7c15ULL);
      z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
      z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
      return z ^ (z >> 31);
    }
  };

  Xoshiro128ss(uint64_t seed = 1) noexcept {
    set_seed(seed);
  }

  inline void set_seed(uint64_t seed) noexcept {
    SplitMix64 sm(seed);
    uint64_t a = sm.next();
    uint64_t b = sm.next();
    s[0] = uint32_t(a);
    s[1] = uint32_t(a >> 32);
    s[2] = uint32_t(b);
    s[3] = uint32_t(b >> 32);
  }

  static constexpr result_type min() noexcept { return 0; }
  static constexpr result_type max() noexcept { return UINT32_MAX; }

  inline result_type operator()() noexcept {
    // xoshiro128** 1.1
    const uint32_t result = rotl(s[1] * 5u, 7) * 9u;
    const uint32_t t = s[1] << 9;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= t;
    s[3] = rotl(s[3], 11);

    return result;
  }

  inline uint64_t next_u64() noexcept {
    return (uint64_t((*this)()) << 32) | (*this)();
  }

  // [0.0, 1.0) の一様乱数を生成する
  // -O2 以上前提で、コンパイラが除算を乗算に最適化する
  inline double nextDouble01() noexcept {
    return (*this)() / 4294967296.0;
  }
};

// 問題のパラメータなどはここに書いていく
struct Problem {
  // 入力の読み込みはここに書いていく
  void read(istream& is) {
  }
};

struct Solution {
  // 問題の生スコア。Solverでセットする
  double rawScore;

  // 出力の書き込みはここに書いていく
  void write(ostream& os) const {
  }
};

// 問題の入力や出力、アルゴリズムの実装などはここに書いていく
struct Solver {
  // 必要な作業領域などはここにメンバ変数として定義する
  // できるだけで、FixedSizeContainers 名前空間のコンテナを利用する

  // 乱数生成器は Solver で1個を使いまわす。
  // デバッグしやすいように、固定のシード値で初期化しておく
  Xoshiro128ss rng;

  Problem problem;

  Solver(Problem const& problem, int64_t seed = 42) : problem(problem),
                                                      rng(seed) {
  }

  // アルゴリズムの実装
  Solution solve() {
  }
};

int main() {
  Problem problem;
#ifdef _MSC_VER
  ifstream ifs("C:/Users/matsu/Workspace/atcoder/heuristic/tools/in/0000.txt");
  problem.read(ifs);
#else
  problem.read(cin);
#endif

  Solver* solver_ptr = new Solver(problem);
  Solver& solver = *solver_ptr;
  auto sol = solver.solve();

  sol.write(cout);

  // 競技プログラミングなので、main 関数の最後で問題のインスタンスを delete する必要はない
  return 0;
}
