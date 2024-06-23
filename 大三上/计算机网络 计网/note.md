# 计网笔记

## Chapter 1 计算机网络体系结构

### 1.1 计算机网络概述

#### 1.1.1 计算机网络的概念

- 比较浅显，这里不做概述

#### 1.1.2 计算机网络的组成

- 从组成角度看，计算机网络由硬件，软件和协议组成，协议是计算机网络的核心
- 从工作方式上看，计算机网络可以分为边缘部分和核心部分两部分。
- 从**功能组成**上看，可以分为资源子网和通信子网两部分，其中前者由各种传输介质，通信设备和对应的网络协议组成，是的网络由数据传输交换，控制和存储的能力；资源子网是实现资源共享功能的设备和软件的集合，想网络用户提供其他计算机上的硬件，软件和数据的服务。
- ![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/GMgNKA.png)

- 在 ISO 七层模型中，通信子网占据下三部分，资源子网占上三部分。

#### 1.1.3 计算机网络的功能

1. 通信
2. 资源共享
3. 分布式处理
4. 提高可靠性
5. 负载均衡

#### 1.1.4 计算机网络的分类

1. 按照分布区域
   1. 广域网 wan
   2. 城域网 man
   3. 局域网 lan
   4. 个人区域网 pan
2. 按照传输技术
   1. 广播式网络
   2. 点对点网络（p2p）
3. 按照拓扑结构
   1. 总线型
   2. 星型
   3. 环形
   4. 网状
4. == 按照交换技术分类 ==
   1. 电路交换网络
      1. 数据直接传送，时延小，但是线路利用率低，不容易进行差错控制。
   2. 报文交换网络
      1. 在数据之外进行封装，发送之后，接收者按照存储 - 转发方式进行信息传输，重复这个过程达到目标，可以充分利用线路容量
   3. 分组交换网络
      1. 在上述基础上限制报文长度，平均时延小，容易标准化。

#### 1.1.5 性能指标

1. 带宽，指的是比特每秒

2. 时延

   1. 指的是一个数据从网络的一端到另一端所需要的时间，由发送时延，传播时延，处理时延和排队时延组成
   2. 发送时延：将所有的 bit 推到链路中所需要的时间，如果数据包大小为 m，带宽为 n，那么发送时延就是 m / n
   3. 传播时延：指的是一个 bit 从一端到另一端所需要的时间，数值上等于信道的长度 / 信道的传播速率
   4. 处理时延：指的是接收端处理数据包所需要的时间
   5. 排队时延：可能需要排队，这里消耗的时间就是排队时延

3. ###### 时延带宽积

   1. 指的是一个 bit 即将到达终点的时候，发送端已经发出了多少个 bit，数值上等于发送速率 * 单项传播时延

4. 往返时延 rtt，不言而喻

5. 信道利用率，数值上就是信道上有数据通过的时间 / 总时间

6. 吞吐量，指的是一段时间内通过某个网络的总数据量

练习题

| 题号 | 作答    | 如果错误地原因                                               |
| ---- | ------- | ------------------------------------------------------------ |
| 1    | B       |                                                              |
| 2    | A       |                                                              |
| 3    | D       |                                                              |
| 4    | C       |                                                              |
| 5    | D       |                                                              |
| 6    | C       |                                                              |
| 7    | A       |                                                              |
| 8    | A       |                                                              |
| 9    | A       |                                                              |
| 10   | A ==B== | 局域网和广域网使用的协议是不一样的，前者用的广播技术，后者用的是点对点技术 |
| 11   | D       |                                                              |
| 12   | A       |                                                              |
| 13   | C       |                                                              |
| 14   | C       |                                                              |
| 15   | A       |                                                              |
| 16   | D       |                                                              |
| 17   | B       |                                                              |
| 18   | B       |                                                              |

计算题

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/4LTkeM.png)

注意这里的传播时延只计算单向的（也就是 $\frac{2km}{2 * 10^8m/s}$），和 rtt 不同

### 1.2 常用术语介绍

#### 1.2.1 分层结构

- SDU 上一个层次要求传输的数据
- PCI，协议要求太耐的数据
- PDU，对等层次之间传输的数据单元，注意 == 链路层的 pdu 叫做帧，网络层 pdu 叫做分组，传输层的 pdu 叫做报文段 ==
- 关系 n-pdu + n-pci = (n-1)sdu，本层次用户奥球发送的信息加上本层次加上的信息 = 下一层次要发送的用户信息
- 不言而喻，一目了然
- ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/sjShfJ.png)
-

#### 1.2.2. 协议 接口和服务

- sap 服务访问点，表示为 n 层向 n + 1 层提供服务的接口

#### 1.2.3  模型

- OSI 模型

  - 首先上图

  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/rCWubE.png)

  - 注意到 osi 模型一共有 7 层，分别是物理测过、链路层、网络层、传输层、会话层、表示层、和用户层，其中前三个层次叫做通信子网，后三个层次叫做资源子网
    - 物理层：负责传输比特流，但是没有差错控制和流量控制的功能，== 注意这一层不包括光纤等硬件 ==
    - 链路层：负责传输数据帧，==能够进行差错控制，也能进行流量控制==，负责对网络层发送过来的数据包进行封装，只能够进行点到点的通信
    - 网络层：负责传输数据包，通常是 ip 协议，能够进行 == 流量控制、差错控制和拥塞控制 ==，负责对传输层次要求传输的数据报文进行封装传输，尽最大努力传输数据，但是不保证可靠交付
    - 传输层：负责传输数据报文（tcp）或者是数据报 (udp)，主要是 tcp/UDp 协议，对 tcp 能够进行差错控制和流量控制，并且能够自动分包，对 udp 不能，只能够加上源端口、ip 地址和目标端口和 ip 地址，尽最大努力交付，但是不可靠，不属于通信子网，也不属于资源子网，能够进行端到端的通信
    - 会话层：负责在对等的实体之间建立可靠的会话连接
    - 表示层：负责对传输的数据进行编码和解码，主要确定编码方式
    - 应用层：这个比较明显，面向用户通过服务

