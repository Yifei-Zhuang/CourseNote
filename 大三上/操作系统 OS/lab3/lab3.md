# Lab 3: RV64 内核线程调度

**课程名称:**操作系统
**指导老师:**寿黎但

**姓名**:

 庄毅非 3200105872
 胡競文 3200105990 

**分工**:

 胡競文 两种调度算法实现、线程初始化

 庄毅非 switch_to和__switch_to函数实现，do_timer函数实现

## 1 实验目的

- 了解线程概念, 并学习线程相关结构体, 并实现线程的初始化功能。
- 了解如何使用时钟中断来实现线程的调度。
- 了解线程切换原理, 并实现线程的切换。
- 掌握简单的线程调度算法, 并完成两种简单调度算法的实现。

## 2 实验环境

- Environment in previous labs

## 3 实验步骤

### 3.1 线程初始化

初始化函数实现如下。

```c
void task_init()
{
    // printk("Begin!\n");
    // 1. 调用 kalloc() 为 idle 分配一个物理页
    idle = (struct task_struct *)kalloc();
    // printk("Allocate success!\n");

    // 2. 设置 state 为 TASK_RUNNING;
    idle->state = TASK_RUNNING;
    // 3. 由于 idle 不参与调度 可以将其 counter / priority 设置为 0
    idle->counter = 0;
    idle->priority = 0;
    // 4. 设置 idle 的 pid 为 0
    idle->pid = 0;
    // 5. 将 current 和 task[0] 指向 idle
    current = idle;
    task[0] = idle;
    /* YOUR CODE HERE */

    // 1. 参考 idle 的设置, 为 task[1] ~ task[NR_TASKS - 1] 进行初始化
    // 2. 其中每个线程的 state 为 TASK_RUNNING, counter 为 0, priority 使用 rand() 来设置, pid 为该线程在线程数组中的下标。
    // 3. 为 task[1] ~ task[NR_TASKS - 1] 设置 `thread_struct` 中的 `ra` 和 `sp`,
    // 4. 其中 `ra` 设置为 __dummy （见 4.3.2）的地址,  `sp` 设置为 该线程申请的物理页的高地址
    for (int i = 1; i <= NR_TASKS - 1; ++i)
    {
        task[i] = (struct task_struct *)kalloc();
        task[i]->state = TASK_RUNNING;
        task[i]->counter = 0;
        task[i]->priority = rand();
        task[i]->pid = i;
        task[i]->thread.ra = (uint64)__dummy;
        task[i]->thread.sp = (uint64)task[i] + PGSIZE;
        // printk("SET [PID = %d] COUNTER = %d\n", task[i] -> pid, task[i] -> counter);
    }
    /* YOUR CODE HERE */
    printk("...proc_init done!\n");
}
```

### 3.2 __dummy与dummy函数

dummy函数添加如下。

```c
void dummy()
{
    uint64 MOD = 1000000007;
    uint64 auto_inc_local_var = 0;
    int last_counter;
    last_counter = -1;
    printk("dummy::\n");
    while (1)
    {
        if (last_counter == -1 || current->counter != last_counter)
        {
            last_counter = current->counter;
            auto_inc_local_var = (auto_inc_local_var + 1) % MOD;
            printk("[PID = %d] is running. auto_inc_local_var = %d\n", current->pid, auto_inc_local_var);
        }
    }
}
```

__dummy函数实现如下。

```asm
	.global __dummy
__dummy:
# 将dummy函数地址加载到t0寄存器中
    la t0, dummy
# 将t0写入sepc寄存器中
    csrw sepc,t0
# 调用sret，线程从中断中返回，并将pc设定为sepc中的值（即 dummy ），这样使线程运行在dummy的while部分中。
    sret
```

### 3.3 实现线程切换

`switch_to`实现如下。

