# 第三章：刚体力学基础

1. 力矩：$M = Fd = \vec{r}\vec{F}$ ,一个系统内力的合力矩为0

2. 刚体定轴转动定律：$\vec{M} = J\beta$ ,J表示转动惯量，$J = \sum m_{i} r_{i}^{2} = \int r^{2} d m$  

3. 平行轴定理：刚体对于转轴的转动惯量等于对于通过质心的转轴的转动惯量加上刚体质量加上两周之间距离的平方。$J = J_C+mh^2$ 

4. 垂直轴定理：刚体对于Z轴的转动惯量等于对于X轴的转动惯量加上对于Y轴的转动惯量$J_z = J_x+J_y$

5. 常用结论：

1. 圆环的转动惯量：$J = mR^2$
2. <img src="/Users/zhuangyifei/Desktop/tech_Learning/myhomework/大一下学期/大学物理/src/image/Snipaste_2021-06-26_14-23-32.png" alt="Snipaste_2021-06-26_14-23-32" style="zoom:50%;" />
3. ![Snipaste_2021-06-26_14-23-55](/Users/zhuangyifei/Desktop/tech_Learning/myhomework/大一下学期/大学物理/src/image/Snipaste_2021-06-26_14-23-55.png)
4. ![Snipaste_2021-06-26_14-24-13](/Users/zhuangyifei/Desktop/tech_Learning/myhomework/大一下学期/大学物理/src/image/Snipaste_2021-06-26_14-24-13.png)

6. 刚体定轴转动的动能定理：$E_k = \frac{1}{2}J\omega^2 + \frac{1}{2}mv_c^2$,其中$v_c$表示质心平动的速度

7. 力矩做功：$A = \int_{\theta_0}^{\theta}Md\theta$ ，力矩的功率：$P = \frac{dA}{dt} = M\omega$

8. 动能定理：$A = \frac{1}{2}J\omega^2 - \frac{1}{2}J\omega_0^2$,合外力矩做功等于转动动能的增加量

9. 质点对轴的角动量：$L = mvrsin\varphi = \vec{r}\times\vec{p}$ ，刚体对轴的角动量：$L = J\omega$ 

10. 力矩对于时间的积分等于角动量的变化，因此，如果力矩为0，那么角动量守恒

11. 附对比图![Snipaste_2021-06-26_14-41-21](/Users/zhuangyifei/Desktop/tech_Learning/myhomework/大一下学期/大学物理/src/image/Snipaste_2021-06-26_14-41-21.png)![Snipaste_2021-06-26_14-42-12](/Users/zhuangyifei/Desktop/tech_Learning/myhomework/大一下学期/大学物理/src/image/Snipaste_2021-06-26_14-42-12.png)

    



# 第四章：狭义相对论

1. 洛伦兹变换：<font size = 5>$x_1 = \frac{x-ut}{\sqrt{1-\frac{u^2}{c^2}}}$ ，$t_1 = \frac{t-\frac{ux}{c^2}}{\sqrt{1-\frac{u^2}{c^2}}}$ </font>

2. 上式微分之后，用t式比上x式，可以得到速度变换公式.<font size = 5>$v_{1x} = \frac{v_x-u}{1-\frac{uv_x}{c^2}} v_{1y} = \frac{v_y-u}{1-\frac{uv_y}{c^2}} v_{1z} = \frac{v_z-u}{1-\frac{uv_z}{c^2}}$ </font>

3. 相对论时间公式（注意要相对于运动的参考系相对静止）才能使用。$t_1 = \frac{t}{\sqrt{1-\frac{u^2}{c^2}}}$

4. 相对论长度公式（注意事项同上）：$l_1 = l_0\sqrt{1-\frac{u^2}{c^2}}$

5. 如果研究对象相对于参考系不是相对静止的，那么不能使用上述两个公式，只能使用洛伦兹变换。

6. 时空间隔：$S=\sqrt{-\left(x_{2}-x_{1}\right)^{2}-\left(y_{2}-y_{1}\right)^{2}-\left(z_{2}-z_{1}\right)^{2}+c^{2}\left(t_{2}-t_{1}\right)^{2}}$ 相对于任何参考系都是一样的

7. 质量与速度的关系：$m = \frac{m_0}{\sqrt{1-\frac{v^2}{c^2}}}$

