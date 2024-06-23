# Lab 4:RV64 虚拟内存管理

课程:操作系统

指导老师:寿黎但

班级:软件工程2003 

姓名:庄毅非 3200105872胡競文 3200105990

分工:
 庄毅非:负责 setup_vm 和 head.S 的编写
 胡競文:负责 setup_vm_final 和 create_mapping 的编写

## 1. 实验目的

学习虚拟内存的相关知识，实现物理地址到虚拟地址的切换。
 了解 RISC-V 架构中 SV39 分页模式，实现虚拟地址到物理地址的映射，并对不同的段进行相应的 权限设置。

## 2. 实验环境

 Environment in previous labs

## 3. 实验过程

### 3.1 准备工程

`vm.c`

```c
void setup_vm(void)
{
    /*
    1. 由于是进行 1GB 的映射 这里不需要使用多级页表
    2. 将 va 的 64bit 作为如下划分： | high bit | 9 bit | 30 bit |
        high bit 可以忽略
        中间9 bit 作为 early_pgtbl 的 index
        低 30 bit 作为 页内偏移 这里注意到 30 = 9 + 9 + 12， 即我们只使用根页表， 根页表的每个 entry 都对应 1GB 的区域。
    3. Page Table Entry 的权限 V | R | W | X 位设置为 1
    */
    // 低地址映射
    unsigned long index = (PHY_START >> VPN2OFFSET) & MUSK;
    early_pgtbl[index] = ((PHY_START >> VPN2OFFSET) & 0x3ffffff) << 28;
    early_pgtbl[index] |= (VALID | READABLE | WRITABLE | EXECUTABLE);

    // 高地址映射
    index = ((PHY_START + PA2VA_OFFSET) >> VPN2OFFSET) & MUSK;
    early_pgtbl[index] = ((PHY_START >> VPN2OFFSET) & 0x3ffffff) << 28;
    early_pgtbl[index] |= (VALID | READABLE | WRITABLE | EXECUTABLE);
}

```

`head.S`

```asm
relocate:
    # set ra = ra + PA2VA_OFFSET
    # set sp = sp + PA2VA_OFFSET (If you have set the sp before)

    ###################### 
    #   YOUR CODE HERE   #
    ######################
    // 将ra和sp修改为虚拟内存高地址映射中的地址
    li t0,PA2VA_OFFSET;
    add ra,ra,t0;
    add sp,sp,t0;
    # set satp with early_pgtbl
    # 设置satp模式为rv39
    add t1,zero,zero;
    ori t1,t1,1;
    slli t1,t1,63;
    # 设置satp中的ppn
    la t0,early_pgtbl;
    srli t0,t0,12;
    add t0,t0,t1
    # 开启虚拟内存
    csrw satp,t0;
    ###################### 
    #   YOUR CODE HERE   #
    ######################

    # flush tlb
    sfence.vma zero, zero
	fence.i
    ret
```

### 3.2 `setup_vm_final`的实现

