        .orig x3005
        lea r2, data
        ldr r4,r2, #0
loop    add r4,r4, #-3
        brzp loop
        trap x25
data    .FILL x000B
        .END