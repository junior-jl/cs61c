## Exercise 2

### Code of [old_cc_test.s](old_cc_test.s):


```s
.globl simple_fn naive_pow inc_arr

.data
failure_message: .asciiz "Test failed for some reason.\n"
success_message: .asciiz "Sanity checks passed! Make sure there are no CC violations.\n"
array:
    .word 1 2 3 4 5
exp_inc_array_result:
    .word 2 3 4 5 6

.text
main:
    # We test our program by loading a bunch of random values
    # into a few saved registers - if any of these are modified
    # after these functions return, then we know calling
    # convention was broken by one of these functions
    li s0, 2623
    li s1, 2910
    # ... skipping middle registers so the file isn't too long
    # If we wanted to be rigorous, we would add checks for
    # s2-s10 as well
    li s11, 134
    # Now, we call some functions
    # simple_fn: should return 1
    jal simple_fn # Shorthand for "jal ra, simple_fn"
    li t0, 1
    bne a0, t0, failure
    # naive_pow: should return 2 ** 7 = 128
    li a0, 2
    li a1, 7
    jal naive_pow
    li t0, 128
    bne a0, t0, failure
    # inc_arr: increments "array" in place
    la a0, array
    li a1, 5
    jal inc_arr
    jal check_arr # Verifies inc_arr and jumps to "failure" on failure
    # Check the values in the saved registers for sanity
    li t0, 2623
    li t1, 2910
    li t2, 134
    bne s0, t0, failure
    bne s1, t1, failure
    bne s11, t2, failure
    # If none of those branches were hit, print a message and exit normally
    li a0, 4
    la a1, success_message
    ecall
    li a0, 10
    ecall

# Just a simple function. Returns 1.
#
# FIXME Fix the reported error in this function (you can delete lines
# if necessary, as long as the function still returns 1 in a0).
simple_fn:
    mv a0, t0
    li a0, 1
    ret

# Computes a0 to the power of a1.
# This is analogous to the following C pseudocode:
#
# uint32_t naive_pow(uint32_t a0, uint32_t a1) {
#     uint32_t s0 = 1;
#     while (a1 != 0) {
#         s0 *= a0;
#         a1 -= 1;
#     }
#     return s0;
# }
#
# FIXME There's a CC error with this function!
# The big all-caps comments should give you a hint about what's
# missing. Another hint: what does the "s" in "s0" stand for?
naive_pow:
    # BEGIN PROLOGUE
    # END PROLOGUE
    li s0, 1
naive_pow_loop:
    beq a1, zero, naive_pow_end
    mul s0, s0, a0
    addi a1, a1, -1
    j naive_pow_loop
naive_pow_end:
    mv a0, s0
    # BEGIN EPILOGUE
    # END EPILOGUE
    ret

# Increments the elements of an array in-place.
# a0 holds the address of the start of the array, and a1 holds
# the number of elements it contains.
#
# This function calls the "helper_fn" function, which takes in an
# address as argument and increments the 32-bit value stored there.
inc_arr:
    # BEGIN PROLOGUE
    # FIXME What other registers need to be saved?
    addi sp, sp, -4
    sw ra, 0(sp)
    # END PROLOGUE
    mv s0, a0 # Copy start of array to saved register
    mv s1, a1 # Copy length of array to saved register
    li t0, 0 # Initialize counter to 0
inc_arr_loop:
    beq t0, s1, inc_arr_end
    slli t1, t0, 2 # Convert array index to byte offset
    add a0, s0, t1 # Add offset to start of array
    # Prepare to call helper_fn
    #
    # FIXME Add code to preserve the value in t0 before we call helper_fn
    # Hint: What does the "t" in "t0" stand for?
    # Also ask yourself this: why don't we need to preserve t1?
    #
    jal helper_fn
    # Finished call for helper_fn
    addi t0, t0, 1 # Increment counter
    j inc_arr_loop
inc_arr_end:
    # BEGIN EPILOGUE
    lw ra, 0(sp)
    addi sp, sp, 4
    # END EPILOGUE
    ret

# This helper function adds 1 to the value at the memory address in a0.
# It doesn't return anything.
# C pseudocode for what it does: "*a0 = *a0 + 1"
#
# FIXME This function also violates calling convention, but it might not
# be reported by the Venus CC checker (try and figure out why).
# You should fix the bug anyway by filling in the prologue and epilogue
# as appropriate.
helper_fn:
    # BEGIN PROLOGUE
    # END PROLOGUE
    lw t1, 0(a0)
    addi s0, t1, 1
    sw s0, 0(a0)
    # BEGIN EPILOGUE
    # END EPILOGUE
    ret

# YOU CAN IGNORE EVERYTHING BELOW THIS COMMENT

# Checks the result of inc_arr, which should contain 2 3 4 5 6 after
# one call.
# You can safely ignore this function; it has no errors.
check_arr:
    la t0, exp_inc_array_result
    la t1, array
    addi t2, t1, 20 # Last element is 5*4 bytes off
check_arr_loop:
    beq t1, t2, check_arr_end
    lw t3, 0(t0)
    lw t4, 0(t1)
    bne t3, t4, failure
    addi t0, t0, 4
    addi t1, t1, 4
    j check_arr_loop
check_arr_end:
    ret
    

# This isn't really a function - it just prints a message, then
# terminates the program on failure. Think of it like an exception.
failure:
    li a0, 4 # String print ecall
    la a1, failure_message
    ecall
    li a0, 10 # Exit ecall
    ecall
    
```