- TCP/IP 模型
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Nizqom.png)

- 区别和联系

  - osi 模型在网络层支持连接和无连接两种传输方式，在传输层只支持无连接的通信方式，tcp 模型在传输层支持两种传输方式，但是在网络层支持无连接传输方式

- 练习
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/9i7hZ3.png)
  - 插入同步点的行为发生在会话层
  - 链路层主要处理的是数据帧传输的顺序和正确性，对于用户和网络的接口，提供的是应用层；对于信号的传输，处理的是物理层；对于路由选择，控制的是网络层
  - 服务访问点：物理层的访问点就是网卡接口，链路层的 sap 就像是 mac 地址，网络层的 sap 就是 ip 地址，传输层的 sap 就是端口，应用层次就是用户界面

## 2. 物理层

### 2.1 通信基础

#### 2.1.1 常用术语

- 传输方式
  - 系带传输
    - 将数字信号 1 和 0 直接用电压表示，直接送到数字信道上传输
  - 宽带传输
    - 将基带信号经过调制之后形成部分评分服用模拟信号，送到模拟信道上传输

#### 2.1.3 编码方式

- 数字信号编码为数字

  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/QZfXTi.png)

  - 归零编码：使用高电平表示 1，使用低电平表示 0，每一个周期中间都需要进行归零来同步时钟

  - 非归零编码，中间不需要进行时钟的同步，避免了速率的浪费，但是需要双方使用时钟线同步时间
  - 反向非归零编码，每一个周期头如果发生变化，那么就是 0，否则就是 1，==USB2.0 使用的就是这个编码 ==
  - 曼彻斯特编码，对于一个周期，如果前高后低，那就是 1，否则就是 0，注意这里如果一个局域网传播的信号只有两种状态，信道的传播速率是 w 波特，那么实际的信息传播速率就是 w / 2 比特每秒，== 以太网使用的就是这种编码方式 ==
  - 和反向非归零码类似，如果是 1，那么和前一个周期的信号的后半个部分的波形相同，否则相反，能够实现自同步
  - 4/5b 编码，将每四个 bit 作为一个组合，添加一个 bit，有效传输速率（当然，不包括数据头的开销），是 80%，如果一个信道的极限传输速率是 5m，那么实际传输速率就是 4m

- 数字信号调制为模拟信号
  - ask，通过振幅表示 1 和 0，同意实现，但是抗干扰比较差
  - ask，改变频率表示 1 和 0，容易实现，抗干扰比较强
  - psk（相移键控，相位的应为就是 phase），改变相位表示 1 和 0。
  - == 正交振幅调制（QAM）==，组合使用 ask 和 fsk，比如波特率是 B，相位是 m 个，每个相位的振幅有 n 个，那么实际传播速率就是 $B*log_2{m n}$
- 模拟信号到数字信号
  - PCM，采样频率大于信号频率的两倍
- 模拟信号到模拟信号
  - FDM

#### 2.1.4 传输方式

- 虚电路方式（注意是物理层的）
  - 如果交换的数据包只是比较小的数据包，那么建立虚电路会比较浪费
  - 虚电路能够进行流量控制

- 习题

  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/LwPSlh.png)

    计算机内部用的十并行传输

  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/MmM6IC.png)

    这里如果使用奈奎斯特计算的话答案是 112kb/s，实际上这里不能用奈奎斯特计算，因为其要求已知信道带宽，但是这里没给出信道带宽，只说了采样频率，所以最后的答案就是 8k * 7 = 56k

  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/rikQwi.png)

    虚电路包传输的时候要携带一个 id

  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Usw8AY.png)

    首先是 b，虚电路是有永久性虚电路的，所以是临时性就是错的；数据报确实都要有两个地址
### 2.2 传输介质
#### 2.2.1 常用传输介质
- 双绞线
  - 长度为几到几十千米，绞是为了减少电磁干扰，如果是带金属丝屏蔽层的，那么叫做 stp，不然叫做 utp
  - 远距离传输的时候，如果是数字信号，那么需要用中继器对信号进行整形；如果是模拟信号，那么要用放大器放大衰减的信号
- 同轴电缆
  - 有更好的屏蔽能力和抗噪能力
  - 50Ω能够传输基带数字信号，75Ω用来传输宽带信号（有线电视）
- 光纤
  - 多模光纤
    - 使用光的全反射，适合近距离传输
  - 单模光纤
    - 光的直径减少到一个光的波长，适合远距离传输
#### 2.2.2 常用网络使用的介质
- 单词
  - 双绞线 twisted pair
  - 光纤 fiber
