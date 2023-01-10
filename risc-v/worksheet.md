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
