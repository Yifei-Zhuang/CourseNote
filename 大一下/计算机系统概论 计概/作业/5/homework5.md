1. 

    x3000: 0010 000 0 0000 0100
    x3002: 1011 000 0 0000 0011
    x3003: 1111 0000 0010 0001
    x3006: 0100 0000 0000 0001

2. 

  Symbol  Address
  TEST	   x301F
  FINISH	x3027
  SAVE3	  x3029
  SAVE2	  x302A

3. 

  R0: xA400
  R1: x23FF
  R2: xE1FF
  R3: xA401
  R4: x0000
  R5: x0000
  R6: x0000
  R7: x0000

4. 

  Error is in instruction "ADD R3, R3, #30", for 30 is too large to be the immedinate number. 
  Fix method: modify this instruction to two instructions:
      				<font color = "red">ADD R3, R3, #15;    </font>

  ​                    <font color = "red">ADD R3, R3, #15;    </font>

  It will be detected when the assembler works.

5. 

  (a):LDR R3,R1,#0
  (b):NOT R3,R3
  (c):ADD R3,R3, #1
  
6. （a):ADD R1,R1,#-1
     (b):LDR R4,R1, #0
     (c):ADD R0, R0, #1
     (d): ADD R1, R1, #-1
     (e):BR LOOP