- 10BASE-T：双绞线 100m 以太网
- 10BASE-F：光纤 500m
- 10BASE-5：粗同轴电缆 500m
- 10BASE-2：细同轴电缆 185m
- 10BASE-TX：双绞线，100m
- 1000BASE-T：双绞线，100m
- 1000BASE-LX：单模光纤，3km
- 1000BASE-SX：多模光纤，300-550m
- 记忆方式
  - 有 T 的都是双绞线，双绞线长度都是 100m
  - 最后啥标志都没有的是同轴电缆，5 表示 500m，2 表示 185m
  - 最后三个就是 10Base-F 表示 500 米，LX 表示 3km 单模光纤 , SX 表示 300~550 米多模光纤
### 2.2.3 物理层接口特性
- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/cP1R23.png)
  - 答案是 C，同轴电缆的抗干扰性比较强
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/jNqVUZ.png)
  - 卫星通讯的缺点是成本高，时延长，收气候影响大，保密性差，误码率高
### 2.3 物理层网络设备
- 中继器
  - 能够对数字信号进行再生，理论上可以无限连接，实际上是有一定范围的
- 集线器
  - 只能够分割一个冲突域，如果一个 hub 链接了 n 个计算机，总带宽是 M，那么每个计算机的真正带宽是 $M / n$
- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/nLYhS4.png)
  转发器是物理层设备，本身不知道数据帧的概念，答案是 A
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/6Vi6VZ.png)
  5-4-3 规则
  - 集线器的拓扑结构是星型
  - 网段互联的要求
    - 如果是在物理层互联，那么传输速率要相同，但是链路层协议可以不同
    - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/xlvT1l.png) 答案是 C
## 3 链路层
### 3.1 功能
- 有确认的链接
- 有确认的无连接
- 无确认的无连接
- 相关概念
  - 帧定界：在数据帧的开始和结束的地方加上特定的比特流
  - MTU： 帧的数据部分的大小的上限
  - 透明传输：不论比特流是什么，链路层都要能够传
- 流量控制 ：协调发送方和接收方的速率（OSI 模型具有，但是 TCP 模型没有）
- 差错控制：CRC 计算，ARQ（重传输）
- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/CP5IgE.png)
    流量控制控制的是发送方的数据流量
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/iOndf5.png)
    首先，实时性要求高，需要使用无连接传输，其次比较可靠，那么不需要确认
### 3.2 组帧
- 方法
  - 字符计数法：在每一个帧头部加上数字，表示有几个字节（注意要加上自己，比如传输 abc，那么这就是 4），缺点是一个错，后面全错
  - 字符填充：在头尾加上一个特定的比特流，中间如果出现，那么加上一个转义字符
  - 比特填充：使用特定比特流（01111110）作为起止标志，中间每出现 5 个 1，就补上一个 0，接收者自动去掉这个 0
  - 违规编码：比如曼彻斯特编码中低 - 高表示 0，高 - 低表示 1，那么使用低低和高高表示起止，ieee 802 使用
### 3.3 差错控制
#### 3.3.1 检错编码
- 奇偶校验码：只能发现奇数个错误
- 循环冗余码：直接上图
- ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/YdUmBP.png)
#### 3.3.2 纠错编码
- 海明码
  - 纠错需要 2b + 1 位数，检错只需要 b + 1 位数
  - 假设 n 是有效信息位数，k 是检验位数，那么有 $n + k <= 2 ^k - 1$
- 习题
  - CRC 计算
  ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/4PFDij.png)
  注意这里在计算的开头要在原始字符串的尾巴加上对应的填充 0
### 3.4 可靠传输
- 协议
  - 停止等待协议
  - 后退 n 帧协议
  - 选择重传协议
- 注意上述三个协议的窗口大小即可
- 习题
  -  ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/P3fPBC.png)
    答案是 n-1，注意这里的窗口表示发送 + 接收窗口之和
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/wn2n20.png)
    注意 sr 协议中 ack 不是累计确认的，所以这里没有收到 0 和 2 的确认帧，认为接收方没有收到
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/IkwI6k.png)
    这里要注意最后一题，这个信道利用率过程中确认帧的传输时延不一定都是 0，这里使用捎带确认，确认真的传输时间就是 0.08ms
    ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/nLPO6y.png)
### 3.5 介质访问控制
#### 3.5.1 划分方式

![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/plF5mV.png)

1. FDM
   1. 将带宽分割为一个一个小块，中间插入保护段
   2. ![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/Pjb0Gw.png)
2. TDM 时间分割 将一秒分割为多个区段
   1. 如果用户个数 weiM，实际数据传输速率 weiN，那么每个用户的传输速率就是 N / M
3. STDM 对 TDM 的改进，动态调节用户分配到的时间片大小
4. WDM，光纤使用 不考虑
5. CDM，码分多域，每个用户分配到的站点的向量是正交的，接收端将收到的向量和用户分配到的向量做内积除以向量的模，如果为 1 就是 1，否则为 0

#### 3.5.2 随机介质访问控制
- ALOHA
  ![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/nHlP5q.png)

#### 3.5.3 CSMA 协议

![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/Ee1AF4.png)

1. 1 - 坚持

   1. 如果信道空闲，就直接发
   2. 如果不空闲，那么等到空闲直接发
   3. 碰撞，等待一段时间时间

2. 非坚持

   1. 空闲直接发
   2. 忙就等一段时间再来监听

3. p - 坚持

   1. 忙一直监听
   2. 空闲，p 概率直接发送，1-p 推迟到下一个 slot

   ![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/BotUPQ.png)