### What caused the errors in `simple_fn`, `naive_pow`, and `inc_arr` that were reported by the Venus CC checker?

![image](https://user-images.githubusercontent.com/69206952/213286417-cf66c358-b2f6-4eed-a83f-d7760140d35e.png)


**Ans**:
- `simple_fn` was using the value of the register `t0` without initializing it. Solved by not using `t0` at all, and just putting the immediate 1 in `a0`.
- `naive_pow` did not have a prologue and epilogue. Fixed by adding it.
- `inc_arr` had a prologue and epilogue, but only saved `ra`, it need to save `s0` and `s1`. Solved by saving those registers onto the stack.
- (Need to understand better...) The saving of `t0` apparently made no difference in the result.

### In RISC-V, we call functions by jumping to them and storing the return address in the `ra` register. Does calling convention apply to the jumps to the `naive_pow_loop` or `naive_pow_end labels`?

**Ans**: No, because they aren't functions, just labels/loops. 

### Why do we need to store `ra` in the prologue for `inc_arr`, but not in any other function?

**Ans**: Because `inc_arr` is also a caller to another function, so we need to save `ra` to be able to execute the line after the call.

### Why wasn't the calling convention error in `helper_fn` reported by the CC checker? (**Hint**: it's mentioned above in the exercise instructions.)

**Ans:**

The instructions say:

```
Note: Venus's calling convention checker will not report all calling convention bugs; it is
intended to be used primarily as a basic check. Most importantly, it will only look for
bugs in functions that are exported with the .globl directive - the meaning of .globl is
explained in more detail in the Venus reference.
```

So... it doesn't report the error because the function is not ddeclared with the `.globl` directive.

## Exercise 3

#### Bug 1 - `add t1, s0, x0` -> s0 actually holds the address of the node, so this instruction puts the address of the node in `t1`. In order to put the address of the array, `lw t1, 0(s0)`.

#### Bug 2 - `t1, t1, t0` -> offset the array address by the count (`t0`) is supposed to be `t1 = t1 + 4 * t0`. Using `t3` as `4 * t0`, the line was changed to `slli t3, t0, 2` and `add t1, t1, t3`.

#### Bug 3 - `sw a0, 0(t1)` -> it does the right thing, but the temporary variables might change between function calls, so they need to be saved. To do this, the following lines were changed...

On the epilogue of `map`, `addi sp, sp, -12`: `addi sp, sp, -24`.
On the prologue of `map`, `addi sp, sp, 12`: `addi sp, sp 24`.
Before `jalr s1`, these lines were added:

```s
sw t2, 12(sp)
sw t1, 16(sp)
sw t2, 20(sp)       # SOLVE BUG 3
```

After `jalr s1`, these lines were added:

```s
lw t2, 12(sp)
lw t1, 16(sp)
lw t2, 20(sp)       # SOLVE BUG 3
```

#### Bug 4 - `la a0, 8(s0)` -> the right instruction to 'load the address of the next nodde into a0' is `lw a0, 8(s0)`.

#### Bug 5 - `lw a1, 0(s1)` -> this instruction does not put the address of the function in a1, it puts the first word of the function in it. `mv a1, s1` solves it.

#### Bug 6 - After the epilogue of `done`, the program does not follow the right flow, it needs to go back using `jr ra`. 

## Exercise 4

**Ans**:

- Acc 1 - Prologue is not the first thing of the function... s0 being used before being saved. Also, on the epilogue `t1` is restored to `0(sp)` instead of `s0`.
- Acc 2 - On the prologue, the stack pointer is being incremented and on the epilogue, being decremented, the opposite of what should happen.
- Acc 3 - It is probably right, but the `j Epiloguethree` on `TailCasethree` is not necessary.
- Acc 4 - `t2` is not initialized, but used. The function needs for it to be 0 so the result is right. 
- Acc 5 - The loop condition is never applied to the first element, so it would fail if the array starts with 0.
