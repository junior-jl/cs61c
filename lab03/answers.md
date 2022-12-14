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

## Exercise 3

### ex2.s

```s
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
    slli s3, t0, 2
    add t1, s1, s3
    lw t2, 0(t1)
    beq t2, x0, exit
    add a0, x0, t2
    addi sp, sp, -8
    sw t0, 0(sp)
    sw t2, 4(sp)
    jal fun
    lw t0, 0(sp)
    lw t2, 4(sp)
    addi sp, sp, 8
    add t2, x0, a0
    add t3, s2, s3
    sw t2, 0(t3)
    add s0, s0, t2
    addi t0, t0, 1
    jal x0, loop
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
```

### ex2.c

```c
int source[] = {3, 1, 4, 1, 5, 9, 0};
int dest[10];

int fun(int x) {
	return -x * (x + 1);
}

int main() {
    int k;
    int sum = 0;
    for (k = 0; source[k] != 0; k++) {
        dest[k] = fun(source[k]);
        sum += dest[k];
    }
    return sum;
}
``` 

#### Find and identify the following components of this assembly file, and be able to explain how they work.

- The register representing the variable **k**: `t0` is the register used in the Assembly code that performs the same operations as `k` in the C code. It is used in the loop to access elements in the array and is incremented after each iteration.

- The register representing the variable **sum**: `s0` is the equivalent register to `sum` variable in C. It is the sum of the `dest` elements.

- The registers acting as pointers to `source` and `dest` arrays: As shown by these two lines of code, `s1` and `s2` are the registers acting as pointers to `source` and `dest`, respectively.

```s
la s1, source
la s2, dest
```

- The assembly code for the `loop` found in the C code: The comments explain how the `loop` is implemented in the RISC-V code (equivalent to the `for` loop in the C code):

```s
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


```

- How the `pointers` are manipulated in the assembly code: As one can see in the commented snippet above, the pointers are used by loading to a register the what is in the address of itself plus the offset given by `t0` shifted to the left twice (i.e. 4 times k, where k is the index of the element). It is worth mentioning that the true offset (4 times t0) is being stored in `s3`.