```c
void create_mapping(unsigned long *pgtbl, unsigned long va, unsigned long pa, unsigned long sz, int perm)
{
    /*
    pgtbl 为根页表的基地址
    va, pa 为需要映射的虚拟地址、物理地址
    sz 为映射的大小, represents bits of current slice
    perm 为映射的读写权限

    创建多级页表的时候可以使用 kalloc() 来获取一页作为页表目录
    可以使用 V bit 来判断页表项是否存在
    */
    // 存储已经完成映射的页面的总大小
    int mapped = 0;
    while (mapped < sz)
    {
        unsigned long *pglevel2 = swapper_pg_dir;
        unsigned long vpn2 = (va >> VPN2OFFSET) & MUSK;
        // 如果本级页表不存在，那么分配一个新的物理页
        if ((pglevel2[vpn2] & VALID) == 0)
        {
            unsigned long pglevel1 = (unsigned long)(kalloc());
            pglevel2[vpn2] = ((((pglevel1 - PA2VA_OFFSET) >> 12) << 10) | VALID);
        }
        unsigned long *pglevel1 = (unsigned long *)((pglevel2[vpn2] >> 10) << 12);
        unsigned long vpn1 = (va >> VPN1OFFSET) & MUSK;
        // 如果本级页表不存在，那么分配一个新的物理页
        if ((pglevel1[vpn1] & VALID) == 0)
        {
            unsigned long pglevel0 = (unsigned long)(kalloc());
            pglevel1[vpn1] = ((((pglevel0 - PA2VA_OFFSET) >> 12) << 10) | VALID);
        }
        unsigned long *pglevel0 = (unsigned long *)((pglevel1[vpn1] >> 10) << 12);
        unsigned long vpn0 = (va >> VPN0OFFSET) & MUSK;
        pglevel0[vpn0] = ((pa >> 12) << 10) | perm;
        mapped += PGSIZE;
        va += PGSIZE;
        pa += PGSIZE;
    }
}


void setup_vm_final(void)
{
    memset(swapper_pg_dir, 0x0, PGSIZE);

    // No OpenSBI mapping required

    unsigned long pm_pointer = PHY_START + OPENSBI_SIZE;
    unsigned long vm_pointer = VM_START + OPENSBI_SIZE;
    // mapping kernel text X|-|R|V
    create_mapping(swapper_pg_dir, vm_pointer, pm_pointer, _srodata - _stext, EXECUTABLE | READABLE | VALID);
    pm_pointer += _srodata - _stext;
    vm_pointer += _srodata - _stext;
    // mapping kernel rodata -|-|R|V
    create_mapping(swapper_pg_dir, vm_pointer, pm_pointer, _sdata - _srodata, READABLE | VALID);
    pm_pointer += _sdata - _srodata;
    vm_pointer += _sdata - _srodata;
    // mapping other memory -|W|R|V
    create_mapping(swapper_pg_dir, vm_pointer, pm_pointer, 0x80000000 - (_sdata - _stext), WRITABLE | READABLE | VALID);

    // pm_pointer += 0x80000000 - (_sdata - _stext);
    unsigned long phypg = (unsigned long)swapper_pg_dir - PA2VA_OFFSET;
    // set satp with swapper_pg_dir
    __asm__ volatile(
        "add t1, zero, zero\n"
        "ori t1, t1, 1\n"
        "slli t1, t1, 63\n"
        "mv t0, %[phypg]\n"
        "srli t0, t0, 12\n"
        "add t0, t0, t1\n"
        "csrw satp, t0\n"
        :
        : [phypg] "r"(phypg)
        : "memory");
    // YOUR CODE HERE
    printk("setup_vm_final finish\n");
    // flush TLB
    __asm__ volatile("sfence.vma zero, zero");
    return;
}

```

## **4.** 思考题

#### 1. 验证 .text , .rodata 段的属性是否成功设置，给出截图。

>我们实现了`print_vm`和`print_helper`两个辅助函数，用来输出页表中指定区间合法项的信息以及权限，实现如下。
>
>```c
>// 输出指定区间中合法项的信息（起止位置，物理地址等）以及对应的权限控制信息
>void print_helper(unsigned long begin, unsigned long end)
>{
>    for (unsigned long vm_pointer = begin; vm_pointer <= end; vm_pointer += PGSIZE)
>    {
>        unsigned long pte1 = swapper_pg_dir[(vm_pointer >> VPN2OFFSET) & MUSK];
>        if (pte1 & VALID)
>        {
>            printk("%lx: PTE_V:%d\n", ((pte1 >> 10) << 12) + PA2VA_OFFSET, pte1 & VALID);
>            unsigned long pte2 = ((unsigned long *)(((pte1 >> 10) << 12) + PA2VA_OFFSET))[(vm_pointer >> VPN1OFFSET) & MUSK];
>            if (pte2 & VALID)
>            {
>                // printk("\t%lx: PTE_V:%d\n", ((pte2 >> 10) << 12) + PA2VA_OFFSET, pte2 & VALID);
>                unsigned long pte3 = ((unsigned long *)(((pte2 >> 10) << 12) + PA2VA_OFFSET))[(vm_pointer >> VPN0OFFSET) & MUSK];
>                if (pte3 & VALID)
>                {
>                    printk("\t\t%lx: PTE_V:%d,PTE_R:%d,PTE_W:%d,PTE_X:%d\n", ((pte3 >> 10) << 12) + PA2VA_OFFSET, !!(pte3 & VALID), !!(pte3 & READABLE), !!(pte3 & WRITABLE), !!(pte3 & EXECUTABLE));
>                }
>            }
>        }
>    }
>}
>// 输出指定的text段和rodata段的信息
>void print_vm()
>{
>    unsigned long textStart = PGROUNDUP(((unsigned long)(VM_START + OPENSBI_SIZE)));
>    unsigned long textEnd = PGROUNDDOWN(((unsigned long)(VM_START + OPENSBI_SIZE + _srodata - _stext - 1)));
>    printk("kernel text:\n");
>    print_helper(textStart, textEnd);
>    printk("\n");
>    unsigned long roDataStart = PGROUNDUP((unsigned long)(VM_START + OPENSBI_SIZE + _srodata - _stext));
>    unsigned long roDataEnd = PGROUNDDOWN((unsigned long)(VM_START + OPENSBI_SIZE + _sdata - _stext - 1));
>    printk("kernel rodata:\n");
>    print_helper(roDataStart, roDataEnd);
>    printk("\n");
>}
>```
>
>代码运行截图如下。
>
>![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/gcfV7l.png)
>
>可以看到，kernel text段的权限被正确设置为RWXV，kernel rodata段的权限被正确设置为RXV

