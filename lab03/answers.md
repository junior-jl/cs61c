## Exercise 2

### Code of ex1.s

```s
.data
.word 2, 4, 6, 8
n: .word 9

.text
main:
    add t0, x0, x0
    addi t1, x0, 1
    la t3, n
    lw t3, 0(t3)
fib:
    beq t3, x0, finish
    add t2, t1, t0
    mv t0, t1
    mv t1, t2
    addi t3, t3, -1
    j fib
finish:
    addi a0, x0, 1
    addi a1, t0, 0
    ecall # print integer ecall
    addi a0, x0, 10
    ecall # terminate ecall

```

1. What do the `.data`, `.word`, `.text` directives mean (i.e. what do you use them for)? Hint: think about the 4 sections of memory.

**Ans**: The `.data` directive is used to mark the start of the data section of a program. Here is where variables can be declared, for example.

The `.word` directive stores enough space in memory for a word.

The `.text` directive marks the beginning of the instructions.

2. Run the program to completion. What number did the program output? What does this number represent?

**Ans**: 34. It is the ninth number in the Fibonacci sequence starting at 1.

3. At what address is n stored in memory? Hint: Look at the contents of the registers.

**Ans**: ![image](https://user-images.githubusercontent.com/69206952/211394939-3ae4eb56-23b1-4b90-a137-fbc899d0a156.png)

4. Without actually editing the code (i.e. without going into the "Editor" tab), have the program calculate the 13th fib number (0-indexed) by manually modifying the value of a register. You may find it helpful to first step through the code. If youprefer to look at decimal values, change the "Display Settings" option at the bottom.

**Ans**: By putting a C in the t3 register after the assignment to 9, the program outputs `144`.
