;; recursively implement factorial

        .orig x3000
        ld r0, value
        ld r6, pointer
        jsr factorial
        and r1, #0
        add r1, r0
        ld r0, ascii
        add r0,r1,r0
        trap x21
        trap x25
        
; recursively implement factorial
factorial 
        add r6, #-1
        str r1,r6, #0
        
        add r1,r0, #-1
        brz norecurse
        
        add r6,r6, #-1
        str r7,r6, #0
        add r6,r6, #-1
        str r0,r6 ,#0
        jsr factorial
        ldr r1,r6, #0
        add r6,r6, #1
        mul r0,r0, r1
        ldr r7, r6, #0
        add r6, r6, #1
        
norecurse ldr r1,r6, #0
        add r6, r6, #1
        ret
        
ascii   .fill x0030
value   .fill x0009
pointer .fill xffdf
.end