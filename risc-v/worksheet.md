# RISC-V Intro & Control Flow
## 1. Pre-Check

### 1.1. After calling a function and having that function return, the `t` registers may have been changed during execution of the function, while `a` registers cannot.

**Ans**: False. The pseudo-names `a0` and `a1` for registers `x10` and `x11` are generally used for function arguments and return values, so they are very likely to change during function calls.

### 1.2. Let `a0` point to the start of an array `x`. `lw s0, 4(a0)` will always load `x[1]` into `s0`.

**Ans**: False. Because of the 'always'. It represents `x[1]` correctly only if the array elements are 4 bytes wide.

### 1.3. Assuming no compiler or operating system protections, it is possible to have the code jump to data stored at `0(a0)` (offset 0 from the value in register `a0` and execute instructions from there.

**Ans**: True. I didn't quite understand the question, but I'm assuming `a0` has the address of a code instruction.

### 1.4. Assuming integers are 4 bytes, adding the ASCII character ’d’ to the address of an integer array would get you the element at index 25 of that array (assuming the array is large enough).

**Ans**: True. 'd' = $100_{10}$. $\frac{100}{4} = 25$.

### 1.5. `jalr` is a shorthand expression for a `jal` that jumps to the specified label and does not store a return address anywhere.

**Ans**: False. Both `jalr` and `jal` store the return address in a register. `jalr` stores it in a register passed as argument to the instruction and `jal` in `ra`.

### 1.6. Calling `j label` does the exact same thing as calling `jal label`.

**Ans**: False: `jal label` is the same as `jal ra, label`. While `j label` is `jal x0, label`, so it discards the return address.

## 2. Basic Instructions

For your reference, here are some of the basic instructions for arithmetic operations and dealing with memory (Note: ARG1 is argument register 1, ARG2 is argument register 2, and DR is destination register):

![image](https://user-images.githubusercontent.com/69206952/212407198-920bf775-3abd-4ef7-bbdb-8ea39ff47abd.png)

You may also see that there is an "i" at the end of certain instructions, such as `addi`, `slli`, etc. This means that ARG2 becomes an "immediate" or an integer instead of using a register. There are also immediates in some other instructions such as `sw` and `lw`. Note that the size (maximum number of bits) of an immediate in any given instruction depends on what type of instruction it is (more on this soon!).

### 2.1. Assume we have an array in memory that contains `int *arr = {1, 2, 3, 4, 5, 6, 0}`. Let register `s0` hold the address of the element at index 0 in `arr`. You may assume integers are four bytes and our values are word-aligned. What do the snippets of RISC-V code do? Assume that all the instructions are run one after the other in the same context.

#### a) `lw t0, 12(s0)`

**Ans**: It loads the element of index 3 of `arr` in the register `t0`. `t0 = arr[3];`.

#### b) `sw t0, 16(s0)`

**Ans**: It stores in the index 4 of `arr` what it is in `t0`, so it makes `arr[4] = arr[3];`

#### c)

```
slli t1, t0, 2
add t2, s0, t1
lw t3, 0(t2)
addi t3, t3, 1
sw t3, 0(t2)
```

**Ans**: 

1. Shifts `t0` to the left twice and the result goes to `t1`. `t1 = arr[3] << 2 // arr[3] = 4 (100) -> t1 = 10000 (16)`.
2. Add `s0` (the address of the first element (index 0)) with `t1` (16) and put the result in `t2`. `t2 = s0 + 16;`. So `t2` holds the position of the element of index 4 of `arr`. `t2 = &arr[4];`.
3. Load into `t3` the value of `*t2`, i.e., `arr[4]`. `t3 = arr[4]; // t3 = 5`
4. `t3++; // t3 = 6`
5. `arr[4] = t3 // arr[4] = 6;`

So the whole snippet increments `arr[4]` by 1.

#### d)

```
lw t0, 0(s0)
xori t0, t0, 0xFFF
addi t0, t0, 1
```

1. `t0 = *s0;` i.e., `t0 = arr[0]; // t0 = 1`
2. XOR gate between `t0 (1)` and `0xFFF (0000 1111 1111 1111)`. `t0 ^= 0xFFF; // t0 = 0xFFE`
3. `t0++; // t0 = 0xFFF`

Because of sign extension, the whole code makes `t0 = -t0; // t0 = -1`.
