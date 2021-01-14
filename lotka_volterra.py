# オイラー法
# ロトカーヴォルテラ方程式

import math
import numpy as np
from matplotlib import pyplot as plt

T = 10
x0 = 1
y0 = 1
t = 0
x = x0
y = y0
N = 1000
h = T/N

#初期値(協調系)
'''
#ただただ増えていく
a1 = 0.03
b1 = 0
c1 = 0.07
a2 = 0.01
b2 = 0.09
c2 = 0
'''

#初期値(被食者・捕食系)
'''
#コピペ 保存系
a1 = 3
b1 = 0
c1 = -3
a2 = -1
b2 = 2
c2 = 0
'''
'''
#安定定常点(x*, y*)に収束
#x* = 0.6764705882352942  y* = 0.058823529411764705 python計算 綺麗にでた
a1 = 3
b1 = -4
c1 = -5
a2 = -1
b2 = 2
c2 = -6
'''
'''
#xの種がどんなに多くてもyの種の生存が維持できずyの種は絶滅
a1 = 2
b1 = -6
c1 = -5
a2 = -4
b2 = 3
c2 = -1
'''
#初期値(競争系)
'''
#(i)x = a1/b1 となり yの種が絶滅
a1 = 22
b1 = -0.2
c1 = -0.4
a2 = 17
b2 = -0.5
c2 = -0.3
'''

#(ii)y = a2/b2 となり xの種が絶滅   なぜかできない
a1 = 14
b1 = -1.1
c1 = -0.9
a2 = 20
b2 = -0.5
c2 = -0.4

'''
#(iii)初期状態によって優勢な方が他の種を絶滅させる K1かK2に収束(K1に収束した)
a1 = 25
b1 = -0.1
c1 = -0.4
a2 = 20
b2 = -0.2
c2 = -0.1
'''
'''
#(iv)共存可能
a1 = 23.2
b1 = -0.6
c1 = -0.401
a2 = 18.8
b2 = -0.5
c2 = -0.3
'''

tt = np.linspace(0, T , N + 1)

xt = []
xt.append(x0)
yt = []
yt.append(y0)

#保存系
con = []
con.append(0)

#真の解をx(N = 20000)として求める
#x_a = []
#y_a = []


for i in range(N):
    x_new = x + x*h*(a1 + b1*x + c1*y)
    y_new = y + y*h*(a2 + b2*x + c2*y)
    xt.append(x_new)
    yt.append(y_new)
    x = x_new
    y = y_new
    print("x = ",x_new)
    print("y = ",y_new)
    #保存系の確認
    con_n = (x - (-a2/b2)*math.log(x))/c1 + (y - (a1/-c1)*math.log(y))/b2
    print("constant = ", con_n)
    con.append(con_n)

    if x_new < 0 or y_new < 0:
        continue

#Nから20000
for i in range(N,2000):
    x_new = x + x*h*(a1 + b1*x + c1*y)
    y_new = y + y*h*(a2 + b2*x + c2*y)
    #x_a.append(x_new)
    #y_a.append(y_new)
    x = x_new
    y = y_new

    if x_new < 0 or y_new < 0:
        continue

'''
    if i == N:
        s_nx = x_new
        s_ny = y_new
        print("K1 = ",s_nx)
        print("K2 = ",s_ny)
'''

#誤差を計算する
print("|x(N) - x(20000)| = ",abs(x - xt[-1]))
print("|y(N) - y(20000)| = ",abs(y - yt[-1]))

plt.plot(tt, xt, color = "b")
plt.plot(tt, yt, color = "r")
plt.xlabel("t")
plt.ylabel("b = x(t), r = y(t)")
plt.show()

#保存系
plt.plot(tt, con, color = "c")
plt.xlabel("t")
plt.ylabel("constant")
plt.show()

plt.plot(xt, yt, color = "g")
plt.xlabel("x(t)")
plt.ylabel("y(t)")
plt.show()

'''
plt.plot(tt, x_a, color = "b")
plt.plot(tt, y_a, color = "r")
plt.xlabel("t")
plt.ylabel("b = u(t), r = v(t)")
plt.show()

plt.plot(x_a, y_a, color = "g")
plt.xlabel("u(t)")
plt.ylabel("v(t)")
plt.show()
'''