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

## 3. C to RISC-V

### 3.1. Translate between the C and RISC-V verbatim.

| **C** | **RISC-V** |
|:---:|:---:|
| `// s0 -> a, s1 -> b`<br>`// s2 -> c, s3 -> z`<br><br>`int a = 4, b = 5, c = 6, z;`<br>`z = a + b + c + 10;` |  |
| `//s0 -> int * p = intArr`<br>`//s1 -> a`<br>`*p = 0;`<br>`int a = 2;`<br>`p[1] = p[a] = a;` |  |
| `// s0 -> a, s1 -> b`<br>`int a = 5, b = 10;`<br>`if(a + a == b) {`<br>`    a = 0;`<br>`} else {`<br>`    b = a - 1;`<br>`}` |  |
|  | `addi s0, x0, 0`<br>`addi s1, x0, 1`<br>`addi t0, x0, 30`<br>`loop:`<br>`beq s0, t0, exit`<br>`add s1, s1, s1`<br>`addi s0, s0, 1`<br>`jal x0, loop`<br>`exit:` |
| `// s0 -> n, s1 -> sum`<br>`// assume n > 0 to start`<br>`for (int sum = 0; n > 0; n--) {`<br>`    sum += n;`<br>`}` |  |

**Ans**:

| **C** | **RISC-V** |
|:---:|:---:|
| `// s0 -> a, s1 -> b`<br>`// s2 -> c, s3 -> z`<br><br>`int a = 4, b = 5, c = 6, z;`<br>`z = a + b + c + 10;` | `addi s0, x0, 4`<br>`addi s1, x0, 5`<br>`addi s2, x0, 6`<br>`add s3, s0, s1`<br>`add s3, s3, s2`<br>`addi s3, s3, 10<br>` |
| `//s0 -> int * p = intArr`<br>`//s1 -> a`<br>`*p = 0;`<br>`int a = 2;`<br>`p[1] = p[a] = a;` | `sw x0, 0(s0)`<br>`addi s1, x0, 2`<br>`slli t0, s1, 2`<br>`add t0, t0, s0`<br>`sw s1, 0(t0)`<br>`sw s1, 4(s0)` |
| `// s0 -> a, s1 -> b`<br>`int a = 5, b = 10;`<br>`if(a + a == b) {`<br>`    a = 0;`<br>`} else {`<br>`    b = a - 1;`<br>`}` | `addi s0, x0, 5`<br>`addi s1, x0, 10`<br>`add t0, s0, s0`<br>`bne t0, s1, other`<br>`add s0, x0, x0`<br>`jal x0, finish`<br>`other:`<br>`	addi s1, s0, -1`<br>`finish:` |
| `int s0 = 0, s1 = 1, t0 = 30;`<br>`while (s0 != t0)`<br>`{`<br>  `	s1 += s1;`<br>`	s0++;`<br>`}` | `addi s0, x0, 0`<br>`addi s1, x0, 1`<br>`addi t0, x0, 30`<br>`loop:`<br>`beq s0, t0, exit`<br>`add s1, s1, s1`<br>`addi s0, s0, 1`<br>`jal x0, loop`<br>`exit:` |
| `// s0 -> n, s1 -> sum`<br>`// assume n > 0 to start`<br>`for (int sum = 0; n > 0; n--) {`<br>`    sum += n;`<br>`}` | `    addi s1, x0, 0`<br>`loop:`<br>`    ble s0, x0, exit`<br>`    add s1, s1, s0`<br>`    addi s0, s0, -1`<br>`    jal x0, loop`<br>`exit:` |

## 4. RISC-V with Arrays and Lists

Comment what each code block does. Each block runs in isolation. Assume that there is an array, `int arr[6] = {3, 1, 4, 1, 5, 9}`, which starts at memory address `0xBFFFFF00`, and a linked list struct (as defined below), `struct ll* lst`, whose first element is located at address `0xABCD0000`. Let `s0` contain `arr`'s address `0xBFFFFF00`, and let `s1` contain `lst`'s address `0xABCD0000`. You may assume integers and pointers are 4 bytes and that structs are tightly packed. Assume that `lst`'s last node's `next` is a NULL pointer to memory address `0x00000000`.

```c
struct ll {
  int val;
  struct ll* next;
}
```

### 4.1. 

```s
lw t0, 0(s0)
lw t1, 8(s0)
add t2, t0, t1
sw t2, 4(s0)
```

**Ans**: 

```s
lw t0, 0(s0) # t0 = arr[0]
lw t1, 8(s0) # t1 = arr[2]
add t2, t0, t1 # t2 = arr[0] + arr[2]
sw t2, 4(s0) # arr[1] = arr[0] + arr[2]
```

The block do what the following C code would do: `arr[1] = arr[0] + arr[2];`

### 4.2.

```s
loop: beq s1, x0, end
      lw t0, 0(s1)
      addi t0, t0, 1
      sw t0, 0(s1)
      lw s1, 4(s1)
      jal x0, loop
end:
```

**Ans**:

