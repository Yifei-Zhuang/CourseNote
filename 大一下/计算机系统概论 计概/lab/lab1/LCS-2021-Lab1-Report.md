## LCS-2021-Lab1-Report

#### Main algorithm: 

​	Set r1 to be 0x0007 (i.e. 0000 0000 0000 0111),r2 to be 0,r3 to be 14. And load the data on 0x3100 on r0. 

​	Do a 'AND' instruction between r1 and r0, save the result on r4. If r4 == r1, then the number contains three consecutive 1s, and we set r2 to be 1, then halt. Otherwise we do a left shift on r1, let r3 = r3 - 1, repeat the process on this paragraph until r3 = 0, and we break. Finally we halt the machine.

​	The main process is like this ( the picture I draw is too ugly, so i use this ).

```c
	// all data has 16 bits
	r0 = M[0x3100];
	r2 = 0;
  r1 = 0x0007;
	r3 = 14; //r3 is the counter
	while(r3 != 0){
    r4 = r0 & r1;
    if(r4 == r1){
      r2 = 1;
      break;
    }
    r3 = r3 - 1;
    r1 << 1;
	}
	halt();
```





#### Essential parts:

​	initialize the register![image-20210715163742307](/Users/zhuangyifei/Library/Application Support/typora-user-images/image-20210715163742307.png)



​	cycle and halt

![image-20210715163938091](/Users/zhuangyifei/Library/Application Support/typora-user-images/image-20210715163938091.png)



#### TA's check

1. Question: describe the algorithm you use to solve this problem

   My answer: (just like above, part 1 of this report)Set r1 to be 0x0007 (i.e. 0000 0000 0000 0111),r2 to be 0,r3 to be 14. And load the data on 0x3100 on r0. 

   ​	Do a 'AND' instruction between r1 and r0, save the result on r4. If r4 == r1, then the number contains three consecutive 1s, and we set r2 to be 1, then halt. Otherwise we do a left shift on r1, let r3 = r3 - 1, repeat the process on this paragraph until r3 = 0, and we break. Finally we halt the machine.

    

   <font size = 4px>There is no more question.</font>



​																								    July 15, 2021 By 庄毅非













