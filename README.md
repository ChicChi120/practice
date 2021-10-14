# 微分方程式の数値解法

![test1](https://user-images.githubusercontent.com/47030492/134803694-1a0dc3b9-c134-40c8-876a-ed2f15c51fd6.jpeg)  

![test2](https://user-images.githubusercontent.com/47030492/134803720-b6b77f3f-8941-4319-b5de-1a2b6781248e.jpeg)  

![test3](https://user-images.githubusercontent.com/47030492/134803737-b2552145-46ef-43bc-9a15-9d8573c85ce9.jpeg)

![henon](https://user-images.githubusercontent.com/47030492/137338882-2f7f5e6a-9f42-4bae-81cc-75ce2aa27d90.jpeg)

上の画像を表示するには  
```
$  cd 2021/lorenz_le/  
$  gnuplot  
  
gnuplot>  splot 'data.dat' w l
```

のようにすれば良い.

## オイラー法


## ルンゲ・クッタ法 (4次)


## 微分方程式


### ローレンツ系
極度に単純化された大気対流のモデルとして,  1963 年に E.N. ローレンツ (E.N. Lorenz) によって最初に定式化されたこの系は,  「ストレンジ・アトラクター」として知られることになるものを持っている.  ローレンツ・モデルが大ニュースとなり始める以前は,  微分方程式で知られていた安定なアトラクターのタイプは,  平衡点と閉軌道だけだった.


### Lyapunov 指数
不規則な変動が現れるからといってカオスとは限らない. 実際, ランダムなノイズを付加すればどのようなシステムも不規則になる. カオスとしての不規則性の特徴は, 初期値への依存性が強いことである. つまり, 初期値を変えると, その後の変動が大きく変わってしまう. (中略) このような性質を __初期値鋭敏性__ とよび, カオス的変動を特徴づける重要な性質の１つである.  
初期値鋭敏性によって, 初期値がわずかに異なる軌道の差の変化は指数関数的である. この変化を関数としたときの指数を __Lyapunov指数__ という. Lyapunov 指数は系の次元の数だけ存在し, その最大値を __最大Lyapunov指数__ とよぶ.  
ローレンツ系, レスラー系, ラングフォード系のそれぞれで Lyapunov 指数を計算している. 特に, lorenz_lyapunov.cpp でローレンツ系の lyapunov 指数を計算した結果, 1.36971 という値が出力され正の値であることからカオスであることが確かめられる.
  
## 引用
* 力学系入門 - 微分方程式からカオスまで - 原著第3版 ,  
Morris W.Hirsch ・ Stephen Smale ・ Robert L.Devaney 著,  
桐木 紳 ・ 三波 篤郎 ・ 谷 清隆 ・ 辻井 正人 訳,  共立出版 (2017).  

* 力学系カオス, 松葉 育雄 著, 森北出版 (2011).

## 参考
* 力学系カオス, 松葉 育雄 著, 森北出版 (2011).  

* A Numerical Approach to Ergodie Problem of Dissipative Dynamical Systems, Ippei SHIMADA and Tomomasa NAGASHIMA (1978).