.globl main

.data
source:
    .word   3
    .word   1
    .word   4
    .word   1
    .word   5
    .word   9
    .word   0
dest:
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0

.text
fun:
    addi t0, a0, 1
    sub t1, x0, a0
    mul a0, t0, t1
    jr ra

main:
    # BEGIN PROLOGUE
    addi sp, sp, -20
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw ra, 16(sp)
    # END PROLOGUE
    addi t0, x0, 0
    addi s0, x0, 0
    la s1, source
    la s2, dest
loop:
    slli s3, t0, 2 # t0 is 'k' -> it is being mult. by 4 because a word is 4 bytes.
    add t1, s1, s3 # t1 = s1 (source) + s3 (4*k) (current element's address)
    lw t2, 0(t1) # t2 = source[k]
    beq t2, x0, exit # if (source[k] == 0), exit - Assembly condition inverted the C condition
    add a0, x0, t2 # a0 = t2 (source[k])
    addi sp, sp, -8 # Allocate space in the stack to call fun() (PUSH)
    sw t0, 0(sp) # save t0 (k)
    sw t2, 4(sp) # save t2 (source[k])
    jal fun # Call fun() and store return address in ra
    lw t0, 0(sp) # recover t0
    lw t2, 4(sp) # recover t2
    addi sp, sp, 8 # increment stack (POP)
    add t2, x0, a0 # t2 = a0 (return value of fun(source[k]))
    add t3, s2, s3 # t3 = s2 (dest) + s3 (4*k) (current element's address of dest)
    sw t2, 0(t3) # dest[k] = fun(source[k])
    add s0, s0, t2 # s0 (sum) += dest[k]
    addi t0, t0, 1 # k++
    jal x0, loop # (j loop) discard return address
exit:
    add a0, x0, s0
    # BEGIN EPILOGUE
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw ra, 16(sp)
    addi sp, sp, 20
    # END EPILOGUE
    jr ra
