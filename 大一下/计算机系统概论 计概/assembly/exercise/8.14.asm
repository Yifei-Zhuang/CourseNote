        .orig x4000
        and r0,r0, #0
        add r1,r0, #0
        add r0,r0 ,#4
        ld r2, B
A       ldr r3,r2, #0
        add r1,r1,r3
        add r2,r2, #1
        add r0,r0, #-1
        brnp A
        jsr shifter
        add r1,r3, #0
        jsr shifter
        st r4, C
        trap x25
shifter jmp r7
B       .BLKW #1
C       .blkw #1
        .end