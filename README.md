# pocketpy-experiments

C++ ヘッダオンリーな Python 処理系
[pocketpy](https://github.com/blueloveTH/pocketpy) で遊んで見るリポジトリ。

## ネイティブビルド

C++17 が必要。Clang 16.0 以上では C++17 がデフォルトなので指定しなくても大丈夫。

```
$ clang++ main.cpp -o main
$ ./main
```

## Emscripten ビルド

```
$ em++ main.cpp -s WASM=1 -o main.html
$ emrun main.html
```

## Clean

```
$ rm -rf main main.js main.html main.js main.wasm
```