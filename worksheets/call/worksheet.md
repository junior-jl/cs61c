# CALL, RISC-V Procedures

## 1. Pre-Check

This section is designed as a conceptual check for you to determine if you conceptually understand and have any misconceptions about this topic. Please answer true/false to the following questions, and include an explanation:

### 1.1. The compiler may output pseudoinstructions.

**Ans**: True. The assembler is responsible for changing the pseudoinstructions for the real ones.

### 1.2. The main job of the assembler is to generate optimized machine code.

**Ans**: False. It is to replace pseudoinstructions.

### 1.3. The object files produced by the assembler are only moved, not edited, by the linker.

**Ans**: False. The linker will fill the blanks on some references.

### 1.4. The destination of all jump instructions is completely determined after linking.

**Ans**: False. Some references from jumps are only known at run-time.

### 2. CALL

The following is a diagram of the CALL stack detailing how C programs are built and executed by machines:

![image](https://user-images.githubusercontent.com/69206952/213331708-17723d0a-6497-456d-84ad-6c1d81834014.png)

### 2.1. What is the Stored Program concept and what does it enable us to do?

**Ans**: The store program concept is the idea that a program can be represented in the same way as data, because the instructions executed by the computer are just bytes, words, etc, just like the data that it stores. So, this allows the computer to execute more programs by just adding them to the memory, giving it the ability to perform different actions and tasks without changing the hardware.

### 2.2. How many passes through the code does the Assembler have to make? Why?

**Ans**: Two. Because in the first one, it needs to keep track of all the labels that can be referenced in the code to avoid the 'forward reference' problem. On the second one converts all instructions and replace pseudoinstructions.

### 2.3. Describe the six main parts of the object files outputted by the Assembler (Header, Text, Data, Relocation Table, Symbol Table, Debugging Information).

**Ans**: 

1. The header contains the metadata of all the other parts.
2. The text is basically the machine code itself.
3. The data is any data (byte, word, etc.) that is declared or used by the program.
4. The relocation table contains the references that will be filled by the linker.
5. The symbol table keeps track of all the labels.
6. Debugging information is some additional information that is only used for these purposes.


### 2.4. Which step in CALL resolves relative addressing? Absolute addressing?

**Ans**: The assembler converts the instructions to machine code, including the relative addresses. The linker will be responsible for combining multiple files into an executable, calculating the absolute addresses. It also updates the machine code to use absolute addresses.

## 3. Assembling RISC-V

Let's say that we have a C program that has a single function `sum` that computes the sum of an array. We've compiled it to RISC-V, but we haven't assembled the RISC-V code yet.

```s
1 .import print.s # print.s is a different file
2 .data
3 array: .word 1 2 3 4 5
4 .text
5 sum: la t0, array
6 li t1, 4
7 mv t2, x0
8 loop: blt t1, x0, end
9 slli t3, t1, 2
10 add t3, t0, t3
11 lw t3, 0(t3)
12 add t2, t2, t3
13 addi t1, t1, -1
14 j loop
15 end: mv a0, t2
16 jal ra, print_int # Defined in print.s
```

### 3.1. Which lines contain pseudoinstruction that need to be converted to regular RISC-V instructions?

**Ans**: 5, 6, 7, 14 and 15.

### 3.2. For the branch/jump instructions, which labels will be resolved in the first pass of the assembler? The second?

**Ans**: On the first pass, the line 14 can be resolved, since it is a reference to a label that has been seen. `blt t1, x0, end` is a forward reference, so it's only resolved in the second pass.

### Let’s assume that the code for this program starts at address `0x00061C00`. The code below is labelled with its address in memory (think: why is there a jump of 8 between the first and second lines?).

```
1 0x00061C00: sum: la t0, array
2 0x00061C08: li t1, 4
3 0x00061C0C: mv t2, x0
4 0x00061C10: loop: blt t1, x0, end
5 0x00061C14: slli t3, t1, 2
6 0x00061C18: add t3, t0, t3
7 0x00061C1C: lw t3, 0(t3)
8 0x00061C20: add t2, t2, t3
9 0x00061C24: addi t1, t1, -1
10 0x00061C28: j loop
11 0x00061C2C: end: mv a0, t2
12 0x00061C30: jal ra, print_int
```

### 3.3. What is in the symbol table after the assembler makes its passes?

**Ans**: So, answering first why is there a jump of 8 between the first and second lines... the `la` pseudoinstruction is actually "made of" two instructions. The symbol table would contain:

- `sum` -> `0x00061C00`
- `loop` -> `0x00061C10`
- `end` -> `0x00061C2C`

### 3.4. What's contained in the relocation table?

**Ans**: `array` lives in the static memory. And `print_int` which will be included in the program by the linker.

## 4. RISC-V Addressing

We have several addressing modes to access memory (immediate not listed):

1. Base displacement addressing adds an immediate to a register value to create a memory address (used for `lw`, `lb`, `sw`, `sb`).
2. PC-relative addressing uses the PC and adds the immediate value of the instruction (multiplied by 2) to create an address (used by branch and jump instructions).
3. Register Addressing uses the value in a register as a memory address. For instance, `jalr`, `jr`, and `ret`, where `jr` and `ret` are just pseudoinstructions that get converted to `jalr`.

### 4.1. What is the range of 32-bit instructions that can be reached from the current PC using a branch instruction?

**Ans**: Only 12 bits are avaliable for the immediate on branch instructions, and we need to be able to go forward and back, so the range is from $PC - 2^{11}$ to $PC + 2^{11} - 1$, but only addresses that are multiples of 2 are valid (for RV32), so we need to divide it by 2. The final range is from $PC - 2^{10}$ to $PC + 2^{10} - 1$.