#### 2. 为什么我们在 setup_vm 中需要做等值映射? 此时在 head.S 中的

>因为在rolocate中我们实现了页表的切换，
>
>```asm
>    relocate:
>        ...
>        csrw satp,t0;           
>        sfence.vma zero, zero;   # pc
>        fence.i
>        ret
>```
>
>在执行完`csrw satp,t0`之后，虚拟内存机制已经开启，但是pc这时候仍然指向原来的`sfence`指令的地址，如果不做等值映射，这时候会触发一个page fault，而我们没有实现page fault的处理，这会导致系统卡死

#### 3. 在 Linux 中，是不需要做等值映射的。请探索一下不在 setup_vm 中做等值映射的方法。

思路：使用2中的方法，利用系统执行` sfence.vma zero, zero; `指令·触发page fault的现象，在一开始设置一个特殊的trap处理入口，在这里将sepc修改为虚拟地址中下一条指令的地址，之后sret之后，pc就会正确指向新的地址。

将setup_vm中等值映射部分删去

```c
void setup_vm(void)
{
    // 高地址映射
    unsigned long index = ((PHY_START + PA2VA_OFFSET) >> VPN2OFFSET) & MUSK;
    early_pgtbl[index] = ((PHY_START >> VPN2OFFSET) & 0x3ffff) << 28;
    early_pgtbl[index] |= (VALID | READABLE | WRITABLE | EXECUTABLE);
}
```



将 relocate 改为:

```asm
relocate:
    # 设置中断向量
    la t0, _forvm
    li t1,PA2VA_OFFSET
    add t0,t0,t1
    csrw stvec,t0

    li t0,PA2VA_OFFSET;
    add ra,ra,t0;
    addi ra,ra, 4 # 让ra指向setup_vm_final的虚拟地址
    add sp,sp,t0;
    # set satp with early_pgtbl
    # 设置satp模式为rv39
    add t1,zero,zero;
    ori t1,t1,1;
    slli t1,t1,63;
    # 设置satp中的ppn
    la t0,early_pgtbl;
    srli t0,t0,12;
    add t0,t0,t1
    # 开启虚拟内存
    csrw satp,t0;
    ###################### 
    #   YOUR CODE HERE   #
    ######################

    # flush tlb
    sfence.vma zero, zero
	fence.i
    ret
```

在_traps前加入forvm标签

```asm
.global _forvm
_forvm:
    sfence.vma zero,zero
    fence.i
    la t0,mm_init
    # 设置中断返回地址为mm_init
    csrw sepc,t0
.globl _traps 
	...
```

修改trap_handler为

```c
void trap_handler(unsigned long scause, unsigned long sepc)
{
    if ((scause >> 63) & 1)
    {
        // interrupt
        if ((scause & 5) == 5)
        {
            clock_set_next_event();
            do_timer();
        }
    }
    else
    {
        // 触发exception，这里是pagefault，直接返回
        return;
    }
}

```

这样，系统在执行csrw satp,t0之后，执行sfence指令的时候会触发一个page fault，在这里我们将sepc设置为mm_init的虚拟地址，进入trap_handler之后，函数会直接返回，之后执行sret之后就会进入mm_init中，mm_init执行完毕之后，由于我们之前将setup_vm_final的地址写入了ra寄存器，这时候函数就会正确跳转到setup_vm_final函数进行三级映射，之后系统就可以正常运行。

运行截图：

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/RlCMy3.png)