```c
void switch_to(struct task_struct *next)
{
    // 如果要切换的下一个线程和当前线程相同，那么直接返回
    if (next == current)
        return;
    else
    {
        // 将当前线程切换为下一个线程，调用汇编函数进行线程切换
        struct task_struct *pre = current;
        current = next;
        __switch_to(pre, next);
    }
}
```

`__switch_to`实现如下

```asm
.globl __switch_to
__switch_to:
# save state to prev process
# YOUR CODE HERE
# here, t0 is current, and t1 is next(
# TODO( change to a0 and a1?)
# 保存ra寄存器
sd ra, 5 * 8(a0)
# 保存sp寄存器
sd sp, 6 * 8(a0)
# 保存剩下的12个caller-saved寄存器
sd s0 , 7 * 8(a0)
sd s1 , 8 * 8(a0)
sd s2 , 9 * 8(a0)
sd s3 , 10 * 8(a0)
sd s4 , 11 * 8(a0)
sd s5 , 12 * 8(a0)
sd s6 , 13 * 8(a0)
sd s7 , 14 * 8(a0)
sd s8 , 15 * 8(a0)
sd s9 , 16 * 8(a0)
sd s10 , 17 * 8(a0)
sd s11 , 18 * 8(a0)
# restore state from next process
# YOUR CODE HERE
# 加载另一个线程的ra寄存器
ld ra, 5 * 8(a1)
# 加载另一个线程的sp寄存器
ld sp, 6 * 8(a1)
# 加载另一个线程的sx寄存器
ld s0 , 7 * 8(a1)
ld s1 , 8 * 8(a1)
ld s2 , 9 * 8(a1)
ld s3 , 10 * 8(a1)
ld s4 , 11 * 8(a1)
ld s5 , 12 * 8(a1)
ld s6 , 13 * 8(a1)
ld s7 , 14 * 8(a1)
ld s8 , 15 * 8(a1)
ld s9 , 16 * 8(a1)
ld s10 , 17 * 8(a1)
ld s11 , 18 * 8(a1)
ret
```

### 3.4 实现调度入口函数

`do_timer`函数实现如下

```c
void do_timer(void)
{
    // 1. 如果当前线程是 idle 线程 直接进行调度
    // 2. 如果当前线程不是 idle 对当前线程的运行剩余时间减1 若剩余时间仍然大于0 则直接返回 否则进行调度
    if (current == idle)
    {
        printk("idle process is running!\n\n");
        schedule();
    }
    else if (--(current->counter) == 0)
    {
        schedule();
    }
}
```

在`trap_handler`中添加`do_timer`函数调用，启动线程切换。

```c
#include "clock.h"
#include "printk.h"
#include "proc.h"
void trap_handler(unsigned long scause, unsigned long sepc)
{
    if ((scause >> 63) & 1)
    {
        if ((scause & 5) == 5)
        {
            clock_set_next_event();
            do_timer();
        }
    }
}

```

### 3.5 实现线程调度

#### 3.5.1  短作业优先调度(SJF)算法

- 历线程指针数组`task`(不包括 `idle` , 即 `task[0]` ), 在所有运行状态 (`TASK_RUNNING`) 下的线程运行剩余时间`最少`的线程作为下一个执行的线程。
- 如果`所有`运行状态下的线程运行剩余时间都为0, 则对 `task[1]` ~ `task[NR_TASKS-1]` 的运行剩余时间重新赋值 (使用 `rand()`) , 之后再重新进行调度。

