.orig x3000
ld r6, userstack
add r5,r6, #0
ld r0, maphead
ldr r1, r0, #0
st r1,fullrow
ldr r2,r0, #1
st r2,fullcolumn
lea r2, memarea
ld r1,counter
and r3,r3, #0
add r3,r3, #-1
st r3,result
initializemem
    brz initdone
    str r3,r2, #0
    add r2,r2, #1
    add r1,r1, #-1
    brnzp initializemem
initdone
and r1,r1, #0
add r1,r1, #-1
and r2,r2, #0
add r2,r2, #-1
outloop
add r1,r1,#1
ld r3, fullrow
not r3,r3 
add r3, r3 ,#1
add r3,r1,r3
brz gettheresult
innerloop
add r2,r2, #1
ld r3, fullcolumn
not r3,r3
add r3,r3, #1
add r3,r3, r2
brzp nextloop
add r6,r6, #-2
str r1,r6, #0
str r2,r6, #1
st r1,nowrow
st r2,nowcolumn
JSR dfs ; 假设函数会将找到的最大值放在栈顶
ld r1, nowrow
ld r2, nowcolumn
ldr r3,r6, #0
add r6,r6, #1
add r5,r6, #0
ld r7, result
not r7,r7
add r7,r7, #1
add r7,r3,r7
brp change
brnzp innerloop
change 
st r3,result
brnzp innerloop
nextloop 
    and r2,r2, #0
    add r2,r2, #-1
    brnzp outloop
gettheresult
ld r2,result 
add r2,r2, #1
halt
nowrow .blkw 1
nowcolumn .blkw 1
result .blkw #1
fullrow .blkw #1
fullcolumn .blkw #1
maphead .fill x4000
userstack .fill xfd00
counter .fill #90
dfs
    add r6,r6 ,#-1
    str r5,r6, #0
    add r5,r6 , #0
    
    add r6,r6, #-1
    str r7,r6, #0
    
    ldr r0,r5,#1
    ld r1, fullcolumn
    and r2,r2, #0
    add r0,r0,#0
mul brz mulover
    add r2,r2,r1
    add r0,r0, #-1
    brnzp mul
mulover
    ldr r1,r5, #2
    add r2,r2, r1
    add r2,r2, #2 ; r2 -> pos
    lea r7,memarea
    add r7,r2,r7
    ldr r3,r7, #0
    brzp ismem
    add r6,r6, #-1
    str r2,r6, #0
    ld r3,maphead
    add r3,r2,r3
    ldr r2,r3, #0
    add r6,r6, #-1
    str r2,r6, #0
left
    ldr r0,r5,#1
    ldr r1,r5,#2
    brz notleft ; push 0
    ldr r2, r5, #-2
    add r2, r2, #-1
    ld r3,maphead
    add r3,r3,r2
    ldr r3,r3, #0
    not r3,r3
    add r3,r3, #1
    ldr r4,r5, #-3
    add r3,r3,r4 ; r3 save the diff
    brnz notleft
    ldr r0,r5, #1
    ldr r1,r5, #2
    add r6, r6 ,#-2
    str r0,r6, #0
    add r1,r1, #-1
    str r1, r6, #1
    JSR dfs
    ldr r7,r6, #0
    add r7,r7, #1
    str r7,r6, #0
    brnzp right
notleft 
    add r6,r6, #-1
    and r0,r0, #0
    str r0,r6, #0
right
    ldr r0,r5,#1
    ldr r1,r5,#2
    ld r2,fullcolumn
    add r1,r1, #1
    not r2,r2
    add r2,r2, #1
    add r2,r1, r2
    brzp notright

    ldr r2, r5, #-2
    add r2, r2, #1
    ld r3,maphead
    add r3,r3,r2
    ldr r3,r3, #0
    not r3,r3
    add r3,r3, #1
    ldr r4,r5, #-3
    add r3,r3,r4 ; r3 save the diff
    brnz notright
    ldr r0, r5, #1
    ldr r1,r5, #2
    add r6, r6 ,#-2
    str r0,r6, #0
    add r1,r1, #1
    str r1, r6, #1
    JSR dfs
    ldr r7,r6, #0
    add r7,r7, #1
    str r7,r6, #0
    brnzp up
