.data
.word 2, 4, 6, 8
n: .word 9

.text
main:
    add t0, x0, x0 # Sets t0 (x5) to 0
    addi t1, x0, 1 # Sets t1 (x6) to 1
    la t3, n # la (load address) - puts the address of $n in t3 (x28)
    lw t3, 0(t3) # lw (load word) - what's in the address of $n (i.e. n itself) is put into t3 (x28)
fib:
    beq t3, x0, finish # if t3 is zero, jump to finish
    add t2, t1, t0 # t2 = t1 + t0
    mv t0, t1 # t0 = t1
    mv t1, t2 # t1 = t2
    addi t3, t3, -1 # t3--
    j fib # back to loop (fib)
finish:
    addi a0, x0, 1
    addi a1, t0, 0
    ecall # print integer ecall
    addi a0, x0, 10
    ecall # terminate ecall
