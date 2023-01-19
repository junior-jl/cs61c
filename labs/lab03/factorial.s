.globl factorial


.data
n: .word 1

.text
main:
    la t0, n # address of n in t0
    lw a0, 0(t0) # value of n in a0
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    mv t1, a0 # t1 = a0
    addi t0, x0, 1 # t0 = 1 (used for test)
teste:
    bne t1, t0, loop # if t1 != 1, go to loop
    jr ra # else, go back
loop: 
    addi t1, t1, -1 # t1--
    mul a0, a0, t1 # a0 *= t1
    j teste # check condition again

    