notright 
    add r6,r6, #-1
    and r0,r0, #0
    str r0,r6, #0
brnzp up
memarea .blkw #90
up
    ldr r1,r5,#2
    ldr r0,r5,#1
    brz notup ; push 0
    ldr r2, r5, #-2
    ld r3, fullColumn
    not r3,r3
    add r3,r3, #1
    add r2,r2, r3
    ld r3,maphead
    add r3,r3,r2
    ldr r3,r3, #0
    not r3,r3
    add r3,r3, #1
    ldr r4,r5, #-3
    add r3,r3,r4 ; r3 save the diff
    brnz notup
    ldr r0,r5, #1
    ldr r1,r5, #2
    add r6, r6 ,#-2
    add r0,r0, #-1
    str r0,r6, #0
    str r1, r6, #1
    JSR dfs
    ldr r7,r6, #0
    add r7,r7, #1
    str r7,r6, #0
    brnzp down
notup 
    add r6,r6, #-1
    and r0,r0, #0
    str r0,r6, #0
down
    ldr r1,r5,#2
    ldr r0,r5,#1
    add r0,r0, #1
    ld r2,fullRow
    not r2,r2
    add r2, r2 , #1
    add r2,r2,r0
    brzp notdown
    
    ldr r2, r5, #-2
    ld r3, fullColumn
    add r2,r2, r3
    ld r3,maphead
    add r3,r3,r2
    ldr r3,r3, #0
    not r3,r3
    add r3,r3, #1
    ldr r4,r5, #-3
    add r3,r3,r4 ; r3 save the diff
    brnz notdown
    ldr r0,r5, #1
    ldr r1,r5, #2
    add r6, r6 ,#-2
    add r0,r0, #1
    str r0,r6, #0
    str r1, r6, #1
    JSR dfs
    ldr r7,r6, #0
    add r7,r7, #1
    str r7,r6, #0
    brnzp done
notdown
    add r6,r6, #-1
    and r0,r0, #0
    str r0,r6, #0
done
    ldr r7,r6, #0
    ldr r4,r6, #1
    add r6,r6, #1
    not r4,r4
    add r4,r4, #1
    add r4,r4,r7
    brn isr4
    brnzp com2
isr4
    ldr r7, r6, #0
com2
    ldr r4,r6, #1
    add r6,r6, #1
    not r4,r4
    add r4,r4, #1
    add r4,r4,r7
    brn isr42
    brnzp com3
isr42
    ldr r7, r6, #0
com3
    ldr r4,r6, #1
    add r6,r6, #1
    not r4,r4
    add r4,r4, #1
    add r4,r4,r7
    brn isr43
    brnzp finish
isr43
    ldr r7, r6, #0
finish 
    ldr r3,r5, #-2
    lea r4,memarea
    add r3,r3, r4
    str r7,r3, #0
    add r6, r6, #6
    str r7,r6, #0 
    ldr r7,r5, #-1
    ldr r5,r5, #0
    ret
ismem
    lea r4,memarea
    add r4,r2,r4
    ldr r7,r4, #0
    add r6, r6, #3
    str r7,r6, #0
    ldr r7,r5, #-1
    ldr r5,r5, #0
    ret

.end

		.ORIG x4000
	.FILL #3
	.FILL #4
	.FILL #12
	.FILL #11
	.FILL #10
	.FILL #9
	.FILL #8
	.FILL #7
	.FILL #6
	.FILL #5
	.FILL #4
	.FILL #3
	.FILL #2
	.FILL #1
	.END
	