动能和速度的关系：$E_k = mc^2-m_0c^2 = m_0c^2(\frac{1}{\sqrt{1-\frac{v^2}{c^2}}}-1)$ 

8. 能量和动量的关系：$E = mc^2 = \sqrt{p^2c^2+m_0^2c^4}$

9. 对于光子：$m = \frac{E}{c^2} = \frac{hv}{c^2}$      $p = \frac{E}{c} = \frac{h}{\lambda}$



# 第五章：

1. 符合加速度（合外力）和位移成正比的运动就是简谐运动
2. 在弹簧振子系统中，我们有：
1. 运动角速度$\omega = \sqrt{\frac{k}{m}}$
2. 运动振幅：$A = \sqrt{{x_0}^2+(\frac{v_0}{\omega})^2}$ ,$\varphi = arctan(\frac{-v_0}{\omega x_0})$
3. 总能量守恒$E=\frac{1}{2} k x^{2}+\frac{1}{2} m v^{2}=\frac{1}{2} k A^{2}$ 
3. 例子
1. 单摆：符合方程：$\frac{d^{2} \theta}{d t^{2}}=-\frac{g}{l} \theta=-\omega^{2} \theta$ 则有$\theta=\theta_{m} \cos (\omega t+\varphi), \text { 其中 } \omega=\sqrt{\frac{g}{l}}$ ![Snipaste_2021-06-26_12-55-23](/Users/zhuangyifei/Desktop/tech_Learning/myhomework/大一下学期/大学物理/src/image/Snipaste_2021-06-26_12-55-23.png)
2. 复摆：符合方程$\theta=\theta_{m} \cos (\omega t+\varphi) \text { 其中: } \quad \omega=\sqrt{\frac{m g l}{J}}$                  ![Snipaste_2021-06-26_12-54-52](/Users/zhuangyifei/Desktop/tech_Learning/myhomework/大一下学期/大学物理/src/image/Snipaste_2021-06-26_12-54-52.png)
3. 扭摆:...
4. 振动的合成：
1. 两个沿x轴的简谐运动$x_{1}=A_{1} \cos \left(\omega t+\varphi_{1}\right) \quad x_{2}=A_{2} \cos \left(\omega t+\varphi_{2}\right)$ 合成之后仍然是简谐运动：$x = Acos(\omega t + \varphi)$。其中$A = \sqrt{A_1^2+A_2^2+2A_1A_2cos(\varphi_2-\varphi_1)}$,$\varphi = arctan{\frac{A_1sin\varphi_1+A_2sin\varphi_2}{A_1cos\varphi_1+A_2cos\varphi_2}}$ 
2. 同方向不同频率的两个简谐振动的合成（拍）$$x_{1}=A_{1} \cos \left(\omega t+\varphi_{1}\right) \quad x_{2}=A_{2} \cos \left(\omega t+\varphi_{2}\right)$$ ,$x=2 a \cos \left(\frac{\omega_{2}-\omega_{1}}{2}\right) t \cdot \cos \left(\frac{\omega_{2}+\omega_{1}}{2}\right) t$ ，振幅$A = 2acos(\frac{w_2-w_1}{2}t)$  这里假设$A_1 = A_2 = a$
3. 相互垂直的简谐振动的合成。$$x_{1}=A_{1} \cos \left(\omega t+\varphi_{1}\right) \quad x_{2}=A_{2} \cos \left(\omega t+\varphi_{2}\right)$$     轨迹是一个椭圆：$\frac{x^{2}}{A_{1}^{2}}+\frac{y^{2}}{A_{2}^{2}}-2 \frac{x y}{A_{1} A_{2}} \cos \left(\varphi_{2}-\varphi_{1}\right)=\sin ^{2}\left(\varphi_{2}-\varphi_{1}\right)$ 
5. 

# 第十章：机械波