### 3.5.4 CSMA/CD

以太网最短帧长：51.2 us * 10m = 64B

二进制指数退避

![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/WTLJbQ.png)

### 3.5.5 CSMA/CA
- 802.11 无线网络中链路层使用停止 - 等待协议
- 802.11 定义了三种帧间间隔 ifs
  - sifs 最短的 ifs，包括 ack,cts, 分片后的数据帧和回答 ap 探寻的帧
  - pifs（点协调）：中等长度的 ifs，在 pcf 中使用
  - difs（分布式协调）， 
  
  - >1. 如果站点最初有数据要发送（注意是一开始，不是重传），信道空闲，等待 difs 之后发送整个数据帧
    >2. 否则执行 csma/ca 算法，用一个随机回退值，只有信道空闲的时候，计时器才会自减
    >3. 当退避计时器为 0，信道必然是空的，那么就发送
    >4. 如果收到确认帧，那么回到第二步，尝试发送下一帧
    >5. 如果没有收到 ack，那么回到第二步，尝试重传
- 隐蔽站处理方法
  - 在发送前，**广播**一个 rts 帧到 ap，如果信道空闲，ap 广播一个 cts 帧
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Rhary3.png) 注意这里的帧间间隔
### 3.5.6 令牌环网

![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/A8zFuq.png)

- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/R7iB10.png)
  答案是 D，因为在每一个 slot 中可以看做一个信号独占了信道，所以介质的速率应该大于单 s 个信号的位速率
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/YudAPk.png)
  这里答案是 B，fdm 主要传输模拟信号，tdm 传输数字信号
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/fioFEQ.png)
  计算公式 $800b = \frac{2 * \Delta L}{v}$, 计算得到结果是 80m，注意这里因为是往返的，所以右边的距离要乘上 2，不然就会错选 C
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/cXeJmS.png)
  注意这里，以太网一个数据帧的数据部分是 1500，所以计算的时候分子应该是 1500，不是 1518
### 3.6 局域网
#### 3.6.1 以太网结构的数据帧
- ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/IxGBRx.png)
- FCS 是用来做校验的，范围是不包括前导码的 mac 帧。
- 数据部分限制
  - 46： 最小帧长度是 64，64 - 18 = 46
  - 1500： 规定的，没有为什么
- 高速以太网： 速度超过 100Mb/s 的以太网叫做高速以太网
  - 100 Base T： 双绞线， 100Mb/s，全双工和半双工都可以，全双工模式下不使用 csmd/ca
  - 吉比特以太网：千兆以太网，全双工和半双工都可以
  - 10 吉比特以太网：只能全双工
#### 3.6.2 无线局域网 ieee 802.11
- mac 帧结构
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/iTD6AX.png)
  - 这里主要是三个地址之间的关系，如图
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/zmlGzu.png)
  - 记忆方式：首先三个地址存储的一定是来源地址，目的地址和 ap 地址，然后第一个地址存储的是当前发送的目的地，第二个地址存储的是当前帧的来源，那么就可以比较明显的记下来了
#### 3.6.4 vlan
- vlan 结构
  ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/avtiqd.png)
- 计算机自己不知道自己是用的哪一个 vlan，所以发送的都是标准的以太网帧，但是交换机知道，在转发给别的交换机的时候会将其封装成 802.1Q 帧，接收交换机会去掉 vlan 标签，将一个标准以太网帧转发给目标主机。（事实上是广播的）
- 注意上述例子中实一个 vlan 内部的通信，如果要实现跨 valn 的通信，需要使用上层路由器。
- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/rTUiaj.png)
    ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Xu5QiF.png)
    这里要注意的是，以太网的逻辑结构是总线型结构，使用的是无确认的无连接服务。然后是局域网只涉及下两层，广域网涉及下三层（路由器）
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/d6tHRw.png)
    同轴电缆的关键参数
    ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/DzyoDA.png)
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/E66Hjg.png)
    ieee 802 标准对应了 osi 模型的物理层和链路层
  - 无限局域网使用 csma/ca 的原因：不需要再发送的过程中进行检测

### 3.7 广域网技术
  - 广域网使用的协议
     - ppp 协议
      - LCP，管理数据链路
      - NCP，ppp 能够链接不同的网络层协议，对每一个不同的网络层协议建立一个 ncp 进行管理
      - 将 ip 数据包封装到串行链路上，受到 mtu 限制
      - 结构图
      ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Ti6OOK.png)
      - 只保证无差错，没有确认和序号机制
      - 只支持全双工点对点通信
    - hdlc 协议
      - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/ixmZSE.png)
      - 使用比特填充法
- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/U73hF1.png)
  注意报文交换技术和分组交换技术的区别，前者没有最大限制

### 3.8 链路层设备
- 网桥
  - 能够分割不同的冲突域
  - 能够互联不同的物理层、不同的 mac 子层和不同速率的以太网
- 局域网交换机
  - 能够进行学习，能够分割冲突域和广播域
  - 交换机能够独占带宽，所以如果一个交换机连接了 n 个计算机，那么总带宽就是 n * M
  - 部分交换机可以支持不同速率的网段的链接
  - 一般是全双工的，但是也可能是半双工的
- 区别
  - 交换机可以看做多个端口的网桥
  - 交换机允许多对计算机同时通信，但是网桥只允许同一个网段上的计算机同时通信
  - 网桥只能存储转发，但是交换机可以直通方式，交换机速度一般更快
