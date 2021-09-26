# オイラー法
# 連立線形常微分方程式


import math
import numpy as np
from matplotlib import pyplot as plt
import numpy.linalg as LA

T = 10.0
x0 = 1
y0 = 0
t = 0
x = x0
y = y0
N = 1000
h = T/N

#初期値(1)
'''
a_11 = 0
a_12 = 1
a_21 = -1
a_22 = 0
'''
#初期値(2)

a_11 = -1
a_12 = 1
a_21 = -4
a_22 = 0

#初期値(3)
'''
a_11 = 1
a_12 = 1
a_21 = -4
a_22 = 0
'''


A = np.array([[a_11, a_12], [a_21, a_22]])

tt = np.linspace(0, T , N + 1)

xt = [] 
xt.append(x0)
yt = []
yt.append(y0)

#真の解をx(N = 20000)として求める
#x_a = []
#y_a = []

for i in range(N):
    x_new = x + h*(a_11*x + a_12*y)
    y_new = y + h*(a_21*x + a_22*y)
    xt.append(x_new)
    yt.append(y_new)
    x = x_new
    y = y_new

for i in range(N,20000):
    x_new = x + h*(a_11*x + a_12*y)
    y_new = y + h*(a_21*x + a_22*y)
    #x_a.append(x_new)
    #y_a.append(y_new)
    x = x_new
    y = y_new
'''
    if i == N:
        s_nx = x_new
        s_ny = y_new
'''
#行列Aの固有値
print(LA.eig(A))

#誤差を計算する
print("|x(N) - x(20000)| = {:.3e}".format(abs(float(x - xt[-1]))))
print("|y(N) - y(20000)| = {:.3e}".format(abs(float(y - yt[-1]))))

plt.plot(tt, xt, color = "b")
plt.plot(tt, yt, color = "r")
plt.xlabel("t")
plt.ylabel("b = x(t), r = y(t)")
plt.show()

plt.plot(xt, yt, color = "g")
plt.xlabel("x(t)")
plt.ylabel("y(t)")
plt.show()

'''
yのリストを作ってないから
yが更新されずずっと0
あとx_exいらない
xをyに変えただけ
'''