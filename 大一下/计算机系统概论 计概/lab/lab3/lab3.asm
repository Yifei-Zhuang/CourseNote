; zyf ics2021 lab3 code
; part 1: sys booting code
        .orig x0200
        ld r6, os_sp
        ld r0, usr_psr
        add r6,r6, #-1
        str r0,r6, #0
        ld r0, user_pc
        add r6,r6, #-1
        str r0,r6, #0
        ; 注册中断处理函数
        ld r0, handleKBI
        sti r0,kbi
        ; 允许键盘中断
        ld r0, enable
        sti r0, os_kbsr
        rti
os_sp   .fill x3000
usr_psr .fill x8002
user_pc .fill x3000
kbi     .fill x0180 ; 键盘中断向量所在的位置
handleKBI .fill x0800 ; 中断处理函数地址
enable  .fill x4000 
os_kbsr    .fill xfe00
        .end

; part 2: interrupt service routine
        .orig x0800
        st r0, kbiSaveR0
        st r1, kbiSaveR1
        st r2, kbiSaveR2
        ; ldi r0, kbsr
        ; brzp rti
        ldi r0, kbdr
        ; 分支部分
        ld r1,antiEnter
        add r1, r0, r1
        brz decrease1
        ld r1, antiAscii0
        add r1, r1, r0
        brzp mayBeNum
        brnzp other
decrease1 
        ld r1, kbiSaver0
        ld r2, antiAscii0
        add r2, r1, r2 ;处理已经是0的情况
        brz done
        add r1, r1, #-1
        st r1, kbiSaveR0
        brnzp done
mayBeNum
        ld r1, antiAscii9
        add r1, r1, r0
        brp other
        ;;确实是数字
        st r0, kbiSaveR0
        brnzp done
other   ;;其他字符，那么就输出40次
        ld r2, counter 
        add r1, r0 ,#0 ;存储当前的值
        ld r0, kbiNewLine
        trap x21
        add r0, r1, #0
outputother 
        trap x21
        add r2, r2, #-1
        brnp outputother
        add r1, r0 ,#0 ;存储当前的值
        ld r0, kbiNewLine
        trap x21
        add r0, r1, #0
done    ld r0, kbiSaveR0 ;;注意这一项之后要改
        ld r1, kbiSaveR1
        ld r2, kbiSaveR2
        rti
kbiNewLine .fill x000D
kbiSaveR0 .blkw 1
kbiSaveR1 .blkw 1
kbiSaveR2 .blkw 1
counter .fill #40
kbsr    .fill xfe00
kbdr    .fill xfe02
dsr     .fill xfe04
ddr     .fill xfe06
antiEnter .fill xfff6
antiAscii0 .fill xffd0
antiAscii9 .fill xffc7
        .end

; part 3; userprogram
        .orig x3000
        ; 使用r0保存输出对象,r1做换行计数器,r2作为临时寄存器
        ld r0, ascii0
        and r1,r1, #0
        and r2,r2, #0
        add r0, r0, #7
loop    jsr DELAY
        trap x21
        add r1, r1, #1
        ld r2, anti40
        add r2, r1, r2
        brnp loop
        and r1,r1, #0
        st r0, userSaveR0
        ld r0, newLine
        trap x21
        ld r0, userSaveR0
        brnzp loop
        halt
ascii0  .fill x0030
newLine .fill x000D
anti40  .fill xFFD8
userSaveR0 .blkw 1
; 减慢输出速度
DELAY   ST R1, DELAY_R1
        LD R1, DELAY_COUNT
DELAY_LOOP ADD R1, R1, #-1
        BRnp DELAY_LOOP
        LD R1, DELAY_R1
        RET
DELAY_COUNT .FILL #256
DELAY_R1 .BLKW #1
        .end
        
        
                

        