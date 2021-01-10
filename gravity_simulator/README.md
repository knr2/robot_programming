# ボールの物理シミュレータの仕様書

Open GLを使ってバウンドするボールを作成しました。

# 目次

- [性能](#性能)
- [動作環境](#動作環境)
- [デモ動画](#デモ動画)
- [インストール方法](#インストール方法)
- [使用方法](#使用方法)
- [ライセンス](#ライセンス)


# 性能

基本性能
- ボールと壁の衝突判定
- ボールとボールの衝突判定
- ボールのバウンド
- ボールの自由落下
- 開店から速度へ変換

その他機能
- Defineをいじることでボールの数や、フィールドの広さを簡単に変化可能


# 動作環境

以下の環境にて動作確認を行っています。

- OS: Ubuntu 18.04 LTS


# デモ動画

[![バウンドするボール](http://img.youtube.com/vi/3zt6zq_mfJk/hqdefault.jpg)](https://youtu.be/3zt6zq_mfJk)


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
cd robot_programming/gravity_simulator/
gcc -Wall -Weffc++ -o glut_main ball.c -lglut -lGLU -lGL -lm;./glut_main
```

操作方法
- 右クリックでシミュレーターが起動，演算開始
- 左クリックで一時停止，再度右クリックで再開


# ライセンス

MIT License