1. 横波：震动方向和传播方向垂直
2. 纵波：震动方向就是传播的方向
3. 平面简谐波的波函数：$y(x, t)=A \cos \omega\left(t-\frac{x}{u}\right)$ 
4. 相速等于波速，但是相速和振动速度不同
5. 波的能量：$W_{k}=W_{p}=\frac{1}{2} \rho A^{2} \omega^{2}(\Delta V) \sin ^{2} \omega\left(t-\frac{x}{u}\right) = \frac{1}{2}\rho \Delta V v^2$,因此总能量就是$\rho \Delta V v^2$
6. 能量密度$w=\frac{W}{\Delta V}=\rho A^{2} \omega^{2} \sin ^{2} \omega\left(t-\frac{x}{u}\right) = \rho v^2$ ,代表介质中波的单位体积的能量
7.  平均能量密度,代表一个周期内穿过单位体积的能量大小：$\bar{w}=\frac{1}{T} \int_{0}^{T} w \mathrm{~d} t=\frac{1}{T} \int_{0}^{T} \rho A^{2} \omega^{2} \sin ^{2} \omega\left(t-\frac{x}{u}\right) \mathrm{d} t=\frac{1}{2} \rho A^{2} \omega^{2} = \frac{1}{2} \rho {v_m}^2$
8. 能流密度表示一个周期内穿过单位面积的能量，用P表示
9. 平均能流密度：$I = \overline{\omega}u = \frac{1}{2}\rho u \omega^2 A^2 = \frac{1}{2}\rho u v_m^2$ 表示一个周期内穿过单位面积的能量大小
10. 对于平面波，传播的过程中振幅不变。![Snipaste_2021-06-26_11-13-47](/Users/zhuangyifei/Desktop/tech_Learning/myhomework/大一下学期/大学物理/src/image/Snipaste_2021-06-26_11-13-47.png)
11. 对于球面波：根据通过球壳的能流大小不变，我们有$A_1r_1 = A_2r_2$表示球面波的振幅和传播的距离成反比，也就是球面波的传播方程是$y(r, t)=\frac{A_{0}}{r} \cos \omega\left(t-\frac{x}{u}\right)$             						![Snipaste_2021-06-26_11-23-44](/Users/zhuangyifei/Desktop/tech_Learning/myhomework/大一下学期/大学物理/src/image/Snipaste_2021-06-26_11-23-44.png)
11. 频率相同的波的干涉：两个波合成之后的方程为$y=y_{1}+y_{2}=A \cos (\omega t+\varphi)$ ，其中$A = \sqrt{{A_1}^2+{A_2}^2+2A_1A_2cos(\Delta \varphi)}$  ,$\Delta \varphi = (\varphi_2 - \varphi_1)-\frac{2\pi}{\lambda}(r_2-r_1)$
12. 从上式可以看出，如果两个波源的初相位相同或相差$2\pi$的整数倍，那么合成之后波相当于原波相加，如果是$(2\pi+1)$的整数倍，那么相当于两个波相减
13. 多普勒效应$v_{R}=\frac{u \pm v_{R}}{\lambda \mp v_{S} T_{s}}=\frac{u \pm v_{R}}{u \mp v_{S}} v_{s}$ 其中u表示波速,$v_R$表示观察者相对于在自身和波源连线方向上的速度，$v_s$表示波源在观察者和自身连线上的速度
14. 



# 第十一章：热学

1. 气体分子向各个方向的运动几率相等

2. 压强公式：$p=\frac{1}{3} n m \overline{v^{2}}=\frac{2}{3} n\left(\frac{1}{2} m \overline{v^{2}}\right)=\frac{2}{3} n \overline{\varepsilon_{k}}$,其中$n=\frac{N}{V}$代表气体分子密度​

3. 对于自由度为3的分子，我们有：$\bar{\varepsilon}_{t}=\frac{3}{2} k T$，那么${\sqrt{\overline{v^2}} = \sqrt{\frac{3kT}{m}} = \sqrt{\frac{3RT}{\mu}}}$ ，m代表单个气体分子的质量，$\mu$代表气体摩尔质量

4. 对于自由度为i的分子，我们有$\overline{\varepsilon} = \frac{i}{2} k T$

5. 对于理想气体，势能可以忽略，则有$\overline{\varepsilon} = \frac{i}{2}kT$，那么对于vmol气体，内能为$\overline{E} = vN_A(\frac{i}{2}kT) = v\frac{i}{2} RT$

6. 麦克斯韦分布：