```s
# jump to end if lst == 0
# since it's a loop... while (lst)
loop: beq s1, x0, end # while (lst)
      lw t0, 0(s1) # t0 = *lst // (value)
      addi t0, t0, 1 # t0++; // increments value of node by 1
      sw t0, 0(s1) # "put it back"
      lw s1, 4(s1) # s1 now holds the address of the next node
      jal x0, loop # jump back to loop to check condition again
end:
```

The block increments all the values in the linked list by 1.

### 4.3. 

```s
      add t0, x0, x0
loop: slti t1, t0, 6
      beq t1, x0, end
      slli t2, t0, 2
      add t3, s0, t2
      lw t4, 0(t3)
      sub t4, x0, t4
      sw t4, 0(t3)
      addi t0, t0, 1
      jal x0, loop
end:
```

**Ans**:

```s
      add t0, x0, x0 # t0 = 0
loop: slti t1, t0, 6 # t1 = (t0 < 6) ? 1 : 0;
      beq t1, x0, end # if t1 == 0 (t0 >= 6), end
      slli t2, t0, 2 # t2 = t0 << 2 (4 * t0)
      add t3, s0, t2 # t3 = s0 + t2 (t3 -> address of current value of arr)
      lw t4, 0(t3) # t4 = *t3 (t4 -> current value of arr)
      sub t4, x0, t4 # t4 = (-t4); // arr[i] = -arr[i]
      sw t4, 0(t3) # "put it back"
      addi t0, t0, 1 # t0++; // i++
      jal x0, loop # jump to loop to re-check condition
end:
```

The block multiplies all the elements of the array by -1. 

## 5. RISC-V Calling Conventions

### 5.1. How do we pass arguments into functions?

**Ans**: By convention, there are eight registers meant for that `a0 - a7` (`x10 - x17`).

### 5.2. How are values returned by functions?

**Ans**: `a0` and `a1` are used to store return values.

### 5.3. What is `sp` and how should it be used in the context of RISC-V functions?

**Ans**: `sp` is the stack pointer. Since the stack grows from higher addresses to lower ones, when we need to create more space on the stack (to call a function), `sp` is subtracted by the amount of space needed (generally a multiple of 4). When the space is not needed anymore, `sp` is added to that amount again to go back to where it was before the function call.

### 5.4. Which values need to saved by the caller, before jumping to a function using `jal`?

**Ans**: The argument registers, the temporary registers and the return address. So, `a0 - a7` (`x10 - x17`), `t0 - t6` (`x5 - x7 ; x28 - x31)`, `ra` (`x1`).

### 5.5. Which values need to be restored by the callee, before returning from a function?

**Ans**: The stack pointer `sp`, `fp` (frame pointer / s0), all the other saved registers (`s1 - s11`).

### 5.6. In a bug-free program, which registers are guaranteed to be the same after a function call? Which registers aren't guaranteed to be the same?

**Ans**: All the ones mentioned in the last question, because they are always restored by the callee function. 

## 6. Writing RISC-V Functions

### 6.1. Write a function sumSquare in RISC-V that, when given an integer n, returns the summation below. If n is not positive, then the function returns 0.

$$ n^2 + (n - 1)^2 + \cdots + 1^2 $$

For this problem, you are given a RISC-V function called `square` that takes in a single integer and returns its square.

First, let’s implement the meat of the function: the squaring and summing. We will be abiding by the caller/callee convention, so in what register can we expect the parameter n? What registers should hold square’s parameter and return value? In what register should we place the return value of `sumSquare`?

**Ans:**

```s
    addi s0, a0, 0 # t0 = n
    addi s1, x0, 0 # sum (t1) = 0
loop:
    # if n <= 0, sum will never be incremented, so it will return 0
    ble s0, x0, exit # if s0 <= 0, exit
    addi a0, s0, 0 # a0 -> arg to call square
    jal ra, square # call square and keep return address
    add s1, s1, a0 # sum += square(n)
    addi s0, s0, -1 # n-- (s0--)
    jal x0, loop # re-check condition  
exit:
    addi a0, s1, 0 # a0 (return sum)
```

### 6.2. Since `sumSquare` is the callee, we need to ensure that it is not overriding any registers that the caller may use. Given your implementation above, write a prologue and epilogue to account for the registers you used.

**Ans**: The following code is the whole program with $n=3$, a call to print the result on screen and a simple `square` function.

```s
    addi a0, x0, 3 # n = 3
    
    jal ra, sumSquare
    
    ###################################
    # Calls to print result on terminal
    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result
    
    addi a0, x0, 10
    ecall # Exit
    ###################################
    
sumSquare:
    # Prologue
    addi sp, sp, -12
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    # End of prologue
    addi s0, a0, 0 # t0 = n
    addi s1, x0, 0 # sum (t1) = 0
loop:
    ble s0, x0, exit # if s0 == 0, exit
    addi a0, s0, 0 # a0 -> arg to call square
    jal ra, square # call square and keep return address
    add s1, s1, a0 # sum += square(n)
    addi s0, s0, -1 # n-- (s0--)
    jal x0, loop # re-check condition  
exit:
    addi a0, s1, 0 # a0 (return sum)
    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    addi sp, sp, 12
    # End of epilogue
    jr ra

square: 
    mul a0, a0, a0 # a0 *= a0
    jr ra
    
```
