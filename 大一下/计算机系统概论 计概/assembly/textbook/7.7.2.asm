;r0: 获取键盘输入
;r1: 获取存储的字符
;r2: 记录目标字符的个数
;r3: 存储文件保存的地址
        .orig x3000
        and r2,r2, #0
        ld r3, FILE
        ldr r1,r3, #0
        trap x23
        ;EOT代表的就是0
test    add r4,r1,#-4
        brz output ;输出
        not r1,r1
        add r1,r1, #1
        add r1,r0,r1
        brnp getchar
        add r2,r2, #1
getchar add r3,r3, #1
        ldr r1,r3, #0
        brnzp test
output  and r0,r0, #0
        add r0,r2,r0
        trap x21 ;输出r0寄存器的内容
        trap x25
ascii   .FILL x0030
FILE    .FILL x4000
.END