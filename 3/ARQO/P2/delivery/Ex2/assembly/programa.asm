# Prog de prueba para Practica 2. Ej 1

.data 0
num0: .word 1 # posic 0
num1: .word 2 # posic 4
num2: .word 4 # posic 8 
num3: .word 8 # posic 12 
num4: .word 16 # posic 16 
num5: .word 32 # posic 20
num6: .word 7 # posic 24
num7: .word 7 # posic 28
num8: .word 0 # posic 32
num9: .word 0 # posic 36
num10: .word 0 # posic 40
num11: .word 0 # posic 44
.text 0
main:
  # carga num0 a num5 en los registros 9 a 14
  lw $t1, 0($zero) # lw $r9, 0($r0)
  lw $t2, 4($zero) # lw $r10, 4($r0)
  lw $t3, 8($zero) # lw $r11, 8($r0)
  lw $t4, 12($zero) # lw $r12, 12($r0)
  lw $t5, 16($zero) # lw $r13, 16($r0)
  lw $t6, 20($zero) # lw $r14, 20($r0)
  
  # HAZARDS IN BRANCH
  add $t2, $t2, $t2 # En r10 se guarda un 4 
  beq $t2, $t3, goodjumpRtype # It will jump effectively
  lui $t2, 0xFFFF  # lui $r10, 0xFFFF -> This mustn't execute
  nop
  nop
goodjumpRtype:
  add $t7, $t1, $t1 # 2 = 1 + 1
  beq $zero, $t7, dontjumpRtype # 2 != 0, must not jump
  add $t4, $t4, $t2 # r12 -> 12 = 8 + 4
  add $t4, $t4, $t2 # r12 -> 16 = 10 + 4
  nop
  nop
dontjumpRtype:
  lw $t4, 24($zero) # lw $r12, 24($r0) = 7
  lw $t5, 28($zero) # lw $r13, 28($r0) = 7
  beq $t4, $t5, goodjumpLW # Should jump
  lui $t2, 0xFFFF  # lui $r10, 0xFFFF -> This mustn't execute
  nop
  nop
goodjumpLW:
  lw $t4, 12($zero) # lw $r12, 12($r0) = 8
  lw $t5, 16($zero) # lw $r13, 16($r0) = 16
  beq $t4, $t5, final # Should not jump
  add $t4, $t4, $t2 # r12 -> 12 = 8 + 4
  add $t4, $t4, $t2 # r12 -> 16 = 12 + 4
final:
  beq $zero, $zero, final
  nop
  nop
  nop
  nop