- 基于 osi 模型物理层的设备（中继器，集线器）不能分割冲突域，也不能分割广播域
- 基于链路层的设备（交换机，网桥）能够分割冲突域，但是不能分割广播域，但是基于 vlan 的交换机能够隔离广播域
- 基于网络层的设备（路由器）两个都能分割
- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/dQy7Iq.png)
    这里主要是网桥的作用，网桥可以链接不同的物理层，不同的 mac 层和不同速率的以太网
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/9HQcCI.png)
    这里第二项容易误选成 B，注意这里通信是半双工的，所以实际上应该是 24 / 2 * 10M = 120M
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/mSVglP.png)
    这里注意以太网交换机本质上就是一个多端口网桥，然后就是交换机不能支持不同网络层协议的网络互联（但是链路层是可以的，比如广域网的 ppp 协议就可以链接不同的网络层协议），答案是 A
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/rYWfDK.png)
    这里注意直通交换只检查目标 mac 地址（6byte），那么实际上的转发时延就是 6 / 100M = 0.48us，剩下的数据可以视为直接穿过交换机
## 4 网络层（重量级的来了）
### 4.1 网络层介绍
#### 4.1.4 拥塞控制
- 判断是否拥塞的方法： 观察吞吐量和负载的关系，如果负载增加，吞吐量下降，那么说明进入了拥塞
- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Z1AuCH.png)
  路由器连接的异构网络指的是下三蹭的协议可以不同，但是上面的协议必须相同，答案是 D
### 4.2 路由协议（重量级）
- 距离 - 向量算法
  - 每一个节点定期将路由表转发给所有的**相邻节点**
  - 对一个节点来说
    - 如果收到的新路由表中存在一个原来没有映射的路由，那么添加
    - 如果新的路径更短，那么更新自己的路由表
  - 不适合大网络
  - 常见的算法是 RIP 算法
  - 有可能出现路由环路问题
- 链路状态路由算法
  - 常见的是 ospf 算法
  - 使用洪泛法向所有节点发送新的路由信息，收到的路由器向所有节点（不包括来源节点）发送新路由
- 区别：
  - 前者和所有直接邻居交谈，但是后者和**所有节点**交谈，不过只告诉直接相连的链路的 cost
- 层次路由
  - 内部网关协议（IGP），常见的有 rip 和 ospf 算法
  - 外部网关协议（egp），具体协议有 bgp
- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/zAkepx.png)
  如果在同一个子网，路由器就直接交付，否则需要交付给另一个路由器，就是间接交付，直接交付和路由器无关
### 4.3 ipv4
- ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/BgBbgf.png)
- 注意事项
  - 首部长度的单位是 4 字节
  - 总长度的单位是 1 字节
  - 标识，如果数据报分片，那么所有的分片的标识都是一样的
  - 标志：3bit，最低为是 mf，为 1 表示后面还有分片，中间表示是否允许分片
  - 片偏移：表示当前数据报距离开头的字节数，单位是 8byte
  - 协议：tcp 就是 6，udp 就是 17
- ARP 协议介绍
  - 工作在网络层，将 ip 地址映射为一个硬件地址（mac 地址）
  - 每一个主机都有一个 arp 缓存，缓存了 ip 到 mac 地址的映射
  - 主机发送数据包的时候，首先查看自己的缓存里是否有对应 ip 的 mac 地址，如果有，那么直接写入数据包，发送即可，否则发送一个目标 mac 为 ff-ff-ff-ff-ff-ff 的数据包（广播），对应 ip 地址的主机收到之后发送一个响应，包含自己的 mac 地址，发送方收到之后存到缓存里，然后之后就直接发送
  - 如果要跨网段，那么需要路由器参加，流程和上述过程不同。
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/7gp4w2.png)
- dhcp 协议介绍
  - 这是一个应用层协议，用来分发 ip 地址，基于 udp
  - 工作流程
    - 请求 ip 的主机发送一个源 ip 为 0.0.0.0，目标地址为 255.255.255.255 的数据报，寻找 dhcp 服务器
    - dhcp 服务器收到之后，发送一个响应消息，包含有提供的 ip 地址，原地址就是自己的地址，目标地址是 255.255.255.255
    - 请求方收到之后，如果接受这个 ip 地址，就发送一个 dhcp 请求，原地址是 0.0.0.0，目标地址是 255.255.255.255
    - dhcp 服务器之后广播 dhcp 确认消息，原地址就是自己的地址，目标地址就是 255.255.255.255
  - 分配的 ip 一段时间之后会过期
- icmp 协议介绍
  - 工作在网络层
  - 包含有
    - 终点不可达
    - 源点抑制（拥塞）
    - 时间超过（ttl 为 0 或者接收方在一定时间内不能收到所有的分片）
    - 参数问题
    - 重定向
  - 不发送 icmp 情况如下
    - 不是第一个分片
    - 不对 icmp 报文发送 icmp 报文
    - 组播
    - 特殊地址 127.0.0.0，0.0.0.0
- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/yDhf4V.png)
  原来这里出错的原因在于看到 A 选项最后有一个 255, 认为是个广播地址，事实上 A 不是广播地址，广播地址要求主机号都是 1，也就是说后面的 14 位都是 1；然后 BC 显然都是广播地址，D 就是一个组播地址
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/d29bJT.png)
  这里答案是 B，对于 A，显然这是一个主机号都是 0 的 C 类地址，那么不对；对 C，这是环回地址；对于 D，这是 C 类地址，但是出现了无效的 256
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/XC8Ts4.png)
  这里答案是 C，这是一个 C 类地址，那么掩码就是 / 24
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/VEbnMQ.png)
  nat 表中没有映射，那么不转发
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/nT1GmL.png)
  注意这里一开始以为两个数据包的数据部分都是 780bit, 然后想当然就选了 D，实际上由于片偏移需要是 8 的倍数，所以一个数据包中数据最多有 776bit，那么第二个分片的总长度就只有 796bit,mf 标志就是 1（因为后面还有一个）
### 4.4 ipv6 协议
#### 4.4.1 协议结构
- 部分特点
  - 首部必须是 8 的倍数
  - 不支持分片
  - 地址空间 2 ^ 128 位
### 4.5 路由协议
#### 4.5.1 RIP 协议
- 一个路径最多有 15 跳，如果一个路径有 16 跳，那么认为路径是飞发的
- 每 30 秒和相邻的使用 rip 协议的路由器交换一次路由表
- 所有网络的子网掩码必须相同（RIP1 是这样，RIP2 支持不同的子网掩码和 cidr）
- ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/aLKslp.png)
- 特点：
  - 只和相邻节点交换信息
  - 每隔固定时间交换一次
- 如果超过 180s 没有收到相邻路由器的信息，认为不可达，距离变为 16
- 优缺点
  - 容易实现，开销小，收敛比较快
  - 网络规模不大，最大距离 15
  - 交换的是完整的路由表，所以对大网络开销比较大
  - 坏消息传递比较慢
- rip 是应用层协议，使用 udp 传输（端口 520）
#### 4.5.4 开放最短路径 ospf 协议
- 使用洪泛法发送自己的路由表
- 发送的路由表只包含了自己相邻节点的 cost
- 只有路由表发生变化才会发送更新信息，否则不发送
- 不会出现 “坏消息传播慢” 问题
- 是网络层协议，使用 ip 传输
- 五种数据包
  - 问候数据包
  - 数据库描述数据包
  - 链路状态请求数据包
  - 链路状态更新数据包
  - 链路状态确认数据包
- 每隔一段时间，就刷新一次数据包。因为只需要交换相邻节点的信息，所以可以工作在大网络下
- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/5E5Lcm.png)
    bgp 交换的是路径信息
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/aGH2kP.png)
    rip 是距离向量，udp，ospf 是链路状态，ip，bgp 是路径向量，tcp
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/NOGBwJ.png)
    坏消息传得慢，R1 没有收到 R3 的消息，最终更新距离为 3，只能理解为 R1 也向 R2 发送了路由表
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/MJXZNI.png)
    第二题 ttl 计算结果为 61，注意 R1 自己也要减掉
    第三题是增加一个直连线路连接互联网，配置为 0.0.0.0/0,metris = 10
### 4.6 IP 组播
- 只适用于 UDP 协议
- 组播不产生 icmp，所以 ping 没有结果
- 链路层过滤不了，因为目标 mac 和 ip 的对应不是一对一的，所以必须要使用网络层进行过滤
- 使用 igmp 协议
  - 主机加入的时候，向组播地址发送一个 igmp 报文
  - 路由器会周期性轮询主机，如果多次没有响应，那么将其移出组
- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Cy5JUb.png)
    使用组播转发树避免环路
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/QmXDXr.png)
    组播地址到 mac 的映射方式
    组播地址的前三字节必然是 01-00-5E, 之后第一个 bit 必然是 0，之后的 23 位和 ip 地址的后 23 为相同，所以答案是 A
### 4.7 移动 ip
### 4.8 网络层设备
- 重要规律
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/dXtYwT.png)
- 习题
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/RAhkAF.png)
  - ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/BqYWyA.png)





>由题意知，发送窗口的总大小是($2 ^ {64}$)，光纤的传输速率是($75Tbs = 75 * 2^{40} b /s$)，那么发送这么多数据的总时间消耗就是
>$$
>\frac{2 ^ {64} * 8}{75 * 2 ^ {40}}s = 1789569.7066666668s
>$$
>上述结果近似等于497.1小时





## 错题



1. OSI模型为什么没普及：造价太高

2. T1载波

   ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/TXGtCK.png)

   结论就是T1载波的速率就是1.544Mbps

3. PPP协议

   ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/uSOeAs.png)

   可以省略control bit

4. SR协议发送窗口

   ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/tPcpYR.png)

   就是$2^{n-1}$

5. piggypacking

   ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/OD3IHi.png)

   这里是没注意到data这个单词，是捎带确认

6. 波特率

   ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/pe0jHl.png)

   波特率确实是两倍，当时是没注意到baud这个单词

7. CAMA/CA

   ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/9S18lS.png)

   对A,肯定要等待，避免和CTS碰撞；对B，没收到CTS，就是可以发

   对C，收到CTS不能发，没收到RTS可能是因为隐蔽站

   对D，受到CTS就不能发

8. RIP是内部网关协议，interior getway protocol

9. 链路状态路由算法

   ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/eWYyWn.png)

   使用洪泛法交换信息，不只是令居

10. 路由表

  ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Tk3KLm.png)

  原来选的是B，注意路由表最后一项写的是对方接口的地址

11. RIP到直连网络距离是1

