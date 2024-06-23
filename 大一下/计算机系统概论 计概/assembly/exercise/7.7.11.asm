        .orig x3000
        in
        and r3, r3, #0
        add r3, r3, #9
        ld  r4, nasciid
        ld  r5, nhexdif
        
        ld  r1, nconsd
        add r1,r1,r0
        brz getnums
        ld r1,nconsx
        add r1,r1,r0
        brnp fail
        add r3,r3, #6
getnums in
        st r0, char1
        in
        st r0,char2
        lea r6,char1
        and r2,r2, #0
        add r2,r2, #2 ;loop twice
        ; Using r2,r3,r4,r5,r6 here
        and r0,r0,#0 ;result
        
loop    and r1,r3, #0
        add r7,r0, #0
lpcur   add r0,r0, r7
        add r1,r1, #-1
        brp lpcur
        
        ldr r1,r6, #0
        add r1,r1,r4
        
        add r0,r0,r1
        
        add r1,r1,r5
        brn donecur
        add r0,r0, #-7 ;for hex numbers
        
donecur
        add r6,r6, #1
        add r2,r2, #-1
        brp loop
        
        ;r0 has number at this point
        
        and r2,r2, #0
        add r2,r2, #8
        
        lea r3, res2
        ld r4,ascnum
        and r5,r5, #0
        add r5,r5, #1
        
stlp    and r1,r0,r5
        brp onenum
        add r1,r4, #0
        brnzp storch

onenum  add r1,r4, #1
storch  add r5,r5,r5 

        str r1,r3, #-1
        add r3,r3, #-1
        add r2,r2, #-1
        brp stlp
        lea r0,res
        puts

fail    halt
char1   .FILL x0
char2   .FILL x0

ascnum  .FILL x30
nhexdif .FILL xFFEF
nasciid .FILL xffd0
nconsx  .fill xff88
nconsd  .fill xffdd

res     .blkw 8
res2    .fill x0
        .end