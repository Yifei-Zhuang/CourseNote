; 在链表中查找名字符合的对象的信息
; ics 2021 lab2
        .orig x3000
        lea r0, prompt
        trap x22
        ;; 接收字符串
        ;; r1存储接收到的字符串
        lea r1, strInput
        and r4, r4, #0
        and r5,r5, #0
        ;#TODO 注意输入的结束符
getChar trap x20
        trap x21
        ld r7,antiEnter ;;just debug
        ;add r0,r0, #0
        add r7,r7, r0
        brz inputOver
        str r0,r1, #0
        add r1,r1, #1
        brnzp getChar
inputOver 
        and r7,r7, #0
        str r7, r1, #0
        lea r1,strInput ;; 输入结束，输入的字符串存储在strInput中，r1指向输入的字符串
        ;; 在链表中搜索，同时设定标记判断是否存在符合条件的对象，不能使用r0和r5,r7存储
        ;; 搜索方式：r2指向当前对象，r0指向当前对象的名字，r1指向输入的的名字，r3指向下一个对象，通过r5的返回值
        ;;     判断是否匹配,在r4中存储是否有匹配的值
        ;; 
        ldi r2, nodeHead ;
check   brz done
	    ldr r0,r2, #2 ;; 指向first name
        JSR strcmp 
        add r5,r5, #0
        brz fNo ;表示第一个不匹配
fYes        
        ldr r0,r2, #3
        JSR strcmp
        add r5, r5, #0
        brz echoFull
        ;; 只输出一次名字
        brnzp echoHalf
fNo
        ldr r0,r2, #3
        JSR strcmp
        add r5, r5, #0
        brz caseDone ;;失败
        ;; 只有第二个符合，输出结果（全名+房间）
echoFull
        ldr r0,r2, #2
        trap x22
        ld r0, space
        trap x21
echoHalf
        ldr r0,r2, #3
        trap x22
        ld r0, space
        trap x21
        ;;输出房间号
        ldr r0,r2, #1
        trap x22
        ld r0, newLine
        trap x21 ;;换行
        add r4,r4, #1 ;;将r4加一，表示找到了
caseDone ldr r2,r2, #0
        brnzp check
done    add r4,r4, #0
        brnp finish
notFound 
        lea r0,notFoundOutput
        trap x22
finish    halt
nodeHead .fill x4000 ;; 链表头
space    .fill #32
newLine  .fill #10
prompt .STRINGZ "Enter a name: "
notFoundOutput .STRINGZ "Not found"
strInput  .BLKW #17 ; 输入的字符串放的地方
antiEnter .fill xFFF6 ; /r的相反数，表示输入结束
;; 以下代码来自书本第302页
;; 比较存储在r0和r1指向的地址的两个字符串，最终如果r5是0，那么不相等，否则相等
strcmp  st r0,comSaver0
        st r1,comSaver1
        st r2,comSaver2
        st r3,comSaver3
        st r4,comSaver4
        
        and r5,r5, #0
        add r5,r5, #1

        ldr r2,r0, #0
	    brz checkr1 ;判定是否是空串
 
nextChar ldr r3,r1 #0
    	not r3,r3
    	add r3,r3, #1
    	add r3, r2, r3
    	brnp fail
    	add r0,r0, #1
    	add r1,r1, #1
    	ldr r2,r0, #0
    	brnp nextChar
checkr1 ldr r3,r1, #0
	    brz comDone
fail 	and r5,r5, #0
	    brnzp comDone
        
comDone    ld r0,comSaver0
        ld r1,comSaver1
        ld r2,comSaver2
        ld r3,comSaver3
        ld r4,comSaver4
        ret
comSaver0  .blkw 1
comSaver1  .blkw 1
comSaver2  .blkw 1
comSaver3  .blkw 1
comSaver4  .blkw 1
upperbound .fill xffe0
        .end