1. 近似计算公式
* f(v)dv代表在v附近dv为区间的分子占总数的百分比
* Nf(v)dv表示上述分子所占的数量
2. 精确计算：$\int_{v_{1}}^{v_{2}} f(v) d v$ 代表v1~v2分子所占的百分比
3. 归一条件:$\int_{0}^{+\infty} f(v) d v = 1$，此式可以解出某些式子中的参数
4. 最概然速率：计算方法为求分布函数的极值点，对于一般的麦克斯韦分布，$v_p = \sqrt{\frac{2kT}{m}} = \sqrt{\frac{2RT}{\mu}}$
5. 平均速率：计算方法为求$\int_{0}^{+\infty} vf(v) d v$,对于一般的麦克斯韦分布，$\overline{v} = \sqrt{\frac{8 k T}{\pi m}}=\sqrt{\frac{8 R T}{\pi \mu}}$ 
6. 方均根速率：计算方法为计算$\int_{0}^{+\infty} v^2f(v) d v$，对于一般的麦克斯韦分布，我们有$\sqrt{\overline{v^{2}}}=\sqrt{\frac{3 k T}{m}}=\sqrt{\frac{3 R T}{\mu}}$ 
7. 上述的三个速度的比值满足:$v_{p}: \bar{v}: \sqrt{\overline{v^{2}}}=\sqrt{2}: \sqrt{\frac{8}{\pi}}: \sqrt{3}$ 

7. <strong><font color="red" size="6px">平均碰撞频率：$\overline{Z} = \sqrt{2}\pi d^2\overline{v}n$,平均自由程：$\overline{\lambda} = \frac{\overline{v}}{\overline{Z}} = \frac{kT}{\sqrt{2}\pi d^2p}$</font></strong>

   

# 第十二章 热力学基础

1. 热力学第一定律：$Q=E_2-E_1+W=\Delta E+W$,Q代表物体吸热，W代表系统对外做功

2. 系统对外做功的绝对值大小等于p-V图像对于V轴所围的面积

3. 自由度：

1. 单原子气体分子：3
2. 刚性多原子分子，双原子气体分子：6
3. 刚性双原子分子：5

4. 摩尔热容：

1. 热容量的定义：$C = {\rm d}Q/{\rm d}T$
2. 比热：$c = C/M$,M代表系统质量
3. 摩尔热容：$C_m = C/v$，v代表物质的量

5. 系统吸热通用公式：$Q=\int_{T_{1}}^{T_{2}} v C d T$ ，C代表该过程中的摩尔热容

6. **等体积过程**

1. 对于等体过程，由于W=0，我们有$Q_V = \Delta E$,由热力学第一定律，和理想气体内能公式$E=v\frac{i}{2} RT$,我们可以得到：$Q_{V}=\Delta E=v \frac{i}{2} R \Delta T$ ,吸热只和温度变化有关
2. 对于等体过程，我们定义定体摩尔热容：$C_V = \frac{{\rm d}Q_v}{v{\rm d}T}$ 由于理想气体总有${\rm d}Q_v = v\frac{i}{2}R{\rm d}T$，因此我们有${C_v = \frac{i}{2}R}$，也就是说定体摩尔热容只和气体分子的自由度有关。
3. 从以上的定义，我们还有${\rm d}E = vC_v{\rm d}T$

7. **等压过程**：

1. 过程中恒有：$p=vRT/V$为常量
2. 因此，系统做功${\rm d}W = vR{\rm d}T$
3. 热量：${\rm d}Q = vC_p{\rm d}T$ ,$C_p$代表定压摩尔热容
4. 那么，内能的变化就是$dE = dQ-dW = vC_pdT-vRdT$ 
5. 迈耶公式：$C_p = C_V+R$ 
6. 定义摩尔热容比：$\gamma=\frac{C_{p}}{C_{V}}=\frac{C_{V}+R}{C_{V}}=1+\frac{R}{C_{V}}=1+\frac{2}{i}$ 

8. 等温过程：

1. 等温过程中其体内能不变：$\Delta E = 0$
2. $\begin{aligned}
&Q_{T}=W=\int_{V_{1}}^{V_{2}} p d V=\int_{V_{1}}^{V_{2}} \frac{v R T}{V} d V=v R T \ln \frac{V_{2}}{V_{1}}=v R T \ln \frac{p_{1}}{p_{2}}
\end{aligned}$

