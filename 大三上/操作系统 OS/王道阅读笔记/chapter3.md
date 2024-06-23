# 内存管理

## 1. 虚拟内存

- 虚拟内存的最大容量和地址空间有关，比如是64位寻址的，那么最大容量就是2^64

- 虚拟内存的逻辑容量和内外存大小和cpu寻址空间相关，一般取两者中的更小值。

- 堆栈类算法理论上不会有belady现象，队列类可能有（比如fifo）

- 页表相关计算

  ![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/rt8FcF.png)

  计算方式如下

  >显然页内偏移是12位，那么虚拟页号为36位，使用多级页表的时候，第一级页表不能大于一页，而每页能够容纳的页项最多为4096 / 8 = 512 = 2^9个，那么就需要36 / 9 = 4级页表

- 相关错题

  - ![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/sIvj14.png)

    >这里的问题在于引发缺页中断的指令一般是read指令，那么中断处理结束后之后应该回到read指令，也就是被中断的那一条。

  - 内存访问所需要的时间相关计算

    ![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/vNca3J.png)

    >![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/J23j5A.png)
    >
    >这里要注意的是就算tlb命中了，我们拿到的也只是物理页面地址，还要访问一次内存获取数据

  - 加入缺页中断之后的访问时间相关计算

    ![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/mrLkK2.png)

    >![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/h3q7Pp.png)
    >
    >这里要注意的是，缺页中断处理只会将数据读入内存之后刷新tlb和页表，还需要我们读内存，所以这里要加上1us。如果题中给出tlb访问时间为1ns，那么时间还需要改为8us + 1ns + 1us