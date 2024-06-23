### ICS-2021-Lab3-Report

##### Main Algorithm

​	In the sys booting code, using str to write the address of keyboard interrupt code to the address x0180, and sti x4000 to fe00 to activate the kbsr to interupt. Then we enter the user area. 

​	Using a loop to continuously output the value in r0 (initially it is 7).Everytime we receive a input from the keyboard, we enter the interrupt area in x0800. Load the data in the kbdr, if it's Enter and the value in r0 is bigger than 0, then we add -1 to r0, rti. If it's a number, then we change the value in r0 to the number. Else we output the data user input 40 times, return to the user area.



##### Essential Parts

```asm
; sys booting area
; register the interrupt handle function
ld r0, handleKBI
sti r0,kbi
; enable keyboard to interrupt
ld r0, enable
sti r0, os_kbsr

.....

; keyboard interrupt handle function
ldi r0, kbdr
; check the data we input
ld r1,antiEnter
add r1, r0, r1
brz decrease1
ld r1, antiAscii0
add r1, r1, r0
brzp mayBeNum
brnzp other

....

; keep output the data in r0
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
```



##### Questions 

1. What special device is related to this keyboard handler program?

   Answer: The KBDR and the KBSR. The KBSR's 15th value is used to identify whether we have a input from the keyboard or not. The [7:0] part of the KBDR is the ASCII value of what we input (if the kbsr[15] is 1) . And we can read it to do the interrupt work.