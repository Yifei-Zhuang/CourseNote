1. 9.6:If we don't check the kbsr before read the kbdr, we may read an input that has already been read before, causing information read more than once.
  9.10: If we don't check the dsr before write to the ddr, we may overwrite a message that should have been displayed on the screen, which means we lost information.
  
2. 

  ```assembly
    START LDI R1, A
          BRZ START
          AND R0, R0, #0
          STI R0, A, #0
          BRNZP NEXT_TASK
    A     .FILL xFE00
  ```
  
3. 
  Since the address xFE02 is mapped to the KBDR device in LC-3, the ACL will load the value from the kbdr instead of memory location xFE02.

4. We can infer that value in the address x0034 is x1000.

