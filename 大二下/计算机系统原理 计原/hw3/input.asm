LUI $s4, 30000
add $v0,$v1,$a2
addi $t4,$s7,40000
LW $t4,40000($s7)
J 33554431
MFHI $k0
MTHI $k0
JALR $zero,$ra
MFC0 $zero,$ra
MTC0 $zero,$ra
DIV $zero,$ra