9. 绝热过程：

1. 状态方程（柏松公式）：$p V^{Y}=c_{1}$ 
2. 过程做功$\begin{aligned}
W &=\int_{V_{1}}^{V_{2}} p d V=\int_{V_{1}}^{V_{2}} \frac{p_{1} V_{1}^{\gamma}}{V^{\gamma}} d V=\frac{p_{1} V_{1}^{\gamma}}{1-\gamma}\left[\frac{1}{V_{2}^{\gamma-1}}-\frac{1}{V_{1}^{\gamma-1}}\right] \\
&=\frac{1}{1-\gamma}\left[\frac{p_{2} V_{2}^{\gamma}}{V_{2}^{\gamma-1}}-\frac{p_{1} V_{1}^{\gamma}}{V_{1}^{\gamma-1}}\right]=\frac{1}{1-\gamma}\left[p_{2} V_{2}-p_{1} V_{1}\right]
\end{aligned}$

10. <font size = 5 color ="red" font-weight="bold">多方过程(通用公式，重点！)</font>

1. 对于上述的四个过程，有一个通用的状态方程：$pV^n = $常量
2. 对于不同的过程：
1. 等压：n=0
2. 等温：n=1
3. 绝热：n=$\gamma$ ，$\gamma$代表摩尔热容比
4. 等容：$n = +\infty$
3. 那么，多方过程的功：$W = \int_{V_{1}}^{V_{2}} p d V=\int_{V_{1}}^{V_{2}} \frac{p_{1} V_{1}^{n}}{V^{n}} d V=\frac{1}{1-n}\left(p_{2} V_{2}-p_{1} V_{1}\right)$
4. 多方过程中吸收的热量：$Q=v C_{n}\left(T_{2}-T_{1}\right)=\left(v C_{V}-\frac{v R}{n-1}\right)\left(T_{2}-T_{1}\right)$
5. 由热力学第一定律可以求出内能的变化量

11. 效率：$\eta = 1-\frac{Q_2}{Q_1}$，$Q_2$代表系统放热，$Q_1$代表系统吸热

12. 循环过程

1. 正循环（热循环）：沿顺时针方向进行的循环
2. 逆循环（制冷循环）：沿逆时针方向进行的循环

13. 卡诺循环

1. 两个等温，两个绝热。
2. 过程图![Snipaste_2021-06-26_10-18-31](/Users/zhuangyifei/Desktop/tech_Learning/myhomework/大一下学期/大学物理/src/image/Snipaste_2021-06-26_10-18-31.png)
3. 过程一为等温过程，有$Q_1 = vRTln{\frac{V_2}{V_1}}$
4. 过程二为绝热过程：满足$T_1{V_2}^{\gamma-1} = T_2{V_3}^{\gamma-1}$
5. 过程三为等温过程，满足$Q_2 = vRT_2ln{\frac{V_3}{V_4}}$
6. 过程四为绝热过程：$T_1{V_2}^{\gamma-1} = T_2{V_4}^{\gamma-1}$
7. 效率：由$\eta=1-\frac{T_{2}}{T_{1}}$可算出卡诺机的效率，其只和温度有关

14. 逆向卡诺机（空调）$\omega_{c}=\frac{Q_{2}}{|W|}=\frac{Q_{2}}{Q_{1}-Q_{2}}=\frac{T_{2}}{T_{1}-T_{2}}$

15. 

    

# 第十三章 静电学

