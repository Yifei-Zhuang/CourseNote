        .orig x3000
        and r4, r4, #0
        ld r0,a 
        not r5,r0
        add r5, r5, #2
        add r1,r4, #2
        
remod   jsr mod
        brz store0
        
        add r7,r1,r5
        brz store1
        
        add r1,r1, #1
        br remod 
store1  add r4,r4, #1
store0  st r4,result
        trap x25
    
mod add r2,r0, #0
    not r3,r1
    add r3,r3, #1
dec add r2,r2, r3
    brp dec
    ret

a   .blkw 1
result .blkw 1
.end