# DB exercise 

3200105872 庄毅非

##### 18.1  Show that the two-phase locking protocol ensures conflict serializability and that transactions can be serialized according to their lock points.

答案：

使用反证法证明二阶段锁协议可以保证冲突可串行化。

1. 假定二阶段锁协议不能够保证冲突可串行化，那么在其前驱图中必然存在至少一个环。

2. 对于前驱图而言，一条边上的两个节点(假定为$T_1 \rightarrow T_2$)是存在冲突的，可能是在同一个属性上执行了写写，读写和写读三种操作。但是一定有$T_1$的lock point早于$T_2$的lock point（可以由二阶段锁协议的定义得到）。
3. 那么如果存在环，最后就会得到$T_1$的lock point小于$T_1$的lock point，这显然是矛盾的，所以二阶段锁协议可以保证冲突可串行化。



通过以上过程可以知道，在一个调度中各个事务的lock point的先后顺序对应了前驱图的一个偏序，那么可以通过将事务按照lock point进行串行排布得到一个串行调度。





##### 18.7  Consider a database system that includes an atomic increment operation, in addition to the read and write operations. Let V be the value of data item X. The operation increment(X) by C sets the value of X to V + C in an atomic step. The value of X is not available to the transaction unless the latter executes a read(X). Assume that increment operations lock the item in increment mode using the compatibility matrix in Figure 18.25.

1. Show that, if all transactions lock the data that they access in the corresponding mode, then two-phase locking ensures serializability.

答案：

​	观察可以发现，如果调度中的两个操作在同一个属性上都有I类型锁，那么这两个操作是可以交换的（可以从兼容性表中得知），也就是说任意两个increment操作是可以交换的。所以我们总可以通过交换 increment 指令来实现串行化调度。

2. Show that the inclusion of increment mode locks allows for increased concurrency.

答案：

​	在兼容性表中添加了I类型锁的相关信息之后，由于I类型锁和I类型锁之间是兼容的（也就是说，不同的事务都可以在一个属性上持有I类型锁），这样就允许多个事务执行并发的自增操作。如果没有I类型锁而仅仅只有S和X类型锁，那么一个事务在执行自增操作的时候，由于取得了X锁，其他要执行自增操作的事务必然需要等待，这样就降低了系统的并发执行能力。

​	综上，添加了I类型锁之后，系统的并发程度增加了。





##### 18.18 Most implementations of database systems use strict two-phase locking. Suggest three reasons for the popularity of this protocol.

答案：
	1. 二阶段锁协议容易实现
	1. 严格的二阶段锁协议保证了数据库调度的可恢复性，避免了级联回滚的出现
	1. 在使用严格的二阶段锁协议的同时，系统的并发执行能力仍然比较强。