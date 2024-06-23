1. 
   a. We can implement $16^2 = 256$​​ types of trap services in the LC-3 machine, because the trap table holds the space from x0000 to x00ff.

   b. Because by using the instruction RTI we can restore the PSR, SP and the the value of register PC of the position which calls the trap service. We cannot use BR instruction, for the offset may be too large for the immediate number to represent. And every time we call BR, it will always jump to the same address, causing the problem that we cannot return to the desired location.

   c. There is 1 assess to the memory during the process of  a TRAP instruction. We just nees to load the value of x00vv (v represents the trap vector) into the register PC.

2. 
   
   This LC-3 program receives a sentence ending with ascii code of 'newline', and the sentence's  length cannot be larger than 50. Then output the reverse form the sentence we input.

