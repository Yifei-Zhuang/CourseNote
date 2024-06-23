; r0: data to be examined
; r1: result 
; r2: checker
; r3: temp
        .ORIG   x3000
        and r1, r1, #0
        ld  r2, init
test    brz done
        and r3,r0,r2
        not r3,r3
        add r3,r3, #1
        add r3,r3,r2
        brnp notadd
        add r1,r1, #1
notadd  add r2,r2,r2
        brnzp test
done    ld r0,ASCII
        ; just debug
        and r4, r4, #0
        add r4,r0,r0
        ;debug over
        add r0,r1,r0
        trap x21
        trap x25
ASCII .FILL x0030  
init  .FILL x0001
        .END 