12. dns记录格式

    1. ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/MAOXTr.png)
    2. SOA 授权信息
    3. TXT 文本信息
    4. MX 邮件服务器
    5. A IPv4地址

13. MIME协议传输类型

    1. ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/gpIVCS.png)
    2. 这里传输音频就是Audio/basic

14. MPLS (MultiProtocol Label Switching)

    1. the core concept of mpls is to add a label in front of each packet and doing the routing based on the label rather than on the destination address.We focused on adding a label in front of each packet and doing the routing based on the label rather than on the destination address.
    2. 根据label转发，而不是根据ip转发

15. DNS地址类型

    1. ![](https://cdn.nlark.com/yuque/0/2021/png/641515/1638467617642-2554041b-6351-47e2-a0c3-c0e49050ac5e.png?x-oss-process=image%2Fresize%2Cw_868%2Climit_0)

16. ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/TI0iT6.png)

17. ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/QbMxjz.png)

18. ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/S1DvaV.png)

19. vlan命令

20. ip命令

21. 判断题： One type of person-to-person communication often goes by the name of end-to-end communication, to distinguish it from the client-server model.

    错误，❌因为是peer-to-peer

22. 判断题： Rate-based flow control, the receiver sends back information to the sender giving it permission to send more data or at least telling the sender how the receiver is doing.

    错误，❌

23. 判断题：IETF has devised a simpler approach to quality of service, one that can be largely implemented locally in each router without advance setup and without having the whole path involved. This approach is known as flow- based quality of service.

    错误，❌

24. ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/SNcd7z.png)

    802.3的数据帧会转发给**冲突域**里面的所有设备

25. IEEE 802.3u定义了快速以太网和帧标记

26. 数据变化过程：Data, segment, packet, frame, bit

27. **各种电缆的长度**

    1. ![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/lTdIC3.png)

28. Which protocol used in PPP allows multiple Network layer protocols to be used during a connection?
     A. LCP
     **B. NCP** ☑️ ncp支持多种网络层协议
     C. HDLC
     D. X.25

29. The two-wire connections between each subscriber’s telephone and the end office are known in the trade as the____.
     A. trunk B. local loop C. link **D. switch ☑️**

30. Which protocol can connect the computer components together without wires? 

    A. 802.11
     **B. 802.15 ☑️**
     C. 802.16
     D. None of the above

31. Which is a connection-less network?

    A. X.25
     B. Frame Relay
     C. ATM
     **D. None of the above ☑️**

32. Which kind of satellites has the highest altitude?
     **A. GEO satellites ☑️**
     B. MEO satellites
     C. LEO satellites
     D. A, B, and C are equal

33. Given a code with only four valid codewords: 0000000000, 0000011111, 1111100000, 1111111111, how many errors can be corrected?
     A. 5
     B. 3
     **C. 2 ☑️ 编码距离是5**
     D. 1

34. Which is not derived from SDLC?
     A. HDLC
     B. LAP
     C. LAPB
     **D. 802.3 ☑️ 快速以太网 不是sdlc派生的**

35. Which is/are used for collision-free protocols? 

    A. Bit-map

    B. Binary countdown

    **C. Both A and B ☑️**

    D. Neither A or B

36. Which is incorrect?
     A. VC subnet requires circuit setup.
     B. VC subnet can guarantee QoS easily.
     C. VC subnet can avoid congestion problem easily.
     **D. VC subnet can handle router failure easily. ☑️ 迷惑**

37. the checksum in the IP packet covers ______. 

    **A. Just the header**

    B. Just the data
     C. The header and the data
     D. Just the source and destination addresses

38. What is the minimum number of bits that can be borrowed to form a subnet? (According to the latest RFC standards)

    **A. 1 ☑️**
     B. 2
     C. 4
     D. None of the above

39. Which of the following can NOT be used to traffic shaping? 

    **A. Overprovisioning ？☑️**

    B. Leaky bucket algorithm
     C. Token bucket algorithm
     D. Packet schedulin

40. To prevent silly window syndrome created by a receiver that processes data at a very slow rate, __________ can be used.
     **A. Clark’s solution ☑️ 不知道是啥**
     B. Nagle’s algorithm
     C. Both A and B
     D. Neither A or B

41. The __________ timer is needed to handle the zero window-sized advertisement.
     A. Retransmission
     **B. Persistence ☑️**
     C. Keepalive
     D. Time-waited

42. Which is more suitable for byte-by-byte encryption?
     A. Electronic code book mode
     B. Cipher block chaining mode
     **C. Cipher feedback mode ☑️**
     D. Stream cipher mode

43. Which tool can be used to analyze the fields of a network protocol?
     A. netstat
     B. ping
     **C. ethereal ☑️**
     D. tracert

44. what is wdm

    **A.) Multiplexing on fiber-optic cable. ☑️**

    B.) Multiplexing using the density of the transmission media. 

    C.) A form of flow control that monitors WAN delays.
    D.) A form of congestion management for WANs.

45. Which technology is not a type of wireless communication? 

    A.) Cellular

     **B.) Broadband ☑️** 宽带

    C.) Infrared
     D.) Spread spectrum

46. 802.11使用csma/ca

47. Which connector does UTP (Unshield Twised Pair) use? 

    A.) STP

    **B.) RJ-45 ☑️**

    C.) RJ-69
    D.) BNC