1. 库仑定律：$\vec{F}_{12}=-\vec{F}_{21}=k \frac{q_{1} q_{2}}{r_{12}^{3}} \vec{r}_{12}$ ，也可写作$\vec{F}_{12}=-\vec{F}_{21}=\frac{1}{4 \pi \varepsilon_{0}} \frac{q_{1} q_{2}}{r_{12}^{3}} \vec{r}_{12}$ 
2. 场强定义式：$\vec{E}=\frac{\vec{F}}{q_{0}}$ 
3. 点电荷电场强度:$\vec{E}=\frac{\vec{F}}{q_{0}}=\frac{1}{4 \pi \varepsilon_{0}} \frac{Q}{r^{3}} \vec{r}$ 
4. 均匀带电圆环的场强：$E =\frac{z \lambda}{4 \pi \varepsilon_{0}\left(z^{2}+R^{2}\right)^{3 / 2}} \int_{0}^{2 \pi R} d l=\frac{z q}{4 \pi \varepsilon_{0}\left(z^{2}+R^{2}\right)^{3 / 2}} \approx \frac{q}{4 \pi \varepsilon_{0} z^{2}}$ 相当于电荷集中在圆心的点电荷
5. 圆盘的场强：$E=\int d E_{z}=\frac{z \sigma}{4 \varepsilon_{0}} \int_{0}^{R}\left(z^{2}+r^{2}\right)^{-3 / 2}(2 r) d r=\frac{\sigma}{2 \varepsilon_{0}}\left(1-\frac{z}{\sqrt{z^{2}+R^{2}}}\right)$ 
1. 如果z远小于R，那么圆盘可以视为无穷大，则$E = \frac{\sigma}{2 \varepsilon_{0}}$
2. 如果z远大于R，那么圆盘可以视为点电荷
6. 电通量：$\begin{aligned}
&\phi_{e}=\int d \phi_{e}=\int_{S} E \cos \theta d S 
=\int_{S} \vec{E} \cdot d \vec{S}
\end{aligned}$ 
7. 高斯定理：闭合曲面的电通量和其包围的电荷存在确定关系:$\phi_{e}=\oiint_{S} \vec{E} \cdot d \vec{S}=\frac{1}{\varepsilon_{0}} \sum_{i} q_{i}$ 如果电荷分布和空间坐标有关，那么做一个积分即可
8. 需要注意的是，闭合曲面的电通量只和它所包围的电荷量有关，但是其场强和外部电荷也有关系
9. 由高斯定律，我们有如下的结论：
1. 带电直线的场强：$E \cdot 2 \pi r l=\frac{1}{\varepsilon_{0}} \lambda l \quad E=\frac{\lambda}{2 \pi \varepsilon_{0} r}$ 
2. 无限大平面产生的场强：$$2 E S=\frac{1}{\varepsilon_{0}} \sigma S \quad E=\frac{\sigma}{2 \varepsilon_{0}}$$ 



## 历年卷要点总结

1. 注意机械波传递的方向

2. 注意合成的是机械波还是两个振动，主要是振幅的计算方法不同

3. 拍$x=2acos(\frac{w_1-w_2}{2})tcos(\frac{w_1+w_2}{2})$

4. 熵变$\Delta S = v(C_vln(\frac{T_1}{T_2})+Rln(\frac{V_2}{V_1}))$ （口诀：CTRV）

5. 无限大的平面 $E = \varphi/2e$

6. 力矩和角动量的关系$FR=J\beta$

7. 多方过程：$W = \frac {1} {1-n} (p_2V_2-p_1V_1)$       $ Q = v(C_v + { \frac{R}{1-n}} $$  )(T_2-T_1) $     (顺序 压温热容)

等温过程不可使用上述公式  $W=Q=vRTln(\frac{V_2}{V_1}) = vRTln(\frac{P_2}{P_1})$

8. 如果机械波的基准点在x=d,t=t0处，那么将结果中的t换为t-t0,x换为x-d

9. 自由程公式：$\lambda = \frac{1}{\sqrt{2}\pi d^2 n}$ 

10. 注意变换：$a = \frac{dv}{dt} = v\frac{dv}{dx}$

11. 绝热过程熵变为0

12. 分析轴对于杆的力的大小的时候，用质心分析（沿杆：向心力，重力 垂直杆：加速度）

13. 机械波能够同时取到动能和势能的最值，但是振动不可以

14. 势能计算: $\frac{i-3}{kT}$

15. 曲率半径 $\rho = \frac{v^2}{a_n}$ an代表法向加速度

16. 火箭发射分析公式：$m\frac{dv}{dt} = F+u\frac{dm}{dt}$

17. 判断初相位的时候注意分析对象是一个质点还是波

18. 简谐运动$A=\sqrt{x_{0}^{2}+\left(\frac{v_{0}}{\omega}\right)^{2}}$ $\varphi=\arctan \frac{-v_{0}}{\omega x_{0}}$

19. g取9.8计算

20. 做积分运算的时候注意初始条件不一定是0，不要忽略

21. 

22. 