```c
#ifdef SJF
void schedule(void) {
    /* YOUR CODE HERE */
    printk("time chedule!\n");
    int flag = 0;
    int t = 0, mint = 1000000007;
    // printk("schedule:: begin for %d, %d\n", 1, NR_TASKS - 1);
    for (int i = 0; i <= NR_TASKS - 1; ++i) {
        // 遍历线程列表，寻找持有最小非负counter的线程id
        if((task[i] -> state == TASK_RUNNING) && (task[i] -> counter != 0)) {
            // printk("schedule:: i = %d, ok!\n", i);
            flag = 1;
            if (task[i] -> counter < mint) {
                t = i;
                // 更新mint值
                mint = task[i] -> counter;
            }
        }
    }
    // printk("schedule:: end for\n");
    // 如果flag为真，那么找到了所需的持有最小非负counter的线程，进行线程切换
    if(flag) {
        printk("switch to [PID = %d COUNTER = %d]\n", task[t] -> pid, task[t] -> counter);
        switch_to(task[t]);
    }
    // flag为false，说明所有线程的counter均为0，那么重新初始化所有线程（除idle）的counter，调用schedule函数重新进行线程调度
    else {
        for (int i = 1; i < NR_TASKS; i++) {
            task[i]->counter = rand();
            printk("SET [PID = %d COUNTER = %d]\n", task[i]->pid, task[i]->counter);
        }
        schedule();
    }
}
#endif

```



### 3.5.2 优先级调度算法

```c
#ifdef PRIORITY
void schedule(void)
{
    /* YOUR CODE HERE */
    // printk("priority schedule!\n");
    int flag = 0;
    int t = 0, maxp = 0;
    // printk("schedule:: begin for %d, %d\n", 1, NR_TASKS - 1);
    for (int i = 0; i <= NR_TASKS - 1; ++i)
    {
        // 遍历线程列表，寻找持有非负counter，并且优先级最高的的线程id
        if ((task[i]->state == TASK_RUNNING) && (task[i]->counter != 0))
        {
            // printk("schedule:: i = %d, ok!\n", i);
            flag = 1;
            if (task[i]->priority >= maxp)
            {
                t = i;
                maxp = task[i]->priority;
            }
        }
    }
    // printk("schedule:: end for\n");
    // 如果flag为真，那么找到了所需持有非负counter，并且优先级最高的的线程id，进行线程切换
    if (flag)
    {
        printk("switch to [PID = %d PRIORITY = %d COUNTER = %d]\n", task[t]->pid, task[t]->priority, task[t]->counter);
        switch_to(task[t]);
    }
    else
    {
        for (int i = 1; i < NR_TASKS; i++)
        {
            // flag为false，说明所有线程的counter均为0，那么重新初始化所有线程（除idle）的counter，调用schedule函数重新进行线程调度
            task[i]->counter = rand();
            printk("SET [PID = %d PRIORITY = %d COUNTER = %d]\n", task[i]->pid, task[i]->priority, task[i]->counter);
        }
        schedule();
    }
}
#endif
```

### 3.6 程序输出

#### 3.6.1 SJF调度

![image-20221025224238645](../../../../../../Library/Application Support/typora-user-images/image-20221025224238645.png)



#### 3.6.2 优先级调度

![image-20221025224123824](../../../../../../Library/Application Support/typora-user-images/image-20221025224123824.png)



## 4. 思考题

### 4.1 在 RV64 中一共用 32 个通用寄存器, 为什么 `context_switch` 中只保存了14个 

>答：
>
>  在本lab的实现中，线程的上下文切换逻辑如下。
>
>  程序触发时钟中断，保存32个寄存器，设定好sepc和sscause之后切换到trap_handler中->trap_handler设定好下一次时钟中断的时间，调用do_timer进入线程调度逻辑->do_timer根据线程的剩余counter判断是否需要进行线程切换->如果需要进行切换，那么在schedule中选择下一个需要切换到的线程->switch_to中进行对应切换逻辑->__switch_to中进行相关寄存器的保存和恢复，执行线程切换。
>
>  从上述过程中可以发现，被时钟中断打断的线程本身在中断地址所持有的32个寄存器在最初的__traps中已经被保存，最终也会被恢复；又因为32个寄存器中只有12个s系列寄存器、sp寄存器和ra寄存器是callee-saved寄存器，剩下的都不是callee-saved寄存器所以对于被切换的线程而言，其没有必要存储所有的寄存器，只需要保存这对应的14个寄存器即可。
>
>

