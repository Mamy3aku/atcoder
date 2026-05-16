# AtCoder 競技プログラミング用テンプレート

AtCoder での解答提出に使用するテンプレートと、[AtCoder Library (ACL)](https://github.com/atcoder/ac-library) をまとめたリポジトリです。

## ディレクトリ構成

```
.
├── algorithm/      # 通常の競プロ問題用テンプレート (C++)
├── heauristic/     # ヒューリスティック・マラソン問題用テンプレート (C++)
└── ac-library/     # AtCoder Library (ACL)
```

## テンプレート

### `algorithm/main.cpp` — 通常問題用

- `bits/stdc++.h` + `atcoder/all` をインクルード
- `ll` (`int64_t`)、`mint` (`modint998244353`) の型エイリアス
- `fastio()`, `rep`, `rep2` マクロ
- `chmin` / `chmax` / `make2d` ユーティリティ関数
- 二分探索ヘルパー (`binary_search`)
- `ATCODER` マクロが定義されているとき `debug()` は無効化される

### `heauristic/main.cpp` — ヒューリスティック問題用

- GCC 最適化プラグマ (`Ofast`, `unroll-loops`, `avx2` など)
- Visual Studio / GCC 両対応のため個別ヘッダをインクルード
- 時間計測・制限管理用 `Timer` 構造体 (デフォルト制限: 1990ms)
- パフォーマンス重視の固定サイズコンテナ (`FixedSizeArray` など)
- `debug()` マクロは `ATCODER` 定義時に無効化される

## AtCoder Library (ACL)

`ac-library/` に ACL を同梱しています。主なコンポーネント:

| モジュール | 内容 |
|---|---|
| `dsu` | Union-Find (Disjoint Set Union) |
| `fenwicktree` | Binary Indexed Tree (BIT) |
| `segtree` | セグメント木 |
| `lazysegtree` | 遅延セグメント木 |
| `modint` | 剰余演算整数 |
| `maxflow` | 最大流 |
| `mincostflow` | 最小費用流 |
| `scc` | 強連結成分分解 |
| `twosat` | 2-SAT |
| `convolution` | 畳み込み (NTT) |
| `string` | 文字列アルゴリズム (SA, LCP 等) |

## ローカルデバッグ

`ATCODER` マクロを **未定義** にしてビルドすると `debug(x)` が標準エラー出力に値を表示します。
提出時は `ATCODER` を定義するか、ジャッジ環境で自動的に無効化されます。