48. When the congestion is very seriously, which kind of control should be used? 

    A.) Warning bits
     B.) Load shedding
     **C.) Chocke packets ☑️**

    D.) Hop-by-hop chope packets

49. A notebook computer which connects to Internet via ADSL is . A. not wireless and not mobile **B. not wireless but mobile ☑️**
     C. wireless and not mobile D. wireless and mobile

50. Connectionless Services is also called  					.
     A. virtual circuit service B. Acknowledged datagram service C. client-server service **D. datagram service ☑️**

51. coaxial cable is commonly used for analog transmission and cable television. A. 50-ohm **B. 75-ohm ☑️** C. 300-ohm D. 120-ohm

52. Different Fourier components propagate at different speed, this leads to .
     A. attenuation B. crosstalk C. thermal noise **D. Delay distortion ☑️**

53. An E1 channel contains 32 PCM signals, its data rate is . 

    **A. 2.048 Mbps ☑️** 

    B. 1.544 Mbps

    C. 64kbps 

    D. 2.5 Gbps

54. A HDLC frame includes fields flag, address, control, data and

    **A. checksum ☑️** B. protocol C. LCP D. NCP

55. Which type of connector is used to connect thin coaxial cable to 10Base-2 network adapter card?

    A. RJ-11 B. RJ-80 transceiver **C BNC T-connector ☑️**

56. Carrier extension is a feature of Gigabit Ethernet to
     **A. increase the transmission distance ☑️** 

    B. increase the data rate

    C. enhance the reliability 

57. Suppose that the TCP congestion window is set to 18KB and a timeout occurs. How big will the window be if the next four transmission bursts are all successful? Assume that the maximum size of segment is 1KB.

    A. 4KB **B. 8KB ☑️** C. 9KB D. 16KB

58. 105.Which type of network does Frame Relay belongs to? 

    A) circuit switching
     B) message switching
     **C) packet switching ☑️**

    D) frequency switching

59. Which of the following can be a substitution for ADSL in future?

    A.) 802.3
    B.) 802.11
    C.) 802.5
    **D.) 802.16 ☑️**

60. (1). The sending sequence number of HDLC PDUs increments by 100 when 100 frames are sent, while the sending sequence number of TCP PDUs increments by 100 when 100 bytes are sent.
     (2). HDLC’s sending window uses a fixed value; TCP’s sending window uses a variable value which is determined by the header field “window-size ” of the TCP segment sent by receiver.

    (3). TCP uses three-way handshake to establish a connection. Some segment’s flag bit SYN is set to 1 during the period of connection establishment.
     (4). In TCP, when receiver sends a PDU with its field window-size set to 0, the sender should stop sending data; In HDLC, when receiver sends a PDU with its field type set to 2 which stands for RECEIVE-NOT-READY, the sender should stop sending data.


















- ip-sec
- castiong
  - multi-casting 组播
  - unicasting 单播
  - anycasting
  - broadcasting 广播
- 0~1023之间一些协议的端口
- 密码学加密算法
- RTP、FORM协议
  - rtp: real-time protocol
  - form: 貌似是表单
- dns格式









>1. Which of the following can a VLAN be considered? 
>
>   A.) Broadcast domain
>    B.) Collision domain
>    C.) Both a broadcast and a collision domain
>
>   D.) Domain name
>
>

>28. Which of the following is true of a switch’s function?
>A.) Switches increase the size of a collision domains.
>B.) Switches combine the connectivity of a hub with the capability to filter
>or flood traffic based on the destination MAC address of the frame.
>C.) Switches combine the connectivity of a hub with the traffic direction of
>a router.
>D.) Switches perform Layer 4 path selection.
>
>

>1. Which of the following is not a feature of microsegmentation?
>    A.) It enables dedicated access.
>    B.) It supports multiple conversions at any given time.
>    C.) It increases the capacity for each workstation connected to the network. D.) It increases collisions.

>1. Media Access Control refers to what?
>    A.) The state in which a NIC has captured the networking medium and is ready to transmit
>
>   B.)  Rules that govern media capture and release
>
>​	C.)  Rules that determine which computer on a shared-medium environment is allowed to transmit the data
>
>​	D.)  A formal byte sequence that has been transmitted.
>
>

>1. Which best describes a CSMA/CD network?
>
>   1. A.)  One node’s transmission traverses the entire network and is received and examined by every node.
>
>   2. B.)  Signals are sent directly to the destination if the source knows both the MAC and IP addresses
>
>   3. C.)  One node’s transmission goes to the nearest router, which sends it
>
>      directly to the destination.
>
>   4. D.)  Signals always are sent in broadcast mode.
>
>

>1. The subnet mask for a class B network is 255.255.255.192. How many subnetworks are available? (Disregard special addresses)
>    A.) 2
>    B.) 4
>
>   C.) 1024
>    D.) 192
>
>

>1. Which of the following can be used to connect a keyboard with a computer? A.) 802.3
>
>   ```
>       B.) 802.11
>       C.) 802.15
>       D.) 802.16
>   ```
>
>

>1. Which of the following can be used as the wireless local loop for public switched telephone systems?
>    A.) 802.3
>    B.) 802.11
>
> C.) 802.15
> D.) 802.16
> 
> 

>1. What is one advantage of distance vector algorithms?
>    A.) They are not likely to count to infinity.
>    B.) You can implement them easily on very large networks. C.) They are not prone to routing loops.
>    D.) They are computationally simple
>
>

>一堆默认端口

repeater 中继器

