### 4.2 当线程第一次调用时, 其 `ra` 所代表的返回点是 `__dummy`。 那么在之后的线程调用中 `context_switch` 中, `ra` 保存/恢复的函数返回点是什么呢 ？ 请同学用 gdb 尝试追踪一次完整的线程切换流程, 并关注每一次 `ra` 的变换 (需要截图)。

这里主要是对线程3（系统中运行的第一个非idle线程）的追踪

1. 在第一次线程3触发时钟中断的时候，对于跳转到`_traps`中的的线程3，其ra保存的是其触发时钟中断的时候所运行的代码段，在这里就是`dummy`函数的一段

![image-20221025230622608](../../../../../../Library/Application Support/typora-user-images/image-20221025230622608.png)

2. 在保存了线程所使用的32个寄存器之后，线程调用`call trap_handler`切换到中断处理函数中，这时候的ra寄存器保存的是上述call指令的地址，在这里是`_traps+152`

   ![image-20221025231204655](../../../../../../Library/Application Support/typora-user-images/image-20221025231204655.png)

3. 之后`trap_handler`调用`clock_set_timer`函数设定下一次时钟中断的时间，这里ra再一次发生变化，变为函数调用点点的地址。

   ![image-20221025231617350](../../../../../../Library/Application Support/typora-user-images/image-20221025231617350.png)

4. 在`clock_set_timer`函数中调用了`sbi_ecall`，这里ra再次变化，变为`jal sbi_ecall`指令的地址

   ![image-20221025231740438](../../../../../../Library/Application Support/typora-user-images/image-20221025231740438.png)

5. 在执行完`sbi_ecall`之后，函数一路返回，ra寄存器也沿着调用栈一路被恢复，到`trap_handler`中时，可以发现此时的ra寄存器恢复为了_traps中调用trap_handler函数的指令的地址。

   ![image-20221025231942307](../../../../../../Library/Application Support/typora-user-images/image-20221025231942307.png)

6. 接下来分析线程时间片用完之后的ra变化情况。如图，这里线程3用尽了初始的5个counter。

   ![image-20221025232101958](../../../../../../Library/Application Support/typora-user-images/image-20221025232101958.png)

7. 首先线程进入_traps和trap_handler以及clock_set_timer进行相关属性的设定，这里ra的变化情况和上述过程一致。

8. 在进入do_timer函数的时候，这时候线程ra设定为trap_handler函数中jal do_timer指令的下一句指令的地址。

   ![image-20221025232532827](../../../../../../Library/Application Support/typora-user-images/image-20221025232532827.png)

9. 由于线程的counter已经为耗尽，线程随后切换到schedule函数中，在这里线程的ra寄存器保存的是do_timer中调用schedule函数的指令的下一条指令的地址![](../../../../../../Library/Application Support/typora-user-images/image-20221025232808593.png)

10. 在执行切换逻辑的switch_to函数中，这里ra寄存器保存的是schedule函数中调用其的指令的下一条指令的地址。![image-20221025232814593](../../../../../../Library/Application Support/typora-user-images/image-20221025232814593.png)

11. 在switch_to函数中，我们会调用__switch_to函数进行真正的上下文切换，这里ra保存的是switch_to函数中调用指令的下一条指令的地址。

    ![image-20221025233036997](../../../../../../Library/Application Support/typora-user-images/image-20221025233036997.png)

12. 在执行完切换逻辑之后，程序使用ret返回，这时候会返回到切换到的进程的ra的地址，由于是第一次被切换到，所以这里程序跳转到了_\_dummy逻辑中，这时候ra的值就是\_\_dummy的地址![image-20221025233315138](../../../../../../Library/Application Support/typora-user-images/image-20221025233315138.png)

13. 最后，在执行了sret指令之后，程序进入dummy函数中，这时候ra寄存器保存的就是__dummy的地址。

    ![image-20221025233433032](../../../../../../Library/Application Support/typora-user-images/image-20221025233433032.png)