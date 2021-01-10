# 関数電卓の仕様書


# 目次

- [性能](#性能)
- [動作環境](#動作環境)
- [インストール方法](#インストール方法)
- [使用方法](#使用方法)
- [ライセンス](#ライセンス)


# 性能

可能な計算
- 四則演算
- 三角関数
- ルートの計算

その他機能
- 計算結果をテキストファイル(math.txt)に保存
- 1つ前に戻る機能
- 連続で計算可能
- モード変更有と、モード変更なしの選択


# 動作環境

以下の環境にて動作確認を行っています。

- OS: Ubuntu 18.04 LTS


# インストール方法

- Open GLとGLFW
ターミナル
```sh
sudo apt-get install -y libx11-dev xorg-dev
sudo apt-get install -y libglu1-mesa libglu1-mesa-dev
sudo apt-get install -y libgl1-mesa-glx libgl1-mesa-dev
sudo apt install -y libglfw3 libglfw3-dev
sudo apt install -y libglew-dev
```


- プログラム
ターミナル
```sh
git clone https://github.com/knr2/robot_programming.git
```


# 使用方法

以下のコマンドで使用できます。

ターミナル
```sh
cd robot_programming/function_calculator/
gcc function_calculator.c -o test -lm; ./test
```

履歴を見る場合
ターミナル
```sh
cd robot_programming/function_calculator/
gcc function_calculator.c -o test -lm; ./test
```

# ライセンス

MIT License
