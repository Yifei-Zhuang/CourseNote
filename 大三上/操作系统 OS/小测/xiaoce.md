https://classroom.zju.edu.cn/livingroom?course_id=26599&sub_id=518042&tenant_code=112



## quiz1 round robin

如果在切换的时刻刚好来了一个新的进程，那么调度方式为"新的放尾巴，原来运行的放真正的尾巴"

比如原来是P1 （正在运行）<- P2 <- P3，在P1结束的时候刚好来了P4,那么首先新的（P4）放尾巴，变成P1 <- P2 <- P3 <- P4，然后原来的放真正的尾巴，变成P2 <- P3 <- P4 <- P1

## 大概是quiz2

1. 编译linux内核，运行make install之后，内核被装载到/boot文件夹中

2. 在bash中，~表示home文件夹

3. linux中，我们定义进程控制块的结构是struct task_struct 

4. N个进程，M个资源，每一个进程最多使用W个资源，求死锁条件 :W<=(W-1) * N，选择M=4，N=2，W=3

5. ![image-20221105162040418](../../../../../../Library/Application Support/typora-user-images/image-20221105162040418.png)

   安全序列是45123

6. 5的need向量是110,111超过了need向量，所以拒绝

7. ![image-20221105162228049](../../../../../../Library/Application Support/typora-user-images/image-20221105162228049.png)

   分配之后，系统不安全，所以拒绝

8. 分配之后是安全的，因为在第五题仲可以发现，就算所有资源一开始都给了P4,系统也是安全的。

9. 段表

   ![image-20221105162510325](../../../../../../Library/Application Support/typora-user-images/image-20221105162510325.png)

   段2总长度只有100，所以110是非法地址

10. tlb命中率计算

    ![image-20221105162603384](../../../../../../Library/Application Support/typora-user-images/image-20221105162603384.png)

    >10H + 110(1 - H) >= 50 ==> H <= 0.6

11. 信号量

    ![image-20221105163105429](../../../../../../Library/Application Support/typora-user-images/image-20221105163105429.png)

    ![image-20221105163151748](../../../../../../Library/Application Support/typora-user-images/image-20221105163151748.png)

    ![image-20221105163201961](../../../../../../Library/Application Support/typora-user-images/image-20221105163201961.png)



https://classroom.zju.edu.cn/livingroom?course_id=6909&sub_id=111010&tenant_code=112

![](https://raw.githubusercontent.com/workflowBot/image_bed/main/uPic/XO8amt.png)

为每一个frame维护一个计数器counter，如果一个页面存储了在一个frame中，那么就说这个页面和frame关联，如果这个页面后续没有被访问，那么将counter-1，否则不变，如果一个新页面和这个frame关联，并且这个新页面后续也会被访问，那么将计数器+1，如果不会被访问，那么不变计数器；所有的旧页面都只会存储和它关联的页面上；新页面进来的时候查找最小counter的frame进行装填，如果存在多个具有最小counter的页面，那么使用fifo

答案是page fault的次数是13次

![image-20221105170008036](../../../../../../Library/Application Support/typora-user-images/image-20221105170008036.png)



https://classroom.zju.edu.cn/livingroom?course_id=6909&sub_id=180780&tenant_code=112

4. 请求分页系统中，哪一种结构的视线方式是最差的

![image-20221105170120350](../../../../../../Library/Application Support/typora-user-images/image-20221105170120350.png)

显然是hash table，因为内存不连续，tlb和cache频繁刷新

![image-20221105170217890](../../../../../../Library/Application Support/typora-user-images/image-20221105170217890.png)

软链接是 ln -s

ls -l不能查看inode信息

比较明显，要查看state，那么就是state字段

/proc能够查看进程和系统的状态信息

![image-20221105170400592](../../../../../../Library/Application Support/typora-user-images/image-20221105170400592.png)

为了同步，加上3个锁

![image-20221105170438159](../../../../../../Library/Application Support/typora-user-images/image-20221105170438159.png)



https://classroom.zju.edu.cn/livingroom?course_id=26599&sub_id=518042&tenant_code=112

小测提大概就是这样